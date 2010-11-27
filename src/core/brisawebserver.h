/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaconfig.cpp
 * Created:
 * Description: Definition of BrisaWebserver class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
 *          Leandro Melo de Sales <leandroal@gmail.com> @since 2009-2010
 *          Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com> @since 2010
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

#ifndef _BRISAWEBSERVER_H
#define _BRISAWEBSERVER_H
#include <QtCore>
#include <QtNetwork>
#include "brisaglobal.h"

#include "httpserver.h"

namespace Brisa {

/*!
 *  \brief The BrisaWebserver class is a web server implementation.
 *
 *  BrisaWebServer implements a Web Server using libQxt.
 */
    class BrisaWebService;
    class BrisaWebserverSession;

    class BRISA_CORE_EXPORT BrisaWebserver: public HttpServer
    {
    Q_OBJECT
    public:
        BrisaWebserver(const QHostAddress &host, quint16 port);
        ~BrisaWebserver();

        void addService(QByteArray path, BrisaWebService *service);
        void removeService(QByteArray path);
        BrisaWebService *service(QByteArray path) const;

    protected:
        HttpServerFactory &factory();

    private:
        class Factory: public HttpServerFactory
        {
        public:
            Factory(BrisaWebserver *server) : server(server) {}
            HttpSession *generateSessionHandler(HttpSessionManager *parent);

        private:
            BrisaWebserver *server;
        } m_factory;

        // QHash and QList are reentrant, not thread-safe
        mutable QMutex mutex;
        QHash<QByteArray, BrisaWebService *> services;
    };

}

#endif /* _BRISAWEBSERVER_H */
