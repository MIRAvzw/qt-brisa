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

#ifndef _BRISADEVICE_H
#define _BRISADEVICE_H

#include <QString>
#include <QList>
#include <QXmlDefaultHandler>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QtDebug>
#include <QObject>
#include <BrisaCore>

#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisadevicexmlhandlercp.h"
#include "brisaglobal.h"

namespace BrisaUpnp{

class BRISA_UPNP_EXPORT BrisaControlPointDevice : public QObject
{
    Q_OBJECT

    public:
        BrisaControlPointDevice(QObject *parent = 0);
        BrisaControlPointDevice(QTemporaryFile *xml, QUrl *url, QObject *parent = 0);
        BrisaControlPointDevice(BrisaControlPointDevice &dev, QObject *parent = 0);
        BrisaControlPointDevice(QString deviceType, QString friendlyName= "",
                      QString manufacturer= "" , QString manufacturerURL = "",
                      QString modelDescription= "", QString modelName= "", QString modelNumber= "",
                      QString modelURL= "", QString serialNumber= "", QString UDN= "",
                      QString UPC= "", QString presentationURL = "", QObject *parent = 0);

        ~BrisaControlPointDevice();

        typedef enum { Major,
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
                       FileAddress} xmlTags;

        QString getAttribute(xmlTags key);
        void setAttribute(xmlTags key, QString value);

        void addIcon(BrisaIcon *icon);
        void addService(BrisaControlPointService *service);
        void addDevice(BrisaControlPointDevice *device);

        QList<BrisaIcon*> getIconList();
        QList<BrisaControlPointService*> &getServiceList();
        QList<BrisaControlPointDevice*> getEmbeddedDeviceList();

        BrisaControlPointService *getServiceById(QString serviceId);
        BrisaControlPointService *getServiceByType(QString serviceType);

        void clear();

    private:
        QList<BrisaIcon*> iconList;
        QList<BrisaControlPointService*> serviceList;
        QList<BrisaControlPointDevice*> embeddedDeviceList;

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

        QString fileAddress;
};

}

#endif /* _BRISADEVICE_H */

