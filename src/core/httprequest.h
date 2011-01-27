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

namespace Brisa {

class BRISA_CORE_EXPORT HttpRequest: public HttpMessage
{
public:
    explicit HttpRequest(const QByteArray &method = QByteArray(),
                         const QByteArray &uri = "/",
                         const HttpVersion &version = HttpVersion());

    QByteArray method() const;
    void setMethod(const QByteArray &method);

    QByteArray uri() const;
    void setUri(const QByteArray &uri);

private:
    QByteArray m_method;              // char *request_method;
    QByteArray m_uri;                 // char *uri
};

} // namespace Brisa

inline QByteArray Brisa::HttpRequest::method() const
{
    return m_method;
}

inline QByteArray Brisa::HttpRequest::uri() const
{
    return m_uri;
}

inline QDebug &operator<<(QDebug dbg, const Brisa::HttpRequest &request)
{
    dbg.nospace() << "{\n  " << request.method().data() << ' ' << request.uri().data() << ' ' << request.httpVersion() << '\n';
    for (QHash<QByteArray, QByteArray>::const_iterator i = request.headersBeginIterator();i != request.headersEndIterator();++i) {
        dbg.nospace() << "  " << i.key().data() << ": " << i.value().data() << '\n';
    }
    if (request.entitySize())
        dbg.nospace() << " Entity body size: " << request.entitySize() << '\n';
    dbg.nospace() << "}\n";
    return dbg.maybeSpace();
}

#endif // HTTPREQUEST_H
