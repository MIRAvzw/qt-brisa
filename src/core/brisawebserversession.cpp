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
using namespace BrisaCore;

#ifdef USE_NEW_BRISA_WEBSERVER

BrisaWebserverSession::BrisaWebserverSession(int socketDescriptor) :
    HttpSession(socketDescriptor)
{
    lastSupportedHttpVersion = HttpVersion(1, 1);
}

BrisaWebserverSession::~BrisaWebserverSession()
{
}

int BrisaWebserverSession::isRequestSupported(const HttpRequest &request) const
{
    if (request.httpVersion() != 1.0 && request.httpVersion() != 1.1) {
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
        if (request.header("Content-Type").isNull()) {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }/* else if(request.header("Content-Type") != "text/xml; charset=\"utf-8\"") {
            throw HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST);
        }*/

        if (request.header("Content-Length").isNull()) {
            throw HttpResponse(request.httpVersion(), HttpResponse::LENGTH_REQUIRED);
        } else {
            bool ok;
            entitySize = request.header("Content-Length").toInt(&ok);

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
    if (request.httpVersion() == lastSupportedHttpVersion &&
        request.header("Host").isNull()) {
        HttpResponse response(lastSupportedHttpVersion, HttpResponse::BAD_REQUEST);

        writeResponse(response, true);
        return;
    }
    if (request.method() == "GET") {
        WebResource resource = server->resource(WebResourceIdentifier(request.uri(), request.header("Host")));
        if (!resource)
            resource = server->resource(WebResourceIdentifier(request.uri()));

        if (resource) {
            HttpResponse response(request.httpVersion(), HttpResponse::OK);

            if (!resource.contentType.isNull())
                response.setHeader("Content-Type", resource.contentType);

            response.setEntityBody(new QFile(resource.fileName));
            return;
        } else {
            HttpResponse response(request.httpVersion(), HttpResponse::NOT_FOUND);

            writeResponse(response);
            return;
        }
    } else if (request.method() == "POST"){
    }
}

#endif // USE_NEW_BRISA_WEBSERVER
