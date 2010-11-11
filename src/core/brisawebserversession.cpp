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

#include "brisawebserversession.h"
#include "brisawebserver.h"
#include "brisawebservice.h"
using namespace BrisaCore;

#ifdef major
#undef major
#endif

#ifdef minor
#undef minor
#endif

#ifdef USE_NEW_BRISA_WEBSERVER

enum State
{
    WAITING_FOR_CHUNK_SIZE = 1,
    WAITING_FOR_CHUNK,
    WAITING_FOR_TRAILLING_HEADERS
};

BrisaWebserverSession::BrisaWebserverSession(BrisaWebserver *server, HttpSessionManager *parent) :
    HttpSession(parent),
    server(server)
{
    lastSupportedHttpVersion = HttpVersion(1, 1);
    connect(this, SIGNAL(responsePosted(HttpResponse)), this, SLOT(writeResponse(HttpResponse)));
}

BrisaWebserverSession::~BrisaWebserverSession()
{
}

void BrisaWebserverSession::respond(const HttpResponse &r)
{
    emit responsePosted(r);
}

int BrisaWebserverSession::isRequestSupported(const HttpRequest &request) const
{
    if ((request.httpVersion().major() != 1)
        || (request.httpVersion().minor() != 0 && request.httpVersion().minor() != 1)) {
        return HttpResponse::HTTP_VERSION_NOT_SUPPORTED;
    }
    if (request.method() != "GET" && request.method() != "POST"
        && request.method() != "SUBSCRIBE" && request.method() != "UNSUBSCRIBE") {
        return HttpResponse::NOT_IMPLEMENTED;
    }
    return 0;
}

bool BrisaWebserverSession::hasEntityBody(const HttpRequest &request) throw(HttpResponse)
{
    if (request.method() == "POST") {
        // REQUIRED. Field value MUST be text/xml; charset="utf-8" for description documents.
        if (request.header("CONTENT-TYPE").isNull()) {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }/* else if(request.header("CONTENT-TYPE") != "text/xml; charset=\"utf-8\"") {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }*/

        if (!request.header("CONTENT-LENGTH").isNull()) {
            bool ok;
            entitySize = request.header("CONTENT-LENGTH").toInt(&ok);

            if (!ok)
                throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);

            chunkedEntity = false;
        } else if (request.header("TRANSFER-ENCODING") == "chunked") {
            chunkedEntity = true;
        } else {
            throw HttpResponse(request.httpVersion(), HttpResponse::LENGTH_REQUIRED);
        }

        return true;
    } else {
        return false;
    }
}

bool BrisaWebserverSession::atEnd(HttpRequest &request, QByteArray &buffer) throw(HttpResponse)
{
    while (true) {
        switch (chunkedEntity) {
        case WAITING_FOR_CHUNK_SIZE:
            {
                int i = buffer.indexOf("\r\n");
                if (i != -1) {
                    QByteArray n = buffer.left(i);
                    buffer.remove(0, i + 2);

                    bool ok;
                    entitySize = n.toInt(&ok, 16);

                    if (!ok)
                        throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST, true);

                    if (entitySize)
                        chunkedEntity = WAITING_FOR_CHUNK;
                    else
                        chunkedEntity = WAITING_FOR_TRAILLING_HEADERS;

                    break;
                } else {
                    return false;
                }
            }
        case WAITING_FOR_CHUNK:
            {
                if (buffer.size() >= entitySize) {
                    chunksBuffer.append(buffer.left(entitySize));
                    buffer.remove(0, entitySize);
                    chunkedEntity = WAITING_FOR_CHUNK_SIZE;
                    break;
                } else {
                    return false;
                }
            }
        case WAITING_FOR_TRAILLING_HEADERS:
            {
                for (int i = buffer.indexOf("\r\n") ; i != -1 ; i = buffer.indexOf("\r\n")) {
                    // don't starts with \r\n
                    if (i != 0) {
                        QByteArray header = buffer.left(i);
                        buffer.remove(0, i + 2);

                        i = header.indexOf(':');
                        if (i > 0) {
                            if (i + 1 < header.size())
                                request.setHeader(header.left(i).trimmed(), header.mid(i + 1).trimmed());
                            else
                                request.setHeader(header.left(i).trimmed(), QByteArray());
                        } else {
                            throw HttpResponse(request.httpVersion() < lastSupportedHttpVersion ?
                                               request.httpVersion() : lastSupportedHttpVersion,
                                               HttpResponse::BAD_REQUEST, true);
                        }
                    } else {
                        buffer = chunksBuffer;
                        chunksBuffer.clear();

                        return true;
                    }
                }
            }

        // not a chunked entity
        case false:
            if (buffer.size() >= entitySize) {
                buffer.chop(buffer.size() - entitySize);
                return true;
            } else {
                return false;
            }
        }
    }
}

void BrisaWebserverSession::onRequest(const HttpRequest &request)
{
    if (request.httpVersion() == lastSupportedHttpVersion &&
        request.header("HOST").isNull()) {
        writeResponse(HttpResponse(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST, true));
        return;
    }
    if (BrisaWebService *service = server->service(request.uri())) {
        service->postRequest(request, this);
    } else {
        writeResponse(HttpResponse(request.httpVersion(), HttpResponse::NOT_FOUND, true));
    }
}

#endif // USE_NEW_BRISA_WEBSERVER
