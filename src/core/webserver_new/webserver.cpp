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

#include "webserver.h"
#include "webserversession.h"
#include "webresource.h"

WebServer::WebServer(const QHostAddress &address, quint16 port,
                     QObject *parent) :
    HttpServer(address, port, parent)
{
}

HttpSession *WebServer::incomingConnection(int socketDescriptor)
{
    return new WebServerSession(socketDescriptor, this);
}

void WebServer::publishFile(const WebResourceIdentifier &uri, const WebResource &resource)
{
    if (!uri.uri.isEmpty()) {
        mutex.lock();
        handle[uri] = resource;
        mutex.unlock();
    }
}

WebResource WebServer::resource(const WebResourceIdentifier &uri) const
{
    return handle.value(uri);
}
