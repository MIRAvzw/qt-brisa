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
#ifndef _BRISAARGUMENT_H
#define _BRISAARGUMENT_H

#include <QObject>
#include <QString>

#ifndef BRISA_UPNP_EXPORT
#define BRISA_UPNP_EXPORT
#endif

namespace Brisa {

/*!
 * \internal
 *
 * \class Brisa::BrisaArgument brisaargument.h BrisaUpnp/BrisaArgument
 *
 * \brief Represents the action's input and output arguments.
 */
class BRISA_UPNP_EXPORT BrisaArgument {
public:

    /*!
     * \internal
     *
     * Constructs an argument with given \a name, \a direction and
     * \a relatedStateVariable.
     */
    BrisaArgument(const QString &name = "", const QString &direction = "",
            const QString &relatedStateVariable = "");

    /*!
     * \internal
     *
     * Constructs an argument with an argument reference.
     */
    BrisaArgument(const BrisaArgument &brisaArgument);

    typedef enum {
        ArgumentName, Direction, RelatedStateVariable
    } xmlArgument;

    /*!
     * \internal
     *
     * Sets the argument's attribute \a key to the given \a value.
     */
    void setAttribute(xmlArgument key, const QString &value);

    /*!
     * \internal
     *
     * Returns the value of the argument's attribute \a key.
     */
    QString getAttribute(xmlArgument key) const;

    /*!
     * \internal
     *
     * Sets the argument's attributes to their default value.
     */
    void clear();

private:
    QString name;
    QString direction;
    QString relatedStateVariable;
};

}

#endif /* BRISAARGUMENT_H_ */
