/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "brisaeventmessage.h"

using namespace BrisaUpnp;

/*!
 * \internal
 * \class BrisaUpnp::BrisaEventMessage
 *
 * \brief Represents an UPnP event message.
 */

/*!
 * \property VARIABLES
 *
 * \brief the list of state variables related to the event
 */

/*!
 * \property SEQ
 *
 * \brief its event key
 */

/*!
 * \property subscription
 *
 * \brief the subscription for which the message will be sent
 */


/*!
 * Contructs a new event message to the given \a subscription and related to the
 * given \a variables, with the given \a parent object.
 */
BrisaEventMessage::BrisaEventMessage(BrisaEventSubscription &subscription,
                                     const QList<BrisaStateVariable *> *variables,
                                     QObject *parent) :
    QObject(parent),
    VARIABLES(variables),
    SEQ(subscription.getNextSeq()),
    subscription(subscription)
{
}

/*!
 * Returns this event message's http header.
 */
QHttpRequestHeader BrisaEventMessage::getMessageHeader() const
{
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
    header.setValue("CONTENT-LENGTH", QString::number(this->getMessageBody().size()));
    header.setValue("NT", "upnp:event");
    header.setValue("NTS", "upnp:propchange");
    header.setValue("SID", "uuid:" + subscription.getSid());
    header.setValue("SEQ", QString::number(SEQ));

    return header;
}

/*!
 * Returns this event message's http body.
 */
QByteArray BrisaEventMessage::getMessageBody() const
{
    QByteArray body;

    body.append("<?xml version=\"1.0\"?>\r\n");
    body.append("<e:propertyset: xmlns:e=\"urn:schemas-upnp-org:event-1-0\">\r\n");

    for (QList<BrisaStateVariable *>::const_iterator i = this->VARIABLES->begin();
         i != this->VARIABLES->end(); ++i) {
        QString variableName = (*i)->getAttribute(BrisaStateVariable::Name);
        QString variableValue = (*i)->getAttribute(BrisaStateVariable::Value);

        body.append("  <e:property>\r\n");
        body.append("    <" + variableName + ">" + variableValue + "</" + variableName + ">\r\n");
        body.append("  </e:property>\r\n");
    }

    body.append("</e:propertyset>\r\n");

    return body;
}

