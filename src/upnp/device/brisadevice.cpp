/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
  */

#include <QtDebug>
#include <QIODevice>

#include "brisadevice.h"
#include "brisassdpserver.h"


using namespace BrisaUpnp;

/*!
 *  \class BrisaUpnp::BrisaDevice brisadevice.h BrisaUpnp/BrisaDevice
 *  \brief UPnP device implementation
 *
 *  BrisaDevice provides a easy and fast way to create UPnP devices. Simply create a new BrisaDevice
 *  and call start() to join the network and be visible to available control points.
 *
 *  To add a service to the device, just create a new BrisaService with the chosen actions and
 *  events and add it to the device by calling \a addService(). The service will be automatically
 *  added to the device and the appropriate webserver urls paths will be created.
 *
 *  Embedded devices are also supported by BrisaDevice. Create a new BrisaDevice and call
 *  \a addEmbeddedDevice(), the embedded device will be announced when the root device joins the
 *  network.
 *
 *  To stop the device and leave the network, simply call the \a stop() method, ssdp messages will
 *  also be sent for any embedded devices.
 *
 *  \sa BrisaUpnp::BrisaService
 */

/*!
 *  Creates a BrisaDevice with the given parent QObject.
 */
BrisaDevice::BrisaDevice(QObject *parent) :
    QObject(parent),
    running(false)
{
    webserver = new BrisaWebserver(QHostAddress(ipAddress), port);
    ssdp = new BrisaSSDPServer();

    QObject::connect(ssdp, SIGNAL(msearchRequestReceived(QString, QString, quint16)),
                     this, SLOT(respondMSearch(QString, QString, quint16)));
}

/*!
 *  Creates a BrisaDevice with the given device information.
 */
BrisaDevice::BrisaDevice(const QString &deviceType, QString friendlyName,
                         const QString &manufacturer, const QString &manufacturerURL,
                         const QString &modelDescription, const QString &modelName,
                         const QString &modelNumber, const QString &modelURL,
                         const QString &serialNumber, const QString &UDN,
                         const QString &UPC, const QString &presentationURL, QObject *parent) :
    QObject(parent),

    deviceType(deviceType),
    friendlyName(friendlyName),
    manufacturer(manufacturer),
    manufacturerUrl(manufacturerURL),
    modelDescription(modelDescription),
    modelName(modelName),
    modelNumber(modelNumber),
    modelUrl(modelURL),
    serialNumber(serialNumber),
    udn(UDN),
    upc(UPC),
    presentationUrl(presentationURL),
    server("BRisa Webserver UPnP/1.0 " + modelName + " " + modelNumber),
    fileAddress(friendlyName.remove(QChar(' ')).append(".xml")),
    running(false)
{
    this->buildUrlBase();
    this->location = urlBase + "/" + fileAddress;

    this->major = "1";
    this->minor = "0";

    webserver = new BrisaWebserver(QHostAddress(ipAddress), port);
    ssdp = new BrisaSSDPServer();

    QObject::connect(ssdp, SIGNAL(msearchRequestReceived(QString, QString, quint16)),
                     this, SLOT(respondMSearch(QString, QString, quint16)));
}

/*!
 *  Copy constructor.
 */
BrisaDevice::BrisaDevice(const BrisaDevice &dev) :
    QObject(dev.parent()),

    iconList(dev.getIconList()),
    serviceList(dev.getServiceList()),
    embeddedDeviceList(dev.getEmbeddedDeviceList()),
    urlBase(dev.getAttribute(BrisaDevice::UrlBase)),
    deviceType(dev.getAttribute(BrisaDevice::DeviceType)),
    friendlyName(dev.getAttribute(BrisaDevice::FriendlyName)),
    manufacturer(dev.getAttribute(BrisaDevice::Manufacturer)),
    manufacturerUrl(dev.getAttribute(BrisaDevice::ManufacturerUrl)),
    modelDescription(dev.getAttribute(BrisaDevice::ModelDescription)),
    modelName(dev.getAttribute(BrisaDevice::ModelName)),
    modelNumber(dev.getAttribute(BrisaDevice::ModelNumber)),
    modelUrl(dev.getAttribute(BrisaDevice::ModelUrl)),
    serialNumber(dev.getAttribute(BrisaDevice::SerialNumber)),
    udn(dev.getAttribute(BrisaDevice::Udn)),
    upc(dev.getAttribute(BrisaDevice::Upc)),
    presentationUrl(dev.getAttribute(BrisaDevice::PresentationUrl)),

    location(dev.getAttribute(BrisaDevice::Location)),
    server(dev.getAttribute(BrisaDevice::Server)),
    ipAddress(dev.getAttribute(BrisaDevice::IpAddress)),
    port(dev.getAttribute(BrisaDevice::Port).toInt()),

    fileAddress(dev.getAttribute(BrisaDevice::FileAddress)),
    running(dev.running)
{
    this->major = dev.getAttribute(BrisaDevice::Major);
    this->minor = dev.getAttribute(BrisaDevice::Minor);

    webserver = new BrisaWebserver(QHostAddress(ipAddress), port);
    ssdp = new BrisaSSDPServer();
}

/*!
 *  Destructor for BrisaDevice.
 *
 *  Stops the device if running.
 */
BrisaDevice::~BrisaDevice()
{
    if (isRunning())
        stop();

    while (!serviceList.empty())
        delete serviceList.takeFirst();

    while (!embeddedDeviceList.empty())
        delete embeddedDeviceList.takeFirst();

    delete ssdp;
    delete webserver;
}

/*!
 *  Creates a temporary XML file containning the device information.
 *
 *  \sa deviceGenerator()
 */
void BrisaDevice::xmlGenerator()
{
    BrisaDeviceXMLHandler handler;
    handler.xmlGenerator(this, &descriptionFile);
}


/*!
 *  Assigns dev to this BrisaDevice and returns a copy.
 */
BrisaDevice &BrisaDevice::operator=(const BrisaDevice &dev)
{
    this->iconList = dev.getIconList();
    this->serviceList= dev.getServiceList();
    this->embeddedDeviceList = dev.getEmbeddedDeviceList();

    this->major = dev.getAttribute(BrisaDevice::Major);
    this->minor = dev.getAttribute(BrisaDevice::Minor);
    this->urlBase = dev.getAttribute(BrisaDevice::UrlBase);
    this->deviceType = dev.getAttribute(BrisaDevice::DeviceType);
    this->friendlyName = dev.getAttribute(BrisaDevice::FriendlyName);
    this->manufacturer = dev.getAttribute(BrisaDevice::Manufacturer);
    this->manufacturerUrl = dev.getAttribute(BrisaDevice::ManufacturerUrl);
    this->modelDescription = dev.getAttribute(BrisaDevice::ModelDescription);
    this->modelName = dev.getAttribute(BrisaDevice::ModelName);
    this->modelNumber = dev.getAttribute(BrisaDevice::ModelNumber);
    this->modelUrl = dev.getAttribute(BrisaDevice::ModelUrl);
    this->serialNumber = dev.getAttribute(BrisaDevice::SerialNumber);
    this->udn = dev.getAttribute(BrisaDevice::Udn);
    this->upc = dev.getAttribute(BrisaDevice::Upc);
    this->presentationUrl = dev.getAttribute(BrisaDevice::PresentationUrl);

    this->location = dev.getAttribute(BrisaDevice::Location);
    this->server = dev.getAttribute(BrisaDevice::Server);
    this->ipAddress = dev.getAttribute(BrisaDevice::IpAddress);
    this->port = dev.getAttribute(BrisaDevice::Port).toInt();

    this->fileAddress = dev.getAttribute(BrisaDevice::FileAddress);
    this->running = dev.running;

    return *this;
}

/*!
 *  Attribute setter.
 *
 *  \sa getAttribute()
 */
void BrisaDevice::setAttribute(xmlTags key, const QString &v)
{
    switch(key)
    {
        case Major:
            this->major = v;
            break;
        case Minor:
            this->minor = v;
            break;
        case UrlBase:
            this->urlBase = v;
            break;
        case DeviceType:
            this->deviceType = v;
            break;
        case FriendlyName:
            this->friendlyName = v;
            this->fileAddress = this->friendlyName.remove(QChar(' '));
            this->fileAddress.append(".xml");
            break;
        case Manufacturer:
            this->manufacturer = v;
            break;
        case ManufacturerUrl:
            this->manufacturerUrl = v;
            break;
        case ModelDescription:
            this->modelDescription = v;
            break;
        case ModelName:
            this->modelName = v;
            break;
        case ModelNumber:
            this->modelNumber = v;
            break;
        case ModelUrl:
            this->modelUrl = v;
            break;
        case SerialNumber:
            this->serialNumber = v;
            break;
        case Udn:
            this->udn = v;
            break;
        case Upc:
            this->upc = v;
            break;
        case PresentationUrl:
            this->presentationUrl = v;
            break;
        case FileAddress:
            this->fileAddress = v;
            break;
        case Location:
            this->location = v;
            break;
        case Server:
            this->server = v;
            break;
        case IpAddress:
            this->ipAddress = v;
            break;
        case Port:
            this->port = v.toInt();
            break;
        case Running:
            this->running = !this->running;
            break;
    }
}

/*!
 *  Attribute getter.
 *
 *  \sa setAttribute()
 */
QString BrisaDevice::getAttribute(xmlTags key) const
{
    switch(key)
    {
        case Major:
            return major;
            break;
        case Minor:
            return minor;
            break;
        case UrlBase:
            return urlBase;
            break;
        case DeviceType:
            return deviceType;
            break;
        case FriendlyName:
            return friendlyName;
            break;
        case Manufacturer:
            return manufacturer;
            break;
        case ManufacturerUrl:
            return manufacturerUrl;
            break;
        case ModelDescription:
            return modelDescription;
            break;
        case ModelName:
            return modelName;
            break;
        case ModelNumber:
            return modelNumber;
            break;
        case ModelUrl:
            return modelUrl;
            break;
        case SerialNumber:
            return serialNumber;
            break;
        case Udn:
            return udn;
            break;
        case Upc:
            return upc;
            break;
        case PresentationUrl:
            return presentationUrl;
            break;
        case FileAddress:
            return fileAddress;
            break;
        case Location:
            return location;
            break;
        case Server:
            return server;
            break;
        case IpAddress:
            return ipAddress;
            break;
        case Port:
            return QString(port);
            break;
        case Running:
            return (this->running) ? "TRUE" : "FALSE";
            break;
        default:
            return "";
            break;
    }
}

/*!
 *  Call this method to add a icon to the device.
 */
void BrisaDevice::addIcon(const QString &mimetype, const QString &width, const QString &height,
                          const QString &depth, const QString &url)
{
    BrisaIcon iconSwap(mimetype, width, height, depth, url);
    iconList.append(iconSwap);
}

/*!
 *  Creates and adds a service to the device with the given information.
 */
void BrisaDevice::addService(const QString &serviceType, const QString &serviceId,
                             const QString &SCPDURL, const QString &controlURL,
                             const QString &eventSubURL)
{
    BrisaService *serviceSwap = new BrisaService(serviceType, serviceId, SCPDURL, controlURL,
                                                 eventSubURL, this->urlBase);
    serviceList.append(serviceSwap);
}

/*!
 *  Overloads addService().
 *
 *  Create a \a BrisaService and add it to the device. We recommend using this method for better
 *  object orientation.
 *
 *  \sa BrisaUpnp::BrisaService
 */
void BrisaDevice::addService(BrisaService *servdev)
{
    serviceList.append(servdev);
}

/*!
 *  Creates and adds a embedded device with the given information to the device.
 */
void BrisaDevice::addEmbeddedDevice(const QString &deviceType, const QString &friendlyName,
                                    const QString &manufacturer, const QString &manufacturerURL,
                                    const QString &modelDescription, const QString &modelName,
                                    const QString &modelNumber, const QString &modelURL,
                                    const QString &serialNumber, const QString &UDN,
                                    const QString &UPC, const QString &presentationURL)
{
    BrisaDevice *deviceSwap = new BrisaDevice(deviceType, friendlyName, manufacturer, manufacturerURL,
                                              modelDescription, modelName, modelNumber, modelURL,
                                              serialNumber, UDN, UPC, presentationURL);
    embeddedDeviceList.append(deviceSwap);
}

/*!
 *  Overloads addEmbeddedDevice()
 *
 *  Create a new \a BrisaDevice and call this method to add it as a embedded device to a root
 *  device. We recommend using this method for better object orientation.
 */
void BrisaDevice::addEmbeddedDevice(BrisaDevice *newEmbeddedDevice)
{
    embeddedDeviceList.append(newEmbeddedDevice);
}

/*!
 *  Getter for BrisaService in the service list.
 */
BrisaService *BrisaDevice::getServiceById(const QString &serviceId)
{
    foreach (BrisaService *s, this->serviceList) {
        if(s->getAttribute(BrisaService::ServiceId) == serviceId)
            return s;
    }

    return 0;
}

/*!
 *  Getter for BrisaService in the service list.
 */
BrisaService *BrisaDevice::getServiceByType(const QString &serviceType)
{
    foreach (BrisaService *s, this->serviceList) {
        if(s->getAttribute(BrisaService::ServiceType) == serviceType)
            return s;
    }

    return 0;
}

/*!
 *  Call this method to join the network and start the device.
 *
 *  \sa stop()
 */
void BrisaDevice::start()
{
    if (isRunning()) {
        qDebug() << "BrisaDevice already running!";
        return;
    }

    xmlGenerator();
    startWebServer();
    ssdp->start();
    doNotify();
    running = true;
}

/*!
 *  Stops the device and leaves the network.
 *
 *  \sa start()
 */
void BrisaDevice::stop()
{
    if (!isRunning()) {
        qDebug() << "BrisaDevice already stopped!";
        return;
    }

    doByeBye();
    ssdp->stop();
    running = false;
}

/*!
 *  Starts the webserver.
 */
void BrisaDevice::startWebServer()
{
    buildWebServerTree();
    this->webserver->start();
}

/*!
 *  Generates the webserver tree according to the services present in the device.
 *  Eg:
 *     Suppose we have two services, "Gate" and "LightSwitch". So /Gate and /LightSwitch will be
 *  valid URLs in the webserver.
 */
void BrisaDevice::buildWebServerTree()
{
    // open the file to get its name
    this->descriptionFile.open();
    this->webserver->publishFile(this->fileAddress, this->descriptionFile.fileName());
    this->descriptionFile.close();

    foreach (BrisaService *service, serviceList){
        service->buildWebServiceTree(webserver);
        webserver->addService(service->getAttribute(BrisaService::ServiceId),
                              service->getWebService());
    }
}

/*!
 *  Slot connected to the msearchRequestReceived() signal comming from the ssdp module. It parses
 *  the search type and responds accordingly.
 *
 *  \sa respondMSearchAll()
 */
void BrisaDevice::respondMSearch(const QString &st, const QString &senderIp, quint16 senderPort)
{
    QString sDate = QDate::currentDate().toString("dd/MM/yyyy");

    if (st == "ssdp:all") {
        respondMSearchAll(senderIp,senderPort,sDate);
    } else if (st == "upnp:rootdevice") {
        ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server,
                             "upnp:rootdevice", udn + "::upnp:rootdevice");
    } else if (st.contains("uuid:")) {

        QString embeddedUdn;
        QString embeddedType;

        if (st == udn)
            ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server,
                                 "upnp:rootdevice",udn + "::upnp:rootdevice");

        for (int k = 0; k < embeddedDeviceList.size(); k++) {
            embeddedUdn = embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
            embeddedType = embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
            if (st == embeddedUdn)
                ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server,
                                     embeddedUdn, embeddedUdn);
        }
    } else if (st.contains(":device:")) {

        QString embeddedUdn;
        QString embeddedType;

        if (st == deviceType)
            ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server,
                                 "upnp:rootdevice",udn + "::upnp:rootdevice");

        for (int k = 0; k < embeddedDeviceList.size(); k++) {
            embeddedUdn = embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
            embeddedType = embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
            if (st == embeddedType)
                ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server,
                                     embeddedUdn, embeddedUdn);
        }
    } else if (st.contains(":service:")) {

        QString serviceType;
        QString serviceUdn;

        for (int j = 0; j < serviceList.size(); j++) {
            serviceType = serviceList[j]->getAttribute(BrisaService::ServiceType);
            serviceUdn = udn + "::" + serviceType;
            if (st == serviceType)
                ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, serviceUdn,
                                 serviceType);
        }
    }
}


/*!
 *  Responds the msearch in case of a "ssdp:all" search type.
 *
 *  \sa respondMSearch()
 */
void BrisaDevice::respondMSearchAll(const QString &senderIp, quint16 senderPort, const QString &sDate)
{
    QString serviceType;
    QString serviceUdn;
    QString embeddedUdn;
    QString embeddedType;

    //MSearch response for root device
    ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, "upnp:rootdevice",
                         udn + "::upnp:rootdevice");
    ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, udn, udn);
    ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, udn + "::"
                         + deviceType, deviceType);

    //MSearch response for embedded devices
    for (int k = 0; k < embeddedDeviceList.size(); k++) {
        embeddedUdn = embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
        embeddedType = embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
        ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, embeddedUdn,
                             embeddedUdn);
        ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, embeddedUdn
                             + "::" + embeddedType,embeddedType);
    }

    //MSearch response for services
    for (int j = 0; j < serviceList.size(); j++) {
        serviceType = serviceList[j]->getAttribute(BrisaService::ServiceType);
        serviceUdn = udn + "::" + serviceType;
        ssdp->respondMSearch(senderIp, senderPort, "1800", sDate, location, server, serviceUdn,
                             serviceType);
    }
}

/*!
 *  Returns the icon list.
 *
 *  \sa getEmbeddedDeviceList() , getServiceList()
 */
QList<BrisaIcon> BrisaDevice::getIconList() const
{
    return this->iconList;
}

/*!
 *  Returns the embedded device list.
 *
 *  \sa getIconList() , getServiceList()
 */
QList<BrisaDevice*> BrisaDevice::getEmbeddedDeviceList() const
{
    return this->embeddedDeviceList;
}

/*!
 *  Returns the service list.
 *
 *  \sa getEmbeddedDeviceList() , getIconList()
 */
QList<BrisaService*> BrisaDevice::getServiceList() const
{
    return this->serviceList;
}

/*!
 *  Sends the ssdp:byebye messages for root device, embedded devices and services according to the
 *  UPnP 1.0 especification.
 */
void BrisaDevice::doByeBye()
{
    QString serviceType;
    QString serviceUdn;
    QString embeddedUdn;
    QString embeddedType;

    //Notify for root device
    ssdp->doByeBye(udn + "::upnp:rootdevice", "upnp:rootdevice");
    ssdp->doByeBye(udn, udn);
    ssdp->doByeBye(udn + "::" + deviceType, deviceType);

    //TODO: Use foreach.
    //Notify for embedded devices
    for (int k = 0; k < embeddedDeviceList.size(); k++) {
        embeddedUdn = embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
        embeddedType = embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
        ssdp->doByeBye(embeddedUdn, embeddedUdn);
        ssdp->doByeBye(embeddedUdn + "::" + embeddedType,embeddedType);
    }

    //Notify for services
    for (int j = 0; j < serviceList.size(); j++) {
        serviceType = serviceList[j]->getAttribute(BrisaService::ServiceType);
        serviceUdn = udn + "::" + serviceType;
        ssdp->doByeBye(serviceUdn, serviceType);
    }
}

/*!
 *  Sends the ssdp:alive messages for root device, embedded devices and services according to the
 *  UPnP 1.0 especification.
 */
void BrisaDevice::doNotify()
{
    QString serviceType;
    QString serviceUdn;
    QString embeddedUdn;
    QString embeddedType;

    //Notify for root device
    ssdp->doNotify(udn+"::upnp:rootdevice",location,"upnp:rootdevice",server,"1800");
    ssdp->doNotify(udn,location,udn,server,"1800");
    ssdp->doNotify(udn+"::"+deviceType,location,deviceType,server,"1800");

    //Notify for embedded devices
    for (int k = 0 ; k < embeddedDeviceList.size() ; k++)
    {
        embeddedUdn = embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
        embeddedType = embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
        ssdp->doNotify(embeddedUdn,location,embeddedUdn,server,"1800");
        ssdp->doNotify(embeddedUdn+"::"+embeddedType,location,embeddedType,server,"1800");
    }

    //Notify for services
    for (int j =0 ; j < serviceList.size() ; j++) {
         serviceType = serviceList[j]->getAttribute(BrisaService::ServiceType);
         serviceUdn = udn+"::"+serviceType;
         ssdp->doNotify(serviceUdn,location,serviceType,server,"1800");
     }
}

/*!
 *  Returns true if the device is running.
 */
bool BrisaDevice::isRunning()
{
    return running;
}

/*!
 *  Clears the device information, including services, icons and embedded devices.
 */
void BrisaDevice::clear()
{
    iconList.clear();
    serviceList.clear();
    embeddedDeviceList.clear();;

    this->major.clear();
    this->minor.clear();
    this->urlBase.clear();
    this->deviceType.clear();
    this->friendlyName.clear();
    this->manufacturer.clear();
    this->manufacturerUrl.clear();
    this->modelDescription.clear();
    this->modelName.clear();
    this->modelNumber.clear();
    this->modelUrl.clear();
    this->serialNumber.clear();
    this->udn.clear();
    this->upc.clear();
    this->presentationUrl.clear();

    this->location.clear();
    this->server.clear();
    this->ipAddress.clear();

    this->attribute.clear();
    this->fileAddress.clear();

    port = 0;
}

/*!
 *  Creates the UrlBase attribute according to local IP address and a random port.
 */
void BrisaDevice::buildUrlBase()
{
    this->port = getPort();
    this->ipAddress = getIp("eth0");

    if (this->ipAddress == "")
        this->ipAddress = getIp("wlan0");

    this->urlBase = "http://"+ipAddress+":"+QString::number(this->port);
}

