/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventcontroller.h
 * Created:
 * Description: Defines BrisaEventController class.
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

#ifndef _BRISAEVENTCONTROLLER_H
#define _BRISAEVENTCONTROLLER_H

#include "brisaeventmessage.h"
#include "brisamulticasteventmessage.h"
#include "brisaeventsubscription.h"
#include "brisaglobal.h"
#include "brisautils.h"

#include <BrisaCore>

namespace BrisaUpnp {

#ifdef USE_NEW_BRISA_WEBSERVER

#include <QNetworkAccessManager>

    class BRISA_UPNP_EXPORT BrisaEventController: public BrisaWebService {
    Q_OBJECT

    public:
        BrisaEventController(BrisaCore::BrisaWebserver *sessionManager,
                QList<BrisaStateVariable *> *stateVariableList, QObject *parent = 0);
        ~BrisaEventController();

    public slots:
        void variableChanged(BrisaStateVariable *variable);

        void subscribe(const QMultiHash<QString, QString> &subscriberInfo,
                int sessionId, int requestId);

        void unsubscribe(const QMultiHash<QString, QString> &subscriberInfo,
                int sessionId, int requestId);

        void parseGenericRequest(const HttpRequest &request);

    private:
        BrisaEventController(const BrisaEventController &);

        void sendEvent(const BrisaEventMessage &message, const QUrl &url);

        void sendMulticastEvent(const BrisaMulticastEventMessage &message);

        QStringList getEventUrls(const QString &urls);

        int getTimeOut(const QString &timeout);

        QHttpResponseHeader getErrorHeader(const int &errorCode,
                const QString &errorMessage);

        QList<BrisaEventSubscription *> subscriptions;

        QList<BrisaStateVariable *> *variableList;

        QNetworkAccessManager httpClient;

        QUdpSocket udpSocket;
    };

#else

// TODO: remove using statements from the .h file
using BrisaCore::BrisaWebService;
using BrisaCore::BrisaWebServiceProvider;
using BrisaCore::BrisaWebserver;

/*!
 * \internal
 * \class BrisaUpnp::BrisaEventController
 *
 * \brief Handles the event subscriptions and event messages for the service.
 */

class BRISA_UPNP_EXPORT BrisaEventController: public BrisaWebService {
Q_OBJECT

public:
    BrisaEventController(QxtAbstractWebSessionManager *sessionManager,
	    QList<BrisaStateVariable *> *stateVariableList, QObject *parent = 0);
    /*!
     * Destructor.
     */
    ~BrisaEventController();

public slots:
    /*!
     * Slot that shall be called when some service's state \a variable change.
     */
    void variableChanged(BrisaStateVariable *variable);
    /*!
     * Creates a subscription for the given \a subscriberInfo, \a sessionId and
     * \a requestId.
     */
    void subscribe(const QMultiHash<QString, QString> &subscriberInfo,
            int sessionId, int requestId);
    /*!
     * Removes the subscription for the given \a subscriberInfo, \a sessionId and
     * \a requestId.
     */
    void unsubscribe(const QMultiHash<QString, QString> &subscriberInfo,
            int sessionId, int requestId);

    /*!
     * Parses a generic request to web service and calls the local related methods
     * as necessary.
     */
    void parseGenericRequest(const QString &method, const QMultiHash<QString,
            QString> &headers, const QByteArray &requestContent, int sessionId,
            int requestId);

signals:

private slots:

private:

    /*!
     * Constructs a service's event controller with the given \a sessionManager, service's \a stateVariableList and \a parent.
     */
    BrisaEventController(const BrisaEventController &);

    /*!
     * Sends the event \a message to the given \a url.
     */
    void sendEvent(const BrisaEventMessage &message, const QUrl &url);

    /*!
     * Sends the multicast event \a message.
     */
    void sendMulticastEvent(const BrisaMulticastEventMessage &message);

    /*!
     * Parses the event \a urls of a subscription request from the CALLBACK header
     * value.
     */
    QStringList getEventUrls(const QString &urls);

    /*!
     * Parses the \a timeout of a subscription request from the TIMEOUT header
     * value.
     */
    int getTimeOut(const QString &timeout);

    /*!
     * Returns a header for error messages with the given \a errorCode and
     * \a errorMessage.
     */
    QHttpResponseHeader getErrorHeader(const int &errorCode,
            const QString &errorMessage);

    /*!
     * \property subscriptions
     *
     * \brief the list of subscriptions to the service's events
     */
    QList<BrisaEventSubscription *> subscriptions;

    /*!
     * \property variableList
     *
     * \brief the list of the service's state variables
     */
    QList<BrisaStateVariable *> *variableList;

    /*!
     * \property httpClient
     *
     * \brief the http client that will be used to send the events to the
     * subscribers
     */
    QHttp httpClient;

    QUdpSocket udpSocket;
};

#endif // USE_NEW_BRISA_WEBSERVER

}

#endif /* _BRISAEVENTCONTROLLER_H */
