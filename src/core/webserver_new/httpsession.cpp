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

int HttpSession::isRequestSupported(const HttpRequest &request) const
{
    if (request.httpVersion() <= lastSupportedHttpVersion) {
        return 0;
    } else {
        return HttpResponse::HTTP_VERSION_NOT_SUPPORTED;
    }
}

void HttpSession::writeResponse(HttpResponse r)
{
    socket->write(r.httpVersion());
    socket->write(" ");
    socket->write(QByteArray::number(r.statusCode()));
    socket->write(" ");
    socket->write(r.reasonPhrase());
    socket->write("\r\n");

    for (QHash<QByteArray, QByteArray>::const_iterator i = r.headersBeginIterator();i != r.headersEndIterator();++i) {
        socket->write(i.key());
        if (!i.value().isNull()) {
            socket->write(": ");
            socket->write(i.value());
        } else {
            socket->write(":");
        }
        socket->write("\r\n");
    }

    // this should be work of the higher-level stack
    if (r.entitySize()) {
        socket->write("Content-Length: ");
        socket->write(QByteArray::number(r.entitySize()));

        socket->write("\r\n\r\n");

        r.entityBody(socket);
    } else {
        socket->write("\r\n");
    }

    if (r.closeConnection())
        socket->close();
}

void HttpSession::onReadyRead()
{
    buffer.append(socket->readAll());

    try {
        switch (state) {
        case WAITING_FOR_REQUEST_LINE:
            {
                while (buffer.startsWith("\r\n"))
                    buffer.remove(0, 2);

                int i = buffer.indexOf("\r\n");
                if (i != -1) {
                    QList<QByteArray> request = buffer.left(i).simplified().split(' ');

                    if (request.size() != 3) {
                        writeResponse(HttpResponse(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST, true));
                        return;
                    }

                    requestInfo.setMethod(request.at(0));

                    requestInfo.setUri(request.at(1));

                    {
                        HttpVersion version(request.at(2));

                        if (version) {
                            requestInfo.setHttpVersion(version);
                        } else {
                            writeResponse(HttpResponse(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST, true));
                            return;
                        }
                    }

                    {
                        int statusCode = isRequestSupported(requestInfo);
                        if (statusCode) {
                            writeResponse(HttpResponse(lastSupportedHttpVersion, statusCode, true));
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
                            writeResponse(HttpResponse(requestInfo.httpVersion() < lastSupportedHttpVersion ?
                                                       requestInfo.httpVersion() : lastSupportedHttpVersion,
                                                       HttpResponse::BAD_REQUEST, true));
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
            if (atEnd(requestInfo, buffer)) {
                requestInfo.setEntityBody(buffer);
                buffer.clear();
                state = WAITING_FOR_REQUEST_LINE;

                onRequest(requestInfo);
            }
        }
    } catch (const HttpResponse &r) {
        r.setCloseConnection(true);
        writeResponse(r);
    }
}
