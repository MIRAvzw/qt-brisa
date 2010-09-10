/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaudplistener.cpp
 * Created:
 * Description: This File implements the BrisaUdpListener class.
 * Authors: Danilo Araujo de Freitas <dsurviver@gmail.com> @since 2010
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


#include "brisaudplistener.h"

#ifdef Q_WS_X11
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <cstring>

BrisaUdpListener::BrisaUdpListener(QString address, quint32 port,
                                   QString bindErrorMessage,
                                   QString joinErrorMessage, QObject *parent) :
        QUdpSocket(parent)
{
    this->address = address;
    this->port = port;
    this->bindErrorMessage = bindErrorMessage;
    this->joinErrorMessage = joinErrorMessage;
    this->bind(QHostAddress(address), port);
}

BrisaUdpListener::~BrisaUdpListener()
{
}

void BrisaUdpListener::start()
{
    int fd;

    if (!this->bind(this->port, QUdpSocket::ShareAddress |
                                 QUdpSocket::ReuseAddressHint)) {
        qDebug() << this->bindErrorMessage;
    }

    fd = this->socketDescriptor();
    struct ip_mreq mreq;
    memset(&mreq, 0, sizeof(struct ip_mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(this->address.toUtf8());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mreq,
            sizeof(struct ip_mreq)) < 0) {
        qDebug() << this->joinErrorMessage;
    }
}
