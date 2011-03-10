/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaudplistener.h
 * Created:
 * Description: Defines BrisaUdpListener class.
 * Authors: Danilo Araujo de Freitas <dsurviver@gmail.com> @since 2010
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

#ifndef BRISAUDPLISTENER_H
#define BRISAUDPLISTENER_H

#include <QObject>
#include <QUdpSocket>

#include "brisaglobal.h"
#include "brisanetwork.h"

namespace Brisa {

class BRISA_UPNP_EXPORT BrisaUdpListener : public QUdpSocket
{
    Q_OBJECT
public:

    /*!
     * Constructor.
     *
     * \param address ip address that will be bind to the socket.
     * \param port port that will be bind to the socket.
     * \param objectName name of the object or class that will be using this
     * one. Used on warning messages.
     * \param parent parent.
     */
    BrisaUdpListener(QString address, quint32 port, QString objectName,
                     QObject *parent = 0);

    /*!
     * Destructor
     */
    virtual ~BrisaUdpListener();

    /*!
     * Starts listening to the address and port passed on constructor.
     */
    void start();

private:

    /*!
     * \property objectName
     *
     * Object or class name that will be used on debug messages.
     */
    QString objectName;

    /*!
     * \property address
     *
     * IP address that will be bind to the socket.
     */
    QString address;

    /*!
     * \property port
     *
     * Port that will be bind to the socket.
     */
    quint32 port;

};

}

#endif // BRISAUDPLISTENER_H
