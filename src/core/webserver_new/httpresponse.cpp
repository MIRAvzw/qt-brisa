/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: httpresponse.cpp
 * Created:
 * Description: Implementation of BrisaConfigurationManager class.
 * Authors: Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com> @since 2010
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
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

#include "httpresponse.h"

HttpResponse::HttpResponse(const HttpVersion &httpVersion, int statusCode,
                           const QByteArray &reasonPhrase) :
    m_httpVersion(httpVersion),
    m_statusCode(statusCode),
    m_reasonPhrase(reasonPhrase)
{
}

int HttpResponse::statusCode() const
{
    return m_statusCode;
}

QByteArray HttpResponse::reasonPhrase() const
{
    return m_reasonPhrase;
}

QHash<QByteArray, QByteArray> HttpResponse::headers() const
{
    return m_headers;
}

QByteArray HttpResponse::body() const
{
    return m_body;
}

void HttpResponse::setBody(const QByteArray &body)
{
    m_body = body;
}

bool HttpResponse::setStatusCode(int st, const QByteArray &reasonPhrase)
{
    m_statusCode = st;
    m_reasonPhrase = reasonPhrase;
    return true;
}

void HttpResponse::setHeader(const QByteArray &name, const QByteArray &value)
{
    m_headers[name] = value;
}

QByteArray HttpResponse::header(const QByteArray &name) const
{
    return m_headers.value(name);
}

HttpVersion HttpResponse::httpVersion() const
{
    return m_httpVersion;
}
