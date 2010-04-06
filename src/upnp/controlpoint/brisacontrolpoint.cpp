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

#include <QtCore>
#include <QtDebug>

#include "brisacontrolpoint.h"
#include "brisassdpclient.h"
#include "brisamsearchclientcp.h"

using namespace BrisaUpnp;

/*!
 *    \class BrisaUpnp::BrisaControlPoint brisacontrolpoint.h BrisaUpnp/BrisaControlPoint
 *
 *    \brief Class that implements the control part in UPnP Architecture
 *    \brief Create a ControlPoint and start(), then discover() devices will be found in network.
 *    \brief If you don't want to look for more devices then use stop().
 */

/*!
 *    \fn void BrisaControlPoint::deviceFound(BrisaControlPointDevice *device)
 *
 *    This signal is emitted when a new device is find in network and all it's attributes are created
 *    by the xml reading.
 *
 *    \sa deviceGone(QString usn)
 */

/*!
 *    \fn void BrisaControlPoint::deviceGone(QString usn)
 *
 *    This signal is emitted when a device leaves the network, that means that the the ssdp client
 *    received a "ssdp:byebye" message from the device and, to handle this, the control point emit
 *    a deviceGone event with the device's \a usn as parameter.
 *
 *    \sa deviceFound(BrisaControlPointDevice *device)
 */

/*!
 *    \property http
 *
 *    \brief Do the http request in event subscription.
 */

/*!
 *    \property downloader
 *
 *    \brief Downloads device's xml description file.
 */

/*!
 *    \property ipAddress
 *
 *    \brief Creates the ControlPoint webServer in this ip.
 */

/*!
 *    \property urlBase
 *
 *    \brief ControlPoint's urlBase.
 */

/*!
 *    \property port
 *
 *    \brief ControlPoint's webserver port.
 */

/*!
 *    \property running
 *
 *    \brief Bool to tell if it's running or not.
 */

/*!
 *    \property webserver
 *
 *    \brief Webserver to receive event responses.
 */

/*!
 *    \property ssdpClient
 *
 *    \brief Listen to notify/bye-bye messages.
 */

/*!
 *    \property msearch
 *
 *    \brief Send msearch messages to network.
 */

/*!
 *    \property deliveryPath
 *
 *    \brief Path to receive each event response.
 */

/*!
 *    \property requests
 *
 *    \brief Map to identify each event proxy to a number.
 */

/*!
 *    \property subscriptions
 *
 *    \brief Map to identify each subscription to an int.
 */

/*!
 *    \property requestsMapping
 *
 *    \brief Map that identify each deliveryPath to a subscription.
 */


BrisaControlPoint::BrisaControlPoint(QObject *parent, QString st , int mx) : QObject(parent)
{
    buildUrlBase();
    deliveryPath = 0;
    running = false;

    webserver = new BrisaWebserver(QHostAddress(ipAddress), port);

    /* HTTP protocol implementation for requests */
    http = new QHttp();

    connect(http,
            SIGNAL(requestFinished(int, bool)),
            this,
            SLOT(httpResponse(int, bool)));

    /* SSDP client */
    ssdpClient = new BrisaSSDPClient(this);

    connect(ssdpClient,
            SIGNAL(removedDeviceEvent(QString)),
            this,
            SLOT(deviceRemoved(QString)));
    connect(ssdpClient,
            SIGNAL(newDeviceEvent(QString, QString, QString, QString, QString, QString)),
            this,
            SLOT(deviceFound(QString, QString, QString, QString, QString, QString)));

    /* MSearch client */
    msearch = new BrisaMSearchClientCP(this, st, mx);

    connect(msearch,
            SIGNAL(msearchResponseReceived(QString, QString, QString, QString, QString, QString)),
            this,
            SLOT(deviceFound(QString, QString, QString, QString, QString, QString)));

    /* XML downloader */
    downloader = new QNetworkAccessManager();
    connect(downloader,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));

    webserver->start();
}

BrisaControlPoint::~BrisaControlPoint()
{
    if (!isRunning()) stop();
    delete downloader;
    delete msearch;
    delete ssdpClient;
    delete webserver;
    delete http;
}

void BrisaControlPoint::start()
{
    if (isRunning()) {
        qDebug() << "Control point already started.";
        return;
    }

    ssdpClient->start();
    msearch->start();
    running = true;
}

void BrisaControlPoint::stop()
{
    if (!isRunning()) {
        qDebug() << "Control point already stopped.";
        return;
    }

    ssdpClient->stop();
    msearch->stop();
    running = false;
}

bool BrisaControlPoint::isRunning()
{
    return running;
}

void BrisaControlPoint::discover()
{
    msearch->discover();
}

void BrisaControlPoint::replyFinished(QNetworkReply *reply)
{
    QTemporaryFile *rootXml = new QTemporaryFile();

    if (!rootXml->open()) {
        qWarning() << "Failed to open file for writing root XML.";
        return;
    }

    rootXml->write(reply->readAll());
    rootXml->seek(0);

    QUrl *urlBase = new QUrl(reply->url());
    BrisaControlPointDevice *device = new BrisaControlPointDevice(rootXml, urlBase);

    /* Fix embedded devices host/port attributes */
    QList<BrisaControlPointService*> serviceList = device->getServiceList();

    foreach(BrisaControlPointService *s, serviceList) {
        s->setAttribute(BrisaControlPointService::Host, urlBase->host());
        s->setAttribute(BrisaControlPointService::Port, QString().setNum(urlBase->port()));
    }

    rootXml->remove();
    delete rootXml;
    delete urlBase;

    emit deviceFound(device);
}

void BrisaControlPoint::deviceFound(QString, QString location, QString, QString, QString, QString)
{
    downloader->get(QNetworkRequest(QUrl(location)));
}

void BrisaControlPoint::deviceRemoved(const QString usn)
{
    emit deviceGone(usn);
}

void BrisaControlPoint::buildUrlBase()
{
    QString sPort;
    this->port = getPort();
    sPort.setNum(port);

    this->ipAddress = (!getIp("eth0").isEmpty()) ? getIp("eth0") : getIp("wlan0");
    this->urlBase = "http://" + ipAddress + ":" + sPort;
}

BrisaEventProxy *BrisaControlPoint::getSubscriptionProxy(BrisaControlPointService *service)
{
    deliveryPath++;
    BrisaEventProxy *subscription \
        = new BrisaEventProxy(QStringList(this->urlBase),
                                                 webserver,
                                                 deliveryPath,
                                                 service->getAttribute(BrisaControlPointService::Host),
                                                 service->getAttribute(BrisaControlPointService::Port).toInt(),
                                                 http,
                                                 service->getAttribute(BrisaControlPointService::EventSubUrl));

    requests[deliveryPath] = subscription;
    return subscription;
}

void BrisaControlPoint::httpResponse(int i, bool error)
{
    qWarning() << "Http response for request " << i;

    // Locate request object
    BrisaEventProxy *subscription = NULL;

    foreach(int deliveryPath, requests.keys()) {
        if (requests[deliveryPath]->requestId == i) {
            subscription = requests[deliveryPath];
            qDebug() << "Response for request id" << i << " " << deliveryPath;
            break;
        }
    }

    if (!subscription) {
        qWarning() << "Failed to match response with request id " << i;
        return;
    } else if (error) {
        // TODO forward error to user, notify that subscription didn't work
        qWarning() << "Subscription error" << http->errorString() << i;
        return;
    }

    QHttpResponseHeader header = http->lastResponse();
    QString sid = header.value("SID");

    if (sid.isEmpty()) {
        // Try "sid"
        sid = header.value("sid");
    }

    if (sid.isEmpty()) {
        // TODO report subscription error to user
        qWarning() << "SID header not present on event subscription response.";

        foreach(QString key, header.keys()) {
            qDebug() << key << header.value(key);
        }

        qDebug() << "Finished printing headers.. printing data";
        qDebug() << http->readAll();

        return;
    }

    subscription->setSid(sid);
    qDebug() << "Subscribed with SID " << subscription->getSid();
}
