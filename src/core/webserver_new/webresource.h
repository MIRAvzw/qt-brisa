/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: webresource.h
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

#ifndef WEBRESOURCE_H
#define WEBRESOURCE_H

#include <QByteArray>

class WebResourceIdentifier
{
public:
    WebResourceIdentifier() {}
    WebResourceIdentifier(const QByteArray &uri, const QByteArray &host = QByteArray());
    WebResourceIdentifier(const char *uri, const QByteArray &host = QByteArray());
    WebResourceIdentifier(const char *uri, const char *host);

    bool operator==(const WebResourceIdentifier &r) const;

    QByteArray host;
    QByteArray uri;
};

class WebResource
{
public:
    WebResource() {}
    WebResource(const QString &fileName, const QByteArray &contentType = QByteArray()) :
            fileName(fileName),
            contentType(contentType)
    {
    }
    WebResource(const char *fileName, const QByteArray &contentType = QByteArray()) :
            fileName(fileName),
            contentType(contentType)
    {
    }
    WebResource(const char *fileName, const char *contentType) :
            fileName(fileName),
            contentType(contentType)
    {
    }

    QString fileName;
    QByteArray contentType;
};

inline WebResourceIdentifier::WebResourceIdentifier(const QByteArray &uri, const QByteArray &host) :
    host(host),
    uri(uri)
{
}

inline WebResourceIdentifier::WebResourceIdentifier(const char *uri, const QByteArray &host) :
    host(host),
    uri(uri)
{
}

inline WebResourceIdentifier::WebResourceIdentifier(const char *uri, const char *host) :
        host(host),
        uri(uri)
{
}

inline bool WebResourceIdentifier::operator==(const WebResourceIdentifier &r) const
{
    return (this->host == r.host) && (this->uri == r.uri);
}

inline uint qHash(const WebResourceIdentifier &r)
{
    uint sum = qChecksum(r.host.constData(), r.host.size());
    sum += qChecksum(r.uri.constData(), r.uri.size());
    return sum;
}

#endif // WEBRESOURCE_H
