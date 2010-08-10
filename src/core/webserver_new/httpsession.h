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

#ifndef HTTPSESSION_H
#define HTTPSESSION_H

#include <QDateTime>
#include <QThread>
#include "httprequest.h"
#include "httpresponse.h"

class QTcpSocket;
//class HttpContext;

class HttpSession : public QThread
{
    Q_OBJECT
public:
    explicit HttpSession(int socketDescriptor, QObject *parent = 0);
    virtual ~HttpSession();
    void run();

protected:
    // a api poderia ter alguma coisa como esse método para permitir customização
//    virtual QByteArray handleRequest();
    virtual void onRequest(HttpRequest request) = 0;
    qint64 writeResponse(HttpResponse);

signals:
    void error();

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    int socketDescriptor;
    HttpRequest requestInfo;
    QDateTime birthTime;
    int state;
    QByteArray buffer;

    // os atributos abaixo estavam originalmente presentes.
    // falta verificar se eles pertencerão a o port Qt também
//    bool embeddedAuth; // Used for authorization
//    quint64 numBytesSent;// Total bytes sent to client

    //	SSL		*ssl;		/* SSL descriptor		*/

};

#endif // HTTPSESSION_H
