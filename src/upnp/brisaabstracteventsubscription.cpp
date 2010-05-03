/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstracteventsubscription.cpp
 * Created:
 * Description: This File Implements the BrisaAbstractEventSubscription class.
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

#include "brisaabstracteventsubscription.h"

using namespace BrisaUpnp;

BrisaAbstractEventSubscription::BrisaAbstractEventSubscription(
        const QString &sid, const QStringList &callbackUrls,
        const int &timeout, QObject *parent) :
    QObject(parent),

    SID(sid),

    CALLBACK_URLS(callbackUrls),

    date(QDateTime::currentDateTime()), timeout(timeout),

    lastSeq(0), firstMessageSent(false) {
}

void BrisaAbstractEventSubscription::renew(const int &newTimeout) {
    this->date = QDateTime::currentDateTime();
    this->timeout = newTimeout;
}

bool BrisaAbstractEventSubscription::hasExpired() const {
    return (timeout < 0) ? false : date.secsTo(QDateTime::currentDateTime())
            >= this->timeout;
}

quint32 BrisaAbstractEventSubscription::getNextSeq() {
    if (!firstMessageSent) {
        firstMessageSent = true;
        return 0;
    }

    if (this->lastSeq == 0xFFFFFFFF) /*4294967295L*/
        this->lastSeq = 0;

    return ++(this->lastSeq);
}

QString BrisaAbstractEventSubscription::getSid() const {
    return this->SID;
}

QStringList BrisaAbstractEventSubscription::getCallbackUrls() const {
    return this->CALLBACK_URLS;
}

QUrl BrisaAbstractEventSubscription::getUrl() {
    QString callback;
    if (!CALLBACK_URLS.empty())
        callback = CALLBACK_URLS[0];

    return QUrl(callback);
}

