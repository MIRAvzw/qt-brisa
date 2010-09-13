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

#include "httpmessage.h"
#include "httpversion.h"

class HttpRequest: public HttpMessage
{
public:
    explicit HttpRequest(const QByteArray &method = QByteArray(), const QByteArray &uri = "/",
                         const HttpVersion &version = HttpVersion());

    QByteArray method() const;
    void setMethod(const QByteArray &method);

    QByteArray uri() const;
    void setUri(const QByteArray &uri);

private:
    QByteArray m_method;              // char *request_method;
    QByteArray m_uri;                 // char *uri
};

inline QByteArray HttpRequest::method() const
{
    return m_method;
}

inline QByteArray HttpRequest::uri() const
{
    return m_uri;
}

#endif // HTTPREQUEST_H
