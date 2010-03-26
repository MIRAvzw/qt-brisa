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

#include <QDebug>

#include "brisaeventcontroller.h"

using namespace BrisaUpnp;

#define ERROR_400_MESSAGE "Bad Request"
#define ERROR_412_MESSAGE "Precondition Failed"

/*!
 * \internal
 * \class BrisaUpnp::BrisaEventController
 *
 * \brief Handles the event subscriptions and event messages for the service.
 */

/*!
 * \property subscriptions
 *
 * \brief the list of subscriptions to the service's events
 */ 

/*!
 * \property variableList
 *
 * \brief the list of the service's state variables
 */ 

/*!
 * \property httpClient
 *
 * \brief the http client that will be used to send the events to the
 * subscribers
 */


/*!
 * Constructs a service's event controller with the given \a sessionManager, service's \a stateVariableList and \a parent.
 */
BrisaEventController::BrisaEventController(QxtAbstractWebSessionManager *sessionManager,
                                           QList<BrisaStateVariable *> *stateVariableList,
                                           QObject *parent) :
    BrisaWebService(sessionManager, parent),
    variableList(stateVariableList)
{
      QObject::connect(this, SIGNAL(genericRequestReceived(const QString &,
                                                           const QMultiHash<QString, QString> &,
                                                           const QByteArray &, int, int)),
                       this, SLOT(parseGenericRequest(const QString &,
                                                      const QMultiHash<QString, QString> &,
                                                      const QByteArray &, int, int)));
}

/*!
 * Destructor.
 */
BrisaEventController::~BrisaEventController()
{
    while (!subscriptions.empty())
        delete subscriptions.takeFirst();
}


/*!
 * Parses a generic request to web service and calls the local related methods
 * as necessary.
 */
void BrisaEventController:: parseGenericRequest(const QString &method,
                                                const QMultiHash<QString, QString> &headers,
                                                const QByteArray &requestContent,
                                                int sessionId,
                                                int requestId)
{
    Q_UNUSED(requestContent);

    if (method == "SUBSCRIBE") {
        subscribe(headers, sessionId, requestId);
    } else if (method == "UNSUBSCRIBE") {
        unsubscribe(headers, sessionId, requestId);
    }
}

/*!
 * Slot that shall be called when some service's state \a variable change.
 */
void BrisaEventController::variableChanged(BrisaStateVariable *variable)
{
    QList<BrisaStateVariable *> variables;
    variables.append(variable);

    for (QList<BrisaEventSubscription *>::iterator i = subscriptions.begin();
         i != subscriptions.end(); ++i)
    {
        // Remove expired subscriptions
        if ((*i)->hasExpired()) {
            qDebug() << "Removing subscription:" << (*i)->getSid();
            delete *i;
            subscriptions.erase(i);

            continue; 
        }

        BrisaEventMessage message(*(*i), &variables);
        this->sendEvent(message, (*i)->getUrl());
    }
}

/*!
 * Sends the event \a message to the given \a url.
 */
void BrisaEventController::sendEvent(const BrisaEventMessage &message, const QUrl &url)
{
    httpClient.setHost(url.host(), url.port());
    httpClient.request(message.getMessageHeader(), message.getMessageBody());

    qDebug() << "BrisaEventController Sending event to "
             << message.getMessageHeader().value("SID")
             << "at Host: " << url.host() << ":" << url.port();
}

/*!
 * Creates a subscription for the given \a subscriberInfo, \a sessionId and
 * \a requestId.
 */
void BrisaEventController::subscribe(const QMultiHash<QString, QString> &subscriberInfo,
                                     int sessionId,
                                     int requestId)
{
    if (subscriberInfo.contains("SID")) {  //Then it's probably a renewal request.
        if (subscriberInfo.contains("NT") || subscriberInfo.contains("CALLBACK")) {
            respond(getErrorHeader(400, ERROR_400_MESSAGE), sessionId, requestId);
            return;
        }

        if (subscriberInfo.value("SID") == "") {
            respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);
            return;
        }

        bool validSubscription = false;
        foreach (BrisaEventSubscription *current, subscriptions) {
            if (current->getSid() == subscriberInfo.value("SID")) {
                current->renew(getTimeOut(subscriberInfo.value("TIMEOUT")));

                qDebug() << "BrisaEventController renewing subscription for "
                         << subscriberInfo.value("SID");
                validSubscription = true;

                respond(current->getAcceptSubscriptionResponse(), sessionId, requestId);
            }
        }

        if (!validSubscription)
            respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);

        return;
    } else if (subscriberInfo.contains("NT") && subscriberInfo.contains("CALLBACK")) {

        if (subscriberInfo.value("NT") != "upnp:event") {
            respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);
            return;
        }

        qDebug() << "BrisaEventController received a subscription request:"
        " Callback: " << subscriberInfo.value("CALLBACK") <<
        "- Timeout: " << subscriberInfo.value("TIMEOUT");

        BrisaEventSubscription *newSubscriber = new BrisaEventSubscription(getUuid(),
                                                                           getEventUrls(subscriberInfo.value("CALLBACK")),
                                                                           getTimeOut(subscriberInfo.value("TIMEOUT")));

        subscriptions.append(newSubscriber);
        respond(newSubscriber->getAcceptSubscriptionResponse(), sessionId, requestId);

        BrisaEventMessage *message = new BrisaEventMessage(*newSubscriber, this->variableList);
        sendEvent(*message, newSubscriber->getUrl());
        delete message;

        return;
    } else {
        respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);
    }
}

/*!
 * Removes the subscription for the given \a subscriberInfo, \a sessionId and
 * \a requestId.
 */
void BrisaEventController::unsubscribe(const QMultiHash<QString, QString> &subscriberInfo,
                                       int sessionId,
                                       int requestId)
{
     if (subscriberInfo.contains("SID")) {
        if (subscriberInfo.contains("NT") || subscriberInfo.contains("CALLBACK")){
            respond(getErrorHeader(400, ERROR_400_MESSAGE), sessionId, requestId);
            return;
        }

        if (subscriberInfo.value("SID") == "") {
            respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);
            return;
        }

        bool validSubscription = false;
        for (int i = 0; i < subscriptions.size(); ++i) {
            if (("uuid:"+subscriptions.at(i)->getSid()) == subscriberInfo.value("SID")) {
                respond(subscriptions.at(i)->getAcceptUnsubscriptionResponse(), sessionId, requestId);

                delete subscriptions.at(i);
                subscriptions.removeAt(i);

                qDebug() << "BrisaEventController canceling subscription for "
                         << subscriberInfo.value("SID");

                validSubscription = true;
            }
        }

        if (!validSubscription)
            respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);

    } else {
        respond(getErrorHeader(412, ERROR_412_MESSAGE), sessionId, requestId);
    }
}

/*!
 * Returns a header for error messages with the given \a errorCode and
 * \a errorMessage.
 */
QHttpResponseHeader BrisaEventController::getErrorHeader(const int &errorCode,
                                                         const QString &errorMessage)
{
    return QHttpResponseHeader(errorCode, errorMessage);
}

/*!
 * Parses the event \a urls of a subscription request from the CALLBACK header
 * value.
 */
QStringList BrisaEventController::getEventUrls(const QString &urls)
{
    QList<QString> urlList;
    QStringList list = urls.split(">", QString::SkipEmptyParts);
    list.replaceInStrings("<", "");
    return list;
}

/*!
 * Parses the \a timeout of a subscription request from the TIMEOUT header
 * value.
 */
int BrisaEventController::getTimeOut(const QString &timeout)
{
    QString returnTime = timeout;
    returnTime.remove("Second-");
    bool ok;
    return returnTime.toInt(&ok, 10);
}

/*!
 * Generates random uuids.
 */
QString BrisaEventController::getUuid()
{
    QString uuid = QUuid::createUuid().toString();
    uuid.remove("{");
    uuid.remove("}");
    return uuid;
}

