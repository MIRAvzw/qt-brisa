/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventproxy.h
 * Created:
 * Description: Definition of BrisaEventProxy class.
 * Authors: Name <email> @since 2009
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
#ifndef _BRISAEVENTPROXY_H
#define _BRISAEVENTPROXY_H

#include "brisaabstracteventsubscription.h"
#include "brisaglobal.h"

#include <BrisaCore>

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>
#include <QtXml>

namespace BrisaUpnp {

using BrisaCore::BrisaWebserver;
using BrisaCore::BrisaWebService;

/*!
 *  \class BrisaUpnp::BrisaEventProxy brisaeventproxy.h BrisaUpnp/BrisaEventProxy
 *  Class that implements the event part in control point side in Brisa Qt, this class makes the
 *  operations of subscribe, renew subscription and unsubscribe.
 */
class BRISA_UPNP_EXPORT BrisaEventProxy: virtual public BrisaAbstractEventSubscription
{
Q_OBJECT

public:
    friend class BrisaControlPoint;

    /*!
     *  Destructor
     */
    virtual ~BrisaEventProxy();

    /*!
     *  Gets the request id.
     */
    int getId();

    /*!
     *  Renew the subscribe in a event for the \a newTimeout passed
     *  \param newTimeout new timeout. Less than 0 to infinite
     */
    void renew(const int &newTimeout = -1);

    /*!
     *  Subscribe for the events from a service subscriptions will last the \a timeout passed.
     *  \param timeout timeout
     */
    void subscribe(const int timeout = -1);

    /*!
     *  Unsubscribe the events from a service, using this the user won't receive more event responses.
     */
    void unsubscribe();

signals:
    /*!
     *  \fn BrisaEventProxy::void eventNotification(BrisaEventProxy *subscription,
     *                           QMap<QString, QString> eventingVariables);
     *
     *  \brief Signal that is emitted when an event is received.
     */
    void eventNotification(BrisaEventProxy *subscription,
            QMap<QString, QString> eventingVariables);

#ifdef USE_NEW_BRISA_WEBSERVER
protected:
    void onRequest(const HttpRequest &request, BrisaCore::BrisaWebserverSession *session);
#endif

private:
    /*!
     *  BrisaEventProxy constructor, prepare all the attribute and starts the webServer and the
     *  webService.
     */
    BrisaEventProxy(const QStringList &callbackUrls,
                    BrisaWebserver *webserver,
                    int &deliveryPath,
                    QString host,
                    int port,
                    QHttp *http,
                    QString eventSub,
                    QObject *parent = 0);

    /*!
     *  \property requestId
     *  \brief id that identifies the request.
     */
    int requestId;

    /*!
     *  \property deliveryPath
     *  \brief path to receive in webserver the event notifications.
     */
    int deliveryPath;

    /*!
     *  \property host
     *  \brief host to subscribe events.
     */
    QString host;

    /*!
     *  \property port
     *  \brief  port of the host to subscribe events.
     */
    int port;

    /*!
     *  \property http
     *  \brief http object to send the event notification(subscribe i.e.)
     */
    QHttp *http;

    /*!
     *  \property eventSub
     *  \brief path in service to subscribe events.
     */
    QString eventSub;

    /*!
     *  \property webServer
     *  \brief Webserver to receive event responses.
     */
    BrisaWebserver *webServer;

#ifndef USE_NEW_BRISA_WEBSERVER
    
    /*!
     *  \property eventService
     *  \brief Webservice that is going to be add to web server, and will properly receive the event
     *  responses.
     */
    BrisaWebService *eventService;

#endif

    /*!
     *  Creates and returns a Http subscription header with the passed \a timeout
     *  \param timeout timeout
     *  \return Http subscription header with passed timeout
     */
    QHttpRequestHeader *getSubscriptionRequest(const int timeout);

    /*!
     *    Creates and returns an unsubscription Http header.
     *    \param unsubscription Http header
     */
    QHttpRequestHeader *getUnsubscriptionRequest() const;

    /*!
     *  Creates and returns a Http renew subscription header with the passed \a timeout
     *  \param timeout timeout
     *  \return Http renew subscription header with passed timeout
     */
    QHttpRequestHeader *getRenewRequest(const int timeout) const;

    /*!
     *  Sets the subscription sid.
     *  \param sid sid
     */
    void setSid(QString &sid);

#ifndef USE_NEW_BRISA_WEBSERVER
private slots:

    /*!
     *  Slot to receive and treat the events that are received from \a service with the following
     *  \a headers and the \a rawData.
     *  \param service service
     *  \param headers headers
     *  \param rawData rawData
     */
    void eventReceived(BrisaWebService *service,
            QMultiHash<QString, QString> headers, QString rawData);
#endif
};

}

#endif /* _BRISAEVENTPROXY_H */
