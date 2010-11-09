/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename:
 * Created:
 * Description:
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

#ifndef _BRISANETWORK_H
#define _BRISANETWORK_H

#include <QString>
#include <QList>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QtDebug>
#include <QObject>
#include <ctime>

#include "brisaglobal.h"


#define LOCAL_HOST "127.0.0.1"

/*!
 * Gets an valid IP address from an active interface on the host computer.
 *
 */
BRISA_UTILS_EXPORT QString getValidIP();

/*!
 *  Gets an valid IP address from an specific interface.
 *  \param networkInterface \a The interface to acquire the IP Address from.
 */
BRISA_UTILS_EXPORT QString getIp(QString networkInterface);

/*!
 *  Gets an closed port to be used by the BrisaWebServer.
 */
BRISA_UTILS_EXPORT quint16 getPort();

/*!
 *  Verify if this address is a loopback ipv4 address or not.
 *  \param address \a The address to be tested
 */
BRISA_UTILS_EXPORT QBool isLoopbackIPv4Address(QString address);

/*!
 *  Verify if this address is a loopback ipv6 address or not.
 *  \param address \a The address to be tested
 */
BRISA_UTILS_EXPORT QBool isLoopbackIPv6Address(QString address);

/*!
 *  Verify if this address is a Promiscous ipv4 address or not.
 *  \param address \a The address to be tested
 */
BRISA_UTILS_EXPORT QBool isPromiscuousIPv4Address(QString address);

/*!
 *  Verify if this address is a Promiscous ipv6 address or not.
 *  \param address \a The address to be tested
 */
BRISA_UTILS_EXPORT QBool isPromiscuousIPv6Address(QString address);

/*!
 *  Verify if an port is currently opened on this host.
 *  \param address \a the IP address
 *  \param port    \a the port to be tested
 *  \param timeout \a the timeout to end the test
 */
BRISA_UTILS_EXPORT QBool isPortOpen(QString address, qint16 port, qint16 timeout = 2);

#endif /* _BRISANETWORK_H */

