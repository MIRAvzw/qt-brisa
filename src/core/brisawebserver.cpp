/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisawebserver.cpp
 * Created:
 * Description: Implementation of BrisaWebServer class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
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


#include "brisawebserver.h"
using namespace BrisaCore;

BrisaWebserver::BrisaWebserver(const QHostAddress &host, quint16 port)
{
    QxtHttpSessionManager(this);
    rootService = new BrisaWebServiceProvider(this, this);

    setPort(port);
    setListenInterface(host);
    setConnector(HttpServer);
    setStaticContentService(rootService);
}

BrisaWebserver::~BrisaWebserver()
{
    delete rootService;
}

int BrisaWebserver::newSession()
{
    return QxtHttpSessionManager::newSession();
}

void BrisaWebserver::addService(QString path, QxtWebServiceDirectory *service)
{
    rootService->addService(path, service);
}

void BrisaWebserver::incomingRequest(quint32 requestID, const QHttpRequestHeader &header, QxtWebContent *deviceContent)
{
    QxtHttpSessionManager::incomingRequest(requestID, header, deviceContent);
    qDebug() << requestID << " Request";
    qDebug() << "Method: " << header.method();
    qDebug() << "URI: " << header.path();
}

void BrisaWebserver::publishFile(QString publishPath, QString filePath)
{
    // Publishing a file to the root
    rootService->addFile(publishPath, filePath);
}
