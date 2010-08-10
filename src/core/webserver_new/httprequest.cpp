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

#include "httprequest.h"

HttpRequest::HttpRequest(Method method, const QByteArray &uri,
                         const HttpVersion &httpVersion) :
    m_method(method),
    m_uri(uri),
//    m_httpVersionMajor(httpVersion),
//    m_httpVersionMinor(static_cast<int>(httpVersion * 10) % 10)
    m_httpVersion(httpVersion)
{
}

void HttpRequest::setMethod(const Method &method)
{
    m_method = method;
}

void HttpRequest::setUri(const QByteArray &uri)
{
    m_uri = uri;
}

QByteArray HttpRequest::uri() const
{
    return m_uri;
}

HttpVersion HttpRequest::httpVersion() const
{
    return m_httpVersion;
}

void HttpRequest::setHttpVersion(const HttpVersion &version)
{
    m_httpVersion = version;
}

QHash<QByteArray, QByteArray> HttpRequest::headers() const
{
    return m_headers;
}

void HttpRequest::setHeader(const QByteArray &name, const QByteArray &value)
{
    m_headers[name] = value;
}

void HttpRequest::removeHeader(const QByteArray &name)
{
    m_headers.remove(name);
}

QByteArray HttpRequest::header(const QByteArray &headerName) const
{
    return m_headers.value(headerName);
}
