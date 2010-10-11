/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstracteventsubscription.h
 * Created:
 * Description: This file defines the BrisaAbstractEventSubscription class.
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

#ifndef _BRISAABSTRACTEVENTSUBSCRIPTION_H
#define _BRISAABSTRACTEVENTSUBSCRIPTION_H

#include <QDateTime>
#include <QList>
#include <QString>
#include <QHttpResponseHeader>
#include <QObject>
#include <QtCore>

#include "brisaglobal.h"

#ifdef USE_NEW_BRISA_WEBSERVER
#include "brisawebservice.h"
#endif

namespace BrisaUpnp {

/*!
 * \class BrisaUpnp::BrisaAbstractEventSubscription brisaabstracteventsubscription.h BrisaUpnp/BrisaAbstractEventSubscription
 *
 * \brief Abstract class that represents an event subscription
 */
#ifdef USE_NEW_BRISA_WEBSERVER
class BRISA_UPNP_EXPORT BrisaAbstractEventSubscription: virtual public ::BrisaCore::BrisaWebService {
#else
class BRISA_UPNP_EXPORT BrisaAbstractEventSubscription: virtual public QObject {
#endif
Q_OBJECT

public:

    /*!
     * Construtcs an abstract event subscription with given \a sid, list of
     * \a callbackUrls, \a timeout and \a parent. \a timeout less than 0 means
     * infinite.
     */
    BrisaAbstractEventSubscription(const QString &sid,
            const QStringList &callbackUrls, const int &timeout = -1, // <0 = infinite
            QObject *parent = 0);

    /*!
     * Renews the subscription for the given \a newTimeout.
     */
    virtual void renew(const int &newTimeout = -1) = 0; // <0 = infinite

    /*!
     * Checks if the subscription has already expired. Returns true if it has
     * expired, else returns false.
     */
    bool hasExpired() const;

    /*!
     * Returns the next event key for this subscription.
     */
    quint32 getNextSeq();

    /*!
     * Returns this subscription's SID.
     */
    QString getSid() const;

    /*!
     * Returns this subscription's list of callback URLs.
     */
    QStringList getCallbackUrls() const;

    /*!
     * Returns this subscription's first callback URL.
     */
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
