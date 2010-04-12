/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisastatevariable.h
 * Created:
 * Description: Defines BrisaStateVariable class
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

#ifndef _BSTATEVARIABLE_H
#define _BSTATEVARIABLE_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QtDebug>

#include "brisaglobal.h"

namespace BrisaUpnp {
/*!
 * \class BrisaUpnp::BrisaStateVariable brisastatevariable.h BrisaUpnp/BrisaStateVariable
 *
 * \brief Represents the service's state variables.
 */
class BRISA_UPNP_EXPORT BrisaStateVariable: public QObject {
Q_OBJECT

public:

	/*!
	 * Constructs a BrisaStateVariable that \a sendEvents with the given \a name,
	 * \a datatype, \a defaultValue, \a maximum value, \a minimum value, value
	 * \a step, and \a parent.
	 */
	BrisaStateVariable(QString sendEvents = "", QString name = "",
			QString datatype = "", QString defaultValue = "", QString maximum =
					"", QString minimum = "", QString step = "",
			QObject *parent = 0);

	/*!
	 * Constructs a BrisaStateVariable from the given \a variable.
	 */
	BrisaStateVariable(const BrisaStateVariable &);

	/*!
	 * Sets this variable equals to \a variable.
	 */
	BrisaStateVariable &operator=(const BrisaStateVariable &);

	typedef enum {
		Name,
		SendEvents,
		DataType,
		DefaultValue,
		AllowedValue,
		Minimum,
		Maximum,
		Step,
		Value
	} BrisaStateVariableAttribute;

	/*!
	 * Sets its attribute \a attr to the given \a value.
	 */
	void setAttribute(BrisaStateVariableAttribute attr, QVariant value);

	/*!
	 * Returns \a attr value as a QString.
	 */
	QString getAttribute(BrisaStateVariableAttribute attr, int index = 0) const;

	/*!
	 * Returns the stored value as a QVariant.
	 */
	QVariant getValue() const;

	/*!
	 *  \internal
	 *  Returns the stored type as a valid UPnP type represented as a QVariant::Type.
	 */
	QVariant::Type getDataType() const;

	/*!
	 * Returns true if the variable is set to send events.
	 */
	bool sendEvents() const;

	/*!
	 * Adds a value to the list of values that can be set to its Value attribute.
	 */
	void addAllowedValue(QString allowedValue);

	/*!
	 * Returns the list of values that can be set to its Value attribute.
	 */
	QList<QString> getAllowedValueList();

	/*!
	 * Clears this variable's attributtes.
	 */
	void clear();

signals:
	void changed(BrisaStateVariable *);

private:

	/*!
	 * \internal
	 * Returns true if the given value is valid.
	 */
	bool validateNewValue(const QVariant &value);

	bool events;
	QList<QString> allowedValueList;
	QString name;
	QString defaultValue;
	QString maximum;
	QString minimum;
	QString step;
	QString dataType;
	QVariant value;

};

}

#endif /* _BRISASTATEVARIABLE_H */
