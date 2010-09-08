/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaeventmessage.cpp
 * Created:
 * Description: Implements BrisaEventMessage class.
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

#include "brisaeventmessage.h"

using namespace BrisaUpnp;

BrisaEventMessage::BrisaEventMessage(BrisaEventSubscription &subscription,
        const QList<BrisaStateVariable *> *variables, QObject *parent) :
    BrisaAbstractEventMessage(parent),
    subscription(subscription),
    VARIABLES(variables),
    SEQ(subscription.getNextSeq())
{
}

QHttpRequestHeader BrisaEventMessage::getMessageHeader() const {
    // Select callback url
    QString callback = "";
    QStringList urlList = subscription.getCallbackUrls();
    if (urlList.size() > 0)
        callback = urlList[0];

    QUrl url(callback);

    // Header
    QHttpRequestHeader header("NOTIFY", url.path());

    header.setValue("HOST", url.host() + ":" + QString::number(url.port()));
    header.setValue("CONTENT-TYPE", "text/xml");
    header.setValue("CONTENT-LENGTH", QString::number(
            this->getMessageBody().size()));
    header.setValue("NT", "upnp:event");
    header.setValue("NTS", "upnp:propchange");
    header.setValue("SID", "uuid:" + subscription.getSid());
    header.setValue("SEQ", QString::number(SEQ));

    return header;
}

QByteArray BrisaEventMessage::getMessageBody() const {
    QByteArray body;

    body.append("<?xml version=\"1.0\"?>\r\n");
    body.append(
            "<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">\r\n");

    for (QList<BrisaStateVariable *>::const_iterator i =
            this->VARIABLES->begin(); i != this->VARIABLES->end(); ++i) {
        QString variableName = (*i)->getAttribute(BrisaStateVariable::Name);
        QString variableValue = (*i)->getAttribute(BrisaStateVariable::Value);

        body.append("  <e:property>\r\n");
        body.append("    <" + variableName + ">" + variableValue + "</"
                + variableName + ">\r\n");
        body.append("  </e:property>\r\n");
    }

    body.append("</e:propertyset>\r\n");

    return body;
}
