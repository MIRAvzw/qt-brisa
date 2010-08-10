/*
  Copyright (C) 2010 Vinícius dos Santos Oliveira

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
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
    qDebug(DBG_PREFIX "running server on port %i", (int)socket->serverPort());
    exec();
}

void HttpServer::onNewConnection(int socketDescriptor)
{
    qDebug(DBG_PREFIX "nova conexão solicitada");
    HttpSession *c = incomingConnection(socketDescriptor);
    if (c) {
        connect(c, SIGNAL(finished()), c, SLOT(deleteLater()));

        c->start();
    }
}
