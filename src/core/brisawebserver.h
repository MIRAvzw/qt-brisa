/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaconfig.cpp
 * Created:
 * Description: Definition of BrisaWebserver class.
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


#ifndef _BRISAWEBSERVER_H
#define _BRISAWEBSERVER_H

#include <QtCore>
#include <QtNetwork>
#include "QxtHttpSessionManager"
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#include "brisaglobal.h"
#include "brisawebservice.h"
#include "brisawebfile.h"
#include "brisawebserviceprovider.h"

namespace BrisaCore {

    /*!
     *  \brief The BrisaWebserver class is a web server implementation.
     *
     *  BrisaWebServer implements a Web Server using libQxt.
     */
    class BRISA_CORE_EXPORT BrisaWebserver : public QxtHttpSessionManager
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebServer
         *
         *  \param host \a empty
         *  \param port \a empty
         */
        BrisaWebserver(const QHostAddress &host, quint16 port);

        /*!
         *  Destructor for BrisaWebServer
         */
        ~BrisaWebserver();

        /*!
         *  Publishes a file to the root.
         *
         *  \param publishPath \a empty
         *  \param filePath \a empty
         */
        void publishFile(QString publishPath, QString filePath);

        /*!
         *  Adds a service to the web server. The service url path will be added to the root of the server.
         *
         *  \param path \a empty
         *  \param service \a empty
         */
        void addService(QString path, QxtWebServiceDirectory *service);

    protected:
        /*!
         *  This method dumps request information to the screen.
         *
         *  \param requestID \a empty
         *  \param header \a empty
         *  \param deviceContent \a empty
         */
        void incomingRequest(quint32 requestID, const QHttpRequestHeader &header,
                             QxtWebContent *deviceContent);
        /*!
         *  Creates a new session and returns the session number.
         */
        int newSession();

    private:
        BrisaWebServiceProvider *rootService;
    };

};

#endif /* _BRISAWEBSERVER_H */
