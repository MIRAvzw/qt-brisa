/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventproxy.cpp
 * Created:
 * Description: Implementation of BrisaEventProxy class.
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
#include "brisaeventproxy.h"

#include <brisawebserversession.h>

using namespace Brisa;

BrisaEventProxy::BrisaEventProxy(const QStringList &callbackUrls,
                                 BrisaWebserver *webserver,
                                 int &deliveryPath,
                                 QString host, 
                                 int port,
                                 QHttp *http,
                                 QString eventSub,
                                 QObject *parent) :
    BrisaAbstractEventSubscription(QString(), callbackUrls, -1, parent),
    requestId(-1),
    deliveryPath(deliveryPath),
    host(host),
    port(port),
    http(http),
    eventSub(eventSub),
    webServer(webserver)
{
}

BrisaEventProxy::~BrisaEventProxy() {
}

void BrisaEventProxy::renew(const int &newTimeout) {
    QHttpRequestHeader *renewReq = getRenewRequest(newTimeout);
    http->setHost(host, port);
    requestId = http->request(*renewReq);
    qDebug() << requestId << " renew: " << renewReq->toString();
    delete renewReq;
}

int BrisaEventProxy::getId() {
    return this->requestId;
}

void BrisaEventProxy::subscribe(const int timeout) {
    QHttpRequestHeader *subscribeReq = getSubscriptionRequest(timeout);
    http->setHost(host, port);
    requestId = http->request(*subscribeReq);
    qDebug() << requestId << " subscription: " << subscribeReq->toString();
    delete subscribeReq;
}

void BrisaEventProxy::unsubscribe(void) {
    QHttpRequestHeader *unsubscribeReq = getUnsubscriptionRequest();
    http->setHost(host, port);
    int unsubId = http->request(*unsubscribeReq);
    qDebug() << unsubId << " unsubscription: " << unsubscribeReq->toString();
    delete unsubscribeReq;
}

QHttpRequestHeader *BrisaEventProxy::getSubscriptionRequest(const int timeout) {
    QHttpRequestHeader *request = new QHttpRequestHeader("SUBSCRIBE", eventSub);

    // Remote host
    request->setValue("HOST", host + ":" + QString().setNum(port));

    // Our URL for receiving notifications
    const QUrl url = this->getUrl();

    qDebug() << "Url: " << url.host() << " port: " << url.port();
    request->setValue("CALLBACK", "<http://"
                                    + url.host()
                                    + ":"
                                    + QString().setNum(url.port())
                                    + "/"
                                    + QString().setNum(deliveryPath)
                                    + ">");

    request->setValue("NT", "upnp:event");
    request->setValue("TIMEOUT", (timeout > 0)
                                    ? "Second-" + QString().setNum(timeout)
                                    : "INFINITE"); // INFINITE is obsolete in UPnP 1.1
    return request;
}

QHttpRequestHeader *BrisaEventProxy::getRenewRequest(const int timeout) const {
    if (this->getSid().isEmpty()) {
        qWarning() << "Renew failed: SID field not filled.";
        return NULL;
    }

    QHttpRequestHeader *request = new QHttpRequestHeader("SUBSCRIBE", eventSub);
    request->setValue("HOST", host + ":" + port);
    request->setValue("SID", getSid());
    request->setValue("TIMEOUT", (timeout > 0)
                                    ? "Second-" + QString().setNum(timeout)
                                    : "INFINITE");
    return request;
}

QHttpRequestHeader *BrisaEventProxy::getUnsubscriptionRequest() const {
    QHttpRequestHeader *request = new QHttpRequestHeader("UNSUBSCRIBE", eventSub);
    request->setValue("HOST", this->host + ":" + this->port);
    request->setValue("SID", this->SID);
    return request;
}

void BrisaEventProxy::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    QByteArray sid = request.header("SID");

    if (sid.isEmpty()) {
        // TODO report subscription error to user and should close the connection too
        qDebug() << "SID header not present on event subscription response.";

        return;
    }

    QDomDocument doc;
    QMap<QString, QString> eventingVariables;

    doc.setContent(request.entityBody(), false);
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

    HttpResponse response(request.httpVersion(), HttpResponse::OK, true);
    response.setHeader("CONNECTION", "close");
    response.setHeader("CONTENT-LENGTH", "0");
    session->respond(response);
}

void BrisaEventProxy::setSid(QString &sid) {
    this->SID = sid;
}
