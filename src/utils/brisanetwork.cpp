/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename:
 * Created:
 * Description:
 * Authors: Name <email> @since 2009
 *          Jeysibel de Sousa Dantas <jeysibel@gmail.com> @since 05/05/2010
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
#include <QTcpSocket>
#include "brisanetwork.h"

QBool isLoopbackIPv4Address(QString address) {
    return QBool(!address.compare("127.0.0.1"));
}

QBool isLoopbackIPv6Address(QString address) {
    return QBool(!address.compare("0:0:0:0:0:0:0:1"));
}

QBool isPromiscuousIPv4Address(QString address) {
    return QBool(!address.compare("0.0.0.0"));
}

QBool isPromiscuousIPv6Address(QString address) {
    return QBool(!address.compare("0:0:0:0:0:0:0:0") | !address.compare("::"));
}

QString getValidIP() {
    foreach(QHostAddress addressEntry , QNetworkInterface::allAddresses() )
        {
            QString address = addressEntry.toString();
            if (!(isLoopbackIPv4Address(address)) && !(isLoopbackIPv6Address(
                    address)) && !(isPromiscuousIPv4Address(address))
                    && !(isPromiscuousIPv6Address(address))) {
                return address;
            }
        }
    qDebug()
            << "Couldn't acquire a non loopback IP  address,returning 127.0.0.1.";

    //TODO refactor this when IPv6 becomes to be fully supported
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

QBool isPortOpen(QString address, qint16 port, qint16 timeout) {
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost(address, port);
    socket->waitForConnected(timeout);
    switch (socket->state()) {
    case QAbstractSocket::UnconnectedState:
        return QBool(false);
        delete socket;
        break;

    case QAbstractSocket::ConnectingState:
        //stay waiting for some miliseconds to re-verify the state
        socket->waitForConnected(timeout);
        if (socket->state() == QAbstractSocket::ConnectedState) {
            return QBool(true);
        } else {
            return QBool(false);
        }
        delete socket;
        break;

    case QAbstractSocket::ConnectedState:
        return QBool(true);
        delete socket;
        break;
    }
    delete socket;
    return QBool(false);
}

quint16 getPort() {
    srand( time(NULL));
    //Generate a port number in range [49152,65535]
    //TODO modify this expression to a more legible one
    quint16 randomPort =
            (49152 + rand()/ (RAND_MAX / (65535 - 49152 + 1) + 1));
    qDebug() <<  "Porta Valor:" << randomPort;
    while (isPortOpen(getValidIP(), randomPort)) {
        qDebug() << "Port is already opened, trying another ";
        randomPort = (49152 + rand() / (RAND_MAX / (65535 - 49152 + 1) + 1));
    }
    return randomPort;
}

