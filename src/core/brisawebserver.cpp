/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisawebserver.cpp
 * Created:
 * Description: Implementation of BrisaWebServer class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
 *          Leandro Melo de Sales <leandroal@gmail.com> @since 2009-2010
 *          Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com> @since 2010
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

#ifdef USE_NEW_BRISA_WEBSERVER

#include "brisawebserversession.h"

BrisaWebserver::BrisaWebserver(const QHostAddress &host, quint16 port) :
        HttpServer(host, port)
{
}

BrisaWebserver::~BrisaWebserver()
{
    foreach (BrisaWebserverSession *session, listeners) {
        session->deleteLater();
    }
}

void BrisaWebserver::publishResource(const WebResourceIdentifier &publishPath, const WebResource &filePath)
{
    mutex.lock();

    if (filePath)
        resources[publishPath] = filePath;
    else
        resources.remove(publishPath);

    mutex.unlock();
}

WebResource BrisaWebserver::resource(const WebResourceIdentifier &resourceIdentifier) const
{
    return resources.value(resourceIdentifier);
}

void BrisaWebserver::addService(const QByteArray &path, BrisaWebService *service)
{
    mutex.lock();

    services[path] = service;

    mutex.unlock();
}

BrisaWebService *BrisaWebserver::service(const QByteArray &path) const
{
    return services.value(path);
}

HttpSession *BrisaWebserver::incomingConnection(int socketDescriptor)
{
    BrisaWebserverSession *session = new BrisaWebserverSession(socketDescriptor, this);

    mutex.lock();

    listeners.append(session);

    mutex.unlock();

    return session;
}

#else

BrisaWebserver::BrisaWebserver(const QHostAddress &host, quint16 port) {
    QxtHttpSessionManager(this);
    rootService = new BrisaWebServiceProvider(this, this);

    this->setPort(port);
    this->setListenInterface(host);
    this->setConnector(HttpServer);
    this->setStaticContentService(rootService);
}

BrisaWebserver::~BrisaWebserver() {
    delete this->rootService;
}

int BrisaWebserver::newSession() {
    return QxtHttpSessionManager::newSession();
}

void BrisaWebserver::addService(QString path, QxtWebServiceDirectory *service) {
    this->rootService->addService(path, service);
}

void BrisaWebserver::incomingRequest(quint32 requestID,
        const QHttpRequestHeader &header, QxtWebContent *deviceContent) {
    QxtHttpSessionManager::incomingRequest(requestID, header, deviceContent);
    qDebug() << requestID << " Request";
    qDebug() << "Method: " << header.method();
    qDebug() << "URI: " << header.path();
}

void BrisaWebserver::publishFile(QString path, QString filePath) {
    // Publishing a file to the root
    this->rootService->addFile(path, filePath);
}

#endif // USE_NEW_BRISA_WEBSERVER
