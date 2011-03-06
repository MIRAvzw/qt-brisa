/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisassdpserver.cpp
 * Created:
 * Description: Implements BrisaSSDPServer class.
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
#include "brisassdpserver.h"

#include <QtDebug>
#ifdef Q_OS_UNIX
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <string.h>

using namespace Brisa;

// TODO: Add this three fields commented below in the ALIVE_MESSAGE 
// as per upnp spec 1.1, section 1.2.2.
//  - BOOTID.UPNP.ORG
//  - CONFIGID.UPNP.ORG
//  - SEARCHPORT.UPNP.ORG (optional)
// TODO: Make IP and port below another #define and replace message below
static const QString UPNP_ALIVE_MESSAGE = "NOTIFY * HTTP/1.1\r\n"
                                          "HOST: 239.255.255.250:1900\r\n"
                                          "CACHE-CONTROL: max-age=%1\r\n"
                                          "LOCATION: %2\r\n"
                                          "NT: %3\r\n"
                                          "NTS: ssdp:alive\r\n"
                                          "SERVER: %4\r\n"
                                          "USN: %5\r\n"
                                          "\r\n";

// TODO: Implement ssdp:update as per spec 1.1, section 1.2.4
// and use the below define to build the message, where
// SEARCHPORT.UPNP.ORG are optional.
// TODO: Make IP and port below another #define and replace message below
static const QString UPNP_UPDATE_MESSAGE = "NOTIFY * HTTP/1.1\r\n"
                                           "HOST: 239.255.255.250:1900\r\n"
                                           "LOCATION: %1\r\n"
                                           "NT: %2\r\n"
                                           "NTS: ssdp:update\r\n"
                                           "USN: %3\r\n"
                                           "CONFIGID.UPNP.ORG: %4\r\n"
                                           "NEXTBOOTID.UPNP.ORG: %5\r\n"
                                           "SEARCHPORT.UPNP.ORG: %6\r\n"
                                           "\r\n";

// TODO: Add this two fields commented below in the BYEBYE MESSAGE
// as per upnp spec 1.1, section 1.2.2 and 1.2.3.
//  - BOOTID.UPNP.ORG
//  - CONFIGID.UPNP.ORG
// TODO: Make IP and port below another #define and replace message below
static const QString UPNP_BYEBYE_MESSAGE = "NOTIFY * HTTP/1.1\r\n"
                                           "HOST: 239.255.255.250:1900\r\n"
                                           "NT: %1\r\n"
                                           "NTS: ssdp:byebye\r\n"
                                           "USN: %2\r\n"
                                           "\r\n";

// TODO: Add this three fields commented below in the MSEARCH_RESPONSE
// as per upnp spec 1.1, section 1.3.3.
//  - BOOTID.UPNP.ORG
//  - CONFIGID.UPNP.ORG
//  - SEARCHPORT.UPNP.ORG (optional)
static const QString UPNP_MSEARCH_RESPONSE = "HTTP/1.1 200 OK\r\n"
                                             "CACHE-CONTROL: max-age = %1\r\n"
                                             "DATE: %2\r\n"
                                             "EXT: \r\n"
                                             "LOCATION: %3\r\n"
                                             "SERVER: %4\r\n"
                                             "ST: %5\r\n"
                                             "USN: %6\r\n"
                                             "\r\n";

BrisaSSDPServer::BrisaSSDPServer(QObject *parent) :
    QObject(parent),
    running(false),
    SSDP_ADDR("239.255.255.250"), // TODO: make this as #define
    SSDP_PORT(1900), // TODO: make this as #define
    S_SSDP_PORT("1900") // TODO: make this as #defin
{
    this->udpListener = new BrisaUdpListener(SSDP_ADDR, SSDP_PORT, "Brisa SSDP Server", parent);
    connect(this->udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));
}

BrisaSSDPServer::~BrisaSSDPServer() {
    if (isRunning())
        stop();

    delete this->udpListener;
}

void BrisaSSDPServer::start() {
    if (!isRunning()) {
        this->udpListener->start();
        qDebug() << "BrisaSSDPServer Started!";
        running = true;
    }
    else
    {
        qDebug() << "BrisaSSDPServer already running!";
    }
}

void BrisaSSDPServer::stop() {
    if (isRunning()) {
        udpListener->disconnectFromHost();
        running = false;
    } else {
        qDebug() << "BrisaSSDPServer already stopped!";
    }
}

bool BrisaSSDPServer::isRunning() {
    return running;
}

void BrisaSSDPServer::doNotify(const QString &usn,
                               const QString &location,
                               const QString &st,
                               const QString &server,
                               const QString &cacheControl)
{
    QString message = UPNP_ALIVE_MESSAGE.arg(cacheControl, location, st, server, usn);

    udpListener->writeDatagram(message.toUtf8(),
                               QHostAddress(SSDP_ADDR),
                               SSDP_PORT);

    udpListener->writeDatagram(message.toUtf8(),
                               QHostAddress(SSDP_ADDR),
                               SSDP_PORT);

    qDebug() << "BrisaSSDPServer writing Notify alive for: " << usn << "";
}

void BrisaSSDPServer::doByeBye(const QString &usn, const QString &st) {
    QString message = UPNP_BYEBYE_MESSAGE.arg(st, usn);

    udpListener->writeDatagram(message.toUtf8(),
                               QHostAddress(SSDP_ADDR),
                               SSDP_PORT);

    udpListener->writeDatagram(message.toUtf8(),
                               QHostAddress(SSDP_ADDR),
                               SSDP_PORT);

    qDebug() << "BrisaSSDPServer writing notify byebye for: " << usn << "";
}

void BrisaSSDPServer::datagramReceived() {
    while (this->udpListener->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress *senderIP = new QHostAddress();
        quint16 senderPort;

        datagram.resize(this->udpListener->pendingDatagramSize());
        this->udpListener->readDatagram(datagram.data(),
                                        datagram.size(),
                                        senderIP,
                                        &senderPort);

        QString temp(datagram);
        QHttpRequestHeader *parser = new QHttpRequestHeader(temp);

        this->msearchReceived(parser, senderIP, senderPort);

        delete senderIP;
        delete parser;
    }
}

void BrisaSSDPServer::msearchReceived(QHttpRequestHeader *datagram,
                                      QHostAddress *senderIp,
                                      quint16 senderPort)
{
    if (!datagram->hasKey("man"))
        return;

    if (datagram->value("man") == "\"ssdp:discover\"") {
        qDebug() << "BrisaSSDPServer Received msearch from "
                 << senderIp->toString() << ":" << senderPort
                 << " Search target: " << datagram->value("st");

        emit msearchRequestReceived(datagram->value("st"),
                                    senderIp->toString(),
                                    senderPort);
    }
}

void BrisaSSDPServer::respondMSearch(const QString &senderIp,
                                     quint16 senderPort,
                                     const QString &cacheControl,
                                     const QString &date,
                                     const QString &location,
                                     const QString &server,
                                     const QString &st,
                                     const QString &usn)
{
    QString message = UPNP_MSEARCH_RESPONSE.arg(cacheControl, date, location, server, st, usn);

    this->udpListener->writeDatagram(message.toUtf8(),
                                     QHostAddress(senderIp),
                                     senderPort);

    qDebug() << "BrisaSSDPServer writing msearch response for " << senderIp << ":" << senderPort;
}
