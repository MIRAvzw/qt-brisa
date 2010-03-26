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

#ifndef _BRISAABSTRACTEVENTSUBSCRIPTION_H
#define _BRISAABSTRACTEVENTSUBSCRIPTION_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>
#include <QtCore>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaAbstractEventSubscription : public QObject
{
    Q_OBJECT

    public:
        BrisaAbstractEventSubscription(const QString &sid,
                               const QStringList &callbackUrls,
                               const int &timeout = -1, // <0 = infinite
                               QObject *parent = 0);

        virtual void renew(const int &newTimeout = -1) = 0; // <0 = infinite
        bool hasExpired() const;

        quint32 getNextSeq();
        QString getSid() const;
        QStringList getCallbackUrls() const;
        QUrl getUrl();

    protected:
        QString SID;

        const QStringList CALLBACK_URLS;

        QDateTime date;
        int timeout;

        quint32 lastSeq;
        bool firstMessageSent;
};

}

#endif /* _BRISAABSTRACTEVENTSUBSCRIPTION_H */
