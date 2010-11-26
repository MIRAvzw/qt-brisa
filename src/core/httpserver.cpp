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
#include "httpsessionmanager.h"

#define DBG_PREFIX "HttpContext: "

using namespace Brisa;

HttpServer::HttpServer(const QHostAddress &address, quint16 port, QObject *parent) :
    QTcpServer(parent),
    address(address),
    port(port)
{
    threads.append(new HttpSessionManager(this));
}

void HttpServer::setThreadsNumber(int number)
{
    if (number < 1 || isListening())
        return;

    int oldNumber = threadsNumber();

    if (number > oldNumber) {
        int i = number - oldNumber;
        while (i--) {
            threads.append(new HttpSessionManager(this));
        }
    } else if (number < oldNumber) {
        int i = oldNumber - number;
        while (i--) {
            delete threads.takeLast();
        }
    }
}

HttpServer::~HttpServer()
{
    // TODO: review code
    foreach(HttpSessionManager *thread, threads) {
        thread->terminate();
    }
    foreach(HttpSessionManager *thread, threads) {
        thread->wait();
        delete thread;
    }
}

void HttpServer::incomingConnection(int socketDescriptor)
{
    threads[(ringIndex++) % threads.size()]->addSession(socketDescriptor);
}

void HttpServer::start()
{
    listen(address, port);
    foreach(HttpSessionManager *thread, threads) {
        thread->start();
    }
}
