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

BrisaWebserverSession::BrisaWebserverSession(int socketDescriptor, BrisaWebserver *server) :
    HttpSession(socketDescriptor),
    server(server)
{
    lastSupportedHttpVersion = HttpVersion(1, 1);
}

BrisaWebserverSession::~BrisaWebserverSession()
{
}

void BrisaWebserverSession::respond(const HttpResponse &r)
{
    writeResponse(r);
}

int BrisaWebserverSession::isRequestSupported(const HttpRequest &request) const
{
    if ((request.httpVersion().major() != 1)
        || (request.httpVersion().minor() != 0 && request.httpVersion().minor() != 1)) {
        return HttpResponse::HTTP_VERSION_NOT_SUPPORTED;
    }
    if (request.method() != "GET" && request.method() != "POST") {
        return HttpResponse::NOT_IMPLEMENTED;
    }
    return 0;
}

bool BrisaWebserverSession::hasEntityBody(const HttpRequest &request) throw(HttpResponse)
{
    if (request.method() == "POST") {
        // REQUIRED. Field value MUST be text/xml; charset="utf-8" for description documents.
        /*if (request.header("Content-Type").isNull()) {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }/* else if(request.header("Content-Type") != "text/xml; charset=\"utf-8\"") {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }*/

        if (request.header("content-length").isNull()) {
            throw HttpResponse(request.httpVersion(), HttpResponse::LENGTH_REQUIRED);
        } else {
            bool ok;
            entitySize = request.header("content-length").toInt(&ok);

            if (!ok)
                throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }

        return true;
    } else {
        return false;
    }
}

bool BrisaWebserverSession::atEnd(const HttpRequest &request, const QByteArray &buffer) throw(HttpResponse)
{
    if (entitySize == buffer.size())
        return true;
    else if (entitySize < buffer.size())
        throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);

    return false;
}

void BrisaWebserverSession::onRequest(const HttpRequest &request)
{
//    if (request.httpVersion() == lastSupportedHttpVersion &&
//        request.header("HOST").isNull()) {
//        writeResponse(HttpResponse(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST, true));
//        return;
//    }
    if (BrisaWebService *service = server->service(request.uri())) {
        service->postRequest(request, this);
    } else {
        writeResponse(HttpResponse(request.httpVersion(), HttpResponse::NOT_FOUND, true));
    }
}

#endif // USE_NEW_BRISA_WEBSERVER
