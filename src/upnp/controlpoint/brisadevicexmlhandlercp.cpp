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

#include "brisadevicexmlhandlercp.h"
#include "brisacontrolpointdevice.h"

using namespace BrisaUpnp;

/*!
 *    \internal
 *
 *    \class BrisaDeviceParserContext
 *
 *    Represents a parsing context, defined by a parent, a build target device, service and icon.
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::parent
 *
 *    \brief Same object, the parent of one context
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::device
 *
 *    \brief BrisaControlPointDevice that is going to have it's attributes set.
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::service
 *
 *    \brief Service that is going to be generated to be added by the device.
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::icon
 *
 *    \brief Icon that is going to be generated to be added by the device.
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::stateSkip
 *
 *    \brief incremented when a xml tag that isn't a recognized by UPnP architecture is find in xml.
 */

/*!
 *    \internal
 *
 *    \property BrisaDeviceParserContext::state
 *
 *    \brief The actual state in the reading.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::BrisaDeviceParserContext(BrisaDeviceParserContext *parent,
 *                                                           BrisaControlPointDevice *target)
 *
 *    Constructor that receives the parser and the target that is going to be set.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::getIcon()
 *
 *    Returns context's icon.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::getDevice()
 *
 *    Returns context's device.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::getService()
 *
 *    Returns context's service.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::setIcon(BrisaIcon *icon)
 *
 *    Sets context's icon to \a icon.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::setDevice(BrisaControlPointDevice *device)
 *
 *    Sets context's device to \a device.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::setService(BrisaControlPointService *service)
 *
 *    Sets context's service to \a service.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::hasParent()
 *
 *    Returns true if context's parent different than zero.
 */

/*!
 *    \internal
 *
 *    \fn BrisaDeviceParserContext::getParent()
 *
 *    Returns context's parent.
 */

/*!
 *    \internal
 *
 *    \class BrisaServiceFetcher
 *
 *    \brief Class that generates the service by downloading the xml description file, reading,
 *    and initializing services attributes.
 */

/*!
 *    \internal
 *
 *    \property BrisaServiceFetcher::eventLoop
 *
 *    \brief Guarantees that flow of execution will only continue after the xml download is finished.
 */

/*!
 *    \internal
 *
 *    \property BrisaServiceFetcher::downloader
 *
 *    \brief Do the xml download from network.
 */

/*!
 *    \internal
 *
 *    \property BrisaServiceFetcher::location
 *
 *    \brief Location to download the xml file.
 */

/*!
 *    \internal
 *
 *    \property BrisaServiceFetcher::service
 *
 *    \brief service that is going to have the parameters set.
 */

/*!
 *    \internal
 *
 *    \property BrisaServiceFetcher::error
 *
 *    \brief Flag to detect a error in service fetch.
 */

/*!
 *    \internal
 *
 *    \fn BrisaServiceFetcher::fetchFinished()
 *
 *    \brief Signal emitted when the service fetch is finished.
 */

/*!
 *    \internal
 *
 *    \fn BrisaServiceFetcher::BrisaServiceFetcher(BrisaControlPointService *service, QString location,
 *                                                 QObject *parent)
 *
 *    \brief BrisaServiceFetcher constructor, receives the \a service that is going to be set, the
 *    \a location to download xml, and a QObject as parent.
 */

/*!
 *    \internal
 *
 *    \fn BrisaServiceFetcher::~BrisaServiceFetcher()
 *
 *    \brief Destructor.
 */

/*!
 *    \internal
 *
 *    \fn BrisaServiceFetcher::fetch()
 *
 *    \brief Start the xml download and initializes the event loop, returns \a error(bool).
 */

/*!
 *    \internal
 *
 *    \fn BrisaServiceFetcher::downloadFinished(QNetworkReply *reply)
 *
 *    \brief When download is finished, this slop write the download content into a temporary file
 *    and tells the service parameter to be generate from it that means it initializes the service
 *    too.
 */

/*!
 *    \class BrisaUpnp::BrisaDeviceXMLHandlerCP brisadevicexmlhandlercp.h BrisaUpnp/BrisaDeviceXMLHandlerCP
 *
 *    \brief BrisaDeviceXMLHandlerCP creates a device from a xml description file, with all it's
 *    attributes, it let's it ready to be used.
 */

/*!
 *    \property context
 *
 *    \brief Used to see what reading is going to be done and set device's attributes.
 */

/*!
 *    \property reader
 *
 *    \brief Object that do the xml parse.
 */

/*!
 *    \property input
 *
 *    \brief input source that reader is going to use in the parser.
 */

/*!
 *    \enum BrisaUpnp::BrisaDeviceXMLHandlerCP::SaxParserState
 *
 *    \brief This enum specifies the devices attributes that are going to be set/get
 *
 *    \param Start  Beginning state in the parser.
 *
 *    \param Root  Root tag in xml.
 *
 *    \param SpecVersion  Tag to start editing spec version in device.
 *
 *    \param SpecVersionMajor  Tag where the state is to edit the major spec version
 *
 *    \param SpecVersionMinor  Tag where the state is to edit the major spec version
 *
 *    \param UrlBase  Tag to edit urlBase.
 *
 *    \param Device  Tag to signal the edit begin of device's attributes.
 *
 *    \param DeviceType  Tag to edit device type.
 *
 *    \param DeviceFriendlyName  Tag to edit deviceFriendlyName
 *
 *    \param Manufacturer  Tag to edit Manufacturer's name.
 *
 *    \param ManufacturerUrl  Tag to edit Web site for Manufacturer.
 *
 *    \param ModelDescription  Tag to edit the long description for end user.
 *
 *    \param ModelName  Tag to edit Model name.
 *
 *    \param ModelNumber  Tag to edit Model number.
 *
 *    \param ModelUrl  Tag to edit Web site for model.
 *
 *    \param SerialNumber  Tag to edit Serial number.
 *
 *    \param Udn  Tag to edit Unique Device Name.
 *
 *    \param Upc  Tag to edit Universal Product Code.
 *
 *    \param IconList  Tag to signal the start the beginning of the addition of icons.
 *
 *    \param Icon  Tag to signal the start of icon's parameter edition.
 *
 *    \param IconMimetype  Tag to edit context's icon's myme type.
 *
 *    \param IconWidth  Tag to edit context's icon's width.
 *
 *    \param IconHeight  Tag to edit context's icon's height.
 *
 *    \param IconDepth  Tag to edit context's icon's depth.
 *
 *    \param IconUrl  Tag to edit context's icon's url.
 *
 *    \param PresentationUrl  Tag to edit URL to presentation for device.
 *
 *    \param DeviceList  Tag to signal the embedded devices addition.
 *
 *    \param ServiceList  Tag to signal services addition.
 *
 *    \param Service  Tag to start context's service's attributes edition.
 *
 *    \param ServiceType  Tag to edit the service's type.
 *
 *    \param ServiceId  Tag to edit the service's id.
 *
 *    \param ServiceType  Tag to edit the service's type.
 *
 *    \param ServiceScpdUrl  Tag to edit service's scpd url.
 *
 *    \param ServiceControlUrl  Tag to edit service's control url.
 *
 *    \param ServiceEventSubUrl  Tag to edit service's eventsub url.
 *
 *    \param Finished  Tag to signal the reading is done.
 *
 *    \param Error  Tag to signal an error in the parser.
 *
 *    \sa setAttribute(xmlTags key, QString v), getAttribute(xmlTags key)
 */

/*!
 *    Method that initializes \a device attributes from \a tmp file.
 */
void BrisaDeviceXMLHandlerCP::parseDevice(BrisaControlPointDevice *device, QTemporaryFile *tmp)
{
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

/*!
 *    Method inherited from QXmlDefaultHandler it's called in every beginning tag, depending on tag
 *    the context state passes to a different state so that it can process separately. It's
 *    important to say that in each state it performs a different action.
 */
bool BrisaDeviceXMLHandlerCP::startElement(const QString &, const QString & , const QString &qName,
                                           const QXmlAttributes &)
{
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
            BrisaDeviceParserContext *newContext = new BrisaDeviceParserContext(context);

            // Switch context
            context = newContext;

           break;
        }
        else if (qName == "serviceList")
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

/*!
 *    Method that set properly the attribute value to \str value that it is the content between the
 *    beginning tag and the finish one. It's important to say that in each state it performs a
 *    different action.
 */
bool BrisaDeviceXMLHandlerCP::characters(const QString &str)
{
    switch (context->state) {

    case SpecVersionMajor:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Major, str);
        break;

    case SpecVersionMinor:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Minor, str);
        break;

    case UrlBase:
        context->getDevice()->setAttribute(BrisaControlPointDevice::UrlBase, str);
        break;

    case DeviceType:
        context->getDevice()->setAttribute(BrisaControlPointDevice::DeviceType, str);
        break;

    case DeviceFriendlyName:
        context->getDevice()->setAttribute(BrisaControlPointDevice::FriendlyName, str);
        break;

    case Manufacturer:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Manufacturer, str);
        break;

    case ManufacturerUrl:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ManufacturerUrl, str);
        break;

    case ModelDescription:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ModelDescription, str);
        break;

    case ModelName:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ModelName, str);
        break;

    case ModelUrl:
        context->getDevice()->setAttribute(BrisaControlPointDevice::ModelUrl, str);
        break;

    case SerialNumber:
        context->getDevice()->setAttribute(BrisaControlPointDevice::SerialNumber, str);
        break;

    case Upc:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Upc, str);
        break;

    case Udn:
        context->getDevice()->setAttribute(BrisaControlPointDevice::Udn, str);
        break;

    case PresentationUrl:
        context->getDevice()->setAttribute(BrisaControlPointDevice::PresentationUrl, str);
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
        context->getService()->setAttribute(BrisaControlPointService::ServiceType, str);
        break;

    case ServiceId:
        context->getService()->setAttribute(BrisaControlPointService::ServiceId, str);
        break;

    case ServiceScpdUrl:
        context->getService()->setAttribute(BrisaControlPointService::ScpdUrl, str);
        break;

    case ServiceEventSubUrl:
        context->getService()->setAttribute(BrisaControlPointService::EventSubUrl, str);
        break;

    case ServiceControlUrl:
        context->getService()->setAttribute(BrisaControlPointService::ControlUrl, str);
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

/*!
 * Method that is called in the tag end, this method add the attribute to the device so that
 * attributes can be initialized in device. It's important to say that in each state it performs a
 * different action.
 */
bool BrisaDeviceXMLHandlerCP::endElement(const QString &, const QString &, const QString &)
{

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
        }
        else {
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

    case Service:
        {
        context->state = ServiceList;
        BrisaServiceFetcher *f = new BrisaServiceFetcher(context->getService(),
                                                         context->getDevice()->getAttribute(BrisaControlPointDevice::UrlBase) +
                                                         context->getService()->getAttribute(BrisaControlPointService::ScpdUrl));

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
