/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisadevicexmlhandlercp.cpp
 * Created:
 * Description: Implementation of BrisaDeviceParserContext, BrisaDeviceXMLHandlerCP and
 * BrisaServiceFetcher classes.
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
#include "brisadevicexmlhandlercp.h"
#include "brisacontrolpointdevice.h"

#define PORT_INDEX 2

using namespace BrisaUpnp;

BrisaDeviceXMLHandlerCP::~BrisaDeviceXMLHandlerCP() {
    delete context;
}

void BrisaDeviceXMLHandlerCP::parseDevice(BrisaControlPointDevice *device,
        QTemporaryFile *tmp) {
    context = new BrisaDeviceParserContext(NULL, device);
    input = new QXmlInputSource(tmp);
    reader = new QXmlSimpleReader();

    context->state = Start;
    context->stateSkip = 0;
    reader->setContentHandler(this);
    reader->setErrorHandler(this);
    reader->parse(input);

    delete input;
    delete reader;
}

bool BrisaDeviceXMLHandlerCP::startElement(const QString &, const QString &,
        const QString &qName, const QXmlAttributes &) {
    switch (context->state) {
    case Start:
        if (qName == "root")
            context->state = Root;
        else
            context->state = Error;
        break;

    case Root:
        if (qName == "specVersion")
            context->state = SpecVersion;
        else if (qName == "URLBase")
            context->state = UrlBase;
        else if (qName == "device")
            context->state = Device;
        else
            context->stateSkip++;
        break;

    case SpecVersion:
        if (qName == "major")
            context->state = SpecVersionMajor;
        else if (qName == "minor")
            context->state = SpecVersionMinor;
        else
            context->stateSkip++;
        break;

    case Device:
        if (!context->getDevice())
            context->setDevice(new BrisaControlPointDevice());

        if (qName == "deviceType")
            context->state = DeviceType;
        else if (qName == "friendlyName")
            context->state = DeviceFriendlyName;
        else if (qName == "manufacturer")
            context->state = Manufacturer;
        else if (qName == "manufacturerURL")
            context->state = ManufacturerUrl;
        else if (qName == "modelDescription")
            context->state = ModelDescription;
        else if (qName == "modelName")
            context->state = ModelName;
        else if (qName == "modelURL")
            context->state = ModelUrl;
        else if (qName == "serialNumber")
            context->state = SerialNumber;
        else if (qName == "presentationURL")
            context->state = PresentationUrl;
        else if (qName == "deviceList") {
            // Create new parsing context
            BrisaDeviceParserContext *newContext =
                    new BrisaDeviceParserContext(context);

            // Switch context
            context = newContext;

            break;
        } else if (qName == "serviceList")
            context->state = ServiceList;
        else if (qName == "UPC")
            context->state = Upc;
        else if (qName == "UDN")
            context->state = Udn;
        else if (qName == "iconList")
            context->state = IconList;
        else
            context->stateSkip++;
        break;

    case IconList:
        if (qName == "icon")
            context->state = Icon;
        else
            context->stateSkip++;
        break;

    case Icon:
        if (!context->getIcon()) {
            context->setIcon(new BrisaIcon());
        }

        if (qName == "mimetype")
            context->state = IconMimetype;
        else if (qName == "width")
            context->state = IconWidth;
        else if (qName == "height")
            context->state = IconHeight;
        else if (qName == "depth")
            context->state = IconDepth;
        else if (qName == "url")
            context->state = IconUrl;
        else
            context->stateSkip++;
        break;

    case DeviceList:
        if (qName == "device")
            context->state = Device;
        else
            context->stateSkip++;
        break;

    case ServiceList:
        if (qName == "service")
            context->state = Service;
        else
            context->stateSkip++;
        break;

    case Service:
        if (!context->getService())
            context->setService(new BrisaControlPointService());

        if (qName == "serviceType")
            context->state = ServiceType;
        else if (qName == "serviceId")
            context->state = ServiceId;
        else if (qName == "SCPDURL")
            context->state = ServiceScpdUrl;
        else if (qName == "controlURL")
            context->state = ServiceControlUrl;
        else if (qName == "eventSubURL")
            context->state = ServiceEventSubUrl;
        else
            context->stateSkip++;
        break;

    default:
        context->stateSkip++;
    }

    return true;
}

bool BrisaDeviceXMLHandlerCP::characters(const QString &str) {
    switch (context->state) {

    case SpecVersionMajor:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Major, str);
        break;

    case SpecVersionMinor:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Minor, str);
        break;

    case UrlBase:
        context->getDevice()->setAttribute(BrisaControlPointDevice::UrlBase,
                str);
        break;

    case DeviceType:
        context->getDevice()->setAttribute(BrisaControlPointDevice::DeviceType,
                str);
        break;

    case DeviceFriendlyName:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::FriendlyName, str);
        break;

    case Manufacturer:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::Manufacturer, str);
        break;

    case ManufacturerUrl:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::ManufacturerUrl, str);
        break;

    case ModelDescription:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::ModelDescription, str);
        break;

    case ModelName:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ModelName,
                str);
        break;

    case ModelUrl:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ModelUrl,
                str);
        break;

    case SerialNumber:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::SerialNumber, str);
        break;

    case Upc:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Upc, str);
        break;

    case Udn:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Udn, str);
        break;

    case PresentationUrl:
        context->getDevice()->setAttribute(
                BrisaControlPointDevice::PresentationUrl, str);
        break;

    case IconMimetype:
        context->getIcon()->setAttribute(BrisaIcon::Mimetype, str);
        break;

    case IconUrl:
        context->getIcon()->setAttribute(BrisaIcon::Url, str);
        break;

    case IconWidth:
        context->getIcon()->setAttribute(BrisaIcon::Width, str);
        break;

    case IconHeight:
        context->getIcon()->setAttribute(BrisaIcon::Height, str);
        break;

    case IconDepth:
        context->getIcon()->setAttribute(BrisaIcon::Depth, str);
        break;

    case ServiceType:
        context->getService()->setAttribute(
                BrisaControlPointService::ServiceType, str);
        break;

    case ServiceId:
        context->getService()->setAttribute(
                BrisaControlPointService::ServiceId, str);
        break;

    case ServiceScpdUrl:
        context->getService()->setAttribute(BrisaControlPointService::ScpdUrl,
                str);
        break;

    case ServiceEventSubUrl:
        context->getService()->setAttribute(
                BrisaControlPointService::EventSubUrl, str);
        break;

    case ServiceControlUrl:
        context->getService()->setAttribute(
                BrisaControlPointService::ControlUrl, str);
        break;

        /*
         * Shut up compiler warnings
         */
    case Start:
    case Root:
    case SpecVersion:
    case Device:
    case IconList:
    case Icon:
    case DeviceList:
    case ServiceList:
    case Service:
    case Finished:
    case Error:
        break;
    }

    return true;
}

bool BrisaDeviceXMLHandlerCP::endElement(const QString &, const QString &,
        const QString &) {

    if (context->stateSkip) {
        context->stateSkip--;
        return true;
    }

    switch (context->state) {

    case Root:
        context->state = Finished;
        break;

    case Device:
        if (context->hasParent()) {
            /*
             * Finished building an embedded device, parent existence means
             * we're inside a DeviceList.
             */
            context->getParent()->getDevice()->addDevice(context->getDevice());
            context->state = DeviceList;
        } else {
            /*
             * Finished building the root device.
             */
            context->state = Root;
        }

        break;

    case DeviceList:
        if (!context->hasParent()) {
            /*
             * Finished building device list
             */
            context->state = Root;
            break;
        }

        /*
         * Switch back to previous context
         */
        BrisaDeviceParserContext *inner;
        inner = context;
        context = inner->getParent();
        delete inner;
        break;

    case SpecVersion:
    case UrlBase:
        context->state = Root;
        break;

    case SpecVersionMajor:
    case SpecVersionMinor:
        context->state = SpecVersion;
        break;

    case IconList:
    case Udn:
    case SerialNumber:
    case ModelUrl:
    case ModelDescription:
    case ModelName:
    case Upc:
    case PresentationUrl:
    case Manufacturer:
    case ManufacturerUrl:
    case DeviceFriendlyName:
    case DeviceType:
    case ServiceList:
        context->state = Device;
        break;

    case IconMimetype:
    case IconWidth:
    case IconHeight:
    case IconDepth:
    case IconUrl:
        context->state = Icon;
        break;

    case Icon:
        context->state = IconList;
        context->getDevice()->addIcon(context->getIcon());
        context->setIcon(NULL);
        break;

    case Service: {
        context->state = ServiceList;
        QStringList urlBase = context->getDevice()->getAttribute(BrisaControlPointDevice::UrlBase).split(":");
        if (urlBase.size() > PORT_INDEX) {
            QString port = urlBase[PORT_INDEX];
            QString newPort = "";
            quint8 index = 0;
            while (port[index].isDigit()) {
                newPort.append(port[index]);
                index++;
            }
            urlBase[PORT_INDEX] = newPort;
            while (urlBase.size() > PORT_INDEX + 1) urlBase.pop_back();
        }

//        BrisaServiceFetcher *f = new BrisaServiceFetcher(context->getService(),
//                context->getDevice()->getAttribute(
//                        BrisaControlPointDevice::UrlBase)
//                        + context->getService()->getAttribute(
//                                BrisaControlPointService::ScpdUrl));
        BrisaServiceFetcher *f = new BrisaServiceFetcher(context->getService(),
                  urlBase.join(":") + context->getService()->
                  getAttribute(BrisaControlPointService::ScpdUrl));

        if (!f->fetch()) {
            context->getDevice()->addService(context->getService());
            context->setService(NULL);
        } else {
            // TODO handle error
            qWarning() << "Failed to dowload service XML.";
        }

        delete f;
        break;
    }

    case ServiceType:
    case ServiceId:
    case ServiceScpdUrl:
    case ServiceControlUrl:
    case ServiceEventSubUrl:
        context->state = Service;
        break;

        /*
         * Shut up compiler warnings
         */
    case Start:
    case Finished:
    case Error:
        break;
    }

    return true;
}
