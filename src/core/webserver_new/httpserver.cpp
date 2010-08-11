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

#include "httpserver.h"
#include <QTcpServer>
#include "tcpserver.h"

#define DBG_PREFIX "HttpContext: "

HttpServer::HttpServer(const QHostAddress &address, quint16 port, QObject *parent) :
    QThread(parent),
    socket(new TcpServer(this)),
    address(address),
    port(port)
{
}

HttpServer::~HttpServer()
{
}

void HttpServer::run()
{
    connect(socket, SIGNAL(newConnection(int)), this, SLOT(onNewConnection(int)));
    socket->listen(address, port);
    exec();
}

void HttpServer::onNewConnection(int socketDescriptor)
{
    HttpSession *c = incomingConnection(socketDescriptor);
    if (c) {
        connect(c, SIGNAL(finished()), c, SLOT(deleteLater()));

        c->start();
    }
}
