/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstractservice.h
 * Created:
 * Description: This file defines the BrisaAbstractService class.
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
#ifndef _BRISAABSTRACTSERVICE_H
#define _BRISAABSTRACTSERVICE_H

#include "brisaaction.h"
#include "brisastatevariable.h"
#include "brisaglobal.h"

#include <qtsoap.h>

#include <QMap>
#include <QString>
#include <QObject>

namespace BrisaUpnp
{

/*!
 * \class BrisaUpnp::BrisaAbstractService brisaabstractservice.h BrisaUpnp/BrisaAbstractService
 *
 * \brief An abstract class for the control point side and device side service
 */
class BRISA_UPNP_EXPORT BrisaAbstractService: public QObject
{
Q_OBJECT

public:

	BrisaAbstractService(QObject *parent = 0);
	/*!
	 *
	 * Constructs an abstract service with given \a serviceType, \a serviceId,
	 * \a scpdUrl, \a controlUrl, \a eventSubUrl, \a host and \a parent.
	 */
	BrisaAbstractService(const QString &serviceType, const QString &serviceId =
			"", const QString &scpdUrl = "", const QString &controlUrl = "",
			const QString &eventSubUrl = "", const QString &host = "",
			QObject *parent = 0);
	/*!
	 * \internal
	 *
	 * Constructs and abstract service from given \a serv.
	 */
	BrisaAbstractService(BrisaAbstractService &service);
	/*!
	 * \internal
	 *
	 * Destroys the and abstract service.
	 */
	virtual ~BrisaAbstractService();

	typedef enum {
		Major,
		Minor,
		FileAddress,
		ServiceType,
		ServiceId,
		ScpdUrl,
		ControlUrl,
		EventSubUrl,
		Host,
		Port
	} xmlTags;

	/*!
	 * \internal
	 *
	 * Set its attribute \a key to the given \a value.
	 */
	void setAttribute(xmlTags key, const QString &value);
	/*!
	 * \internal
	 *
	 * Get the attribute \a key 's value.
	 */
	QString getAttribute(xmlTags key);
	/*!
	 * \internal
	 *
	 * Creates an BrisaAction with the given \a name and adds it to the service's
	 * action list.
	 */
	void addAction(const QString &name);
	/*!
	 * \internal
	 *
	 * Adds the given \a action to the service's action list.
	 */
	void addAction(BrisaAction *action);
	/*!
	 * \internal
	 *
	 * Returns the service's action with the given \a name. If it has no action
	 * with that name, it returns 0.
	 */
	BrisaAction *getAction(const QString &name);
	/*!
	 * \internal
	 *
	 * Returns the service's action list.
	 */
	QList<BrisaAction *> getActionList();
	/*!
	 * \internal
	 *
	 * Adds the given \a stateVariable to the service's state variables list.
	 */
	void addStateVariable(BrisaStateVariable *stateVariable);

	/*!
	 * \internal
	 *
	 * Creates a BrisaStateVariable that \a sendEvents with the given \a name,
	 * \a datatype, \a defaultValue, \a maximum value, \a minimum value and \a step,
	 * and adds it to the service's state variables list.
	 */
	void
			addStateVariable(const QString &sendEvents, const QString &name,
					const QString &datatype, const QString &defaultValue,
					const QString &maximum, const QString &minimum,
					const QString &step);

	/*!
	 * \internal
	 *
	 * Returns the service's state variables list.
	 */
	const QList<BrisaStateVariable *> getStateVariableList();

	/*!
	 * \internal
	 *
	 * Set the service's attributes to their default values.
	 */
	void clear();

signals:
	void requestFinished(QString root, QString lastMethod);

protected:
	virtual void call(const QString &method,
			const QMap<QString, QString> &param) = 0;

	QList<BrisaAction *> actionList;
	QList<BrisaStateVariable *> stateVariableList;

	QString controlUrl;
	QString eventSubUrl;
	QString fileAddress;
	QString major;
	QString minor;
	QString scpdUrl;
	QString serviceType;
	QString serviceId;

	QString host;
	int port;

	QtSoapHttpTransport http;
};

}

#endif /* _BRISAABSTRACTSERVICE_H */
