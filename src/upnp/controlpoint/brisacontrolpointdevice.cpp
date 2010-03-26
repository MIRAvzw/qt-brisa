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

#include "brisacontrolpointdevice.h"

using namespace BrisaUpnp;

/*!
 *    \class BrisaUpnp::BrisaControlPointDevice brisacontrolpointdevice.h BrisaUpnp/BrisaControlPointDevice
 *
 *    \brief Class that implements the devices that control point part is going to handle.
 */

/*!
 *    \enum BrisaUpnp::BrisaControlPointDevice::xmlTags
 *
 *    \brief This enum specifies the devices attributes that are going to be set/get
 *
 *    \param Major  Major version of the UPnP Device Architecture.
 *
 *    \param Minor  Minor version of the UPnP Device Architecture.
 *
 *    \param UrlBase  Defines the base URL. Used to construct fully-qualified URLs.
 *
 *    \param DeviceType  UPnP device type. Single URI.
 *
 *    \param FriendlyName  Short description for end user.
 *
 *    \param Manufacturer  Manufacturer's name.
 *
 *    \param ManufacturerUrl  Web site for Manufacturer.
 *
 *    \param ModelDescription  Long description for end user.
 *
 *    \param ModelName  Model name. Should be less then 32 characters.
 *
 *    \param ModelNumber  Model number. Should be less then 32 characters.
 *
 *    \param ModelUrl  Web site for model.
 *
 *    \param SerialNumber  Serial number. Should be less then 64 characters
 *
 *    \param Udn  Unique Device Name. Universally-unique identifier for the device.
 *
 *    \param Upc  Universal Product Code. 12-digit, all-numeric code that identifies the consumer package.
 *
 *    \param PresentationUrl  URL to presentation for device.
 *
 *    \param FileAddress  Device's file address.
 *
 *    \sa setAttribute(xmlTags key, QString v), getAttribute(xmlTags key)
 */

/*!
 *    \property iconList
 *
 *    \brief Device's icon list.
 */

/*!
 *    \property serviceList
 *
 *    \brief Device's service list.
 */

/*!
 *    \property embeddedDeviceList
 *
 *    \brief Device's embedded device list.
 */

/*!
 *    Constructor to BrisaControlPointDevice, when it makes use of this constructor the device's
 *    attributes should be set.
 */
BrisaControlPointDevice::BrisaControlPointDevice(QObject *parent) : QObject(parent)
{
}

/*!
 *    Constructor for BrisaControlPointDevice that receives a xml file containing the device
 *    description, so that the device's attributes can be initialized.
 */
BrisaControlPointDevice::BrisaControlPointDevice(QTemporaryFile *xml, QUrl *url, QObject *parent) : QObject(parent)
{
    this->setAttribute(BrisaControlPointDevice::UrlBase, url->toString(QUrl::RemovePath));
    BrisaDeviceXMLHandlerCP *handler = new BrisaDeviceXMLHandlerCP();
    handler->parseDevice(this, xml);
    delete handler;
}

/*!
 *    Constructor where all device's attributes are passed as parameter.
 */
BrisaControlPointDevice::BrisaControlPointDevice(QString deviceType, QString friendlyName, QString manufacturer,
                             QString manufacturerURL, QString modelDescription, QString modelName,
                             QString modelNumber, QString modelURL, QString serialNumber,
                             QString UDN, QString UPC, QString presentationURL, QObject *parent)
                             : QObject(parent)
{
    this->major = "1";
    this->minor = "0";
    this->deviceType = deviceType;
    this->friendlyName = friendlyName;
    this->manufacturer = manufacturer;
    this->manufacturerUrl = manufacturerURL;
    this->modelDescription = modelDescription;
    this->modelName = modelName;
    this->modelNumber = modelNumber;
    this->modelUrl = modelURL;
    this->serialNumber = serialNumber;
    this->udn = UDN;
    this->upc = UPC;
    this->presentationUrl = presentationURL;
    this->fileAddress = friendlyName.remove(QChar(' '));
    this->fileAddress.append(".xml");
}

/*!
 *    Constructor for BrisaControlPointDevice that receives another object of the same type and
 *    copy it's attributes.
 */
BrisaControlPointDevice::BrisaControlPointDevice(BrisaControlPointDevice &dev, QObject *parent) : QObject(parent)
{
    this->iconList = dev.getIconList();
    this->serviceList= dev.getServiceList();
    this->embeddedDeviceList = dev.getEmbeddedDeviceList();

    this->major = dev.getAttribute(BrisaControlPointDevice::Major);
    this->minor = dev.getAttribute(BrisaControlPointDevice::Minor);
    this->urlBase = dev.getAttribute(BrisaControlPointDevice::UrlBase);
    this->deviceType = dev.getAttribute(BrisaControlPointDevice::DeviceType);
    this->friendlyName = dev.getAttribute(BrisaControlPointDevice::FriendlyName);
    this->manufacturer = dev.getAttribute(BrisaControlPointDevice::Manufacturer);
    this->manufacturerUrl = dev.getAttribute(BrisaControlPointDevice::ManufacturerUrl);
    this->modelDescription = dev.getAttribute(BrisaControlPointDevice::ModelDescription);
    this->modelName = dev.getAttribute(BrisaControlPointDevice::ModelName);
    this->modelNumber = dev.getAttribute(BrisaControlPointDevice::ModelNumber);
    this->modelUrl = dev.getAttribute(BrisaControlPointDevice::ModelUrl);
    this->serialNumber = dev.getAttribute(BrisaControlPointDevice::SerialNumber);
    this->udn = dev.getAttribute(BrisaControlPointDevice::Udn);
    this->upc = dev.getAttribute(BrisaControlPointDevice::Upc);
    this->presentationUrl = dev.getAttribute(BrisaControlPointDevice::PresentationUrl);

    this->fileAddress = dev.getAttribute(BrisaControlPointDevice::FileAddress);
}

/*!
 *    Destructor
 */
BrisaControlPointDevice::~BrisaControlPointDevice()
{
}

/*!
 *    Set a device's attribute, depending on the \a key that is passed as parameter, so that,
 *    the attribute e set to value \a v
 */
void BrisaControlPointDevice::setAttribute(xmlTags key, QString v)
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
    }
}

/*!
 *    Gets the \a key attribute.
 */
QString BrisaControlPointDevice::getAttribute(xmlTags key)
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
        default:
            return "";
            break;
    }
}

/*!
 *    Check the device's service list and return the service that has the passed \serviceId.
 */
BrisaControlPointService *BrisaControlPointDevice::getServiceById(QString serviceId)
{
    for(int i = 0; i < this->serviceList.size(); i++)
    {
        if(this->serviceList.at(i)->getAttribute(BrisaControlPointService::ServiceId).compare(serviceId) == 0)
        {
            return serviceList.at(i);
        }
    }
    return NULL;
}

/*!
 *    Check the device's service list and return the service that has the passed \serviceType.
 */

BrisaControlPointService *BrisaControlPointDevice::getServiceByType(QString serviceType)
{
    for(int i = 0; i < this->serviceList.size(); i++)
    {
        if(this->serviceList.at(i)->getAttribute(BrisaControlPointService::ServiceType).compare(serviceType) == 0)
        {
            return serviceList.at(i);
        }
    }
    return NULL;
}

/*!
 *    Returns device's icon list.
 */
QList<BrisaIcon*> BrisaControlPointDevice::getIconList()
{
    return this->iconList;
}

/*!
 *    Returns device's service list.
 */
QList<BrisaControlPointService*> &BrisaControlPointDevice::getServiceList()
{
    return this->serviceList;
}

/*!
 *    Returns device's embedded device list.
 */
QList<BrisaControlPointDevice*> BrisaControlPointDevice::getEmbeddedDeviceList()
{
    return this->embeddedDeviceList;
}

/*!
 *    Add \a icon to device's icon list.
 */
void BrisaControlPointDevice::addIcon(BrisaIcon *icon)
{
    iconList.append(icon);
}

/*!
 *    Add \a serviceSwap to device's service list.
 */
void BrisaControlPointDevice::addService(BrisaControlPointService *serviceSwap)
{
    serviceList.append(serviceSwap);
}

/*!
 *    Add \a device to device's embedded device list.
 */
void BrisaControlPointDevice::addDevice(BrisaControlPointDevice *device)
{
    embeddedDeviceList.append(device);
}

/*!
 *    Clear device's attributes.
 */
void BrisaControlPointDevice::clear()
{
    this->iconList.clear();
    this->serviceList.clear();
    this->embeddedDeviceList.clear();

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

    this->fileAddress.clear();
}

