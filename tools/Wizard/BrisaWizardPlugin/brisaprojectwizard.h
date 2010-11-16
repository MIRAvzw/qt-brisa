/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaprojectwizard.h
 * Created: 11/13/2010
 * Description: Implements the new BRisa project function.
 * Authors: Willian Victor Silva <willian.victors@gmail.com> 2010
 *          Camilo Costa Campos <zeromaisum@gmail.com> 2010
 *
 *
 * Copyright (C) <2010> <Pervasive Computing Laboratory @ Federal
 * University of Alagoas>
 *
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

#ifndef BRISAPROJECTWIZARD_H
#define BRISAPROJECTWIZARD_H
#include <extensionsystem/iplugin.h>
#include <coreplugin/icore.h>
#include <coreplugin/basefilewizard.h>
#include <QStringList>


class BrisaProjectWizard : public Core::IWizard
{
public:
    BrisaProjectWizard() {}
    ~BrisaProjectWizard() { qDebug("hell2"); }
    Core::IWizard::WizardKind kind() const;
    QIcon icon() const;
    QString description() const;
    QString name() const;
    QString category() const;
    QString trCategory() const;
    QStringList runWizard(const QString &path, QWidget *parent);

    bool initialize(const QStringList& args, QString *errMsg);

    QString displayName() const;
    QString id() const;
    QString displayCategory() const;
    Q_OBJECT
public slots:
    void on_finished();
    static void setProjectPaths(QStringList paths);

};

#endif //BRISAPROJECTWIZARD_H
