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

#include "brisaargument.h"

using namespace BrisaUpnp;

/*!
 * \internal
 *
 * \class BrisaUpnp::BrisaArgument brisaargument.h BrisaUpnp/BrisaArgument
 *
 * \brief Represents the action's input and output arguments.
 */

/*!
 * \internal
 *
 * Constructs an argument with given \a name, \a direction and
 * \a relatedStateVariable.
 */
BrisaArgument::BrisaArgument(const QString &name, const QString &direction,
                             const QString &relatedStateVariable) :
    name(name),
    direction(direction),
    relatedStateVariable(relatedStateVariable)
{
}

/*!
 * \internal
 *
 * Sets the argument's attribute \a key to the given \a value.
 */
void BrisaArgument::setAttribute(xmlArgument key, const QString &value)
{
    switch(key)
    {
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

/*!
 * \internal
 *
 * Returns the value of the argument's attribute \a key.
 */
QString BrisaArgument::getAttribute(xmlArgument key) const
{
    switch(key)
    {
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
            return "";
            break;
    }
}

/*!
 * \internal
 *
 * Sets the argument's attributes to their default value.
 */
void BrisaArgument::clear()
{
    this->name.clear();
    this->direction.clear();
    this->relatedStateVariable.clear();
}

