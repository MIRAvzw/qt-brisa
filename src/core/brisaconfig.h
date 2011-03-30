/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaconfig.cpp
 * Created:
 * Description: Implementation of BrisaConfigurationManager class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
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

#ifndef _BRISACONFIG_H
#define _BRISACONFIG_H

#include <QHash>
#include <QString>
#include <QObject>
#include <QStringList>

#include "brisaglobal.h"

namespace Brisa {

/*!
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

class BRISA_CORE_EXPORT BrisaConfigurationManager: public QObject {
Q_OBJECT

public:

    /*!
      Returns the only instance of BrisaConfigurationManager (singleton).
     */
    static BrisaConfigurationManager* getInstance();

    /*!
     Sets the direct access option of the ConfigurationManager. When True, direct access makes all
     get and set methods work directly on the database, not on the current state.
     \param access a boolean argument to set direct access option of the BrisaConfigurationManager
     */
    void setDirectAccess(bool access);
    /*!
     Returns False if the ConfigurationManager is currently working on the runtime state. Otherwise,
     it will return True, which means it's  working directly on the persistence.
     \return The current status of the ConfigurationManager
     */
    bool getDirectAccess();

    /*!
     Updates the current state of the manager according to persistence data.
     */
    void update();
    /*!
     Stores the state of the manager on the persistence.
     */
    void save();

    /*!
     Retrieves the value associated with the parameter in the section given.
     \param section a section to find the parameter
     \param parameter a parameter to return the value
     \return the value for the given parameter
     */
    QString getParameter(const QString &section, const QString &parameter);
    /*!
     Sets a parameter's value in the given section. If the parameter does not exist, it gets created.
     \param section a section to set the parameter
     \param parameter a parameter to set the value
     \param parameter a value to be set
     */
    void setParameter(const QString &section, const QString &parameter,
            const QString &parValue);

    /*!
     Returns the names of all sections.
     \return a QList with its parameters and values
     */
    QList<QString> getSectionNames();
    /*!
     Returns all the items of the given section.
     \param section name
     \return a dictionary with all the items of the given section
     */
    QHash<QString, QString> items(const QString &section);
    /*!
     Removes a section given the name.
     \param section: section name to be removed
     \return a boolean. true whether is possible remove it
     */
    bool removeSection(const QString &section);
    /*!
      Sets a new path for the configuration file.
      \param path new path
     */
    bool setConfigFilePath(QString &path);

    QString getConfigFilePath();

    static bool setGlobalConfigPath(QString &path);

private:
    /*!
     Constructor for the BrisaConfigurationManager class.
     \param config_path a QString that represents the path of the database to work on.
     If not supplied will work on a memory database.
     \param state: hash as a dictionaryr with sections and parameters.\
            Keys are section.parameters format and values are the their respective values.
     */
    BrisaConfigurationManager(const QString &configPath, const QHash<QString,
            QString> &state);

    QHash<QString, QString> state;
    QString configPath;
    QString fileName;
    QString parameterSeparator;
    bool directAccess;
    static BrisaConfigurationManager *instance;
    static QString globalConfigPath;
    static bool checkConfigFile;
};
}

#endif /* _BRISACONFIG_H */

