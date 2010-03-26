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

#ifndef _BRISAEVENTSUBSCRIPTION_H
#define _BRISAEVENTSUBSCRIPTION_H

#include "brisaabstracteventsubscription.h"
#include "brisaglobal.h"

#include <BrisaCore>

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaEventSubscription : public BrisaAbstractEventSubscription
{
    Q_OBJECT

    public:
        BrisaEventSubscription(const QString &sid,
                               const QStringList &callbackUrls,
                               const int &timeout = -1, // <0 = infinite
                               QObject *parent = 0) :
            BrisaAbstractEventSubscription(sid, callbackUrls, timeout, parent) {}

        void renew(const int &newTimeout = -1); // <0 = infinite
        QHttpResponseHeader getAcceptSubscriptionResponse() const;
        QHttpResponseHeader getAcceptUnsubscriptionResponse() const;
};

}

#endif /* _BRISAEVENTSUBSCRIPTION_H */
