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

#ifndef _BRISAARGUMENT_H
#define _BRISAARGUMENT_H

#include <QObject>
#include <QString>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaArgument
{
    public:
        BrisaArgument(const QString &name = "", const QString &direction = "",
                      const QString &relatedStateVariable = "");

        typedef enum { ArgumentName,
                       Direction,
                       RelatedStateVariable} xmlArgument;

        void setAttribute(xmlArgument key, const QString &value);
        QString getAttribute(xmlArgument key) const;

        void clear();

    private:
        QString name;
        QString direction;
        QString relatedStateVariable;
};

}

#endif /* BRISAARGUMENT_H_ */
