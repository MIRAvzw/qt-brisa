/*
  Copyright (C) 2010 Vinícius dos Santos Oliveira

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "httpsession.h"
#include "httpserver.h"
#include <QTcpSocket>
#include <QStateMachine>
#define DBG_PREFIX "HttpConnection: "

enum State
{
    WAITING_FOR_REQUEST_LINE,
    WAITING_FOR_HEADERS
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

    QByteArray body = r.body();

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

    qDebug("Ready read");

    switch (state) {
    case WAITING_FOR_REQUEST_LINE:
        {
            qDebug("Waiting for request line state");
            int i = buffer.indexOf("\r\n");
            if (i != -1) {
                QList<QByteArray> request = buffer.left(i).split(' ');

                if (request.size() > 1) {
                    if (request.at(0) == "GET")
                        requestInfo.setMethod(HttpRequest::GET);
                    else if (request.at(0) == "POST")
                        requestInfo.setMethod(HttpRequest::POST);
                    else {
                        // 501
                    }

                    requestInfo.setUri(request.at(1));

                    requestInfo.setHttpVersion(request.at(2).split('/').at(1).toDouble());

                    buffer.remove(0, request.at(0).size() + request.at(1).size() +
                                  request.at(2).size() + 4);

                    state = WAITING_FOR_HEADERS;
                } else {
                    // BAD REQUEST
                    qDebug(DBG_PREFIX "bad request");
                    socket->close();
                }
            }
        }
    case WAITING_FOR_HEADERS:
        {
            qDebug("waiting for headers state");
            for (int i = buffer.indexOf("\r\n") ; i != -1 ; i = buffer.indexOf("\r\n")) {
                // don't starts with \r\n
                if (i != 0) {
                    QByteArray header = buffer.mid(0, i);
                    buffer.remove(0, i + 2);

                    i = header.indexOf(':');
                    if (i > 0 && i < header.size() - 2) {
                        requestInfo.setHeader(header.left(i), header.mid(i + 2));
                    }
                } else {
                    buffer.clear();
                    state = WAITING_FOR_REQUEST_LINE;

                    onRequest(requestInfo);
                }
            }
        }
    }
}
