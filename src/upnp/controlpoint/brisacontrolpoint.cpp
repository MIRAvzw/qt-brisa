/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisacontrolpoint.cpp
 * Created:
 * Description: Implementation of BrisaControlPoint class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com>      @since 2009
 *          Jeysibel de Sousa Dantas <jeysibel@gmail.com>  @since 06/04/2010
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

#include <QtCore>
#include <QtDebug>

#include "brisacontrolpoint.h"
#include "brisassdpclient.h"
#include "brisamsearchclientcp.h"

using namespace BrisaUpnp;

BrisaControlPoint::BrisaControlPoint(QObject *parent, QString st, int mx) :
    QObject(parent) {
    buildUrlBase();
    deliveryPath = 0;
    running = false;

    webserver = new BrisaWebserver(QHostAddress(ipAddress), port);

    /* HTTP protocol implementation for requests */
    http = new QHttp();

    connect(http, SIGNAL(requestFinished(int, bool)), this,
            SLOT(httpResponse(int, bool)));

    /* SSDP client */
    ssdpClient = new BrisaSSDPClient(this);

    connect(ssdpClient, SIGNAL(removedDeviceEvent(QString)), this,
            SLOT(deviceRemoved(QString)));
    connect(
            ssdpClient,
            SIGNAL(newDeviceEvent(QString, QString, QString, QString, QString, QString)),
            this,
            SLOT(deviceFound(QString, QString, QString, QString, QString, QString)));

    /* MSearch client */
    msearch = new BrisaMSearchClientCP(this, st, mx);

    connect(
            msearch,
            SIGNAL(msearchResponseReceived(QString, QString, QString, QString, QString, QString)),
            this,
            SLOT(deviceFound(QString, QString, QString, QString, QString, QString)));

    /* XML downloader */
    downloader = new QNetworkAccessManager();
    connect(downloader, SIGNAL(finished(QNetworkReply*)), this,
            SLOT(replyFinished(QNetworkReply*)));

    webserver->start();
}

BrisaControlPoint::~BrisaControlPoint() {
    if (!isRunning())
        stop();
    delete downloader;
    delete msearch;
    delete ssdpClient;
    delete webserver;
    delete http;
}

void BrisaControlPoint::start() {
    if (isRunning()) {
        qDebug() << "Control point already started.";
        return;
    }

    ssdpClient->start();
    msearch->start();
    running = true;
}

void BrisaControlPoint::stop() {
    if (!isRunning()) {
        qDebug() << "Control point already stopped.";
        return;
    }

    ssdpClient->stop();
    msearch->stop();
    running = false;
}

bool BrisaControlPoint::isRunning() {
    return running;
}

void BrisaControlPoint::discover() {
    msearch->discover();
}

void BrisaControlPoint::replyFinished(QNetworkReply *reply) {
    QTemporaryFile *rootXml = new QTemporaryFile();

    if (!rootXml->open()) {
        qWarning() << "Failed to open file for writing root XML.";
        return;
    }

    rootXml->write(reply->readAll());
    rootXml->seek(0);

    QUrl *urlBase = new QUrl(reply->url());
    BrisaControlPointDevice *device = new BrisaControlPointDevice(rootXml,
            urlBase);

    /* Fix embedded devices host/port attributes */
    QList<BrisaControlPointService*> serviceList = device->getServiceList();

    foreach(BrisaControlPointService *s, serviceList)
        {
            s->setAttribute(BrisaControlPointService::Host, urlBase->host());
            s->setAttribute(BrisaControlPointService::Port, QString().setNum(
                    urlBase->port()));
        }

    rootXml->remove();
    delete rootXml;
    delete urlBase;

    emit deviceFound(device);
}

void BrisaControlPoint::deviceFound(QString, QString location, QString,
        QString, QString, QString) {
    downloader->get(QNetworkRequest(QUrl(location)));
}

void BrisaControlPoint::deviceRemoved(const QString usn) {
    emit deviceGone(usn);
}

void BrisaControlPoint::buildUrlBase() {
    QString sPort;
    this->port = getPort();
    sPort.setNum(port);

    this->ipAddress = (!getIp("eth0").isEmpty()) ? getIp("eth0") : getIp(
            "wlan0");
    this->urlBase = "http://" + ipAddress + ":" + sPort;
}

BrisaEventProxy *BrisaControlPoint::getSubscriptionProxy(
        BrisaControlPointService *service) {
    deliveryPath++;
    BrisaEventProxy *subscription = new BrisaEventProxy(QStringList(
            this->urlBase), webserver, deliveryPath, service->getAttribute(
            BrisaControlPointService::Host), service->getAttribute(
            BrisaControlPointService::Port).toInt(), http,
            service->getAttribute(BrisaControlPointService::EventSubUrl));

    requests[deliveryPath] = subscription;
    return subscription;
}

void BrisaControlPoint::httpResponse(int i, bool error) {
    qWarning() << "Http response for request " << i;

    // Locate request object
    BrisaEventProxy *subscription = NULL;

    foreach(int deliveryPath, requests.keys())
        {
            if (requests[deliveryPath]->requestId == i) {
                subscription = requests[deliveryPath];
                qDebug() << "Response for request id" << i << " "
                        << deliveryPath;
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

        foreach(QString key, header.keys())
            {
                qDebug() << key << header.value(key);
            }

        qDebug() << "Finished printing headers.. printing data";
        qDebug() << http->readAll();

        return;
    }

    subscription->setSid(sid);
    qDebug() << "Subscribed with SID " << subscription->getSid();
}
