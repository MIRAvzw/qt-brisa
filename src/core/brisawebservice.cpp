/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Authors: Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com> 2010
 *
 * Copyright (C) <2010> <Pervasive Computing Laboratory @ Federal
 * University of Alagoas>
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

#include "brisawebservice.h"
using namespace BrisaCore;

#ifdef USE_NEW_BRISA_WEBSERVER

BrisaWebService::BrisaWebService(QObject *parent = 0) :
    QObject(parent),
    server(NULL)
{
}

BrisaWebService::~BrisaWebService()
{
}

void BrisaWebService::postRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    onRequest(request, session);
}

void BrisaWebService::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    emit genericRequestReceived(request, session);
}

#else

BrisaWebService::BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent) :
                QxtWebServiceDirectory(sm, parent)
{
}

void BrisaWebService::pageRequestedEvent(QxtWebRequestEvent *event)
{
    this->sessionID = event->sessionID;
    this->requestID = event->requestID;

    QByteArray requestContent("");
    if (event->content) {
         event->content->waitForAllContent();
         requestContent = event->content->readAll();
    }
    emit genericRequestReceived(event->method,
                                event->headers,
                                requestContent,
                                event->sessionID,
                                event->requestID);
    emit genericRequestReceived(this, event->headers, requestContent);

    if (event->method == "GET")
        postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, DEFAULT_PAGE));
}

void BrisaWebService::respond(QByteArray response)
{
    this->respond(response, this->sessionID, this->requestID);
}

void BrisaWebService::respond(const QByteArray &response, const int &sessionId, const int &requestId)
{
    this->postEvent(new QxtWebPageEvent(sessionId, requestId, response));
}

void BrisaWebService::respond(const QHttpResponseHeader &response)
{
    this->respond(response, this->sessionID, this->requestID);
}

void BrisaWebService::respond(const QHttpResponseHeader &response, const int &sessionId,
                     const int &requestId)
{
    QxtWebPageEvent *event = new QxtWebPageEvent(sessionId, requestId, "");

    event->status = response.statusCode();
    event->statusMessage = response.reasonPhrase().toAscii();

    // Set key-value pairs from header to event's headers
    // it is done because LibQxt's events cannot receive QHttpResponseHeaders
    QList<QPair<QString, QString> > headerValues = response.values();
    for (QList<QPair<QString, QString> >::iterator i = headerValues.begin();
    i != headerValues.end(); ++i) {
        event->headers.insertMulti(i->first, i->second);
    }

    this->postEvent(event);
}

#endif
