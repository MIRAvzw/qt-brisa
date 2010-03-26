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
#include <QIODevice>

#include "brisanetwork.h"

QString getIp(QString networkInterface)
{
    foreach( QNetworkInterface interface, QNetworkInterface::allInterfaces() ){
            foreach( QNetworkAddressEntry addressEntry, interface.addressEntries() ){
                if(interface.name() == networkInterface)
                    return QHostAddress( addressEntry.ip() ).toString();
                }
     }
    return "";
}

quint16 getPort()
{
    srand((unsigned)time(NULL));
    return (49152 + rand() / (RAND_MAX / (65535 - 49152 + 1) + 1));
}

