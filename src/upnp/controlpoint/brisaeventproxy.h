/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _BRISACONTROLPOINTEVENTSUBSCRIPTION_H
#define _BRISACONTROLPOINTEVENTSUBSCRIPTION_H

#include "brisaabstracteventsubscription.h"
#include "brisaglobal.h"

#include <BrisaCore>

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>
#include <QtXml>

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaEventProxy : public BrisaAbstractEventSubscription
{
    Q_OBJECT

    public:
        friend class BrisaControlPoint;

        ~BrisaEventProxy();

        int getId();
        void renew(const int &newTimeout = -1); // <0 = infinite
        void subscribe(const int timeout = -1);
        void unsubscribe();

    signals:
        void eventNotification(BrisaEventProxy *subscription,
                               QMap<QString, QString> eventingVariables);

    protected:

    private:
        BrisaEventProxy(const QStringList &callbackUrls,
                                           BrisaWebserver *webserver,
                                           int &deliveryPath,
                                           QString host,
                                           int port,
                                           QHttp *http,
                                           QString eventSub,
                                           QObject *parent = 0);
        int requestId;
        int deliveryPath;
        QString host;
        int port;
        QHttp *http;
        QString eventSub;
        BrisaWebserver *webServer;
        BrisaWebService *eventService;
        QHttpRequestHeader *getSubscriptionRequest(const int timeout);
        QHttpRequestHeader *getUnsubscriptionRequest() const;
        QHttpRequestHeader *getRenewRequest(const int timeout) const;
        void setSid(QString &sid);

   private slots:
        void eventReceived(BrisaWebService*, QMultiHash<QString, QString>, QString);
};

}

#endif /* _BRISACONTROLPOINTEVENTSUBSCRIPTION_H */
