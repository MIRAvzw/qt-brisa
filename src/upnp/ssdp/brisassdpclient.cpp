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

using namespace Brisa;

BrisaSSDPClient::BrisaSSDPClient(QObject *parent) :
	QObject(parent),
    running(false)
{
}

BrisaSSDPClient::~BrisaSSDPClient() {
    if (isRunning())
        stop();

    delete this->udpListener;
}

void BrisaSSDPClient::start() {
    if (!isRunning()) {
        this->udpListener = new BrisaUdpListener("239.255.255.250", 1900,
                                                 "BrisaSSDPClient");
        connect(this->udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));
        this->udpListener->start();
        running = true;
    } else {
        qDebug() << "Brisa SSDP Client: Already running!";
    }
}

void BrisaSSDPClient::stop() {
    if (isRunning()) {
        this->udpListener->disconnectFromHost();;
        running = false;
    } else {
        qDebug() << "Brisa SSDP Client: Already stopped!";
    }
}

bool BrisaSSDPClient::isRunning() const {
    return running;
}

void BrisaSSDPClient::datagramReceived() {
    while (this->udpListener->hasPendingDatagrams()) {
        QByteArray *datagram = new QByteArray();

        datagram->resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(datagram->data(), datagram->size());

        QString temp(datagram->data());
        QHttpRequestHeader *parser = new QHttpRequestHeader(temp);

        notifyReceived(parser);

        delete datagram;
        delete parser;
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
        qDebug() << "Brisa SSDP Client: Received alive from " <<
                datagram->value("usn") << "";

    } else if (datagram->value("nts") == "ssdp:byebye") {
        emit removedDeviceEvent(datagram->value("usn"));
        qDebug() << "Brisa SSDP Client: Received byebye from " <<
                datagram->value("usn") << "";

    } else {
        qDebug() << "Brisa SSDP Client: Received unknown subtype: " <<
                datagram->value("nts") << "";
    }
}
