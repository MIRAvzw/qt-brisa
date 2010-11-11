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

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>
#include <QFile>
#include <QHostAddress>

class HttpSession;
class HttpSessionManager;

class HttpServerFactory
{
public:
    virtual HttpSession *generateSessionHandler(HttpSessionManager *parent) = 0;
};

class HttpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpServer(const QHostAddress &address = QHostAddress::Any,
                        quint16 port = 0, QObject *parent = 0);
    virtual ~HttpServer();

    void start();

    virtual HttpServerFactory &factory() = 0;

protected:
    void incomingConnection(int handle);

//    virtual HttpSession *incomingSession(int socketDescriptor) = 0;

private:
    QHostAddress address;
    quint16 port;
    QList<HttpSessionManager *> threads;
    int ringIndex;
};

#endif // HTTPSERVER_H
