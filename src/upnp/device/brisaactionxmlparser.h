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

#ifndef BRISAACTIONXMLPARSER_H_
#define BRISAACTIONXMLPARSER_H_

#include <QtCore>
#include <QDomDocument>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaActionXmlParser
{
    public:
        BrisaActionXmlParser();
        virtual ~BrisaActionXmlParser();

        bool parseSOAP();
        void parseElement(QDomElement &element);
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
