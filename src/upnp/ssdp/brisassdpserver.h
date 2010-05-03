/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisassdpserver.h
 * Created:
 * Description: This File implements the BrisaSSDPServer class.
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

#ifndef _BRISASSDPSERVER_H
#define _BRISASSDPSERVER_H

#include <QUdpSocket>
#include <QHttpRequestHeader>
#include <QMap>
#include <QString>

#include "brisaglobal.h"

namespace BrisaUpnp {

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
class BRISA_UPNP_EXPORT BrisaSSDPServer: public QObject {
Q_OBJECT

public:
    /*!
     *  Constructs a BrisaSSDPServer with the given parent object.
     *
     *  \param parent parent
     */
    BrisaSSDPServer(QObject *parent = 0);

    /*!
     *  Destroys the Object.
     *
     *  Stops the server if running.
     */
    virtual ~BrisaSSDPServer();

public slots:
    /*!
     *  Checks if BrisaSSDPServer is running.
     *
     *  \return true if is running
     */
    bool isRunning();

    /*!
     *  Joins the multicast group and
     *  starts listening for UPnP msearch responses.
     *
     *  \sa stop()
     */
    void start();

    /*!
     *  Stops the BrisaSSDPServer.
     *
     *  \sa start()
     */
    void stop();

    /*!
     *  Sends a UPnP notify alive message to the multicast group with the given information.
     *
     *  \param usn \a empty
     *  \param location \a empty
     *  \param st \a empty
     *  \param server \a empty
     *  \param cacheControl \a empty
     *
     *  \sa doByeBye()
     */
    void doNotify(const QString &usn, const QString &location,
            const QString &st, const QString &server,
            const QString &cacheControl);

    /*!
     *  Sends a UPnP notify byebye message to the multicast group with the given information.
     *
     *  \param usn \a empty
     *  \param st \a empty
     *
     *  \sa doNotify()
     */
    void doByeBye(const QString &usn, const QString &st);

    /*!
     *  Sends a UPnP msearch response message to the given sender IP address and port.
     *
     *  Connect this slot to a proper signal to get synchronous response for msearch requests.
     *
     *  \param sender Ip \a empty
     *  \param senderPort \a empty
     *  \param cacheControl \a empty
     *  \param date \a empty
     *  \param location \a empty
     *  \param server \a empty
     *  \param st \a empty
     *  \param usn \a empty
     *
     *  \sa msearchRequestReceived()
     */
    void respondMSearch(const QString &senderIp, quint16 senderPort,
            const QString &cacheControl, const QString &date,
            const QString &location, const QString &server, const QString &st,
            const QString &usn);

signals:
    /*!
     *  \fn void BrisaSSDPServer::msearchRequestReceived(const QString &st, const QString &senderIp,
     quint16 senderPort)
     *
     *  This signal is emmited when the BrisaSSDPServer receives a valid UPnP msearch request.
     *
     *  \param st \a empty
     *  \param senderIp \a empty
     *  \param senderPort \a empty
     *
     *  \sa respondMSearch()
     */
    void msearchRequestReceived(const QString &st, const QString &senderIp,
            quint16 senderPort);

private slots:
    /*!
     *  \internal
     *  Emits msearchRequestReceived if the incoming message is a valid msearch.
     *
     *  \param datagram \a empty
     *  \param senderIp \a empty
     *  \param senderPort \a empty
     */
    void msearchReceived(QHttpRequestHeader *datagram, QHostAddress *senderIp,
            quint16 senderPort);

    /*!
     *  \internal
     *  This slot is called when the readyRead() signal is emmited by the QUdpSocket listening
     *  to incoming messages.
     */
    void datagramReceived();

private:
    bool running;
    QString SSDP_ADDR;
    int SSDP_PORT;
    QString S_SSDP_PORT;

    QUdpSocket *udpListener;
};

}

#endif /* _BRISASSDPSERVER_H */
