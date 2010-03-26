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

#ifndef _BRISASSDPSERVER_H
#define _BRISASSDPSERVER_H

#include <QUdpSocket>
#include <QHttpRequestHeader>
#include <QMap>
#include <QString>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaSSDPServer : public QObject
{
    Q_OBJECT

    public:
        BrisaSSDPServer(QObject *parent = 0);
        virtual ~BrisaSSDPServer();

    public slots:
        bool isRunning();
        void start();
        void stop();

        void doNotify(const QString &usn, const QString &location, const QString &st,
                      const QString &server, const QString &cacheControl);

        void doByeBye(const QString &usn, const QString &st);

        void respondMSearch(const QString &senderIp, quint16 senderPort,
                            const QString &cacheControl, const QString &date,
                            const QString &location, const QString &server,
                            const QString &st, const QString &usn);

    signals:
        void msearchRequestReceived(const QString &st, const QString &senderIp,
                                    quint16 senderPort);

    private slots:
        void msearchReceived(QHttpRequestHeader *datagram, QHostAddress *senderIp,
                             quint16 senderPort);
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
