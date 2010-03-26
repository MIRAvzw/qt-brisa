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

#include "brisanetwork.h"
#include "brisadevicexmlhandler.h"
#include "brisaservice.h"
#include "brisassdpserver.h"
#include "brisaicon.h"
#include "brisaglobal.h"

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaDevice : public QObject
{
    Q_OBJECT

    public:
        BrisaDevice(QObject *parent = 0);
        BrisaDevice(const BrisaDevice &dev);
        BrisaDevice(const QString &deviceType, QString friendlyName = "",
                    const QString &manufacturer = "" , const QString &manufacturerURL = "",
                    const QString &modelDescription = "", const QString &modelName = "",
                    const QString &modelNumber = "", const QString &modelURL = "",
                    const QString &serialNumber = "", const QString &UDN = "",
                    const QString &UPC = "", const QString &presentationURL = "", QObject *parent = 0);
        ~BrisaDevice();

        BrisaDevice &operator=(const BrisaDevice &dev);

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
                       FileAddress,
                       Location,
                       Server,
                       IpAddress,
                       Port,
                       Running} xmlTags;

        void setAttribute(xmlTags key, const QString &value);
        QString getAttribute(xmlTags key) const;

        void addIcon(const QString &mimetype = "", const QString &width = "",
                     const QString &height = "", const QString &depth = "", const QString &url = "");

        void addService(const QString &serviceType = "", const QString &serviceId = "",
                        const QString &SCPDURL = "", const QString &controlURL = "",
                        const QString &eventSubURL = "");

        void addService(BrisaService *serv);

        void addEmbeddedDevice(const QString &deviceType = "", const QString &friendlyName = "",
                               const QString &manufacturer = "", const QString &manufacturerURL = "",
                               const QString &modelDescription = "", const QString &modelName = "",
                               const QString &modelNumber = "", const QString &modelURL = "",
                               const QString &serialNumber = "", const QString &UDN = "",
                               const QString &UPC = "", const QString &presentationURL = "");
        void addEmbeddedDevice(BrisaDevice *newEmbeddedDevice);

        QList<BrisaIcon> getIconList() const;
        QList<BrisaService *> getServiceList() const;
        QList<BrisaDevice *> getEmbeddedDeviceList() const;

        BrisaService *getServiceById(const QString &serviceId);
        BrisaService *getServiceByType(const QString &serviceType);

        void clear();

        void doNotify();
        void doByeBye();
        void start();
        void stop();

    public slots:
       void respondMSearch(const QString &st, const QString &senderIp, quint16 senderPort);

    private:
        void xmlGenerator();

        void buildUrlBase();
        void buildWebServerTree();
        void startWebServer();
        void respondMSearchAll(const QString &senderIp, quint16 senderPort, const QString &sDate);
        bool isRunning();

        QList<BrisaIcon> iconList;
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

