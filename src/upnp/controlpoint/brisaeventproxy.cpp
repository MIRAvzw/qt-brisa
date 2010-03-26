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

#include "brisaeventproxy.h"

using namespace BrisaUpnp;

/*!
 *    \class BrisaUpnp::BrisaEventProxy brisaeventproxy.h BrisaUpnp/BrisaEventProxy
 *
 *    Class that implements the event part in control point side in Brisa Qt, this class makes the
 *    operations of subscribe, renew subscription and unsubscribe.
 */

/*!
 *    \fn BrisaEventProxy::void eventNotification(BrisaEventProxy *subscription,
 *                             QMap<QString, QString> eventingVariables);
 *
 *    \brief Signal that is emitted when an event is received.
 */

/*!
 *    \property requestId
 *
 *    \brief id that identifies the request.
 */

/*!
 *    \property deliveryPath
 *
 *    \brief path to receive in webserver the event notifications.
 */

/*!
 *    \property host
 *
 *    \brief host to subscribe events.
 */

/*!
 *    \property port
 *
 *    \brief  port of the host to subscribe events.
 */

/*!
 *    \property http
 *
 *    \brief http object to send the event notification(subscribe i.e.)
 */

/*!
 *    \property eventSub
 *
 *    \brief path in service to subscribe events.
 */

/*!
 *    \property webServer
 *
 *    \brief Webserver to receive event responses.
 */

/*!
 *    \property eventService
 *
 *    \brief Webservice that is going to be add to web server, and will properly receive the event
 *    responses.
 */

/*!
 *    BrisaEventProxy constructor, prepare all the attribute and starts the webServer and the
 *    webService.
 */
BrisaEventProxy::BrisaEventProxy(const QStringList &callbackUrls,
                                                                       BrisaWebserver *webserver,
                                                                       int &deliveryPath,
                                                                       QString host,
                                                                       int port,
                                                                       QHttp *http,
                                                                       QString eventSub,
                                                                       QObject *parent) :
    BrisaAbstractEventSubscription(QString(), callbackUrls, -1, parent), requestId(-1),
    deliveryPath(deliveryPath), host(host), port(port), http(http), eventSub(eventSub),
    webServer(webserver)
{
    eventService = new BrisaWebService(webServer, this);
    webserver->addService(QString().setNum(deliveryPath), eventService);

    QObject::connect(eventService,
                     SIGNAL(genericRequestReceived(BrisaWebService*, QMultiHash<QString, QString>, QString)),
                     this,
                     SLOT(eventReceived(BrisaWebService*, QMultiHash<QString, QString>, QString)));
}

/*!
 *    Destructor
 */
BrisaEventProxy::~BrisaEventProxy()
{
    // TODO remove service
    delete eventService;
}

/*!
 *    Renew the subscribe in a event for the \a newTimeout passed
 */
void BrisaEventProxy::renew(const int &newTimeout)
{
    QHttpRequestHeader *renewReq = getRenewRequest(newTimeout);
    http->setHost(host, port);
    requestId = http->request(*renewReq);
    qDebug() << requestId << " renew: " << renewReq->toString();
    delete renewReq;
}

/*!
 *    Gets the request id.
 */
int BrisaEventProxy::getId()
{
    return this->requestId;
}

/*!
 *    Subscribe for the events from a service subscriptions will last the \a timeout passed.
 */
void BrisaEventProxy::subscribe(const int timeout)
{
    QHttpRequestHeader *subscribeReq = getSubscriptionRequest(timeout);
    http->setHost(host, port);
    requestId = http->request(*subscribeReq);
    qDebug() << requestId << " subscription: " << subscribeReq->toString();
    delete subscribeReq;
}

/*!
 *    Unsubscribe the events from a service, using this the user won't receive more event responses.
 */
void BrisaEventProxy::unsubscribe(void)
{
    QHttpRequestHeader *unsubscribeReq = getUnsubscriptionRequest();
    http->setHost(host, port);
    int unsubId = http->request(*unsubscribeReq);
    qDebug() << unsubId << " unsubscription: " << unsubscribeReq->toString();
    delete unsubscribeReq;
}

/*!
 *    Creates and returns a Http subscription header with the passed \a timeout
 */
QHttpRequestHeader *BrisaEventProxy::getSubscriptionRequest(const int timeout)
{
    QHttpRequestHeader *request = new QHttpRequestHeader("SUBSCRIBE", eventSub);

    // Remote host
    request->setValue("HOST", host + ":" + QString().setNum(port));

    // Our URL for receiving notifications
    const QUrl url = getUrl();

    qDebug() << "Url is" << url.host() << "porta " << url.port();
    request->setValue("CALLBACK", "<http://" + url.host() + ":" + QString().setNum(url.port()) + "/" + QString().setNum(deliveryPath) + ">");

    request->setValue("NT", "upnp:event");
    request->setValue("TIMEOUT", (timeout > 0) ? "Second-" + QString().setNum(timeout) : "INFINITE");
    return request;
}

/*!
 *    Creates and returns a Http renew subscription header with the passed \a timeout
 */
QHttpRequestHeader *BrisaEventProxy::getRenewRequest(const int timeout) const
{
    if (getSid().isEmpty()) {
        qWarning() << "Renew failed: SID field not filled.";
        return NULL;
    }

    QHttpRequestHeader *request = new QHttpRequestHeader("SUBSCRIBE", eventSub);
    request->setValue("HOST", host + ":" + port);
    request->setValue("SID", getSid());
    request->setValue("TIMEOUT", (timeout > 0) ? "Second-" + QString().setNum(timeout) : "INFINITE");
    return request;
}

/*!
 *    Creates and returns an unsubscription Http header.
 */
QHttpRequestHeader *BrisaEventProxy::getUnsubscriptionRequest() const
{
    QHttpRequestHeader *request = new QHttpRequestHeader("UNSUBSCRIBE", eventSub);
    request->setValue("HOST", host + ":" + port);
    request->setValue("SID", SID);
    return request;
}

/*!
 *    Slot to receive and treat the events that are received from \a service with the following
 *    \a headers and the \a rawData.
 */
void BrisaEventProxy::eventReceived(BrisaWebService *service, QMultiHash<QString, QString> headers, QString rawData)
{
    QString sid = headers.value("SID");

    if (sid.isEmpty()) {
        // Try "sid"
        sid = headers.value("sid");
    }

    if (sid.isEmpty()) {
        // TODO report subscription error to user
        qDebug() << "SID header not present on event subscription response.";

        foreach(QString key, headers.keys()) {
            qDebug() << key << headers.value(key);
        }

        qDebug() << "Finished printing headers..";
        qDebug() << "Raw data: " << rawData;

        return;
    }

    QDomDocument doc;
    QMap<QString, QString> eventingVariables;

    doc.setContent(rawData, false);
    QDomElement root = doc.documentElement();
    QDomNodeList list = root.elementsByTagName("e:property");

    for (int i = 0; i < list.count(); i++) {
        QDomNodeList internal = list.at(i).childNodes();

        for (int j = 0; j < internal.count(); j++) {
            QDomElement stateVariable = internal.at(j).toElement();
            eventingVariables[stateVariable.tagName()] = stateVariable.text();
        }
    }

    emit eventNotification(this, eventingVariables);

    QHttpResponseHeader responseHeader(200, "OK");
    responseHeader.setValue("Connection", "close");
    responseHeader.setValue("Content-length", "0");
    service->respond(responseHeader);
}

/*!
 *    Sets the subscription sid to the \a sid passed.
 */
void BrisaEventProxy::setSid(QString &sid) {
    SID = sid;
}
