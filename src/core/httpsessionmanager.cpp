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

#include "httpsessionmanager.h"
#include "httpsession.h"

using namespace Brisa;

HttpSessionManager::HttpSessionManager(HttpServer *parent) :
    QThread(parent),
    server(parent)
{
}

void HttpSessionManager::run()
{
    connect(this, SIGNAL(newConnection(int)), this, SLOT(onNewConnection(int)));

    exec();
}

void HttpSessionManager::addSession(int socketDescriptor)
{
    emit newConnection(socketDescriptor);
}

void HttpSessionManager::onNewConnection(int socketDescriptor)
{
    bool created = false;

    mutex.lock();

    if (pool.size()) {
        pool.back()->setSession(socketDescriptor);
        pool.pop_back();
        created = true;
    }

    mutex.unlock();

    if (!created) {
        HttpSession *s = server->factory().generateSessionHandler(this);
        s->setSession(socketDescriptor);
    }
}

void HttpSessionManager::releaseSession(HttpSession *session)
{
    mutex.lock();

    pool.append(session);

    mutex.unlock();
}
