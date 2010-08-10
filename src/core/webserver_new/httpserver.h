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

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QThread>
#include <QFile>
#include "httpsession.h"
#include <QHostAddress>

class QTcpServer;
class QTcpSocket;
class TcpServer;

class HttpServer : public QThread
{
    Q_OBJECT
public:
    enum HttpError
    {
        // TODO
    };

public:
    explicit HttpServer(const QHostAddress &address = QHostAddress::Any,
                         quint16 port = 0, QObject *parent = 0);
    virtual ~HttpServer();
    void run();

    // talvez fosse interessante option retornar um QVariant
    /*
     * Return current value of a particular option.
     */
    QByteArray option(const QByteArray &optionName);
    // talvez fosse mais interessante setOption receber um QVariant
    // no lugar do value
    bool setOption(const QByteArray &optionName, const QByteArray &value);

    HttpError error();
    QString errorString();

protected:
    virtual HttpSession *incomingConnection(int socketDescriptor) = 0;

signals:
//    /*
//     * Register SSL password handler.
//     * This is needed only if SSL certificate asks for a password. Instead of
//     * prompting for a password on a console a specified function will be called.
//     */
//    typedef int (*mg_spcb_t)(char *buf, int num, int w, void *key);
//    void mg_set_ssl_password_callback(struct mg_context *ctx, mg_spcb_t func);

public slots:

private slots:
    void onNewConnection(int socketDescriptor);

private:
    TcpServer *socket;
    QHostAddress address;
    quint16 port;
};

#endif // HTTPSERVER_H
