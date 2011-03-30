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

#include <QFile>
#include <QDataStream>
#include <QSet>
#include <QDir>
#include <QDebug>

#include "brisaconfig.h"

#ifdef Q_OS_UNIX
#define DEFAULT_CONFIG_PATH "/etc/brisa"
#else
#define DEFAULT_CONFIG_PATH "C:/brisa"
#endif

#define CONFIG_FILE_NAME "/brisa.conf"

using namespace Brisa;

BrisaConfigurationManager::BrisaConfigurationManager(const QString &configPath,
        const QHash<QString, QString> &state) {
    this->state = state;
    this->configPath = configPath;
    this->fileName = CONFIG_FILE_NAME;
    this->parameterSeparator = ".";
    this->directAccess = false;
}

void BrisaConfigurationManager::setDirectAccess(bool access) {
    this->directAccess = access;
}

bool BrisaConfigurationManager::getDirectAccess() {
    return this->directAccess;
}

void BrisaConfigurationManager::update() {
    QFile file(this->configPath + this->fileName);
    file.open(QIODevice::ReadOnly);

    QDataStream in(&file);
    in >> this->state;
}

void BrisaConfigurationManager::save() {
    QFile file(this->configPath + this->fileName);
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);
    out << this->state;
}

QString BrisaConfigurationManager::getParameter(const QString &section,
        const QString &parameter) {

    if (getDirectAccess())
        update();

    return this->state.value(section + parameterSeparator + parameter);
}

void BrisaConfigurationManager::setParameter(const QString &section,
        const QString &parameter, const QString &parValue) {

    QString str(section + parameterSeparator + parameter);

    if ((parValue == "") and (this->state.contains(str))) {
        this->state.remove(str);
    } else {
        this->state[str] = parValue;
    }

    if (getDirectAccess())
        this->save();

}

QList<QString> BrisaConfigurationManager::getSectionNames() {

    if (this->getDirectAccess())
        this->update();

    QList<QString> sections = this->state.keys();

    for (int i = 0; i < sections.size(); ++i) {
        sections.replace(i, sections.at(i).split('.').value(0));
    }

    QSet<QString> set = sections.toSet();
    QList<QString> auxList = set.toList();
    qSort(auxList.begin(), auxList.end());

    return auxList;
}

QHash<QString, QString> BrisaConfigurationManager::items(const QString &section) {
    if (this->getDirectAccess())
        this->update();

    QHash<QString, QString> items;
    QList<QString> sections = this->state.keys();

    for (int i = 0; i < sections.size(); ++i) {
        if (sections[i].split(parameterSeparator).value(0) == section)
            items[sections[i].split(parameterSeparator).at(1)]
                    = this->state.value(sections[i]);
    }

    return items;
}

bool BrisaConfigurationManager::removeSection(const QString &section) {
    QHash<QString, QString> items;

    QList<QString> sections = this->state.keys();
    bool error = true;
    for (int i = 0; i < sections.size(); ++i) {
        if (sections[i].split(parameterSeparator).value(0) == section) {
            this->state.remove(sections[i]);
            error = false;
        }
    }

    if (this->getDirectAccess())
        this->save();

    return error;
}

bool BrisaConfigurationManager::setConfigFilePath(QString &path)
{
    QDir dir;
    if (dir.exists(path)) {
        this->configPath = path;
        return true;
    } else if (dir.mkpath(path)) {
        qWarning() << "Path " << path << " does not exist. Creating path...";
        this->configPath = path;
        return true;
    }
    return false;
}

QString BrisaConfigurationManager::getConfigFilePath()
{
    return this->configPath;
}

bool BrisaConfigurationManager::setGlobalConfigPath(QString &path)
{
    if (instance) {
        qWarning() << "BrisaConfigurationManager was already instanciated. "
                "Call setConfigFilePath to change the already existing instance configuration file path.";
    }
    QDir dir;
    if (dir.exists(path)) {
        globalConfigPath = path;
        return true;
    } else if (dir.mkpath(path)) {
        qWarning() << "Path " << path << " does not exist. Creating path...";
        globalConfigPath = path;
        return true;
    }
    checkConfigFile = false;
    return false;
}

BrisaConfigurationManager* BrisaConfigurationManager::getInstance()
{
    if (!instance) {
        QString path;
        if (checkConfigFile) {
            if (QFile::exists(globalConfigPath + CONFIG_FILE_NAME)) {
                path = globalConfigPath;
            } else {
                path = DEFAULT_CONFIG_PATH;
            }
        } else {
            path = globalConfigPath;
        }
        instance = new BrisaConfigurationManager(path, QHash<QString, QString>());
    }
    return instance;
}

BrisaConfigurationManager* BrisaConfigurationManager::instance = NULL;

QString BrisaConfigurationManager::globalConfigPath = "./";

bool BrisaConfigurationManager::checkConfigFile = false;
