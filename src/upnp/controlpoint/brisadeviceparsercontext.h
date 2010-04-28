/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisadevicexmlhandlercp.cpp
 * Created:
 * Description: Definition of BrisaDeviceParserContext,BrisaDeviceXMLHandlerCP and
 * BrisaServiceFetcher  classes.
 * Authors: Danilo Araújo de Freitas <dsurviver@gmail.com> @since 2009
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
#ifndef _BRISADEVICEPARSERCONTEXT_H
#define _BRISADEVICEPARSERCONTEXT_H

#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisaglobal.h"

namespace BrisaUpnp {

class BrisaControlPointDevice;

/*!
 *  \enum BrisaUpnp::BrisaDeviceXMLHandlerCP::SaxParserState
 *
 *  \brief This enum specifies the devices attributes that are going to be set/get
 *
 *  \param Start  Beginning state in the parser.
 *  \param Root  Root tag in xml.
 *  \param SpecVersion  Tag to start editing spec version in device.
 *  \param SpecVersionMajor  Tag where the state is to edit the major spec version
 *  \param SpecVersionMinor  Tag where the state is to edit the major spec version
 *  \param UrlBase  Tag to edit urlBase.
 *  \param Device  Tag to signal the edit begin of device's attributes.
 *  \param DeviceType  Tag to edit device type.
 *  \param DeviceFriendlyName  Tag to edit deviceFriendlyName
 *  \param Manufacturer  Tag to edit Manufacturer's name.
 *  \param ManufacturerUrl  Tag to edit Web site for Manufacturer.
 *  \param ModelDescription  Tag to edit the long description for end user.
 *  \param ModelName  Tag to edit Model name.
 *  \param ModelNumber  Tag to edit Model number.
 *  \param ModelUrl  Tag to edit Web site for model.
 *  \param SerialNumber  Tag to edit Serial number.
 *  \param Udn  Tag to edit Unique Device Name.
 *  \param Upc  Tag to edit Universal Product Code.
 *  \param IconList  Tag to signal the start the beginning of the addition of icons.
 *  \param Icon  Tag to signal the start of icon's parameter edition.
 *  \param IconMimetype  Tag to edit context's icon's myme type.
 *  \param IconWidth  Tag to edit context's icon's width.
 *  \param IconHeight  Tag to edit context's icon's height.
 *  \param IconDepth  Tag to edit context's icon's depth.
 *  \param IconUrl  Tag to edit context's icon's url.
 *  \param PresentationUrl  Tag to edit URL to presentation for device.
 *  \param DeviceList  Tag to signal the embedded devices addition.
 *  \param ServiceList  Tag to signal services addition.
 *  \param Service  Tag to start context's service's attributes edition.
 *  \param ServiceType  Tag to edit the service's type.
 *  \param ServiceId  Tag to edit the service's id.
 *  \param ServiceType  Tag to edit the service's type.
 *  \param ServiceScpdUrl  Tag to edit service's scpd url.
 *  \param ServiceControlUrl  Tag to edit service's control url.
 *  \param ServiceEventSubUrl  Tag to edit service's eventsub url.
 *  \param Finished  Tag to signal the reading is done.
 *  \param Error  Tag to signal an error in the parser.
 *
 *  \sa setAttribute(xmlTags key, QString v), getAttribute(xmlTags key)
 */
typedef enum {
    Start,
    Root,
    SpecVersion,
    SpecVersionMajor,
    SpecVersionMinor,
    UrlBase,
    Device,
    DeviceType,
    DeviceFriendlyName,
    Manufacturer,
    ManufacturerUrl,
    ModelDescription,
    ModelName,
    ModelUrl,
    SerialNumber,
    Udn,
    Upc,
    IconList,
    Icon,
    IconMimetype,
    IconWidth,
    IconHeight,
    IconDepth,
    IconUrl,
    PresentationUrl,
    DeviceList,
    ServiceList,
    Service,
    ServiceType,
    ServiceId,
    ServiceScpdUrl,
    ServiceControlUrl,
    ServiceEventSubUrl,
    Finished,
    Error = -1
} SaxParserState;

/*!
 *  \internal
 *
 *  \class BrisaDeviceParserContext
 *
 *  Represents a parsing context, defined by a parent, a build target device, service and icon.
 */
class BRISA_UPNP_EXPORT BrisaDeviceParserContext {

public:

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::BrisaDeviceParserContext(BrisaDeviceParserContext *parent,
     *                                                           BrisaControlPointDevice *target)
     *  Constructor that receives the parser and the target that is going to be set.
     */
    BrisaDeviceParserContext(BrisaDeviceParserContext *parent = 0,
            BrisaControlPointDevice *target = 0);

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::getIcon()
     *  \return context's icon.
     */
    inline BrisaIcon *getIcon(void) {
        return icon;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::getDevice()
     *  \return context's device.
     */
    inline BrisaControlPointDevice *getDevice(void) {
        return device;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::getService()
     *  \return context's service.
     */
    inline BrisaControlPointService *getService(void) {
        return service;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::setIcon(BrisaIcon *icon)
     *  Sets context's icon to \a icon.
     *  \param icon icon
     */
    inline void setIcon(BrisaIcon *icon) {
        this->icon = icon;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::setDevice(BrisaControlPointDevice *device)
     *  Sets context's device to \a device.
     *  \param device device
     */
    inline void setDevice(BrisaControlPointDevice *device) {
        this->device = device;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::setService(BrisaControlPointService *service)
     *  Sets context's service to \a service.
     *  \param service service
     */
    inline void setService(BrisaControlPointService *service) {
        this->service = service;
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::hasParent()
     *  \return true if context's parent different than zero.
     */
    inline bool hasParent(void) {
        return (parent != 0);
    }

    /*!
     *  \internal
     *  \fn BrisaDeviceParserContext::getParent()
     *  \return context's parent.
     */
    inline BrisaDeviceParserContext *getParent(void) {
        return parent;
    }

    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::stateSkip
     *  \brief incremented when a xml tag that isn't a recognized by UPnP architecture is find in xml.
     */
    int stateSkip;

    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::state
     *  \brief The actual state in the reading.
     */
    SaxParserState state;

private:
    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::parent
     *  \brief Same object, the parent of one context
     */
    BrisaDeviceParserContext *parent;

    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::device
     *  \brief BrisaControlPointDevice that is going to have it's attributes set.
     */
    BrisaControlPointDevice *device;

    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::service
     *  \brief Service that is going to be generated to be added by the device.
     */
    BrisaControlPointService *service;

    /*!
     *  \internal
     *  \property BrisaDeviceParserContext::icon
     *  \brief Icon that is going to be generated to be added by the device.
     */
    BrisaIcon *icon;
};

}

#endif /* _BRISADEVICEPARSERCONTEXT_H */
