/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaactionxmlparser.cpp
 * Created:
 * Description: Definition of BrisaActionXmlParser class.
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
#ifndef BRISAACTIONXMLPARSER_H_
#define BRISAACTIONXMLPARSER_H_

#include <QtCore>
#include <QDomDocument>

#include "brisaglobal.h"

namespace Brisa {
/*!
 * \class Brisa::BrisaActionXmlParser brisaactionxmlparser.h BrisaUpnp/BrisaActionXmlParser
 * \brief XML parser for SOAP requests.
 *
 * BrisaActionXmlParser parses information coming from the webserver. If a action is detected,
 * public class members args, method, serviceType will be filled with the parsed data.
 *
 * BrisaActionXmlParser uses DOM.
 */
class BRISA_UPNP_EXPORT BrisaActionXmlParser {
public:

    /*!
     * Constructor.
     */
    BrisaActionXmlParser();

    /*!
     * Destructor.
     */
    virtual ~BrisaActionXmlParser();

    /*!
     * Call this method to parse the SOAP request set by the setXmlContent method.
     */
    bool parseSOAP();

    /*!
     * \internal
     * Parses each DOM element.
     * \param element element to be parsed
     */
    void parseElement(QDomElement &element);

    /*!
     * Sets  the content to be parsed.
     * \param content the content to be parsed
     */
    void setXmlContent(const QByteArray &content);

    QMap<QString, QString> args;
    QString method;
    QString serviceType;

private:
    QDomDocument *reader;
    QDomNodeList domArgList;
};

}

#endif /* XMLPARSER_H_ */
