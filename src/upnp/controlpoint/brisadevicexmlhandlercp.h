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
#ifndef _BRISADEVICEXMLHANDLER_H
#define _BRISADEVICEXMLHANDLER_H

#include <QMainWindow>
#include <QIODevice>
#include <QString>
#include <QtDebug>
#include <QtCore>
#include <QObject>
#include <QDomDocument>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>

#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisaglobal.h"

namespace Brisa {

class BrisaControlPointDevice;

/*!
 *  \class Brisa::BrisaDeviceXMLHandlerCP brisadevicexmlhandlercp.h BrisaUpnp/BrisaDeviceXMLHandlerCP
 *
 *  \brief BrisaDeviceXMLHandlerCP creates a device from a xml description file, with all it's
 *  attributes, it lets it ready to be used.
 */
class BRISA_UPNP_EXPORT BrisaDeviceXMLHandlerCP {
public:


    virtual ~BrisaDeviceXMLHandlerCP();

    /*!
     *  Method that initializes device attributes from a temporary file.
     *  \param device device
     *  \param tmp temporary file
     */
    void parseDevice(BrisaControlPointDevice *device, QTemporaryFile *tmp);

};

/*!
 *  \internal
 *
 *  \class BrisaServiceFetcher
 *
 *  \brief Class that generates the service by downloading the xml description file, reading,
 *  and initializing services attributes.
 */
class BRISA_UPNP_EXPORT BrisaServiceFetcher: public QObject {
Q_OBJECT

public:
    /*!
     *  \internal
     *  \fn BrisaServiceFetcher::BrisaServiceFetcher(BrisaControlPointService *service, QString location,
     *                                               QObject *parent)
     *  \brief BrisaServiceFetcher constructor, receives the \a service that is going to be set, the
     *  \a location to download xml, and a QObject as parent.
     */
    BrisaServiceFetcher(BrisaControlPointService *service, QString location,
            QObject *parent = 0) :
        QObject(parent), location(location), service(service) {
        eventLoop = new QEventLoop();
        downloader = new QNetworkAccessManager();

        connect(this, SIGNAL(fetchFinished()), eventLoop, SLOT(quit()));
        connect(downloader, SIGNAL(finished(QNetworkReply*)), this,
                SLOT(downloadFinished(QNetworkReply*)));
        service = NULL;
        error = false;
    }

    /*!
     *  \internal
     *  \fn BrisaServiceFetcher::~BrisaServiceFetcher()
     *  \brief Destructor.
     */
    virtual ~BrisaServiceFetcher() {
        delete downloader;
        delete eventLoop;
    }

    /*!
     *  \internal
     *  \fn BrisaServiceFetcher::fetch()
     *  \brief Start the xml download and initializes the event loop
     *  \return true if any error occurred
     */
    bool fetch(void) {
        downloader->get(QNetworkRequest(location));
        eventLoop->exec();

        return error;
    }

private:
    /*!
     *  \internal
     *  \property BrisaServiceFetcher::eventLoop
     *  \brief Guarantees that flow of execution will only continue after the xml download is finished.
     */
    QEventLoop *eventLoop;

    /*!
     *  \internal
     *  \property BrisaServiceFetcher::downloader
     *  \brief Do the xml download from network.
     */
    QNetworkAccessManager *downloader;

    /*!
     *  \internal
     *  \property BrisaServiceFetcher::location
     *  \brief Location to download the xml file.
     */
    QString location;

    /*!
     *  \internal
     *  \property BrisaServiceFetcher::service
     *  \brief service that is going to have the parameters set.
     */
    BrisaControlPointService *service;

    /*!
     *  \internal
     *  \property BrisaServiceFetcher::error
     *  \brief Flag to detect a error in service fetch.
     */
    bool error;

signals:
    /*!
     *  \internal
     *  \fn BrisaServiceFetcher::fetchFinished()
     *  \brief Signal emitted when the service fetch is finished.
     */
    void fetchFinished(void);

private slots:
    /*!
     *  \internal
     *  \fn BrisaServiceFetcher::downloadFinished(QNetworkReply *reply)
     *  \brief When download is finished, this slop write the download content into a temporary file
     *  and tells the service parameter to be generate from it that means it initializes the service
     *  too.
     *  \param reply \a empty
     */
    void downloadFinished(QNetworkReply *reply) {
        QTemporaryFile *scpd = new QTemporaryFile();

        if (!scpd->open()) {
            qDebug() << "Failed to open scpd file for writing";
            error = true;
            emit
            fetchFinished();
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

