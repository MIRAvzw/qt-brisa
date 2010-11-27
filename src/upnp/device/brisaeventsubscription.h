/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventsubscription.h
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
#ifndef _BRISAEVENTSUBSCRIPTION_H
#define _BRISAEVENTSUBSCRIPTION_H

#include "brisaabstracteventsubscription.h"
#include "brisaglobal.h"

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>

#include <httpresponse.h>

namespace Brisa {

    class BRISA_UPNP_EXPORT BrisaEventSubscription: public BrisaAbstractEventSubscription {
    Q_OBJECT

    public:
        BrisaEventSubscription(const QString &sid, const QStringList &callbackUrls,
                const int &timeout = -1, // <0 = infinite
                QObject *parent = 0);

        void renew(const int &newTimeout = -1); // <0 = infinite
        HttpResponse getAcceptSubscriptionResponse() const;
        HttpResponse getAcceptUnsubscriptionResponse() const;
    };

}

#endif /* _BRISAEVENTSUBSCRIPTION_H */
