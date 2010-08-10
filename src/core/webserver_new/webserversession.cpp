/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: webserversession.cpp
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

        response.setBody(file.readAll());

        writeResponse(response);
    } else {
        response.setStatusCode(404, "Not Found");

        response.setHeader("Content-Type", "text/html");
        response.setBody(notFound);

        writeResponse(response);
    }
}
