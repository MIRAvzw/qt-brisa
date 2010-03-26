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

/*!
 *  \class BrisaUpnp::BrisaSSDPClient brisassdpclient.h BrisaUpnp/BrisaSSDPClient
 *  \brief SSDP stack implementantion for UPnP control points.
 *
 *  Create a new BrisaSSCPClient and call "start()" to connect to the multicast
 *  group and start listening to ssdp notification messages.
 *
 *  When BrisaSSDPClient receives a notification message it emits \a "newDeviceEvent()"
 *  in case of "ssdp:alive" and \a "removedDeviceEvent" in case of "ssdp:byebye".
 *  Other ssdp messages will be ignored.
 */

/*!
 *  \fn void BrisaSSDPClient::newDeviceEvent(const QString &usn, const QString &location,
                                             const QString &st, const QString &ext,
                                             const QString &server, const QString &cacheControl)

 *  This signal is emitted when the client receives a "ssdp:alive" message from a device joining
 *  the network

 *  \sa removedDeviceEvent()
 */

/*!
 *  \fn void BrisaSSDPClient::removedDeviceEvent(const QString &usn)
 *
 *  This signal is emitted when the client receives a "ssdp:byebye" message from a device leaving the
 *  network
 *
 *  \sa newDeviceEvent()
 */

/*!
 *  Constructs a BrisaSSCPClient with the given parent.
 */
BrisaSSDPClient::BrisaSSDPClient(QObject *parent)
    : QObject(parent),
      running(false),
      SSDP_ADDR("239.255.255.250"),
      SSDP_PORT(1900),
      S_SSDP_PORT("1900")
{
    udpListener = new QUdpSocket(parent);

    connect(udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));
}

/*!
 *  Destroys the client.
 *
 *  Stops the client if it's running.
 */
BrisaSSDPClient::~BrisaSSDPClient()
{
    if(isRunning())
        stop();

    delete udpListener;
}

/*!
 *
 *  Connects to the MultiCast group and starts the client.
 *
 *  \sa isRunning(), stop()
 */
void BrisaSSDPClient::start()
{
    if (!isRunning()) {
        int fd;

        if (!udpListener->bind(SSDP_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint))
            qDebug() << "BrisaSSDPClient BIND FAIL!";

        fd = udpListener->socketDescriptor();
        struct ip_mreq mreq;
        memset(&mreq, 0, sizeof(struct ip_mreq));
        mreq.imr_multiaddr.s_addr = inet_addr(SSDP_ADDR.toUtf8());
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);

        if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(struct ip_mreq)) < 0) {
            qDebug() << "BrisaSSDPClient could not join MULTICAST group";
            return;
        }

        running = true;
    } else {
        qDebug() << "BrisaSSDPClient already running!";
    }
}

/*!
 *  Stops the client.
 *
 *  \sa isRunning(), start()
 */
void BrisaSSDPClient::stop()
{
    if (isRunning()) {
        udpListener->disconnectFromHost();
        running = false;
    } else {
        qDebug() << "BrisaSSDPClient already stopped!";
    }
}

/*!
 *  Returns true if the client is running.
 */
bool BrisaSSDPClient::isRunning() const
{
    return running;
}

/*!
 *  \internal
 *  Receives UDP datagrams from a QUdpSocket.
 */
void BrisaSSDPClient::datagramReceived()
{
    while (udpListener->hasPendingDatagrams()) {
        QByteArray Datagram;
        QList<QByteArray> cmd;

        Datagram.resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(Datagram.data(), Datagram.size());

        QString Temp(Datagram);
        QHttpRequestHeader *Parser = new QHttpRequestHeader(Temp);

        notifyReceived(Parser);

        delete Parser;
    }
}


/*!
 *  \internal
 *  Parses the UDP datagram received from "datagramReceived()".
 */
void BrisaSSDPClient::notifyReceived(QHttpRequestHeader *datagram)
{
    if (!datagram->hasKey("nts"))
        return;

    if (datagram->value("nts") == "ssdp:alive") {
        emit newDeviceEvent(datagram->value("usn"), datagram->value("location"),
                            datagram->value("nt"), datagram->value("ext"),
                            datagram->value("server"), datagram->value("cacheControl"));

        qDebug() << "BrisaSSDPClient received alive from " << datagram->value("usn") << "";
    }
    else if (datagram->value("nts") == "ssdp:byebye") {
        emit removedDeviceEvent(datagram->value("usn"));

        qDebug() << "BrisaSSDPClient received byebye from " << datagram->value("usn") << "";
    }
    else {
        qDebug() << "BrisaSSDPClient received unknown subtype: "
                 << datagram->value("nts") << "";
    }
}
