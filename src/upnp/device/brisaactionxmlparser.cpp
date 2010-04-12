/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaactionxmlparser.cpp
 * Created:
 * Description: Implementation of BrisaActionXmlParser class.
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

#include "brisaactionxmlparser.h"

#include <QtDebug>

using namespace BrisaUpnp;

BrisaActionXmlParser::BrisaActionXmlParser() {
	reader = new QDomDocument();
}

BrisaActionXmlParser::~BrisaActionXmlParser() {
	delete reader;
}

void BrisaActionXmlParser::setXmlContent(const QByteArray &content) {
	reader->setContent(content);
}

bool BrisaActionXmlParser::parseSOAP() {
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

void BrisaActionXmlParser::parseElement(QDomElement &element) {
	QDomElement child = element.firstChildElement();

	while (!child.isNull()) {
		method = child.tagName().section(':', -1);
		serviceType = child.attributes().item(0).nodeValue();
		domArgList = child.childNodes();

		for (uint i = 0; i < domArgList.length(); i++) {
			if (!domArgList.item(i).isElement())
				return;

			QDomElement current = domArgList.item(i).toElement();
			args.insert(current.tagName(), current.text());
		}

		child = child.nextSiblingElement();
	}
}

