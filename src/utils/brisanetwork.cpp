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

#include <QtDebug>
#include <QIODevice>

#include "brisanetwork.h"



QBool isLoopbackIPv4Address(QString address) {
    return QBool(!address.compare("127.0.0.1"));
}

QBool isLoopbackIPv6Address(QString address) {
    return QBool(!address.compare("0:0:0:0:0:0:0:1"));
}

QString getValidIP() {
    foreach(QHostAddress addressEntry , QNetworkInterface::allAddresses() )
        {
            QString address = addressEntry.toString();
            if (!(isLoopbackIPv4Address(address)) && !(isLoopbackIPv6Address(
                    address))) {
                return address;
            }
        }
    qDebug()
            << "Couldn't acquire a non loopback IP  address,returning 127.0.0.1.";
    return "127.0.0.1";
}


//TODO deprecated function
QString getIp(QString networkInterface) {
    foreach( QNetworkInterface interface, QNetworkInterface::allInterfaces() )
        {
            foreach( QNetworkAddressEntry addressEntry, interface.addressEntries() )
                {
                    if (interface.name() == networkInterface)
                        return QHostAddress(addressEntry.ip()).toString();
                }
        }
    return "";
}

quint16 getPort() {
    srand((unsigned) time(NULL));
    return (49152 + rand() / (RAND_MAX / (65535 - 49152 + 1) + 1));
}

