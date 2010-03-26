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

#ifndef _BRISADEVICEXMLHANDLER_H
#define _BRISADEVICEXMLHANDLER_H


#include <QXmlDefaultHandler>
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>
#include <QXmlInputSource>
#include <QXmlAttributes>
#include <QMainWindow>
#include <QIODevice>
#include <QString>
#include <QtDebug>
#include <QtCore>
#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>


#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisaglobal.h"

namespace BrisaUpnp {

class BrisaControlPointDevice;

typedef enum {Start,
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

class BRISA_UPNP_EXPORT BrisaDeviceParserContext
{
    public:
        BrisaDeviceParserContext(BrisaDeviceParserContext *parent=0, BrisaControlPointDevice *target=0)
            : stateSkip(0), state(Root), parent(parent), device(target), service(0), icon(0) {}

        BrisaIcon *getIcon(void) { return icon;}
        BrisaControlPointDevice *getDevice(void) { return device;}
        BrisaControlPointService *getService(void) { return service;}

        void setIcon(BrisaIcon *icon) { this->icon = icon;}
        void setDevice(BrisaControlPointDevice *device) { this->device = device;}
        void setService(BrisaControlPointService *service) { this->service = service;}

        bool hasParent(void) { return (parent != 0);}
        BrisaDeviceParserContext *getParent(void) { return parent;}

        int stateSkip;
        SaxParserState state;

    private:
        BrisaDeviceParserContext *parent;
        BrisaControlPointDevice *device;
        BrisaControlPointService *service;
        BrisaIcon *icon;
};

class BRISA_UPNP_EXPORT BrisaDeviceXMLHandlerCP : public QXmlDefaultHandler
{
    public:
        void parseDevice(BrisaControlPointDevice *device, QTemporaryFile *tmp);

    protected:
        bool startElement(const QString &namespaceURI,
                          const QString &localName,
                          const QString &qName,
                          const QXmlAttributes &attributes);
        bool endElement(const QString &namespaceURI,
                        const QString &localName,
                        const QString &qName);
        bool characters(const QString &str);

    private:
        QXmlStreamWriter *writer;
        QXmlSimpleReader *reader;
        QXmlInputSource *input;

        BrisaDeviceParserContext *context;
};

class BRISA_UPNP_EXPORT BrisaServiceFetcher : public QObject
{
    Q_OBJECT

    public:
        BrisaServiceFetcher(BrisaControlPointService *service, QString location, QObject *parent=0)
            : QObject(parent), location(location), service(service)
        {
            eventLoop = new QEventLoop();
            downloader = new QNetworkAccessManager();

            connect(this, SIGNAL(fetchFinished()),
                    eventLoop, SLOT(quit()));
            connect(downloader, SIGNAL(finished(QNetworkReply*)),
                    this, SLOT(downloadFinished(QNetworkReply*)));
            service = NULL;
            error = false;
        }

        ~BrisaServiceFetcher()
        {
            delete downloader;
            delete eventLoop;
        }

        bool fetch(void) {
            downloader->get(QNetworkRequest(location));
            eventLoop->exec();

            return error;
        }

    private:
        QEventLoop *eventLoop;
        QNetworkAccessManager *downloader;
        QString location;
        BrisaControlPointService *service;
        bool error;

    signals:
        void fetchFinished(void);

    private slots:
        void downloadFinished(QNetworkReply *reply)
        {
            QTemporaryFile *scpd = new QTemporaryFile();

            if (!scpd->open()) {
                qDebug() << "Failed to open scpd file for writing";
                error = true;
                emit fetchFinished();
                return;
            }

            scpd->write(reply->readAll());
            scpd->seek(0);
            service->parseFromXml(scpd);

            scpd->remove();
            delete scpd;
            emit fetchFinished();
        }

};

}

#endif /* _BRISADEVICEXMLHANDLER_H */

