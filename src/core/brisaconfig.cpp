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
 */

#include <QFile>
#include <QDataStream>
#include <QSet>

#include "brisaconfig.h"

using namespace BrisaCore;

/*!
    \class BrisaCore::BrisaConfigurationManager brisaconfig.h BrisaCore/BrisaConfigurationManager
    \brief Class that provides an easy way of managing configurations.

    Configuration is organized in sections, which may contain parameters. Each section has a name
    and a parameter has a name and a value.

    Concerning storage, the configuration can be saved on a sqlite database. Also, there's a feature
    called "direct access" that enables direct operations on the database. For example,a
    getParameter() call would retrieve the value of a parameter directly from the database, if the
    feature is enabled.

    When disabled, all methods apply to (what we call) the "state". The state initially contains the
    same information that is on the database, but if the "direct access" feature is disabled, all
    get()'s and set()'s apply to the state. This means you can have a "runtime configuration" and a
    "static configuration".

    By default, the "direct access" feature is disabled. To enable it, just call
    setDirectAccess(True).

    The state can be saved on the persistence by explicitly calling save() It can also update its
    values by explicitly calling update().
*/

/*!
    Constructor for the BrisaConfigurationManager class.
    \param config_path a QString that represents the path of the database to work on.
    If not supplied will work on a memory database.
    \param state: hash as a dictionaryr with sections and parameters.\
    Keys are section.parameters format and values are the their respective values.
*/
BrisaConfigurationManager::BrisaConfigurationManager(const QString &configPath,
                                                     const QHash<QString,QString> &state)
{
    this->state = state;
    this->configPath = configPath;
    this->directAccess = false;
}

/*!
    Sets the direct access option of the ConfigurationManager. When True, direct access makes all
    get and set methods work directly on the database, not on the current state.
    \param access a boolean argument to set direct access option of the BrisaConfigurationManager
*/
void BrisaConfigurationManager::setDirectAccess(bool access)
{
    this->directAccess = access;
}

/*!
    Returns False if the ConfigurationManager is currently working on the runtime state. Otherwise,
    it will return True, which means it's  working directly on the persistence.
    \return The current status of the ConfigurationManager
*/
bool BrisaConfigurationManager::getDirectAccess()
{
    return this->directAccess;
}

/*!
    Updates the current state of the manager according to persistence data.
*/
void BrisaConfigurationManager::update()
{
    QFile file(this->configPath + "/file.dat");
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);
    in >> this->state;
}

/*!
    Stores the state of the manager on the persistence.
*/
void BrisaConfigurationManager::save()
{
    QFile file(this->configPath + "/file.dat");
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);
    out << this->state;
}

/*!
    Retrieves the value associated with the parameter in the section given.
    \param section a section to find the parameter
    \param parameter a parameter to return the value
    \return the value for the given parameter
*/
QString BrisaConfigurationManager::getParameter(const QString &section, const QString &parameter)
{

    if (getDirectAccess())
        update();

    QString str(section);
    str.append("." + parameter);
    if (this->state.contains(str))
        return this->state.value(str);

    return "";
}

/*!
    Sets a parameter's value in the given section. If the parameter does not exist, it gets created.
    \param section a section to set the parameter
    \param parameter a parameter to set the value
    \param parameter a value to be set
*/
void BrisaConfigurationManager::setParameter(const QString &section, const QString &parameter,
                                             const QString &parValue)
{

    QString str(section);
    str.append("." + parameter);

    if( (parValue == "") and (this->state.contains(str)) ){
        this->state.remove(str);
    }else{
        this->state[str] = parValue;
    }

    if (getDirectAccess())
        this->save();

}

/*!
    Returns the names of all sections.
    \return a QList with its parameters and values
*/
QList<QString> BrisaConfigurationManager::getSectionNames()
{

    if(this->getDirectAccess())
        this->update();

    QList<QString> sections = this->state.keys();

    for (int i = 0; i < sections.size(); ++i) {
        sections.replace(i,sections.at(i).split('.').value(0));
    }

    QSet<QString> set = sections.toSet();
    QList<QString> auxList = set.toList();
    qSort(auxList.begin(), auxList.end());

    return auxList;
}

/*!
    Returns all the items of the given section.
    \param section name
    \return a dictionary with all the items of the given section
*/
QHash<QString,QString> BrisaConfigurationManager::items(const QString &section)
{
    if (this->getDirectAccess())
        this->update();

    QHash<QString, QString> items;
    QList<QString> sections = this->state.keys();

    for (int i = 0; i < sections.size(); ++i) {
        if (sections[i].split('.').value(0) == section)
            items[sections[i].split('.').at(1)] = this->state.value(sections[i]);
    }

    return items;
}

/*!
    Removes a section given the name.
    \param section: section name to be removed
    \return a boolean. true whether is possible remove it
*/
bool BrisaConfigurationManager::removeSection(const QString &section)
{
    QHash<QString, QString> items;

    QList<QString> sections = this->state.keys();
    bool error = true;
    for (int i = 0; i < sections.size(); ++i) {
        if (sections[i].split('.').value(0) == section) {
            this->state.remove(sections[i]);
            error = false;
        }
    }

    if (this->getDirectAccess())
        this->save();

    return error;
}
