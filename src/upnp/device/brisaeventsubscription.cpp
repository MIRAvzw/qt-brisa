/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventsubscription.cpp
 * Created:
 * Description: Implements BrisaEventSubscription class.
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
#include "brisaeventsubscription.h"

using namespace BrisaUpnp;

void BrisaEventSubscription::renew(const int &newTimeout) {
	this->date = QDateTime::currentDateTime();
	this->timeout = newTimeout;
}

QHttpResponseHeader BrisaEventSubscription::getAcceptSubscriptionResponse() const {
	QHttpResponseHeader header(200, "OK");

	header.addValue("DATE", QDateTime::currentDateTime().toUTC().toString(
			"ddd, dd MMM yyyy HH:mm:ss") + " GMT");

	//FIXME: use system information
	header.addValue("SERVER", QString("OS/version") + QString(" UPnP/1.0 ")
			+ QString("product/version"));

	header.addValue("SID", QString("uuid:") + this->SID);

	header.addValue("TIMEOUT", (timeout >= 0) ? QString("Second-")
			+ QString::number(this->timeout) : "infinite");

	return header;
}

QHttpResponseHeader BrisaEventSubscription::getAcceptUnsubscriptionResponse() const {
	return QHttpResponseHeader(200, "OK");
}

