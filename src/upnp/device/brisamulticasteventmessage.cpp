/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisamulticasteventmessage.cpp
 * Created:
 * Description: Implements BrisaAbstractEventMessage class.
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

#include "brisamulticasteventmessage.h"

using namespace Brisa;

BrisaMulticastEventMessage::BrisaMulticastEventMessage(
        BrisaStateVariable *variable, QString LVL, QObject *parent) :
        BrisaAbstractEventMessage(parent),
        variable(variable),
        SEQ(variable->getNextMulticastSeq()),
        LVL(LVL)
{
}

//TODO Use a real value for BOOTID.UPNP.ORG
QHttpRequestHeader BrisaMulticastEventMessage::getMessageHeader() const
{
    QHttpRequestHeader header("NOTIFY", "*");

    header.setValue("HOST","239.255.255.246:7900");
    header.setValue("CONTENT-TYPE", "text/xml");
    header.addValue("CONTENT-TYPE", "charset=\"utf-8\"");
    header.setValue("USN", this->variable->getMulticastUdn() + "::" +
                    this->variable->getMulticastUsn());
    header.setValue("SVCID", variable->getMulticastSvcid());
    header.setValue("NT", "upnp:event");
    header.setValue("NTS", "upnp:propchange");
    header.setValue("SEQ", QString::number(SEQ));
    header.setValue("LVL", LVL);
    header.setValue("BOOTID.UPNP.ORG", "");
    header.setValue("CONTENT-LENGTH", QString::number(
            this->getMessageBody().size()));

    return header;
}

QByteArray BrisaMulticastEventMessage::getMessageBody() const {
    QByteArray body;

    body.append("<?xml version=\"1.0\"?>\r\n");
    body.append(
            "<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">\r\n");

    QString variableName = this->variable->getAttribute(BrisaStateVariable::Name);
    QString variableValue = this->variable->getAttribute(BrisaStateVariable::Value);

    body.append("  <e:property>\r\n");
    body.append("    <" + variableName + ">" + variableValue + "</"
            + variableName + ">\r\n");
    body.append("  </e:property>\r\n");
    body.append("</e:propertyset>\r\n");

    return body;
}
