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

#include "webserversession.h"
#include <QFile>
#include "webserver.h"

#define DBG_PREFIX "WebServerConnection: "

static const QByteArray notFound =
        "<html>"
        " <head>"
        "  <title>404 - Not Found</title>"
        " </head>"
        " <body>"
        "  <h1>Not found</h1>"
        " </body>"
        "</html>";

WebServerSession::WebServerSession(int socketDescriptor,
                                         WebServer *parent) :
    HttpSession(socketDescriptor, parent),
    server(parent)
{
    qDebug(DBG_PREFIX "nova conexão web");
}

void WebServerSession::onRequest(HttpRequest request)
{
    qDebug(DBG_PREFIX "respondendo request");
    HttpResponse response(request.httpVersion());
    qDebug() << request.uri();
    WebResource resource = server->resource(WebResourceIdentifier(request.uri(), request.header("Host")));
    if (resource.fileName.isEmpty()) {
        resource = server->resource(WebResourceIdentifier(request.uri()));
    }
    if (QFile::exists(resource.fileName)) {
        QFile file(resource.fileName);
        file.open(QIODevice::ReadOnly);

        if (!resource.contentType.isEmpty())
            response.setHeader("Content-Type", resource.contentType);

        response.setEntityBody(file.readAll());

        writeResponse(response);
    } else {
        response.setStatusCode(HttpResponse::NOT_FOUND);

        response.setHeader("Content-Type", "text/html");
        response.setEntityBody(notFound);

        writeResponse(response);
    }
}
