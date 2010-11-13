/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: actionpage.h
 * Created: 11/13/2010
 * Description: Implements the page where the BRisa actions will setted.
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

#ifndef ACTIONPAGE_H
#define ACTIONPAGE_H
#include "servicepage.h"
#include <QObject>

#include <QObject>
#include <QWizard>
#include <QDir>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QComboBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QListWidget>
#include <QTableWidget>

#include <BRisa/BrisaUpnp/BrisaAction>
#include <BRisa/BrisaUpnp/brisaargument.h>
#include <BRisa/BrisaUpnp/brisaaction.h>
#include <BRisa/BrisaUpnp/brisastatevariable.h>
#include <BRisa/BrisaUpnp/BrisaService>


using BrisaUpnp::BrisaArgument;
using BrisaUpnp::BrisaStateVariable;
using BrisaUpnp::BrisaAction;
using BrisaUpnp::BrisaService;

Q_DECLARE_METATYPE(BrisaAction*)



class ActionPage : public QWizardPage
{
    Q_OBJECT

public:
    ActionPage(QWidget *parent = 0);
    int currentTableRow;
    QListWidget *actionListWidget;
    QTableWidget *argumentTableWidget;
    QLineEdit * argumentEdit;
private:
    QVBoxLayout *mainBox;
    QLabel *actionNameLabel;


    QComboBox *serviceCbox;
    QPushButton *addActionButton;
    QPushButton *removeActionButton;
    QPushButton *editArgumentsButton;
    QLineEdit *stateVariableLineEdit;
    QPushButton *repeatArgumentsButton;
    QList<BrisaService*> serviceList;
    QLineEdit *actionNameLineEdit;
    QLineEdit *userTypeNameLineEdit;

public slots:
    void on_addActionButton_clicked();

    void on_RemoveActionButton_clicked();
    void on_actionChange(QModelIndex i);
    void on_actionNameLineEdit_edited();
    void on_actionPage(int id);
    void on_selectedService(int i);
    void on_actionListWidget_DoubleClicked();
    void on_EditArgumentsButton_clicked();
    void on_repeatArgumentsButton_clicked();
};

#endif // ACTIONPAGE_H
