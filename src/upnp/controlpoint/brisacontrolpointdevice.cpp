/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisacontrolpointdevice.cpp
 * Created:
 * Description: Implementation of BrisaControlPointDevice class.
 * Authors:                                                 @since 2009
 *           Jeysibel de Sousa Dantas <jeysibel@gmail.com>  @since 06/04/2010
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

#include <QtDebug>
#include <QIODevice>

#include "brisacontrolpointdevice.h"

using namespace Brisa;

BrisaControlPointDevice::BrisaControlPointDevice(QObject *parent) :
    QObject(parent) {
}

BrisaControlPointDevice::BrisaControlPointDevice(QTemporaryFile *xml,
                                                 QUrl *url,
                                                 QObject *parent) : QObject(parent)
{
    this->setAttribute(BrisaControlPointDevice::UrlBase, url->toString(QUrl::RemovePath));
    BrisaDeviceXMLHandlerCP().parseDevice(this, xml);
}

BrisaControlPointDevice::BrisaControlPointDevice(QString udn,
                                                 QString deviceType,
                                                 QString friendlyName,
                                                 QString manufacturer, 
                                                 QString manufacturerURL,
                                                 QString modelDescription,
                                                 QString modelName,
                                                 QString modelNumber,
                                                 QString modelURL,
                                                 QString serialNumber,
                                                 QString upc,
                                                 QString presentationURL,
                                                 QObject *parent) : QObject(parent)
{
    this->_udn = udn;
    this->_major = "1";
    this->_minor = "0";
    this->_deviceType = deviceType;
    this->_friendlyName = friendlyName;
    this->_manufacturer = manufacturer;
    this->_manufacturerUrl = manufacturerURL;
    this->_modelDescription = modelDescription;
    this->_modelName = modelName;
    this->_modelNumber = modelNumber;
    this->_modelUrl = modelURL;
    this->_serialNumber = serialNumber;
    this->_upc = upc;
    this->_presentationUrl = presentationURL;
    this->_fileAddress = friendlyName.remove(QChar(' ')).append(this->_udn).append(".xml");
}

BrisaControlPointDevice::BrisaControlPointDevice(BrisaControlPointDevice &dev,
        QObject *parent) : QObject(parent)
{
    this->iconList = dev.getIconList();
    this->serviceList = dev.getServiceList();
    this->embeddedDeviceList = dev.getEmbeddedDeviceList();

    this->_udn = dev.getAttribute(BrisaControlPointDevice::Udn);
    this->_major = dev.getAttribute(BrisaControlPointDevice::Major);
    this->_minor = dev.getAttribute(BrisaControlPointDevice::Minor);
    this->_urlBase = dev.getAttribute(BrisaControlPointDevice::UrlBase);
    this->_deviceType = dev.getAttribute(BrisaControlPointDevice::DeviceType);
    this->_friendlyName = dev.getAttribute(BrisaControlPointDevice::FriendlyName);
    this->_manufacturer = dev.getAttribute(BrisaControlPointDevice::Manufacturer);
    this->_manufacturerUrl = dev.getAttribute(BrisaControlPointDevice::ManufacturerUrl);
    this->_modelDescription = dev.getAttribute(BrisaControlPointDevice::ModelDescription);
    this->_modelName = dev.getAttribute(BrisaControlPointDevice::ModelName);
    this->_modelNumber = dev.getAttribute(BrisaControlPointDevice::ModelNumber);
    this->_modelUrl = dev.getAttribute(BrisaControlPointDevice::ModelUrl);
    this->_serialNumber = dev.getAttribute(BrisaControlPointDevice::SerialNumber);
    this->_upc = dev.getAttribute(BrisaControlPointDevice::Upc);
    this->_presentationUrl = dev.getAttribute(BrisaControlPointDevice::PresentationUrl);
    this->_fileAddress = dev.getAttribute(BrisaControlPointDevice::FileAddress);
}

BrisaControlPointDevice::~BrisaControlPointDevice()
{
    qDeleteAll(this->iconList);
    this->iconList.clear();
    qDeleteAll(this->serviceList);
    this->serviceList.clear();
    qDeleteAll(this->embeddedDeviceList);
    this->embeddedDeviceList.clear();
}

void BrisaControlPointDevice::setAttribute(xmlTags key, QString v)
{
    switch (key) {
    case Major:
    case major:
        this->_major = v;
        break;
    case Minor:
    case minor:
        this->_minor = v;
        break;
    case UrlBase:
    case urlBase:
        this->_urlBase = v;
        break;
    case DeviceType:
    case deviceType:
        this->_deviceType = v;
        break;
    case FriendlyName:
    case friendlyName:
        this->_friendlyName = v;
        break;
    case Manufacturer:
    case manufacturer:
        this->_manufacturer = v;
        break;
    case ManufacturerUrl:
    case manufacturerUrl:
        this->_manufacturerUrl = v;
        break;
    case ModelDescription:
    case modelDescription:
        this->_modelDescription = v;
        break;
    case ModelName:
    case modelName:
        this->_modelName = v;
        break;
    case ModelNumber:
    case modelNumber:
        this->_modelNumber = v;
        break;
    case ModelUrl:
    case modelUrl:
        this->_modelUrl = v;
        break;
    case SerialNumber:
    case serialNumber:
        this->_serialNumber = v;
        break;
    case Udn:
    case udn:
        this->_udn = v;
        break;
    case Upc:
    case upc:
        this->_upc = v;
        break;
    case PresentationUrl:
    case presentationUrl:
        this->_presentationUrl = v;
        break;
    case FileAddress:
    case fileAddress:
        this->_fileAddress = v;
        break;
    }
}

QString BrisaControlPointDevice::getAttribute(xmlTags key)
{
    switch (key) {
    case Udn:
    case udn:
        return this->_udn;
        break;
    case Major:
    case major:
        return this->_major;
        break;
    case Minor:
    case minor:
        return this->_minor;
        break;
    case UrlBase:
    case urlBase:
        return this->_urlBase;
        break;
    case DeviceType:
    case deviceType:
        return this->_deviceType;
        break;
    case FriendlyName:
    case friendlyName:
        return this->_friendlyName;
        break;
    case Manufacturer:
    case manufacturer:
        return this->_manufacturer;
        break;
    case ManufacturerUrl:
    case manufacturerUrl:
        return this->_manufacturerUrl;
        break;
    case ModelDescription:
    case modelDescription:
        return this->_modelDescription;
        break;
    case ModelName:
    case modelName:
        return this->_modelName;
        break;
    case ModelNumber:
    case modelNumber:
        return this->_modelNumber;
        break;
    case ModelUrl:
    case modelUrl:
        return this->_modelUrl;
        break;
    case SerialNumber:
    case serialNumber:
        return this->_serialNumber;
        break;
    case Upc:
    case upc:
        return this->_upc;
        break;
    case PresentationUrl:
    case presentationUrl:
        return this->_presentationUrl;
        break;
    case FileAddress:
    case fileAddress:
        return this->_fileAddress;
        break;
    default:
        return "";
        break;
    }
}

BrisaControlPointService *BrisaControlPointDevice::getServiceById(QString serviceId)
{
    for (int i = 0; i < this->serviceList.size(); i++) {
        if (this->serviceList.at(i)->getAttribute(BrisaControlPointService::ServiceId).compare(serviceId) == 0) {
            return serviceList.at(i);
        }
    }
    return NULL;
}

BrisaControlPointService *BrisaControlPointDevice::getServiceByType(QString serviceType)
{
    for (int i = 0; i < this->serviceList.size(); i++) {
    	qDebug() << "########### Brisa : String to Compare " << serviceType;
    	qDebug() << "########### Brisa : Service Current " << this->serviceList.at(i)->getAttribute(BrisaControlPointService::ServiceType);
        if (this->serviceList.at(i)->getAttribute(BrisaControlPointService::ServiceType).compare(serviceType) == 0) {
            return serviceList.at(i);
        }
    }
    return NULL;
}

QList<BrisaIcon*> BrisaControlPointDevice::getIconList()
{
    return this->iconList;
}

QList<BrisaControlPointService*> &BrisaControlPointDevice::getServiceList() {
    return this->serviceList;
}

QList<BrisaControlPointDevice*> BrisaControlPointDevice::getEmbeddedDeviceList() {
    return this->embeddedDeviceList;
}

void BrisaControlPointDevice::addIcon(BrisaIcon *icon) {
    iconList.append(icon);
}

void BrisaControlPointDevice::addService(BrisaControlPointService *serviceSwap) {
    serviceList.append(serviceSwap);
}

void BrisaControlPointDevice::addDevice(BrisaControlPointDevice *device) {
    embeddedDeviceList.append(device);
}

void BrisaControlPointDevice::downloadIcons()
{
    downloaded = 0;

    for (int i = 0; i < this->iconList.size(); i++)
    {
        BrisaIcon *icon = this->iconList.at(i);
        connect(icon, SIGNAL(iconDownloadFinished()), this, SLOT(downloadFinished()));
        icon->downloadIcon(this->getAttribute(UrlBase));
    }
}

void BrisaControlPointDevice::downloadFinished()
{
    downloaded++;
    if(downloaded == this->iconList.size())
    {
        emit onReadyDownloadIcons(this);
    }
}

void BrisaControlPointDevice::clear() {
    this->iconList.clear();
    this->serviceList.clear();
    this->embeddedDeviceList.clear();
    this->_udn.clear();
    this->_major.clear();
    this->_minor.clear();
    this->_urlBase.clear();
    this->_deviceType.clear();
    this->_friendlyName.clear();
    this->_manufacturer.clear();
    this->_manufacturerUrl.clear();
    this->_modelDescription.clear();
    this->_modelName.clear();
    this->_modelNumber.clear();
    this->_modelUrl.clear();
    this->_serialNumber.clear();
    this->_upc.clear();
    this->_presentationUrl.clear();
    this->_fileAddress.clear();
}

