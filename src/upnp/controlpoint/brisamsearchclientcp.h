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

#ifndef _BRISAMSEARCHCLIENT_H
#define _BRISAMSEARCHCLIENT_H

#include <QUdpSocket>
#include <QTimer>
#include <QHttpResponseHeader>

#include "brisaglobal.h"

#define DEFAULT_SEARCH_TIME 600
#define DEFAULT_SEARCH_TYPE "ssdp:all"

namespace BrisaUpnp{

class BRISA_UPNP_EXPORT BrisaMSearchClientCP : public QObject
{
    Q_OBJECT

    public:
        BrisaMSearchClientCP(QObject *parent = 0,
                             const QString &type = DEFAULT_SEARCH_TYPE,
                             int mx = 5);
        virtual ~BrisaMSearchClientCP();

        void doubleDiscover();
        bool isRunning() const;
        void start(int interval = DEFAULT_SEARCH_TIME);
        void stop();

    public slots:
        void discover();

    private slots:
        void datagramReceived();

    signals:
        void msearchResponseReceived(const QString &usn, const QString &location,
                                     const QString &st, const QString &ext,
                                     const QString &server, const QString &cacheControl);

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
