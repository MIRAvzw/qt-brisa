/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventcontroller.cpp
 * Created:
 * Description: Implements BrisaEventController class.
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

#include <QDebug>

#include "brisaeventcontroller.h"

#include "brisawebserversession.h"

using namespace Brisa;

BrisaEventController::BrisaEventController(
        BrisaWebserver *sessionManager,
        QList<BrisaStateVariable *> *stateVariableList,
        QObject *parent) :
        BrisaWebService(parent),
        variableList(stateVariableList)
{
    udpSocket.bind(QHostAddress("239.255.255.246"), 7900);
}

void BrisaEventController::onRequest(const HttpRequest &r,
                                     BrisaWebserverSession *session)
{
    if (r.method() == "SUBSCRIBE") {
        subscribe(r, session);
    } else if (r.method() == "UNSUBSCRIBE") {
        unsubscribe(r, session);
    }
}

inline void BrisaEventController::subscribe(const HttpRequest &request,
                                            BrisaWebserverSession *session)
{
    const QHash<QByteArray, QByteArray> headers = request.headers();
    if (headers.contains("SID")) { //Then it's probably a renewal request.
        if (headers.contains("NT") || headers.contains("CALLBACK")) {
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::BAD_REQUEST,
                                          true));
            return;
        }

        if (headers.value("SID").isEmpty()) {
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::PRECONDITION_FAILED,
                                          true));
            return;
        }

        bool validSubscription = false;
        foreach (BrisaEventSubscription *current, subscriptions)
        {
            if (current->getSid() == headers.value("SID")) {
                current->renew(getTimeOut(headers.value("TIMEOUT")));

                qDebug()
                        << "BrisaEventController renewing subscription for "
                        << headers.value("SID");
                validSubscription = true;

                session->respond(current->getAcceptSubscriptionResponse());
            }
        }

        if (!validSubscription)
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::PRECONDITION_FAILED));

        return;
    } else if (headers.contains("NT") && headers.contains("CALLBACK")) {

        if (headers.value("NT") != "upnp:event") {
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::PRECONDITION_FAILED));
            return;
        }

        qDebug() << "BrisaEventController received a subscription request:"
            " Callback: " << headers.value("CALLBACK") << "- Timeout: "
                << headers.value("TIMEOUT");

        BrisaEventSubscription *newSubscriber = new BrisaEventSubscription(
                getUuid(), getEventUrls(headers.value("CALLBACK")),
                getTimeOut(headers.value("TIMEOUT")));

        subscriptions.append(newSubscriber);
        session->respond(newSubscriber->getAcceptSubscriptionResponse());

        BrisaEventMessage *message = new BrisaEventMessage(*newSubscriber,
                                                           this->variableList);
        sendEvent(*message, newSubscriber->getUrl());
        delete message;

        return;
    } else {
        session->respond(HttpResponse(request.httpVersion(),
                                      HttpResponse::PRECONDITION_FAILED));
    }
}

inline void BrisaEventController::unsubscribe(const HttpRequest &request,
                                              BrisaWebserverSession *session)
{
    const QHash<QByteArray, QByteArray> headers = request.headers();
    if (headers.contains("SID")) {
        if (headers.contains("NT") || headers.contains("CALLBACK")) {
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::BAD_REQUEST));
            return;
        }

        if (headers.value("SID").isEmpty()) {
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::PRECONDITION_FAILED,
                                          true));
            return;
        }

        bool validSubscription = false;
        for (int i = 0; i < subscriptions.size(); ++i) {
            if (("uuid:" + subscriptions.at(i)->getSid()).toUtf8()
                == headers.value("SID")) {
                session->respond(subscriptions.at(i)
                                 ->getAcceptUnsubscriptionResponse());

                delete subscriptions.at(i);
                subscriptions.removeAt(i);

                qDebug() << "BrisaEventController canceling subscription for "
                        << headers.value("SID");

                validSubscription = true;
            }
        }

        if (!validSubscription)
            session->respond(HttpResponse(request.httpVersion(),
                                          HttpResponse::PRECONDITION_FAILED,
                                          true));

    } else {
        session->respond(HttpResponse(request.httpVersion(),
                                      HttpResponse::PRECONDITION_FAILED));
    }
}

void BrisaEventController::sendEvent(const BrisaEventMessage &message, const QUrl &url)
{
    QTcpSocket *socket = new QTcpSocket(this);

    socket->connectToHost(url.host(), url.port());

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), socket, SLOT(deleteLater()));

    socket->write(message.getRequestMessage());

    qDebug() << "BrisaEventController sending event to "
             << message.getSid() << " at Host: "
             << url.host() << ":" << url.port();
}

BrisaEventController::~BrisaEventController()
{
    qDeleteAll(this->subscriptions);
    this->subscriptions.clear();
}

void BrisaEventController::variableChanged(BrisaStateVariable *variable)
{
    if (variable->multicastEvents()) {
        BrisaMulticastEventMessage message(variable, "upnp:/general");
        sendMulticastEvent(message);
    }
    QList<BrisaStateVariable *> variables;
    variables.append(variable);

    for (QList<BrisaEventSubscription *>::iterator i = this->subscriptions.begin(); i != this->subscriptions.end(); ++i) {
        // Remove expired subscriptions
        if ((*i)->hasExpired()) {
            qDebug() << "Removing subscription:" << (*i)->getSid();
            delete *i;
            this->subscriptions.erase(i);
            continue;
        }
        BrisaEventMessage message(*(*i), &variables);
        this->sendEvent(message, (*i)->getUrl());
    }
}

void BrisaEventController::sendMulticastEvent(const BrisaMulticastEventMessage &message)
{
    udpSocket.writeDatagram(message.getMessageHeader().toString().toUtf8() +
                            message.getMessageBody(),
                            QHostAddress("239.255.255.246"), 7900);

    qDebug() << "BrisaEventController sending multicast event";
}

QStringList BrisaEventController::getEventUrls(const QString &urls)
{
    QList<QString> urlList;
    QStringList list = urls.split(">", QString::SkipEmptyParts);
    list.replaceInStrings("<", "");
    return list;
}

int BrisaEventController::getTimeOut(const QString &timeout) {
    QString returnTime = timeout;
    returnTime.remove("Second-");
    bool ok;
    return returnTime.toInt(&ok, 10);
}
