/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisamulticasteventmessage.h
 * Created:
 * Description: Defines BrisaAbstractEventMessage class.
 * Authors: Danilo Araújo de Freitas <dsurviver@gmail.com> @since 2010
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

#ifndef BRISAMULTICASTEVENTMESSAGE_H
#define BRISAMULTICASTEVENTMESSAGE_H

#include <QObject>
#include <QList>
#include <QHttpRequestHeader>

#include <brisaabstracteventmessage.h>

namespace Brisa {

class BRISA_UPNP_EXPORT BrisaMulticastEventMessage : public BrisaAbstractEventMessage
{
public:
    BrisaMulticastEventMessage(BrisaStateVariable *variable,
                               QString LVL, QObject *parent = 0);

    QHttpRequestHeader getMessageHeader() const;

    QByteArray getMessageBody() const;

private:
    BrisaStateVariable *variable;

    /*!
     * \property SEQ
     *
     * \brief its event key
     */
    int SEQ;

    /*!
     * \property LVL
     * \brief event level
     */
    QString LVL;
};

}
#endif // BRISAMULTICASTEVENTMESSAGE_H
