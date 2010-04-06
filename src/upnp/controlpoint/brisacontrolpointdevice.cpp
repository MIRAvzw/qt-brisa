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

BrisaControlPointDevice::BrisaControlPointDevice(QObject *parent) : QObject(parent)
{
}

BrisaControlPointDevice::BrisaControlPointDevice(QTemporaryFile *xml, QUrl *url, QObject *parent) : QObject(parent)
{
    this->setAttribute(BrisaControlPointDevice::UrlBase, url->toString(QUrl::RemovePath));
    BrisaDeviceXMLHandlerCP *handler = new BrisaDeviceXMLHandlerCP();
    handler->parseDevice(this, xml);
    delete handler;
}

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

BrisaControlPointDevice::~BrisaControlPointDevice()
{
}

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

QList<BrisaIcon*> BrisaControlPointDevice::getIconList()
{
    return this->iconList;
}

QList<BrisaControlPointService*> &BrisaControlPointDevice::getServiceList()
{
    return this->serviceList;
}

QList<BrisaControlPointDevice*> BrisaControlPointDevice::getEmbeddedDeviceList()
{
    return this->embeddedDeviceList;
}

void BrisaControlPointDevice::addIcon(BrisaIcon *icon)
{
    iconList.append(icon);
}

void BrisaControlPointDevice::addService(BrisaControlPointService *serviceSwap)
{
    serviceList.append(serviceSwap);
}

void BrisaControlPointDevice::addDevice(BrisaControlPointDevice *device)
{
    embeddedDeviceList.append(device);
}

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

