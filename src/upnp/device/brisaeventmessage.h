/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventmessage.h
 * Created:
 * Description: Defines BrisaEventMessage class.
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

#ifndef _BRISAEVENTMESSAGE_H
#define _BRISAEVENTMESSAGE_H

#include <QObject>
#include <QList>
#include <QHttpRequestHeader>

#include "brisastatevariable.h"
#include "brisaeventsubscription.h"
#include "brisaglobal.h"

using namespace BrisaCore;

namespace BrisaUpnp {

/*!
 * \internal
 * \class BrisaUpnp::BrisaEventMessage
 *
 * \brief Represents an UPnP event message.
 */
class BRISA_UPNP_EXPORT BrisaEventMessage: public QObject {
Q_OBJECT

public:
	/*!
	 * Contructs a new event message to the given \a subscription and related to the
	 * given \a variables, with the given \a parent object.
	 */
	BrisaEventMessage(BrisaEventSubscription &subscription, const QList<
			BrisaStateVariable *> *variables, QObject *parent = 0);

	/*!
	 * Returns this event message's http header.
	 */
	QHttpRequestHeader getMessageHeader() const;
	/*!
	 * Returns this event message's http body.
	 */
	QByteArray getMessageBody() const;

public slots:

signals:

private slots:

private:
	/*!
	 * \property VARIABLES
	 *
	 * \brief the list of state variables related to the event
	 */
	const QList<BrisaStateVariable *> *VARIABLES;
	/*!
	 * \property SEQ
	 *
	 * \brief its event key
	 */
	const int SEQ;
	/*!
	 * \property subscription
	 *
	 * \brief the subscription for which the message will be sent
	 */
	BrisaEventSubscription &subscription;
};

}

#endif /* _BRISAEVENTMESSAGE_H */
