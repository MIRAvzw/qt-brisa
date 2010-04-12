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

#include "brisaconfig.h"

using namespace BrisaCore;

BrisaConfigurationManager::BrisaConfigurationManager(const QString &configPath,
		const QHash<QString, QString> &state) {
	this->state = state;
	this->configPath = configPath;
	this->directAccess = false;
}

void BrisaConfigurationManager::setDirectAccess(bool access) {
	this->directAccess = access;
}

bool BrisaConfigurationManager::getDirectAccess() {
	return this->directAccess;
}

void BrisaConfigurationManager::update() {
	QFile file(this->configPath + "/file.dat");
	file.open(QIODevice::ReadOnly);

	QDataStream in(&file);
	in >> this->state;
}

void BrisaConfigurationManager::save() {
	QFile file(this->configPath + "/file.dat");
	file.open(QIODevice::WriteOnly);

	QDataStream out(&file);
	out << this->state;
}

QString BrisaConfigurationManager::getParameter(const QString &section,
		const QString &parameter) {

	if (getDirectAccess())
		update();

	QString str(section);
	str.append("." + parameter);
	if (this->state.contains(str))
		return this->state.value(str);

	return "";
}

void BrisaConfigurationManager::setParameter(const QString &section,
		const QString &parameter, const QString &parValue) {

	QString str(section);
	str.append("." + parameter);

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
		if (sections[i].split('.').value(0) == section)
			items[sections[i].split('.').at(1)]
					= this->state.value(sections[i]);
	}

	return items;
}

bool BrisaConfigurationManager::removeSection(const QString &section) {
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
