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

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "httpserver.h"
#include <QMutex>
#include "webresource.h"

class WebServer : public HttpServer
{
Q_OBJECT
public:
    explicit WebServer(const QHostAddress &address = QHostAddress::Any,
                       quint16 port = 0, QObject *parent = 0);
    void publishFile(const WebResourceIdentifier &uri, const WebResource &resource);
    WebResource resource(const WebResourceIdentifier &uri) const;

signals:

public slots:

protected:
    HttpSession *incomingConnection(int socketDescriptor);

private:
    QMutex mutex;
    QHash<WebResourceIdentifier, WebResource> handle;
};

#endif // WEBSERVER_H
