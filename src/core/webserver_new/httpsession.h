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
    virtual void pageRequest(HttpRequest request) = 0;
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
    // entity body related only
    qint64 remainingBytes;

    // os atributos abaixo estavam originalmente presentes.
    // falta verificar se eles pertencerão a o port Qt também
//    bool embeddedAuth; // Used for authorization
//    quint64 numBytesSent;// Total bytes sent to client

    //	SSL		*ssl;		/* SSL descriptor		*/

};

#endif // HTTPSESSION_H
