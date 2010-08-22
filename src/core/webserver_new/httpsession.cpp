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

// some fixes to work with bad code (alias macro preprocessor)
#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif

enum State
{
    WAITING_FOR_REQUEST_LINE,
    WAITING_FOR_HEADERS,
    WAITING_FOR_ENTITY_BODY
};

HttpSession::HttpSession(int socketDescriptor, QObject *parent) :
    QThread(parent),
    lastSupportedHttpVersion(1, 1),
    socket(NULL),
    socketDescriptor(socketDescriptor),
    state(WAITING_FOR_REQUEST_LINE),
    remainingBytes(-1)
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

bool HttpSession::isVersionSupported(const HttpVersion &version) const
{
    return version <= lastSupportedHttpVersion;
}

// the way of acquiring the number bytes sent isn't safe, and the exception
// handling too
qint64 HttpSession::writeResponse(HttpResponse r, bool closeConnection)
{
    qint64 numberBytesSent = 0;

    numberBytesSent += socket->write(r.httpVersion());
    numberBytesSent += socket->write(" ");
    numberBytesSent += socket->write(QByteArray::number(r.statusCode()));
    numberBytesSent += socket->write(" ");
    numberBytesSent += socket->write(r.reasonPhrase());
    numberBytesSent += socket->write("\r\n");

    for (QHash<QByteArray, QByteArray>::const_iterator i = r.headersBeginIterator();i != r.headersEndIterator();++i) {
        numberBytesSent += socket->write(i.key());
        if (!i.value().isNull()) {
            numberBytesSent += socket->write(": ");
            numberBytesSent += socket->write(i.value());
        } else {
            numberBytesSent += socket->write(":");
        }
        numberBytesSent += socket->write("\r\n");
    }

    numberBytesSent += socket->write("Content-Length: ");
    numberBytesSent += socket->write(QByteArray::number(r.entitySize()));

    numberBytesSent += socket->write("\r\n\r\n");

    numberBytesSent += r.entityBody(socket);

    numberBytesSent += socket->write("\r\n");

    qDebug(DBG_PREFIX "%i bytes enviados", (int)numberBytesSent);

    if (closeConnection)
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
                QList<QByteArray> request = buffer.left(i).simplified().split(' ');

                if (request.size() != 3) {
                    HttpResponse response(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST);

                    writeResponse(response, true);
                    return;
                }

                requestInfo.setMethod(request.at(0));

                requestInfo.setUri(request.at(1));

                {
                    HttpVersion version(request.at(2));

                    if (version) {
                        if (isVersionSupported(version)) {
                            requestInfo.setHttpVersion(version);
                        } else {
                            HttpResponse response(lastSupportedHttpVersion, HttpResponse::HTTP_VERSION_NOT_SUPPORTED);

                            writeResponse(response, true);
                            return;
                        }
                    } else {
                        HttpResponse response(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST);

                        writeResponse(response, true);
                        return;
                    }
                }

                buffer.remove(0, request.at(0).size() + request.at(1).size() +
                              request.at(2).size() + 4);

                state = WAITING_FOR_HEADERS;
            }
        }
    case WAITING_FOR_HEADERS:
        {
            for (int i = buffer.indexOf("\r\n") ; i != -1 ; i = buffer.indexOf("\r\n")) {
                // don't starts with \r\n
                if (i != 0) {
                    QByteArray header = buffer.left(i);
                    buffer.remove(0, i + 2);

                    i = header.indexOf(':');
                    if (i > 0) {
                        if (i + 1 < header.size())
                            requestInfo.setHeader(header.left(i).trimmed(), header.mid(i + 1).trimmed());
                        else
                            requestInfo.setHeader(header.left(i).trimmed(), QByteArray());
                    } else {
                        HttpResponse response(requestInfo.httpVersion() < lastSupportedHttpVersion ?
                                              requestInfo.httpVersion() : lastSupportedHttpVersion,
                                              HttpResponse::BAD_REQUEST);

                        writeResponse(response, true);
                        return;
                    }
                } else {
                    buffer.remove(0, 2);

                    if (hasEntityBody(requestInfo)) {
                        state = WAITING_FOR_ENTITY_BODY;
                    } else {
                        state = WAITING_FOR_REQUEST_LINE;
                        onRequest(requestInfo);
                    }
                }
            }
        }
    case WAITING_FOR_ENTITY_BODY:
        // TODO: handles other methods to discover the size of the entity body
        switch (remainingBytes) {
        case -1:
            {
                QByteArray contentLength = requestInfo.header("Content-Length");
                bool ok = !contentLength.isNull();

                if (ok) {
                    remainingBytes = contentLength.toInt(&ok);
                } else {
                    HttpResponse response(requestInfo.httpVersion() < lastSupportedHttpVersion ?
                                          requestInfo.httpVersion() : lastSupportedHttpVersion,
                                          HttpResponse::LENGTH_REQUIRED);

                    writeResponse(response, true);
                    return;
                }

                if (!ok) {
                    HttpResponse response(requestInfo.httpVersion() < lastSupportedHttpVersion ?
                                          requestInfo.httpVersion() : lastSupportedHttpVersion,
                                          HttpResponse::BAD_REQUEST);

                    writeResponse(response, true);
                    return;
                }
            }
        default:
            if (buffer.size() == remainingBytes) {
                requestInfo.setEntityBody(buffer);
                state = WAITING_FOR_REQUEST_LINE;

                onRequest(requestInfo);
            }
        }
    }
}
