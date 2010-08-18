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

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QUrl>
#include <QHostAddress>
#include "httpversion.h"

class HttpRequest
{
public:
    enum MethodFlag
    {
        HEAD,
        GET,
        POST,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATCH
    };
    Q_DECLARE_FLAGS(Method, MethodFlag)

public:
    explicit HttpRequest(Method method = GET, const QByteArray &uri = "/",
                         const HttpVersion &version = HttpVersion());

    Method method() const;
    void setMethod(const Method &method);

    QByteArray uri() const;
    void setUri(const QByteArray &uri);

    HttpVersion httpVersion() const;
    void setHttpVersion(const HttpVersion &);

    QByteArray entityBody() const;
    void setEntityBody(const QByteArray &body);

    QHash<QByteArray, QByteArray> headers() const;
    void setHeader(const QByteArray &name, const QByteArray &value);
    void removeHeader(const QByteArray &name);
    QByteArray header(const QByteArray &headerName) const;

    //    /*
    //     * Get a value of particular form variable.
    //     * Both query string (whatever comes after '?' in the URL) and a POST buffer
    //     * are scanned. If a variable is specified in both query string and POST
    //     * buffer, POST buffer wins. Return value:
    //     *	NULL      if the variable is not found
    //     *	non-NULL  if found. NOTE: this returned value is dynamically allocated
    //     *		  and is subject to mg_free() when no longer needed. It is
    //     *		  an application's responsibility to mg_free() the variable.
    //     */
    //    char *mg_get_var(const struct mg_connection *, const char *var_name);

private:
    Method m_method;                  // char *request_method;
    QByteArray m_uri;                 // char *uri

    QByteArray remoteUser;            // char *remote_user;
    QHostAddress remoteIp;            // long remote_ip;
    // the socket descriptor to be used by QTcpSocket
    int remotePort;                   // int remote_port;

//    int m_httpVersionMajor;             // int http_version_major;
//    int m_httpVersionMinor;             // int http_version_minor;
    HttpVersion m_httpVersion;
    // the maximum number of headers should be 64
//    QList<HttpHeader> m_headers;      // int num_headers; struct mg_header http_headers[64];
    // max: 32 headers
    QHash<QByteArray, QByteArray> m_headers;

    QByteArray m_entityBody;                // char *post_data; int post_data_len;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(HttpRequest::Method)

#endif // HTTPREQUEST_H
