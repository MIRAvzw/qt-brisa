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

#include "httpsession.h"
#include "httpserver.h"
#include <QTcpSocket>
#include <QStateMachine>
#define DBG_PREFIX "HttpConnection: "

enum State
{
    WAITING_FOR_REQUEST_LINE,
    WAITING_FOR_HEADERS,
    WAITING_FOR_ENTITY_BODY
};

HttpSession::HttpSession(int socketDescriptor, QObject *parent) :
    QThread(parent),
    socket(NULL),
    socketDescriptor(socketDescriptor),
    state(WAITING_FOR_REQUEST_LINE)
{
}

HttpSession::~HttpSession()
{
    qDebug(DBG_PREFIX "Dying");
}

void HttpSession::run()
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(destroyed()), this, SLOT(quit()));
    socket->setSocketDescriptor(socketDescriptor);

    exec();
}

qint64 HttpSession::writeResponse(HttpResponse r)
{
    qint64 numberBytesSent = 0;
    if (r.httpVersion().minor() == 1)
        numberBytesSent += socket->write("HTTP/1.1 ");
    else
        numberBytesSent += socket->write("HTTP/1.0 ");

    qDebug(DBG_PREFIX "status code: %i", r.statusCode());
    qDebug(DBG_PREFIX "Reason Phrase: %s", r.reasonPhrase().constData());

    numberBytesSent += socket->write(QByteArray::number(r.statusCode()));
    numberBytesSent += socket->write(" ");
    numberBytesSent += socket->write(r.reasonPhrase());
    numberBytesSent += socket->write("\r\n");

    {
        QHash<QByteArray, QByteArray> headers = r.headers();
        for (QHash<QByteArray, QByteArray>::iterator i = headers.begin();i != headers.end();++i) {
            qDebug(DBG_PREFIX "%s: %s", i.key().constData(), i.value().constData());
            numberBytesSent += socket->write(i.key());
            numberBytesSent += socket->write(": ");
            numberBytesSent += socket->write(i.value());
            numberBytesSent += socket->write("\r\n");
        }
    }

    QByteArray body = r.entityBody();

    numberBytesSent += socket->write("Content-Length: ");
    numberBytesSent += socket->write(QByteArray::number(body.size()));

    numberBytesSent += socket->write("\r\n\r\n");

    numberBytesSent += socket->write(body);

    numberBytesSent += socket->write("\r\n");

    qDebug(DBG_PREFIX "%i bytes enviados", (int)numberBytesSent);

    // HTTP 1.0
    if (r.httpVersion().minor() == 0)
        socket->close();

    return numberBytesSent;
}

void HttpSession::onReadyRead()
{
    buffer.append(socket->readAll());

    switch (state) {
    case WAITING_FOR_REQUEST_LINE:
        {
            int i = buffer.indexOf("\r\n");
            if (i != -1) {
                QList<QByteArray> request = buffer.left(i).split(' ');

                requestInfo.setHttpVersion(request.at(2).split('/').at(1).toDouble());

                if (requestInfo.httpVersion().major() > 1) {
                    HttpResponse response(HttpVersion(1, 1), HttpResponse::HTTP_VERSION_NOT_SUPPORTED);

                    writeResponse(response);
                    socket->close();
                    return;
                }

                if (request.size() > 1) {
                    if (request.at(0) == "GET")
                        requestInfo.setMethod(HttpRequest::GET);
                    else if (request.at(0) == "POST")
                        requestInfo.setMethod(HttpRequest::POST);
                    else if (request.at(0) == "HEAD")
                        requestInfo.setMethod(HttpRequest::HEAD);
                    else if (request.at(0) == "PUT")
                        requestInfo.setMethod(HttpRequest::PUT);
                    else if (request.at(0) == "DELETE")
                        requestInfo.setMethod(HttpRequest::DELETE);
                    else if (request.at(0) == "TRACE")
                        requestInfo.setMethod(HttpRequest::TRACE);
                    else if (request.at(0) == "OPTIONS")
                        requestInfo.setMethod(HttpRequest::OPTIONS);
                    else if (request.at(0) == "CONNECT")
                        requestInfo.setMethod(HttpRequest::CONNECT);
                    else if (request.at(0) == "PATCH")
                        requestInfo.setMethod(HttpRequest::PATCH);
                    else if (requestInfo.httpVersion().minor() > 1) {
                        HttpResponse response(HttpVersion(1, 1), HttpResponse::NOT_IMPLEMENTED);

                        response.setHeader("Connection", "close");

                        writeResponse(response);
                        socket->close();
                        return;
                    } else {
                        HttpResponse response(requestInfo.httpVersion(), HttpResponse::BAD_REQUEST);

                        if (requestInfo.httpVersion().minor() == 1)
                            response.setHeader("Connection", "close");

                        writeResponse(response);
                        socket->close();
                        return;
                    }

                    requestInfo.setUri(request.at(1));

                    buffer.remove(0, request.at(0).size() + request.at(1).size() +
                                  request.at(2).size() + 4);

                    state = WAITING_FOR_HEADERS;
                } else {
                    HttpResponse response(HttpVersion(1, 0), HttpResponse::BAD_REQUEST);

                    writeResponse(response);
                    socket->close();
                    return;
                }
            }
        }
    case WAITING_FOR_HEADERS:
        {
            for (int i = buffer.indexOf("\r\n") ; i != -1 ; i = buffer.indexOf("\r\n")) {
                // don't starts with \r\n
                if (i != 0) {
                    QByteArray header = buffer.mid(0, i);
                    buffer.remove(0, i + 2);

                    i = header.indexOf(':');
                    if (i > 0) {
                        if (i + 1 < header.size())
                            requestInfo.setHeader(header.left(i), header.mid(i + 1));
                        else
                            requestInfo.setHeader(header.left(i), QByteArray());
                    }
                } else {
                    int versionMinor = requestInfo.httpVersion().minor();
                    if (versionMinor == 0 || ((versionMinor > 0) && !requestInfo.header("Host").isNull())) {
                        // TODO: remove only the consumed piece of the buffer
                        buffer.clear();
                        state = WAITING_FOR_REQUEST_LINE;

                        pageRequest(requestInfo);
                    } else {
                        HttpResponse response(HttpVersion(1, 1), HttpResponse::BAD_REQUEST);

                        writeResponse(response);
                        socket->close();
                    }
                }
            }
        }
    case WAITING_FOR_ENTITY_BODY:
        ;// TODO: store the body to requestInfo.m_entity
    }
}
