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

#ifndef HTTPSESSION_H
#define HTTPSESSION_H

#include <QDateTime>
#include <QThread>
#include "httprequest.h"
#include "httpresponse.h"
#include <exception>

class QTcpSocket;

class HttpSession : public QThread
{
    Q_OBJECT
public:
    explicit HttpSession(int socketDescriptor, QObject *parent = 0);
    virtual ~HttpSession();
    void run();

    // @ret should return the HTTP response status (404 not found, method not implemented,
    // ...) or 0. If a 0 is returned, the server continues to read the request, otherwise,
    // respond the request with the specified response code and closes the connection.
    // Default implementation returns 0 if version is lower or equals to the
    // last supported version or HTTP_VERSION_NOTSUPPORTED otherwise.
    // used to identify if this http request (version, method, uri, ...) is supported
    // always close the connection after respond the message
    virtual int isRequestSupported(const HttpRequest &request) const;

protected:
    // used to respond BAD_REQUESTs
    // must be set in the constructor (HttpVersion isn't thread-safe yet)
    HttpVersion lastSupportedHttpVersion;

    virtual bool hasEntityBody(const HttpRequest &request) throw(HttpResponse) = 0;
    // @ret returns true when the entity body was fully received
    // in future, the entity body should be put on qiodevice buffer, not in memory
    virtual bool atEnd(const HttpRequest &request, const QByteArray &buffer) throw(HttpResponse) = 0;
    virtual void onRequest(const HttpRequest &request) = 0;

    void writeResponse(HttpResponse);

    // the ideia is to help to implement the Object pool pattern
    // http://en.wikipedia.org/wiki/Object_pool_pattern
//    virtual bool die();

private slots:
    void onReadyRead();

private:

    QTcpSocket *socket;
    int socketDescriptor;
    HttpRequest requestInfo;
    QDateTime birthTime;
    int state;
    QByteArray buffer;
};

#endif // HTTPSESSION_H
