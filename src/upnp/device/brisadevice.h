/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisadevice.cpp
 * Created:
 * Description: Defines the BrisaDevice class.
 * Authors: Name <email> @since 2009
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
 *
 * BRisa-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _BRISADEVICE_H
#define _BRISADEVICE_H

#include <QXmlDefaultHandler>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QtDebug>

#include "brisanetwork.h"
#include "brisadevicexmlhandler.h"
#include "brisaservice.h"
#include "brisaicon.h"
#include "brisaglobal.h"

namespace Brisa {

    class BrisaWebserver;

class BrisaSSDPServer;

/*!
 *  \class Brisa::BrisaDevice brisadevice.h BrisaUpnp/BrisaDevice
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
 *  \sa Brisa::BrisaService
 */
class BRISA_UPNP_EXPORT BrisaDevice: public QObject {
Q_OBJECT

public:
    /*!
     *  Creates a BrisaDevice with the given parent QObject.
     */
    BrisaDevice(QObject *parent = 0);

    /*!
     *  Copy constructor.
     */
    BrisaDevice(const BrisaDevice &dev);

    /*!
     *  Creates a BrisaDevice with the given device information.
     */
    BrisaDevice(const QString &deviceType, const QString &friendlyName = "",
            const QString &manufacturer = "", const QString &manufacturerURL = "",
	    const QString &modelDescription = "", const QString &modelName = "",
	    const QString &modelNumber = "", const QString &modelURL = "",
	    const QString &serialNumber = "", const QString &UDN = "",
	    const QString &UPC = "", const QString &presentationURL = "",
	    QObject *parent = 0);

    /*!
     *  Destructor for BrisaDevice.
     *  Stops the device if running.
     */
    virtual ~BrisaDevice();

    /*!
     *  Assigns dev to this BrisaDevice and returns a copy.
     */
    BrisaDevice &operator=(const BrisaDevice &dev);

    typedef enum {
        Major,
        Minor,
        UrlBase,
        DeviceType,
        FriendlyName,
        Manufacturer,
        ManufacturerUrl,
        ModelDescription,
        ModelName,
        ModelNumber,
        ModelUrl,
        SerialNumber,
        Udn,
        Upc,
        PresentationUrl,
        FileAddress,
        Location,
        Server,
        IpAddress,
        Port,
        Running
    } xmlTags;

    /*!
     *  Attribute setter.
     *  \sa getAttribute()
     */
    void setAttribute(xmlTags key, const QString &value);

    /*!
     *  Attribute getter.
     *  \sa setAttribute()
     */
    QString getAttribute(xmlTags key) const;

    /*!
     *  Call this method to add a icon to the device.
     */
    void addIcon(const QString &mimetype = "", const QString &width = "",
            const QString &height = "", const QString &depth = "",
            const QString &url = "");

    /*!
     *  Creates and adds a service to the device with the given information.
     */
    void addService(const QString &serviceType = "", const QString &serviceId =
            "", const QString &SCPDURL = "", const QString &controlURL = "",
            const QString &eventSubURL = "");

    /*!
     *  Overloads addService().
     *  Create a \a BrisaService and add it to the device. We recommend using this method for better
     *  object orientation.
     *  \sa Brisa::BrisaService
     */
    void addService(BrisaService *serv);

    /*!
     *  Creates and adds a embedded device with the given information to the device.
     */
    void addEmbeddedDevice(const QString &deviceType = "",
            const QString &friendlyName = "", const QString &manufacturer = "",
            const QString &manufacturerURL = "",
            const QString &modelDescription = "",
            const QString &modelName = "", const QString &modelNumber = "",
            const QString &modelURL = "", const QString &serialNumber = "",
            const QString &UDN = "", const QString &UPC = "",
            const QString &presentationURL = "");

    /*!
     *  Overloads addEmbeddedDevice()
     *  Create a new \a BrisaDevice and call this method to add it as a embedded device to a root
     *  device. We recommend using this method for better object orientation.
     */
    void addEmbeddedDevice(BrisaDevice *newEmbeddedDevice);

    /*!
     *  Returns the icon list.
     *
     *  \sa getEmbeddedDeviceList() , getServiceList()
     */
    QList<BrisaIcon *> getIconList() const;

    /*!
     *  Returns the service list.
     *
     *  \sa getEmbeddedDeviceList() , getIconList()
     */
    QList<BrisaService *> getServiceList() const;

    /*!
     *  Returns the embedded device list.
     *
     *  \sa getIconList() , getServiceList()
     */
    QList<BrisaDevice *> getEmbeddedDeviceList() const;

    /*!
     *  Getter for BrisaService in the service list.
     */
    BrisaService *getServiceById(const QString &serviceId);

    /*!
     *  Getter for BrisaService in the service list.
     */
    BrisaService *getServiceByType(const QString &serviceType);

    /*!
     *  Clears the device information, including services, icons and embedded devices.
     */
    void clear();

    /*!
     *  Sends the ssdp:alive messages for root device, embedded devices and services according to the
     *  UPnP 1.0 especification.
     */
    void doNotify();

    /*!
     *  Sends the ssdp:byebye messages for root device, embedded devices and services according to the
     *  UPnP 1.0 especification.
     */
    void doByeBye();

    /*!
     *  Call this method to join the network and start the device.
     *
     *  \sa stop()
     */
    void start();

    /*!
     *  Stops the device and leaves the network.
     *
     *  \sa start()
     */
    void stop();

    int threadsNumber() const;
    void setThreadsNumber(int);

    QByteArray addWebservice(QByteArray pathSuffix, BrisaWebService *service);
    void removeWebservice(const QByteArray &path);

public slots:
    /*!
     *  Connects to the msearchRequestReceived() signal comming from the ssdp module. It parses
     *  the search type and responds accordingly.
     *
     *  \sa respondMSearchAll()
     */
    void respondMSearch(const QString &st, const QString &senderIp,
            quint16 senderPort);

private:
    /*!
     *  Creates a temporary XML file containning the device information.
     *  \sa deviceGenerator()
     */
    void xmlGenerator();

    /*!
     *  Creates the UrlBase attribute according to local IP address and a random port.
     */
    void buildUrlBase();

    /*!
     *  Private function to discover the network address currently used by the machine where control
     *  point is running and select an free port to use with BrisaWebServer.
     */
    void discoverNetworkAddress();

    /*!
     *  Generates the webserver tree according to the services present in the device.
     *  Eg:
     *     Suppose we have two services, "Gate" and "LightSwitch". So /Gate and /LightSwitch will be
     *  valid URLs in the webserver.
     */
    void buildWebServerTree();

    /*!
     *  Starts the webserver.
     */
    void startWebServer();

    /*!
     *  Responds the msearch in case of a "ssdp:all" search type.
     *
     *  \sa respondMSearch()
     */
    void respondMSearchAll(const QString &senderIp, quint16 senderPort,
            const QString &sDate);

    /*!
     *  Returns true if the device is running.
     */
    bool isRunning();

    QList<BrisaIcon*> iconList;
    QList<BrisaService *> serviceList;
    QList<BrisaDevice *> embeddedDeviceList;

    QString major;
    QString minor;
    QString urlBase;
    QString deviceType;
    QString friendlyName;
    QString manufacturer;
    QString manufacturerUrl;
    QString modelDescription;
    QString modelName;
    QString modelNumber;
    QString modelUrl;
    QString serialNumber;
    QString udn;
    QString upc;
    QString presentationUrl;

    QString location;
    QString server;
    QString ipAddress;
    quint16 port;

    QString attribute;
    QString fileAddress;

    QTemporaryFile descriptionFile;

    BrisaSSDPServer *ssdp;
    BrisaWebserver *webserver;
    bool running;
};

}

#endif /* _BRISADEVICE_H */

