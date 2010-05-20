/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisastatevariable.cpp
 * Created:
 * Description: Implements BrisaStateVariable class
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

#include "brisastatevariable.h"

using namespace BrisaUpnp;

BrisaStateVariable::BrisaStateVariable(QString sendEvents, QString name,
		QString datatype, QString defaultValue, QString maximum,
		QString minimum, QString step, QObject *parent) :
	QObject(parent) {
	this->events = (sendEvents == "yes");
	this->name = name;
	this->dataType = datatype;
	this->defaultValue = defaultValue;
	this->maximum = maximum;
	this->minimum = minimum;
	this->step = step;
	this->value = this->defaultValue;
}

BrisaStateVariable::BrisaStateVariable(const BrisaStateVariable &variable) :
	QObject(variable.parent()) {
	this->events = variable.sendEvents();
	this->name = variable.getAttribute(Name);
	this->dataType = variable.getAttribute(DataType);
	this->defaultValue = variable.getAttribute(DefaultValue);
	this->maximum = variable.getAttribute(Maximum);
	this->minimum = variable.getAttribute(Minimum);
	this->step = variable.getAttribute(Step);
	this->value = variable.getValue();
}

BrisaStateVariable &BrisaStateVariable::operator=(
		const BrisaStateVariable &variable) {
	if (this == &variable)
		return *this;

	this->setParent(variable.parent());
	this->events = variable.sendEvents();
	this->name = variable.getAttribute(Name);
	this->dataType = variable.getAttribute(DataType);
	this->defaultValue = variable.getAttribute(DefaultValue);
	this->maximum = variable.getAttribute(Maximum);
	this->minimum = variable.getAttribute(Minimum);
	this->step = variable.getAttribute(Step);
	this->value = variable.getValue();

	return *this;
}

void BrisaStateVariable::setAttribute(BrisaStateVariableAttribute attr,
		QVariant value) {
	switch (attr) {
	case SendEvents:
		this->events = (value.toString() == "yes");
		break;
	case Name:
		this->name = value.toString();
		break;
	case DataType:
		this->dataType = value.toString();
		break;
	case DefaultValue:
		this->defaultValue = value.toString();
		break;
	case AllowedValue:
		this->allowedValueList.append(value.toString());
		break;
	case Minimum:
		this->minimum = value.toString();
		break;
	case Maximum:
		this->maximum = value.toString();
		break;
	case Step:
		this->step = value.toString();
		break;
	case Value:
		if (this->validateNewValue(value) && this->value != value) {
			this->value = value;
			emit this->changed(this);
		}
		break;
	default:
		break;
	}
}

QString BrisaStateVariable::getAttribute(BrisaStateVariableAttribute attr,
		int ind) const {
	switch (attr) {
	case Name:
		return this->name;
		break;
	case DataType:
		return this->dataType;
		break;
	case DefaultValue:
		return this->defaultValue;
		break;
	case AllowedValue:
		return this->allowedValueList[ind];
		break;
	case Minimum:
		return QString(this->minimum);
		break;
	case Maximum:
		return QString(this->maximum);
		break;
	case Step:
		return QString(this->step);
		break;
	case Value:
		return QString(this->value.toString());
		break;
	default:
		return "";
		break;
	}
}

QList<QString> BrisaStateVariable::getAllowedValueList() {
	return this->allowedValueList;
}

void BrisaStateVariable::addAllowedValue(QString allowedValue) {
	allowedValueList.append(allowedValue);
}

void BrisaStateVariable::clear() {
	this->allowedValueList.clear();
	this->name.clear();
	this->dataType.clear();
	this->defaultValue.clear();
	this->maximum.clear();
	this->minimum.clear();
	this->step.clear();
	this->value.clear();
}

QVariant BrisaStateVariable::getValue() const {
	return this->value;
}

bool BrisaStateVariable::sendEvents() const {
	return this->events;
}

bool BrisaStateVariable::validateNewValue(const QVariant &value) {
	QVariant::Type type = getDataType();

	if (!value.canConvert(type)) {
		qDebug() << "Type mismatch.";
		return false;
	}

	if (type == QVariant::String) {
		if (allowedValueList.isEmpty())
			return true;
		if (allowedValueList.contains(value.toString())) {
			return true;
		} else {
			qDebug() << "Allowed value list does not contain "
					<< value.toString();
			return false;
		}

	} else if (type == QVariant::Bool) {
		if (value.toString() == "0" || value.toString() == "1"
				|| value.toString() == "true" || value.toString() == "false"
				|| value.toString() == "yes" || value.toString() == "no") {
			return true;
		} else {
			qDebug()
					<< "Value not allowed for boolean type. Try '0', '1', 'true', 'false', 'yes', or 'no'.";
			return false;
		}

	} else if (type == QVariant::UInt) {
		if (maximum == "" || minimum == "") {
			return true;
		} else if (value.toUInt() <= maximum.toUInt() && value.toUInt()
				>= minimum.toUInt()) {
			return true;
		} else {
			qDebug() << "Value out of range.";
			return false;
		}

	} else if (type == QVariant::Int) {
		if (maximum == "" || minimum == "") {
			return true;
		} else if (value.toInt() <= maximum.toInt() && value.toInt()
				>= minimum.toInt()) {
			return true;
		} else {
			qDebug() << "Value out of range.";
			return false;
		}

	} else if (type == QVariant::Double) {
		if (maximum == "" || minimum == "") {
			return true;
		} else if (value.toDouble() <= maximum.toDouble() && value.toDouble()
				>= minimum.toDouble()) {
			return true;
		} else {
			qDebug() << "Value out of range.";
			return false;
		}

	} else {
		return true;
	}
}

QVariant::Type BrisaStateVariable::getDataType() const {
	if (dataType == "ui1") {
		return QVariant::UInt;
	} else if (dataType == "ui2") {
		return QVariant::UInt;
	} else if (dataType == "ui4") {
		return QVariant::UInt;
	} else if (dataType == "i1") {
		return QVariant::Int;
	} else if (dataType == "i2") {
		return QVariant::Int;
	} else if (dataType == "i4") {
		return QVariant::Int;
	} else if (dataType == "int") {
		return QVariant::Int;
	} else if (dataType == "r4") {
		return QVariant::Double;
	} else if (dataType == "r8") {
		return QVariant::Double;
	} else if (dataType == "number") {
		return QVariant::Double;
	} else if (dataType == "fixed") {
		return QVariant::Double;
	} else if (dataType == "float") {
		return QVariant::Double;
	} else if (dataType == "char") {
		return QVariant::Char;
	} else if (dataType == "string") {
		return QVariant::String;
	} else if (dataType == "date") {
		return QVariant::Date;
	} else if (dataType == "dateTime") {
		return QVariant::DateTime;
	} else if (dataType == "dateTime.tz") {
		return QVariant::DateTime;
	} else if (dataType == "time") {
		return QVariant::Time;
	} else if (dataType == "time.tz") {
		return QVariant::Time;
	} else if (dataType == "boolean") {
		return QVariant::Bool;
	} else if (dataType == "bin.base64") {
		return QVariant::String;
	} else if (dataType == "bin.hex") {
		return QVariant::String;
	} else if (dataType == "uri") {
		return QVariant::String;
	} else if (dataType == "uuid") {
		return QVariant::String;
	} else {
		return QVariant::Invalid;
	}
}

