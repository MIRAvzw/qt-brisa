/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisacontrolpoint.cpp
 * Created:
 * Description: Definition of BrisaControlPoint class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com>      @since 2009
 *          Jeysibel de Sousa Dantas <jeysibel@gmail.com>  @since 06/04/2010
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
#ifndef _BRISACONTROLPOINT_H
#define _BRISACONTROLPOINT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
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

/*!
 *    \class BrisaUpnp::BrisaControlPoint brisacontrolpoint.h BrisaUpnp/BrisaControlPoint
 *
 *    \brief Class that implements the control part in UPnP Architecture
 *    \brief Create a ControlPoint and start(), then discover() devices will be found in network.
 *    \brief If you don't want to look for more devices then use stop().
 */
class BRISA_UPNP_EXPORT BrisaControlPoint: public QObject {
Q_OBJECT

    /*!
     *    \property http
     *    \brief Do the http request in event subscription.
     */
    QHttp *http;

    /*!
     *    \property downloader
     *    \brief Downloads device's xml description file.
     */
    QNetworkAccessManager *downloader;

    /*!
     *    \property ipAddress
     *    \brief Creates the ControlPoint webServer in this ip.
     */
    QString ipAddress;

    /*!
     *    \property urlBase
     *    \brief ControlPoint's urlBase.
     */
    QString urlBase;

    /*!
     *    \property port
     *    \brief ControlPoint's webserver port.
     */
    int port;

    /*!
     *    \property running
     *    \brief Bool to tell if it's running or not.
     */
    bool running;

    /*!
     *    \property webserver
     *    \brief Webserver to receive event responses.
     */
    BrisaWebserver *webserver;

    /*!
     *    \property ssdpClient
     *    \brief Listen to notify/bye-bye messages.
     */
    BrisaSSDPClient *ssdpClient;

    /*!
     *    \property msearch
     *    \brief Send msearch messages to network.
     */
    BrisaMSearchClientCP *msearch;

    /*!
     *    \property deliveryPath
     *    \brief Path to receive each event response.
     */
    int deliveryPath;

    /*!
     *    \property requests
     *    \brief Map to identify each event proxy to a number.
     */
    QMap<int, BrisaEventProxy*> requests;

    /*!
     *    \property subscriptions
     *    \brief Map to identify each subscription to an int.
     */
    QMap<QString, int> subscriptions;

    /*!
     *    \property requestsMapping
     *    \brief Map that identify each deliveryPath to a subscription.
     */
    QMap<int, int> requestsMapping;

    /*!
     *  Private function to create the UrlBase of the control point (http:// + ip + : + port)'.
     */
    void buildUrlBase();

    /*!
     *  Private function to discover the network address currently used by the machine where control
     *  point is running and select an free port to use with BrisaWebServer.
     */
    void discoverNetworkAddress();

public:

    /*!
     *  Constructor
     *  \param parent parent
     *  \param st service type
     *  \param mx interval
     */
    BrisaControlPoint(QObject *parent = 0, QString st = "ssdp:all", int mx = 5);

    /**  Destructor
     */
    ~BrisaControlPoint();

    /*!
     *  Starts the control point, the ssdpClient and the msearch
     *  \sa stop(), isRunning()
     */
    void start();

    /*!
     *  Stops the control point, the ssdpClient and the msearch
     *  \sa start(), isRunning()
     */
    void stop();

    /*!
     *  Return if the control point is running
     *  \return true if the control point is running or false otherwise
     *  \sa start(), stop()
     */
    bool isRunning();

    /*!
     *  Starts the control point msearch discover.
     */
    void discover();

    /*!
     *  Gets an event proxy to subscribe, usubscribe or renew the events from a \a service.
     *  \param service \a empty
     */
    BrisaEventProxy *getSubscriptionProxy(BrisaControlPointService *service);

signals:

    /*!
     *    \fn void BrisaControlPoint::deviceFound(BrisaControlPointDevice *device)
     *    This signal is emitted when a new device is find in network and all it's attributes are created
     *    by the xml reading.
     *    \sa deviceGone(QString usn)
     *    \param device the device that has been found
     */
    void deviceFound(BrisaControlPointDevice *device);

    /*!
     *    \fn void BrisaControlPoint::deviceGone(QString usn)
     *    This signal is emitted when a device leaves the network, that means that the the ssdp client
     *    received a "ssdp:byebye" message from the device and, to handle this, the control point emit
     *    a deviceGone event with the device's \a usn as parameter.
     *    \sa deviceFound(BrisaControlPointDevice *device)
     */
    void deviceGone(QString usn);

private slots:

    /*!
     *  Slot called when receive a newDevice event, this slot start the device's xml download.
     *  \param usn \a empty
     *  \param location \a empty
     *  \param ext \a empty
     *  \param server \a empty
     *  \param cacheControl \a empty
     */
    void deviceFound(QString usn, QString location, QString st, QString ext,
            QString server, QString cacheControl);

    /*!
     *  Slot called when ssdp client emits a removed device event, this slot emit the deviceGone signal
     *  which has as parameter the device's usn.
     *  \param usn empty
     */
    void deviceRemoved(const QString usn);

    /*!
     *  Write the content of the downloaded xml in a new xml temporary file to set the device's
     *  attributes emits the deviceFound signal when finished.
     *  \param reply \a empty
     */
    void replyFinished(QNetworkReply *reply);

    /*!
     *  Slot to get the response of the http request, made by BrisaEventProxy class and set the SID
     *  of the subscription object.
     *  \param i \a empty
     *  \param error \a empty
     */
    void httpResponse(int i, bool error);
};

}

#endif /* _BRISACONTROL_POINT_H */
