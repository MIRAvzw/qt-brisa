/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: dialogargument.h
 * Created: 11/13/2010
 * Description: Implements the dialog where brisaStateVariables will be associated to a variable.
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

#ifndef DIALOGARGUMENT_H
#define DIALOGARGUMENT_H

#include <BRisa/BrisaUpnp/BrisaAction>
#include <BRisa/BrisaUpnp/brisaargument.h>
#include <BRisa/BrisaUpnp/brisaaction.h>
#include <BRisa/BrisaUpnp/brisastatevariable.h>
#include <BRisa/BrisaUpnp/BrisaService>
#include <QDialog>
#include<QComboBox>


using namespace BrisaUpnp;

Q_DECLARE_METATYPE(BrisaArgument*)
Q_DECLARE_METATYPE(QComboBox*);

namespace Ui {
    class DialogArgument;
}

class DialogArgument : public QDialog {
    Q_OBJECT
public:
    DialogArgument(QWidget *parent = 0);
    ~DialogArgument();
    void setArgumentList(QList<BrisaArgument*> actionList);
    QList<BrisaArgument*> getArgumentList();
    void setAction(QString action);
    void setStateVariables(QList<BrisaStateVariable*> stateVariableListsA);
    QList<BrisaStateVariable*> getStateVariables();
    void updateTableWidget();

protected:
    void changeEvent(QEvent *e);

private:
    QString actionName;
    QList<BrisaArgument*> argumentList;
    QList<BrisaStateVariable*> stateVariableList;
    Ui::DialogArgument *ui;
    int validateInformation();
    

private slots:
    void on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_btnRemove_clicked();
    void on_btnInsert_clicked();
    void on_buttonBox_accepted();
};

#endif // DIALOGARGUMENT_H
