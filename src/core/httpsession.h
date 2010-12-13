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

#include <QObject>
#include <QDateTime>
#include "httprequest.h"
#include "httpresponse.h"

class QTcpSocket;

namespace Brisa {

class HttpSessionManager;

class BRISA_CORE_EXPORT HttpSession: public QObject
{
Q_OBJECT
public:
    explicit HttpSession(HttpSessionManager *sessionManager);
    virtual ~HttpSession();

    void setSession(int socketDescriptor);

    // @ret should return the HTTP response status (404 not found, method not implemented,
    // ...) or 0. If a 0 is returned, the server continues to read the request, otherwise,
    // respond the request with the specified response code and closes the connection.
    // Default implementation returns 0 if version is lower or equals to the
    // last supported version or HTTP_VERSION_NOTSUPPORTED otherwise.
    // used to identify if this http request (version, method, uri, ...) is supported
    // always close the connection after respond the message
    virtual int isRequestSupported(const HttpRequest &request) const;

protected slots:
    void writeResponse(HttpResponse);

protected:
    // used to respond BAD_REQUESTs
    // must be set in the constructor (HttpVersion isn't thread-safe yet)
    HttpVersion lastSupportedHttpVersion;

    virtual bool hasEntityBody(const HttpRequest &request) throw(HttpResponse) = 0;
    // @ret returns true when the entity body was fully received
    // in future, the entity body should be put on qiodevice buffer, not in memory
    virtual bool atEnd(HttpRequest &request, QByteArray &buffer) throw(HttpResponse) = 0;
    virtual void onRequest(const HttpRequest &request) = 0;

    virtual void prepareResponse(HttpResponse &);
    virtual void writeEntityBody(const HttpResponse &, QTcpSocket *);

    virtual void sessionStarted()
    {
    }

    // this function is called every time a connection is closed
    // should return true if the object must keep alive or false
    // if the object should be deleted
    virtual bool keepAlive()
    {
        return false;
    }

private slots:
    void onReadyRead();
    void onConnectionDie();

private:
    HttpSessionManager *sessionManager;
    QTcpSocket *socket;
    HttpRequest requestInfo;
    int state;
    QByteArray buffer;
};

} // namespace Brisa

#endif // HTTPSESSION_H
