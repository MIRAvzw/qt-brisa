/* brisa-c++
 *
 * Copyright (C) 2009 Andre Dieb Martins <andre.dieb@gmail.com>
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
 *
 */

#ifndef _BRISACONFIG_H
#define _BRISACONFIG_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QStringList>

#include "brisaglobal.h"

namespace BrisaCore {

class BRISA_CORE_EXPORT BrisaConfigurationManager : public QObject
{
    Q_OBJECT

    public:

        BrisaConfigurationManager(const QString &configPath, const QHash<QString,QString> &state);

        void setDirectAccess(bool access);
        bool getDirectAccess();

        void update();
        void save();

        QString getParameter(const QString &section, const QString &parameter);
        void setParameter(const QString &section, const QString &parameter, const QString &parValue);

        QList<QString> getSectionNames();
        QHash<QString,QString> items(const QString &section);
        bool removeSection(const QString &section);

    private:
        QHash<QString,QString> state;
        QString configPath;
        bool directAccess;
};
}

#endif /* _BRISACONFIG_H */

