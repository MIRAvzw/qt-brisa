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

#ifndef _BSTATEVARIABLE_H
#define _BSTATEVARIABLE_H

#include <QString>
#include <QVariant>
#include <QObject>
#include <QtDebug>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaStateVariable : public QObject
{
    Q_OBJECT

    public:
        BrisaStateVariable(QString sendEvents = "", QString name = "", QString datatype = "",
                           QString defaultValue = "", QString maximum = "", QString minimum = "",
                           QString step = "", QObject *parent = 0);
        BrisaStateVariable(const BrisaStateVariable &);
        BrisaStateVariable &operator=(const BrisaStateVariable &);

        typedef enum {Name,
                      SendEvents,
                      DataType,
                      DefaultValue,
                      AllowedValue,
                      Minimum,
                      Maximum,
                      Step,
                      Value
                      } BrisaStateVariableAttribute;

        void setAttribute(BrisaStateVariableAttribute attr, QVariant value);
        QString getAttribute(BrisaStateVariableAttribute attr, int index=0) const;

        QVariant getValue() const;
        QVariant::Type getDataType() const;

        bool sendEvents() const;

        void addAllowedValue(QString allowedValue);

        QList<QString> getAllowedValueList();

        void clear();

    signals:
        void changed(BrisaStateVariable *);

    private:
        bool validateNewValue(const QVariant &value);

        bool events;
        QList<QString> allowedValueList;
        QString name;
        QString defaultValue;
        QString maximum;
        QString minimum;
        QString step;
        QString dataType;
        QVariant value;

};

}

#endif /* _BRISASTATEVARIABLE_H */
