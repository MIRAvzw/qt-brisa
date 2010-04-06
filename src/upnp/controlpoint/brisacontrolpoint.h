/* brisa-c++
 *
 * Copyright (C) 2009 Andre Dieb Martins <andre.dieb@gmail.com>
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

#ifndef _BRISACONTROLPOINT_H
#define _BRISACONTROLPOINT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QMap>
#include <BrisaCore>

#include "brisanetwork.h"
#include "brisacontrolpointdevice.h"
#include "brisacontrolpointservice.h"
#include "brisaeventproxy.h"
#include "brisamsearchclientcp.h"
#include "brisassdpclient.h"
#include "brisaglobal.h"

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaControlPoint : public QObject
{
    Q_OBJECT

    QHttp *http;
    QNetworkAccessManager *downloader;
    QString ipAddress;
    QString urlBase;
    int port;

    bool running;
    BrisaWebserver *webserver;
    BrisaSSDPClient *ssdpClient;
    BrisaMSearchClientCP *msearch;

    int deliveryPath;
    QMap<int, BrisaEventProxy*> requests;
    QMap<QString, int> subscriptions;
    QMap<int, int> requestsMapping;

    /*!
     *  Private function to create the UrlBase of the control point(ip Address) and set the port.
     *  After that creates the urlBase(http:// + ip + : + port)'
     */
    void buildUrlBase();

    public:
		/*!
		 *  Constructor
		 *
		 *  \param parent parent
		 *  \param st service type
		 *  \param mx interval
		 */
        BrisaControlPoint(QObject *parent=0, QString st = "ssdp:all", int mx = 5);

        /**
         *  Destructor
         */
        ~BrisaControlPoint();

        /*!
         *  Starts the control point, the ssdpClient and the msearch
         *
         *  \sa stop(), isRunning()
         */
        void start();

        /*!
         *  Stops the control point, the ssdpClient and the msearch
         *
         *  \sa start(), isRunning()
         */
        void stop();

        /*!
         *  Return if the control point is running
         *
         *  \return true if the control point is running or false otherwise
         *
         *  \sa start(), stop()
         */
        bool isRunning();

        /*!
         *  Starts the control point msearch discover.
         */
        void discover();

        /*!
         *  Gets an event proxy to subscribe, usubscribe or renew the events from a \a service.
         *
         *  \param service \a empty
         */
        BrisaEventProxy *getSubscriptionProxy(BrisaControlPointService *service);

    signals:
        void deviceFound(BrisaControlPointDevice *device);
        void deviceGone(QString usn);

    private slots:
        /*!
         *  Slot called when receive a newDevice event, this slot start the device's xml download.
         *
         *  \param usn \a empty
         *  \param location \a empty
         *  \param ext \a empty
         *  \param server \a empty
         *  \param cacheControl \a empty
         */
        void deviceFound(QString usn, QString location, QString st, QString ext, QString server,
                         QString cacheControl);

        /*!
         *  Slot called when ssdp client emits a removed device event, this slot emit the deviceGone signal
         *  which has as parameter the device's usn.
         *
         *  \param usn empty
         */
        void deviceRemoved(const QString usn);

        /*!
         *  Write the content of the downloaded xml in a new xml temporary file to set the device's
         *  attributes emits the deviceFound signal when finished.
         *
         *  \param reply \a empty
         *
         */
        void replyFinished(QNetworkReply *reply);

        /*!
         *  Slot to get the response of the http request, made by BrisaEventProxy class and set the SID
         *  of the subscription object.
         *
         *  \param i \a empty
         *  \param error \a empty
         */
        void httpResponse(int i, bool error);
};

}

#endif /* _BRISACONTROL_POINT_H */
