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

/*!
    \class BrisaUpnp::BrisaMSearchClientCP brisamsearchclientcp.h BrisaUpnp/BrisaMSearchClientCP
    \brief SSDP MSearch implementation for UPnP control points

    Create a new BrisaMSearchClientCP with the desired service type and mx values, and call start()
    to begin sending discovery messages to possible devices in the multicast group.
    When a device responds to a msearch request, \a msearchResponseReceived() signal is emmited.
*/

/*!
    \internal
    \fn void BrisaMSearchClientCP::msearchResponseReceived(const QString &usn,
                                                           const QString &location,
                                                           const QString &st, const QString &ext,
                                                           const QString &server,
                                                           const QString &cacheControl);

    This signal is emmited every time a valid msearch response is received by the
    BrisaMSearchClientCP.

    It already contains all information in the message headers. So parsing is unnecessary.
*/

/*!
    \internal
    Constructor for BrisaMSearchClientCP.
*/
BrisaMSearchClientCP::BrisaMSearchClientCP(QObject *parent,const QString &serviceType,
                                           int serviceMx) :
    QObject(parent),
    running(false),
    type(serviceType),
    mx(QByteArray::number(serviceMx)),
    SSDP_ADDR("0.0.0.0"),
    SSDP_PORT(1900),
    S_SSDP_PORT("1900")
{
    udpListener = new QUdpSocket(this);
    connect(udpListener, SIGNAL(readyRead()), this, SLOT(datagramReceived()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(discover()));
}

/*!
    \internal
    Stops the BrisaMSearchClientCP if running and destroys the object.
*/
BrisaMSearchClientCP::~BrisaMSearchClientCP()
{
    if (isRunning())
        stop();

    delete udpListener;
    delete timer;
}

/*!
    \internal
    Sends a UPnP discover message to the multicast group with service type and mx values
    defined in the constructor.

    \sa doubleDiscover()
*/
void BrisaMSearchClientCP::discover()
{
    QString discoverMessage = QString(UPNP_MSEARCH_DISCOVER).arg(QString(mx)).arg(type);

    qDebug() << "BrisaMSearch discover message sent";

    udpListener->writeDatagram(discoverMessage.toUtf8(), QHostAddress("239.255.255.250"), 1900);
}

/*!
    \internal
    Sends two discover messages to the multicast group.

    \sa discover()
*/
void BrisaMSearchClientCP::doubleDiscover()
{
    discover();
    discover();
}

/*!
    \internal
    Returns true if the BrisaMSearchClientCP is running.
*/
bool BrisaMSearchClientCP::isRunning() const
{
    return running;
}

/*!
    \internal
    Call this method to listen for UPnP discover responses, and start sending msearch discover
    requests to the multicast group in the given interval.

    \sa stop()
*/
void BrisaMSearchClientCP::start(int interval)
{
    if (!isRunning()) {
        if(!udpListener->bind(QHostAddress(SSDP_ADDR), 1900)) {
            for(qint32 i = 49152; i < 65535; ++i) {
                if(udpListener->bind(QHostAddress(SSDP_ADDR), i)) {
                    break;
                }
            }
        }

        running = true;
        timer->start(interval*1000);

        qDebug() << "BrisaMSearch started - interval: " << interval << "";

    } else {
        qDebug() << "BrisaMSearch already started!";
    }
}

/*!
    \internal
    Disconnect from the network and stop sending UPnP msearch request messages.

    \sa start()
*/
void BrisaMSearchClientCP::stop()
{
    if (isRunning()) {

        udpListener->disconnectFromHost();
        running = false;
        timer->stop();

        qDebug() << "BrisaMSearch stopped!";

    } else {
        qDebug() << "BrisaMSearch already stopped!";
    }
}

/*!
    \internal
    Parser for incoming messages.

    Emits \a msearchResponseReceived() if a valid msearch response is picked up.
*/
void BrisaMSearchClientCP::datagramReceived()
{
    while (udpListener->hasPendingDatagrams()) {

        QByteArray Datagram;

        Datagram.resize(udpListener->pendingDatagramSize());
        udpListener->readDatagram(Datagram.data(), Datagram.size());

        QString Temp(Datagram);
        QHttpResponseHeader *response = new QHttpResponseHeader(Temp);

        if (response->statusCode() == 200) {

            qDebug() << "BrisaMSearch received MSearch answer from " << response->value("usn") << "";

            emit msearchResponseReceived(response->value("usn"),
                                         response->value("location"),
                                         response->value("st"),
                                         response->value("ext"),
                                         response->value("server"),
                                         response->value("cache-control"));
        }

        delete response;
    }
}
