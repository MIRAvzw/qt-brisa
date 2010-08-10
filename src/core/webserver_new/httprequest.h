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

/*
   This file was based on mongoose logic and probably
   will be in the final version of this webserver.

   It's equivalent to mg_request_info
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

    QByteArray m_body;                // char *post_data; int post_data_len;

};

Q_DECLARE_OPERATORS_FOR_FLAGS(HttpRequest::Method)

#endif // HTTPREQUEST_H
