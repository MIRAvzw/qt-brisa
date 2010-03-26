/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "brisassdpserver.h"

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

#define UPNP_ALIVE_MESSAGE "NOTIFY * HTTP/1.1\r\n"          \
                           "HOST: 239.255.255.250:1900\r\n" \
                           "CACHE-CONTROL: max-age=%1\r\n"  \
                           "LOCATION: %2\r\n"               \
                           "NT: %3\r\n"                     \
                           "NTS: ssdp:alive\r\n"            \
                           "SERVER: %4\r\n"                 \
                           "USN: %5\r\n"                    \
                           "\r\n"

#define UPNP_BYEBYE_MESSAGE "NOTIFY * HTTP/1.1\r\n"          \
                            "HOST: 239.255.255.250:1900\r\n" \
                            "NT: %1\r\n"                     \
                            "NTS: ssdp:byebye\r\n"           \
                            "USN: %2\r\n"                    \
                            "\r\n"

#define UPNP_MSEARCH_RESPONSE "HTTP/1.1 200 OK\r\n"             \
                              "CACHE-CONTROL: max-age = %1\r\n" \
                              "DATE: %2\r\n"                    \
                              "EXT: \r\n"                       \
                              "LOCATION: %3\r\n"                \
                              "SERVER: %4\r\n"                  \
                              "ST: %5\r\n"                      \
                              "USN: %6\r\n"                     \
                              "\r\n"

/*! \class BrisaUpnp::BrisaSSDPServer brisassdpserver.h BrisaUpnp/BrisaSSDPServer
 *  \brief SSDP stack implementation for UPnP devices.
 *
 *  Call \a start() to begin listening for MSearch requests from control points. Whenever a new
 *  msearch request is parsed by the BrisaSSDPServer, a \a msearchRequestReceived() signal is
 *  emmited containning all of the request information. You can connect this signal to some slot
 *  wich calls \a respondMSearch() and get a synchronous response to msearch requests.
 *
 *  BrisaSSDPServer also implements SSDP notify messages. Call \a doNotify() or \a doByeBye()
 *  when entering or leaving the multicast group.
 */

/*!
 *  \fn void BrisaSSDPServer::msearchRequestReceived(const QString &st, const QString &senderIp,
                                                     quint16 senderPort)
 *
 *  This signal is emmited when the BrisaSSDPServer receives a valid UPnP msearch request.
 *
 *  \sa respondMSearch()
 */

/*!
 *  Constructs a BrisaSSDPServer with the given parent object.
 */
BrisaSSDPServer::BrisaSSDPServer(QObject *parent) :
        QObject(parent),
        running(false),
        SSDP_ADDR("239.255.255.250"),
        SSDP_PORT(1900),
        S_SSDP_PORT("1900")
{
    udpListener = new QUdpSocket();

    connect(udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));
}

/*!
 *  Destroys the Object.
 *
 *  Stops the server if running.
 */
BrisaSSDPServer::~BrisaSSDPServer()
{
    if(isRunning())
        stop();

    delete udpListener;
}

/*!
 *  Call this method to join the multicast group and
 *  start listening for UPnP msearch responses.
 *
 *  \sa stop()
 */
void BrisaSSDPServer::start()
{
    if (!isRunning()) {
        if (!udpListener->bind(QHostAddress(SSDP_ADDR), SSDP_PORT, QUdpSocket::ShareAddress))
                qDebug() << "BrisaSSDPServer NOT LISTENING!";

        int fd;
        fd = udpListener->socketDescriptor();

        struct ip_mreq mreq;
        memset(&mreq, 0, sizeof(ip_mreq));
        mreq.imr_multiaddr.s_addr = inet_addr(SSDP_ADDR.toUtf8());
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);

        if (::setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char *)&mreq, sizeof(struct ip_mreq)) < 0) {
            qDebug() << "BrisaSSDPServer could not join MULTICAST group";
            return;
        }

        qDebug() << "BrisaSSDPServer Started!";
        running = true;
    } else {
        qDebug() << "BrisaSSDPServer already running!";
    }
}

/*!
 *  Stops the BrisaSSDPServer.
 *
 *  \sa start()
 */
void BrisaSSDPServer::stop()
{
    if (isRunning()) {
        udpListener->disconnectFromHost();
        running = false;
    } else {
        qDebug() << "BrisaSSDPServer already stopped!";
    }
}

/*!
 *  Returns true if BrisaSSDPServer is running.
 */
bool BrisaSSDPServer::isRunning()
{
    return running;
}

/*!
 *  Sends a UPnP notify alive message to the multicast group with the given information.
 *
 *  \sa doByeBye()
 */
void BrisaSSDPServer::doNotify(const QString &usn, const QString &location, const QString &st,
                               const QString &server, const QString &cacheControl)
{
    QString message = QString(UPNP_ALIVE_MESSAGE).arg(cacheControl).arg(location).arg(st).arg(server).arg(usn);

    udpListener->writeDatagram(message.toUtf8(), QHostAddress(SSDP_ADDR), SSDP_PORT);
    udpListener->writeDatagram(message.toUtf8(), QHostAddress(SSDP_ADDR), SSDP_PORT);

    qDebug() << "BrisaSSDPServer writing Notify alive for: " << usn << "";
}

/*!
 *  Sends a UPnP notify byebye message to the multicast group with the given information.
 *
 *  \sa doNotify()
 */
void BrisaSSDPServer::doByeBye(const QString &usn, const QString &st)
{
    QString message = QString(UPNP_BYEBYE_MESSAGE).arg(st).arg(usn);

    udpListener->writeDatagram(message.toUtf8(), QHostAddress(SSDP_ADDR), SSDP_PORT);
    udpListener->writeDatagram(message.toUtf8(), QHostAddress(SSDP_ADDR), SSDP_PORT);

    qDebug() << "BrisaSSDPServer writing notify byebye for: " << usn << "";
}

/*!
 *  \internal
 *  This slot is called when the readyRead() signal is emmited by the QUdpSocket listening
 *  to incoming messages.
 */
void BrisaSSDPServer::datagramReceived()
{
    while (udpListener->hasPendingDatagrams()) {
        QByteArray Datagram;
        QHostAddress *senderIP = new QHostAddress();
        quint16 senderPort;

        Datagram.resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(Datagram.data(), Datagram.size(), senderIP, &senderPort);

        QString Temp(Datagram);
        QHttpRequestHeader *parser = new QHttpRequestHeader(Temp);

        msearchReceived(parser, senderIP, senderPort);

        delete senderIP;
        delete parser;
    }
}

/*!
 *  \internal
 *  Emits msearchRequestReceived if the incoming message is a valid msearch.
 */
void BrisaSSDPServer::msearchReceived(QHttpRequestHeader *datagram, QHostAddress *senderIp,
                                      quint16 senderPort)
{
    if (!datagram->hasKey("man"))
        return;

    if (datagram->value("man") == "\"ssdp:discover\"") {
        qDebug() << "BrisaSSDPServer Received msearch from " << senderIp->toString() << ":"
                 << senderPort << " Search target: " << datagram->value("st");

        emit msearchRequestReceived(datagram->value("st"),senderIp->toString(), senderPort);
    }
}

/*!
 *  Sends a UPnP msearch response message to the given sender IP address and port.
 *
 *  Connect this slot to a proper signal to get synchronous response for msearch requests.
 *
 *  \sa msearchRequestReceived()
 */
void BrisaSSDPServer::respondMSearch(const QString &senderIp, quint16 senderPort,
                                     const QString &cacheControl, const QString &date,
                                     const QString &location, const QString &server,
                                     const QString &st, const QString &usn)
{
    QString message = QString(UPNP_MSEARCH_RESPONSE).arg(cacheControl).arg(date).arg(location).arg(server).arg(st).arg(usn);

    udpListener->writeDatagram(message.toUtf8(), QHostAddress(senderIp), senderPort);

    qDebug() << "BrisaSSDPServer writing msearch response for: " << senderIp << ":" << senderPort;
}
