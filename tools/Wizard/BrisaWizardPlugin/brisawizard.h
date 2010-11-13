/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisawizard.h
 * Created: 11/13/2010
 * Description: Implements the wizard that generates the code of the BRisa project.
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

#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H
#include "intropage.h"
#include "devicepage.h"
#include "servicepage.h"
#include "actionpage.h"
#include <QWizard>
#include <QMap>
#include <QMetaType>
#include <QDir>
#include <BRisa/BrisaUpnp/BrisaAction>
#include <BRisa/BrisaUpnp/brisaargument.h>
#include <BRisa/BrisaUpnp/brisaaction.h>
#include <BRisa/BrisaUpnp/brisastatevariable.h>
#include <BRisa/BrisaUpnp/BrisaService>
#include "brisaprojectwizard.h"

using BrisaUpnp::BrisaArgument;
using BrisaUpnp::BrisaStateVariable;
using BrisaUpnp::BrisaAction;
using BrisaUpnp::BrisaService;


class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QListWidget;
class QTableWidget;
class QFileDialog;
class QComboBox;
class QSpacerItem;
class QListWidgetItem;


class BrisaWizard : public QWizard
{
    Q_OBJECT

public:
    BrisaWizard(QWidget *parent = 0);
    ~BrisaWizard();
    void accept();

    void generateServiceXml();//TODO
    void generatePro();//TODO
    void generateService();//TODO
    void generateDevice();//TODO
    static bool wasAcceptedWizard();
private:
    QList<BrisaService*> serviceList;
    IntroPage* introPage;
    DevicePage *devicePage;
    ServicePage *servicePage;
    ActionPage *actionPage;

    QList<BrisaAction *> listAction;


    QStringList stateVariableList;
    static QDir directory;

public slots:

signals:

};

#endif
