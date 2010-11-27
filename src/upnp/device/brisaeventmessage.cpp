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

using namespace Brisa;

BrisaEventMessage::BrisaEventMessage(BrisaEventSubscription &subscription,
        const QList<BrisaStateVariable *> *variables, QObject *parent) :
    BrisaAbstractEventMessage(parent),
    SEQ(subscription.getNextSeq()),
    VARIABLES(variables),
    subscription(subscription)
{
}

QByteArray BrisaEventMessage::getRequestMessage() const
{
    static const QString genericRequest = "NOTIFY %1 HTTP/1.1\r\n"
                                          "HOST: %2:%3\r\n"
                                          "Connection: close\r\n"
                                          "CONTENT-TYPE: text/xml\r\n"
                                          "CONTENT-LENGTH: %4\r\n"
                                          "NT: upnp:event\r\n"
                                          "NTS: upnp:propchange\r\n"
                                          "SID: uuid:%5\r\n"
                                          "SEQ: %6\r\n"
                                          "\r\n"
                                          "%7";

    QString body = "<?xml version=\"1.0\"?>\r\n"
                   "<e:propertyset xmlns:e=\"urn:schemas-upnp-org:event-1-0\">\r\n";

    for (QList<BrisaStateVariable *>::const_iterator i =
            VARIABLES->begin(); i != VARIABLES->end(); ++i) {
        QString variableName = (*i)->getAttribute(BrisaStateVariable::Name);

        body.append("  <e:property>\r\n"
                    "    <" + variableName + ">"
                    + (*i)->getAttribute(BrisaStateVariable::Value)
                    + "</" + variableName + ">\r\n"
                    "  </e:property>\r\n"
                    );
    }

    body.append("</e:propertyset>\r\n");

    QString callback;
    QStringList urlList = subscription.getCallbackUrls();
    if (urlList.size())
        callback = urlList[0];

    QUrl url(callback);

    return genericRequest.arg(url.path(),                   // URI
                              url.host(),                   // HOST HEADER
                              QString::number(url.port()),
                              QString::number(body.size()), // CONTENT-LENGTH HEADER
                              subscription.getSid(),        // SID HEADER
                              QString::number(SEQ),         // SEQ HEADER
                              body                          // REQUEST BODY
                              ).toAscii();
}
