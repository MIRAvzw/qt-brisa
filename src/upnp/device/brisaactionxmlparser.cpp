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
 */

#include "brisaactionxmlparser.h"

#include <QtDebug>

using namespace BrisaUpnp;

/*!
 * \class BrisaUpnp::BrisaActionXmlParser brisaactionxmlparser.h BrisaUpnp/BrisaActionXmlParser
 * \brief XML parser for SOAP requests.
 *
 * BrisaActionXmlParser parses information coming from the webserver. If a action is detected,
 * public class members args, method, serviceType will be filled with the parsed data.
 *
 * BrisaActionXmlParser uses DOM.
 */

/*!
 * Constructor.
 */
BrisaActionXmlParser::BrisaActionXmlParser()
{
    reader = new QDomDocument();
}

/*!
 * Destructor.
 */
BrisaActionXmlParser::~BrisaActionXmlParser()
{
    delete reader;
}

/*!
 * Sets  the content to be parsed.
 */
void BrisaActionXmlParser::setXmlContent(const QByteArray &content)
{
    reader->setContent(content);
}

/*!
 * Call this method to parse the SOAP request set by the setXmlContent method.
 */
bool BrisaActionXmlParser::parseSOAP()
{
    QDomElement root = reader->documentElement();
    if (!root.tagName().contains("Envelope", Qt::CaseInsensitive))
        return false;

    QDomElement child = root.firstChildElement();

    while (!child.isNull()) {
        if (child.tagName().contains("Body", Qt::CaseInsensitive))
            parseElement(child);
        child = child.nextSiblingElement();
    }

    if (method != "" && serviceType != "")
        return true;

    return false;
}

/*!
 * \internal
 * Parses each DOM element.
 */
void BrisaActionXmlParser::parseElement(QDomElement &element)
{
    QDomElement child = element.firstChildElement();

    while (!child.isNull()) {
        method = child.tagName().section(':', -1);
        serviceType = child.attributes().item(0).nodeValue();
        domArgList = child.childNodes();

        for (uint i = 0; i < domArgList.length(); i++)  {
            if (!domArgList.item(i).isElement())
                return;

            QDomElement current = domArgList.item(i).toElement();
            args.insert(current.tagName(), current.text());
        }

        child = child.nextSiblingElement();
    }
}

