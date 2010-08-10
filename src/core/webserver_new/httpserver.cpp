/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: httpserver.cpp
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
