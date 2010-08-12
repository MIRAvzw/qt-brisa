/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisamsearchclientcp.cpp
 * Created:
 * Description: Implementation of BrisaSearchClientCP class.
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
#include "brisamsearchclientcp.h"

#ifdef Q_WS_X11
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <string.h>

using namespace BrisaUpnp;

#define UPNP_MSEARCH_DISCOVER "M-SEARCH * HTTP/1.1\r\n"       \
                              "HOST: 239.255.255.250:1900\r\n"\
                              "MAN: \"ssdp:discover\"\r\n"    \
                              "MX: %1\r\n"                    \
                              "ST: %2\r\n"                    \
                              "\r\n"

BrisaMSearchClientCP::BrisaMSearchClientCP(QObject *parent,
        const QString &serviceType, int serviceMx) :
    QObject(parent), running(false), type(serviceType), mx(QByteArray::number(
            serviceMx)), SSDP_ADDR("0.0.0.0"), SSDP_PORT(1900), S_SSDP_PORT(
            "1900") {
    udpListener = new QUdpSocket(this);
    connect(udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(discover()));
}

BrisaMSearchClientCP::~BrisaMSearchClientCP() {
    if (isRunning())
        stop();

    delete udpListener;
    delete timer;
}

void BrisaMSearchClientCP::discover() {
    QString discoverMessage =
            QString(UPNP_MSEARCH_DISCOVER).arg(QString(mx)).arg(type);

    qDebug() << "BrisaMSearch discover message sent";

    udpListener->writeDatagram(discoverMessage.toUtf8(), QHostAddress(
            "239.255.255.250"), 1900);
}

void BrisaMSearchClientCP::doubleDiscover() {
    discover();
    discover();
}

bool BrisaMSearchClientCP::isRunning() const {
    return running;
}

void BrisaMSearchClientCP::start(int interval) {
    if (!isRunning()) {
        if (!udpListener->bind(QHostAddress(SSDP_ADDR), 1900)) {
            // TODO remove these magic numbers!
            for (qint32 i = 49152; i < 65535; ++i) {
                if (udpListener->bind(QHostAddress(SSDP_ADDR), i)) {
                    break;
                }
            }
        }

        running = true;
        timer->start(interval * 1000);

        qDebug() << "BrisaMSearch started - interval: " << interval << "";

    } else {
        qDebug() << "BrisaMSearch already started!";
    }
}

void BrisaMSearchClientCP::stop() {
    if (isRunning()) {

        udpListener->disconnectFromHost();
        running = false;
        timer->stop();

        qDebug() << "BrisaMSearch stopped!";

    } else {
        qDebug() << "BrisaMSearch already stopped!";
    }
}

void BrisaMSearchClientCP::datagramReceived() {
    while (udpListener->hasPendingDatagrams()) {

        QByteArray Datagram;

        Datagram.resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(Datagram.data(), Datagram.size());

        QString temp(Datagram);
        QHttpResponseHeader *response = new QHttpResponseHeader(temp);

        if (response->statusCode() == 200) {
            QString usn = response->value("usn");
            if (usn.startsWith("uuid:")) {
                qDebug() << "BrisaMSearch received MSearch answer from "  << usn << "";
                emit msearchResponseReceived(response->value("usn"),
                                             response->value("location"),
                                             response->value("st"),
                                             response->value("ext"),
                                             response->value("server"),
                                             response->value("cache-control"));
            } else {
                qDebug() << "BrisaMSearch received MSearch from " << response->value("location")
                         << " but it does not start with string \"uuid:\". USN field is " << usn;
            }
        }

        delete response;
    }
}
