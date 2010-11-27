/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventsubscription.cpp
 * Created:
 * Description: Implements BrisaEventSubscription class.
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
#include "brisaeventsubscription.h"

using namespace Brisa;

BrisaEventSubscription::BrisaEventSubscription(const QString &sid,
        const QStringList &callbackUrls, const int &timeout, QObject *parent) :
            BrisaAbstractEventSubscription(sid, callbackUrls, timeout, parent) {
}

void BrisaEventSubscription::renew(const int &newTimeout) {
    this->date = QDateTime::currentDateTime();
    this->timeout = newTimeout;
}

HttpResponse BrisaEventSubscription::getAcceptSubscriptionResponse() const {
    HttpResponse response(HttpVersion(1, 1), HttpResponse::OK);

    response.setHeader("DATE", QDateTime::currentDateTime().toUTC().toString(
            "ddd, dd MMM yyyy HH:mm:ss").toAscii() + " GMT");

    //FIXME: use system information
    response.setHeader("SERVER", QByteArray("OS/version") + " UPnP/1.0"
                       + QByteArray("product/version"));

    response.setHeader("SID", QByteArray("uuid:") + SID.toUtf8());

    response.setHeader("TIMEOUT", (timeout >= 0) ? QByteArray("Second-")
                       + QByteArray::number(timeout) : "infinite");

    return response;
}

HttpResponse BrisaEventSubscription::getAcceptUnsubscriptionResponse() const {
    return HttpResponse(HttpVersion(1, 1), HttpResponse::OK);
}
