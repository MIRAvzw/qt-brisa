/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisassdpclient.cpp
 * Created:
 * Description: This File implements the BrisaSSDPClient class.
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

#include "brisassdpclient.h"

#include <QtDebug>
#ifdef Q_WS_X11
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <string.h>

using namespace BrisaUpnp;

BrisaSSDPClient::BrisaSSDPClient(QObject *parent) :
	QObject(parent),
	running(false),
	SSDP_ADDR("239.255.255.250"),
	SSDP_PORT(1900),
	S_SSDP_PORT("1900") {

    udpListener = new QUdpSocket(parent);
    connect(udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));
}

BrisaSSDPClient::~BrisaSSDPClient() {
    if (isRunning())
        stop();

    delete udpListener;
}

void BrisaSSDPClient::start() {
    if (!isRunning()) {
        int fd;

        if (!udpListener->bind(SSDP_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
            qDebug() << "BrisaSSDPClient BIND FAIL!";
		}

        fd = udpListener->socketDescriptor();
        struct ip_mreq mreq;
        memset(&mreq, 0, sizeof(struct ip_mreq));
        mreq.imr_multiaddr.s_addr = inet_addr(SSDP_ADDR.toUtf8());
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);

        if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mreq,
                sizeof(struct ip_mreq)) < 0) {
            qDebug() << "Brisa SSDP Client: Could not join MULTICAST group";
            return;
        }

        running = true;
    } else {
        qDebug() << "Brisa SSDP Client: Already running!";
    }
}

void BrisaSSDPClient::stop() {
    if (isRunning()) {
        udpListener->disconnectFromHost();
        running = false;
    } else {
        qDebug() << "Brisa SSDP Client: Already stopped!";
    }
}

bool BrisaSSDPClient::isRunning() const {
    return running;
}

void BrisaSSDPClient::datagramReceived() {
    while (udpListener->hasPendingDatagrams()) {
        QByteArray *Datagram = new QByteArray();

        Datagram->resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(Datagram->data(), Datagram->size());

        QString Temp(Datagram->data());
        QHttpRequestHeader *Parser = new QHttpRequestHeader(Temp);

        notifyReceived(Parser);

        delete Datagram;
        delete Parser;
    }

}

void BrisaSSDPClient::notifyReceived(QHttpRequestHeader *datagram) {
    if (!datagram->hasKey("nts"))
        return;

    if (datagram->value("nts") == "ssdp:alive") {
        emit newDeviceEvent(datagram->value("usn"),
                datagram->value("location"), datagram->value("nt"),
                datagram->value("ext"), datagram->value("server"),
                datagram->value("cacheControl"));

        qDebug() << "Brisa SSDP Client: Received alive from " << datagram->value(
                "usn") << "";
    } else if (datagram->value("nts") == "ssdp:byebye") {
        emit removedDeviceEvent(datagram->value("usn"));

        qDebug() << "Brisa SSDP Client: Received byebye from " << datagram->value(
                "usn") << "";
    } else {
        qDebug() << "Brisa SSDP Client: Received unknown subtype: "
                << datagram->value("nts") << "";
    }
}
