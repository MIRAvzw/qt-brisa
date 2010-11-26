/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisamsearchclientcp.h
 * Created:
 * Description: Description of BrisaSearchClientCP class.
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
#ifndef _BRISAMSEARCHCLIENT_H
#define _BRISAMSEARCHCLIENT_H

#include <QUdpSocket>
#include <QTimer>
#include <QHttpResponseHeader>

#include "brisaglobal.h"

#define DEFAULT_SEARCH_TIME 600
#define DEFAULT_SEARCH_TYPE "ssdp:all"

namespace Brisa {

/*!
 \class Brisa::BrisaMSearchClientCP brisamsearchclientcp.h BrisaUpnp/BrisaMSearchClientCP
 \brief SSDP MSearch implementation for UPnP control points

 Create a new BrisaMSearchClientCP with the desired service type and mx values, and call start()
 to begin sending discovery messages to possible devices in the multicast group.
 When a device responds to a msearch request, \a msearchResponseReceived() signal is emmited.
 */
class BRISA_UPNP_EXPORT BrisaMSearchClientCP: public QObject {
Q_OBJECT

public:

    /*!
     *  \internal
     *  Constructor for BrisaMSearchClientCP.
     */
    BrisaMSearchClientCP(QObject *parent = 0, const QString &type =
            DEFAULT_SEARCH_TYPE, int mx = 5);

    /*!
     *  \internal
     *  Stops the BrisaMSearchClientCP if running and destroys the object.
     */
    virtual ~BrisaMSearchClientCP();

    /*!
     *  \internal
     *  Sends two discover messages to the multicast group.
     *  \sa discover()
     */
    void doubleDiscover();

    /*!
     *  \internal
     *  Checks if the BrisaMSearchClientCP is running.
     *  \return true if running
     */
    bool isRunning() const;

    /*!
     *  \internal
     *  Call this method to listen for UPnP discover responses, and start sending msearch discover
     *  requests to the multicast group in the given interval.
     *  \param interval interval for discover requests
     *  \sa stop()
     */
    void start(int interval = DEFAULT_SEARCH_TIME);

    /*!
     *  \internal
     *  Disconnect from the network and stop sending UPnP msearch request messages.
     *  \sa start()
     */
    void stop();

public slots:
    /*!
     *   \internal
     *   Sends a UPnP discover message to the multicast group with service type and mx values
     *   defined in the constructor.
     *   \sa doubleDiscover()
     */
    void discover();

private slots:
    /*!
     *  \internal
     *  Parser for incoming messages.
     *  Emits \a msearchResponseReceived() if a valid msearch response is picked up.
     */
    void datagramReceived();

signals:
    /*!
     *  \internal
     *  \fn void BrisaMSearchClientCP::msearchResponseReceived(const QString &usn,
     *                                                         const QString &location,
     *                                                         const QString &st, const QString &ext,
     *                                                         const QString &server,
     *                                                         const QString &cacheControl);
     *  This signal is emmited every time a valid msearch response is received by the
     *  BrisaMSearchClientCP.
     *  It already contains all information in the message headers. So parsing is unnecessary.
     */
    void msearchResponseReceived(const QString &usn, const QString &location,
            const QString &st, const QString &ext, const QString &server,
            const QString &cacheControl);

private:
    QTimer *timer;
    bool running;
    int interval;
    QUdpSocket *udpListener;

    QString type;
    QByteArray mx;

    QString SSDP_ADDR;
    int SSDP_PORT;
    QString S_SSDP_PORT;
};

}

#endif /* _BrisaMSearchClientCP_H */
