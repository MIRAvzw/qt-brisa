/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstracteventmessage.h
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

#ifndef BRISAABSTRACTEVENTMESSAGE_H
#define BRISAABSTRACTEVENTMESSAGE_H

#include <QObject>
#include <QList>
#include <QHttpRequestHeader>

#include "brisastatevariable.h"
#include "brisaglobal.h"

namespace Brisa {

/*!
 * \internal
 * \class Brisa::BrisaEventMessage
 *
 * \brief Represents an UPnP event message.
 */
class BRISA_UPNP_EXPORT BrisaAbstractEventMessage: public QObject {
Q_OBJECT

public:

    BrisaAbstractEventMessage(QObject *parent = 0);

    QByteArray getRequestMessage() const;
};

}

#endif // BRISAABSTRACTEVENTMESSAGE_H
