/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: httpresponse.h
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

#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "httpversion.h"
#include <QHash>

class HttpResponse
{
public:
    HttpResponse(const HttpVersion &httpVersion, int statusCode = 200,
                 const QByteArray &reasonPhrase = "OK");

    HttpVersion httpVersion() const;
    void setHttpVersion(const HttpVersion &version);

    int statusCode() const;
    bool setStatusCode(int st);
    bool setStatusCode(int st, const QByteArray &reasonPhrase);

    QByteArray reasonPhrase() const;
    void setReasonPhrase(const QByteArray &reasonPhrase);

    QByteArray body() const;
    void setBody(const QByteArray &body);

    QHash<QByteArray, QByteArray> headers() const;
    void setHeader(const QByteArray &name, const QByteArray &value);
    void removeHeader(const QByteArray &name);
    QByteArray header(const QByteArray &name) const;

private:
    HttpVersion m_httpVersion;
    int m_statusCode;
    QByteArray m_reasonPhrase;

    QHash<QByteArray, QByteArray> m_headers;

    QByteArray m_body;
};

#endif // HTTPRESPONSE_H
