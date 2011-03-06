/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventcontroller.h
 * Created:
 * Description: Defines BrisaEventController class.
 * Authors: Name <email> @since 2009
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

#ifndef _BRISAEVENTCONTROLLER_H
#define _BRISAEVENTCONTROLLER_H

#include "brisaeventmessage.h"
#include "brisamulticasteventmessage.h"
#include "brisaeventsubscription.h"
#include "brisaglobal.h"
#include "brisautils.h"
#include "brisawebservice.h"
#include "brisawebserver.h"

namespace Brisa {
    class BRISA_UPNP_EXPORT BrisaEventController: public BrisaWebService
    {
    Q_OBJECT

    public:
        BrisaEventController(BrisaWebserver *sessionManager,
       			QList<BrisaStateVariable *> *stateVariableList, QObject *parent = 0);
        virtual ~BrisaEventController();

    public slots:
        void variableChanged(BrisaStateVariable *variable);

        void subscribe(const HttpRequest &request, BrisaWebserverSession *session);

        void unsubscribe(const HttpRequest &request, BrisaWebserverSession *session);

    protected:
        void onRequest(const HttpRequest &, BrisaWebserverSession *session);

    private:
        BrisaEventController(const BrisaEventController &); // = delete;

        void sendEvent(const BrisaEventMessage &message, const QUrl &url);

        void sendMulticastEvent(const BrisaMulticastEventMessage &message);

        QStringList getEventUrls(const QString &urls);

        int getTimeOut(const QString &timeout);

        QList<BrisaEventSubscription *> subscriptions;

        QList<BrisaStateVariable *> *variableList;

        QUdpSocket udpSocket;
    };
}

#endif /* _BRISAEVENTCONTROLLER_H */
