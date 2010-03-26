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

    void buildUrlBase();

    public:
        BrisaControlPoint(QObject *parent=0, QString st = "ssdp:all", int mx = 5);
        ~BrisaControlPoint();
        void start();
        void stop();
        bool isRunning();
        void discover();
        BrisaEventProxy *getSubscriptionProxy(BrisaControlPointService *service);

    signals:
        void deviceFound(BrisaControlPointDevice *device);
        void deviceGone(QString usn);

    private slots:
        void deviceFound(QString usn, QString location, QString st, QString ext, QString server,
                         QString cacheControl);
        void deviceRemoved(const QString usn);
        void replyFinished(QNetworkReply *reply);
        void httpResponse(int i, bool error);
};

}

#endif /* _BRISACONTROL_POINT_H */
