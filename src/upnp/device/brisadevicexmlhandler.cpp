/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisadevicexmlhandler.cpp
 * Created:
 * Description: Implements BrisaDeviceXmlHandler Class
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
#include "brisadevicexmlhandler.h"
#include "brisadevice.h"

#include <QDebug>

using namespace Brisa;

void BrisaDeviceXMLHandler::xmlGenerator(BrisaDevice *device, QFile *file) {
    file->open(QIODevice::ReadWrite | QIODevice::Text);

    this->writer = new QXmlStreamWriter(file);
    this->writer->setAutoFormatting(true);

    this->writer->writeStartDocument();

    this->writer->writeStartElement("root");
    this->writer->writeAttribute("xmlns", "urn:schemas-upnp-org:device-1-0");

    this->writer->writeStartElement("specVersion");
    this->writer->writeTextElement("major", device->getAttribute(
            BrisaDevice::Major));
    this->writer->writeTextElement("minor", device->getAttribute(
            BrisaDevice::Minor));
    this->writer->writeEndElement(); //specversion

    this->writer->writeTextElement("URLBase", device->getAttribute(
            BrisaDevice::UrlBase));
    this->writeDevice(device);
    this->writer->writeEndElement(); //root

    this->writer->writeEndDocument();

    file->close();
    delete this->writer;
}

void BrisaDeviceXMLHandler::writeDevice(BrisaDevice *device) {
    this->writer->writeStartElement("device");
    this->writer->writeTextElement("deviceType", device->getAttribute(
            BrisaDevice::DeviceType));
    this->writer->writeTextElement("friendlyName", device->getAttribute(
            BrisaDevice::FriendlyName));
    this->writer->writeTextElement("manufacturer", device->getAttribute(
            BrisaDevice::Manufacturer));
    this->writer->writeTextElement("manufacturerURL", device->getAttribute(
            BrisaDevice::ManufacturerUrl));
    this->writer->writeTextElement("modelDescription", device->getAttribute(
            BrisaDevice::ModelDescription));
    this->writer->writeTextElement("modelName", device->getAttribute(
            BrisaDevice::ModelName));
    this->writer->writeTextElement("modelNumber", device->getAttribute(
            BrisaDevice::ModelNumber));
    this->writer->writeTextElement("modelURL", device->getAttribute(
            BrisaDevice::ModelUrl));
    this->writer->writeTextElement("serialNumber", device->getAttribute(
            BrisaDevice::SerialNumber));
    this->writer->writeTextElement("UDN",
            device->getAttribute(BrisaDevice::Udn));
    this->writer->writeTextElement("UPC",
            device->getAttribute(BrisaDevice::Upc));
    this->writer->writeStartElement("iconList");
    QList<BrisaIcon*> iconList = device->getIconList();
    foreach(BrisaIcon *i, iconList)
        {
            this->writer->writeStartElement("icon");
            this->writer->writeTextElement("mimetype", i->getAttribute(
                    BrisaIcon::Mimetype));
            this->writer->writeTextElement("width", i->getAttribute(
                    BrisaIcon::Width));
            this->writer->writeTextElement("height", i->getAttribute(
                    BrisaIcon::Height));
            this->writer->writeTextElement("depth", i->getAttribute(
                    BrisaIcon::Depth));
            this->writer->writeTextElement("url",
                    i->getAttribute(BrisaIcon::Url));
            this->writer->writeEndElement(); //icon
        }
    this->writer->writeEndElement(); //iconList

    this->writer->writeStartElement("serviceList");
    QList<BrisaService*> serviceList = device->getServiceList();
    foreach(BrisaService *s, serviceList)
        {
            this->writer->writeStartElement("service");
            this->writer->writeTextElement("serviceType", s->getAttribute(
                    BrisaService::ServiceType));
            this->writer->writeTextElement("serviceId", s->getAttribute(
                    BrisaService::ServiceId));
            this->writer->writeTextElement("SCPDURL", s->getAttribute(
                    BrisaService::ScpdUrl));
            this->writer->writeTextElement("controlURL", s->getAttribute(
                    BrisaService::ControlUrl));
            this->writer->writeTextElement("eventSubURL", s->getAttribute(
                    BrisaService::EventSubUrl));
            this->writer->writeEndElement(); //service
        }
    this->writer->writeEndElement(); //serviceList

    this->writer->writeStartElement("deviceList");
    QList<BrisaDevice*> embeddedDeviceList = device->getEmbeddedDeviceList();
    foreach(BrisaDevice *d, embeddedDeviceList)
        {
            writeDevice(d);
        }
    this->writer->writeEndElement(); //deviceList

    this->writer->writeTextElement("presentationURL", device->getAttribute(
            BrisaDevice::PresentationUrl));

    this->writer->writeEndElement(); //device
}

