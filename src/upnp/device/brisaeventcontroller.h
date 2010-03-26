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

#ifndef _BRISAEVENTCONTROLLER_H
#define _BRISAEVENTCONTROLLER_H

#include "brisaeventmessage.h"
#include "brisaeventsubscription.h"
#include "brisaglobal.h"

#include <BrisaCore>

#include <QObject>

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaEventController : public BrisaWebService
{
    Q_OBJECT

    public:
        BrisaEventController(QxtAbstractWebSessionManager *sessionManager,
                             QList<BrisaStateVariable *> *stateVariableList,
                             QObject *parent=0);
        ~BrisaEventController();

    public slots:
        void variableChanged(BrisaStateVariable *variable);

        void subscribe(const QMultiHash<QString, QString> &subscriberInfo,
                       int sessionId, int requestId);

        void unsubscribe(const QMultiHash<QString, QString> &subscriberInfo,
                         int sessionId, int requestId);

        void parseGenericRequest(const QString &method,
                                 const QMultiHash<QString, QString> &headers,
                                 const QByteArray &requestContent,
                                 int sessionId,
                                 int requestId);

    signals:

    private slots:

    private:
        BrisaEventController(const BrisaEventController &);

        void sendEvent(const BrisaEventMessage &message, const QUrl &url);
        QStringList getEventUrls(const QString &urls);
        int getTimeOut(const QString &timeout);
        QString getUuid();
        QHttpResponseHeader getErrorHeader(const int &errorCode, const QString &errorMessage);

        QList<BrisaEventSubscription *> subscriptions;
        QList<BrisaStateVariable *> *variableList;
        QHttp httpClient;
};

}

#endif /* _BRISAEVENTCONTROLLER_H */
