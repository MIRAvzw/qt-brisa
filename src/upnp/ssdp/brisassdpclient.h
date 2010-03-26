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

#ifndef _BRISASSDPCLIENT_H
#define _BRISASSDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHttpRequestHeader>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaSSDPClient : public QObject
{
    Q_OBJECT

    public:
        BrisaSSDPClient(QObject *parent = 0);
        ~BrisaSSDPClient();

    public slots:
        void start();
        void stop();
        bool isRunning() const;

    signals:
        void newDeviceEvent(const QString &usn, const QString &location, const QString &st,
                            const QString &ext, const QString &server, const QString &cacheControl);
        void removedDeviceEvent(const QString &usn);

    private slots:
        void datagramReceived();
        void notifyReceived(QHttpRequestHeader *datagram);

    private:
        bool running;
        QString SSDP_ADDR;
        int SSDP_PORT;
        QString S_SSDP_PORT;

        QUdpSocket *udpListener;
};

}

#endif /* _BRISASSDPCLIENT_H */
