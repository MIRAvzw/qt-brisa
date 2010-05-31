/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaservicexmkhandler.h
 * Created:
 * Description: This file defines BrisaAbstractService, BrisaServiceParserContext
 * and BrisaServiceXMLHandler classes.
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

#ifndef _BRISAABSTRACTSERVICEXMLHANDLER_H
#define _BRISAABSTRACTSERVICEXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>
#include <QXmlInputSource>
#include <QXmlAttributes>
#include <QIODevice>
#include <QString>

#include "brisaserviceparsercontext.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaServiceXMLHandler: public QXmlDefaultHandler {
public:
    void parseService(BrisaAbstractService *service, QIODevice *scpd);
    BrisaServiceXMLHandler();
    ~BrisaServiceXMLHandler();

protected:
    bool startElement(const QString &namespaceURI, const QString &localName,
            const QString &qName, const QXmlAttributes &attributes);
    bool endElement(const QString &namespaceURI, const QString &localName,
            const QString &qName);
    bool characters(const QString &str);

private:
    BrisaAbstractService *serv;

    QXmlStreamWriter *writer;
    QXmlSimpleReader *reader;
    QXmlInputSource *input;

    QString textSwap;

//    BrisaAction *actionSwap;
//    BrisaStateVariable *stateVariableSwap;
//    BrisaArgument *argumentSwap;

    BrisaServiceParserContext *context;
};

}

#endif /* _BRISAABSTRACTSERVICEXMLHANDLER_H */
