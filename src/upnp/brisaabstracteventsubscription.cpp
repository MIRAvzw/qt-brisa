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

#include "brisaabstracteventsubscription.h"

using namespace BrisaUpnp;

/*!
 * \internal
 * \class BrisaUpnp::BrisaAbstractEventSubscription brisaabstracteventsubscription.h BrisaUpnp/BrisaAbstractEventSubscription
 *
 * \brief Abstract class that represents an event subscription
 */

/*!
 * Construtcs an abstract event subscription with given \a sid, list of
 * \a callbackUrls, \a timeout and \a parent. \a timeout less than 0 means
 * infinite.
 */
BrisaAbstractEventSubscription::BrisaAbstractEventSubscription(const QString &sid,
                                               const QStringList &callbackUrls,
                                               const int &timeout,
                                               QObject *parent) :
    QObject(parent),

    SID(sid),

    CALLBACK_URLS(callbackUrls),

    date(QDateTime::currentDateTime()),
    timeout(timeout),

    lastSeq(0),
    firstMessageSent(false)
{
}

/*!
 * Renews the subscription for the given \a newTimeout.
 */
void BrisaAbstractEventSubscription::renew(const int &newTimeout)
{
    this->date = QDateTime::currentDateTime();
    this->timeout = newTimeout;
}

/*!
 * Checks if the subscription has already expired. Returns true if it has
 * expired, else returns false.
 */
bool BrisaAbstractEventSubscription::hasExpired() const
{
    return (timeout < 0)? false
                        : date.secsTo(QDateTime::currentDateTime()) >= this->timeout;
}

/*!
 * Returns the next event key for this subscription.
 */
quint32 BrisaAbstractEventSubscription::getNextSeq()
{
    if (!firstMessageSent) {
        firstMessageSent = true;
        return 0;
    }

    if (this->lastSeq == 0xFFFFFFFF) /*4294967295L*/
        this->lastSeq = 0;

    return ++(this->lastSeq);
}

/*!
 * Returns this subscription's SID.
 */
QString BrisaAbstractEventSubscription::getSid() const
{
    return this->SID;
}

/*!
 * Returns this subscription's list of callback URLs.
 */
QStringList BrisaAbstractEventSubscription::getCallbackUrls() const
{
    return this->CALLBACK_URLS;
}

/*!
 * Returns this subscription's first callback URL.
 */
QUrl BrisaAbstractEventSubscription::getUrl()
{
    QString callback;
    if (!CALLBACK_URLS.empty())
        callback = CALLBACK_URLS[0];

    return QUrl(callback);
}


