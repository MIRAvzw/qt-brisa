/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaargument.cpp
 * Created:
 * Description: Implements the BrisaArgument class.
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
#include <brisaglobal.h>
#include "brisaargument.h"

using namespace Brisa;

BrisaArgument::BrisaArgument(const BrisaArgument &brisaArgument):
        name(brisaArgument.name),
        direction(brisaArgument.direction),
        relatedStateVariable(brisaArgument.relatedStateVariable) {
}

BrisaArgument::BrisaArgument(const QString &name, const QString &direction,
        const QString &relatedStateVariable) :
    name(name), direction(direction),
            relatedStateVariable(relatedStateVariable) {
}

void BrisaArgument::setAttribute(xmlArgument key, const QString &value) {
    switch (key) {
    case ArgumentName:
        this->name = value;
        break;
    case Direction:
        this->direction = value;
        break;
    case RelatedStateVariable:
        this->relatedStateVariable = value;
        break;
    }
}

QString BrisaArgument::getAttribute(xmlArgument key) const {
    switch (key) {
    case ArgumentName:
        return this->name;
        break;
    case Direction:
        return this->direction;
        break;
    case RelatedStateVariable:
        return this->relatedStateVariable;
        break;
    default:
        return QString();
        break;
    }
}

void BrisaArgument::clear() {
    this->name.clear();
    this->direction.clear();
    this->relatedStateVariable.clear();
}

