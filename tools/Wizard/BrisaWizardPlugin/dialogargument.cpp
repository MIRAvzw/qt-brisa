/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: dialogargument.cpp
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

#include "dialogargument.h"
#include "ui_dialogargument.h"
#include "QComboBox"
#include <QDebug>
#include <QMessageBox>

static int currentTableRow=0;

DialogArgument::DialogArgument(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogArgument)
{
    ui->setupUi(this);
}


DialogArgument::~DialogArgument()
{
    delete ui;
}

void DialogArgument::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogArgument::updateTableWidget(){
    qDebug() << "updateTableWidget calling";
    foreach(BrisaArgument* a, argumentList){
        qDebug() << a->getAttribute(a->ArgumentName);
        qDebug() << "getting argument";
    }
    int currentRow = 0;

    foreach(BrisaArgument* argument, argumentList){
        ui->table->insertRow(currentRow);
        qDebug() << currentRow;
        QTableWidgetItem* argumentItem = new QTableWidgetItem();
        argumentItem->setText(argument->getAttribute(argument->ArgumentName));
        ui->table->setItem(currentRow,0,argumentItem);


        QTableWidgetItem* relatedStateVariableItem = new QTableWidgetItem(argument->getAttribute(argument->RelatedStateVariable));
        ui->table->setItem(currentRow,1,relatedStateVariableItem);

        QComboBox* cbxDirection = new QComboBox();
        QStringList directions;
        directions.append("in");
        directions.append("out");
        cbxDirection->addItems(directions);
        ui->table->setCellWidget(currentRow,3,cbxDirection);
        qDebug() << "GETTING DIRECTION:" + argument->getAttribute(argument->Direction);
        cbxDirection->setCurrentIndex(argument->getAttribute(argument->Direction).trimmed() == "in"? 0 : 1);

        QComboBox* cbxEvent = new QComboBox();
        QStringList events;
        events.append("Yes");
        events.append("No");
        cbxEvent->addItems(events);
        ui->table->setCellWidget(currentRow,4,cbxEvent);

        QComboBox* cbxType = new QComboBox();
        QStringList types;
        types.append("string");
        types.append("float");
        types.append("int");
        types.append("boolean");
        cbxType->addItems(types);
        ui->table->setCellWidget(currentRow,5,cbxType);
        BrisaStateVariable* v= stateVariableList.value(currentRow);
        qDebug() << "GETTING SEVENT:";
        qDebug() << v->sendEventsChange();

        QTableWidgetItem* defaultValueItem = new QTableWidgetItem();
        defaultValueItem->setText(v->getAttribute(v->DefaultValue));
        ui->table->setItem(currentRow,2,defaultValueItem);

        cbxEvent->setCurrentIndex( v->sendEventsChange() == true? 0 : 1 );
        qDebug() << "GETTING type:" + v->getAttribute(v->DataType);

        int indexType = 0;
        if(v->getAttribute(v->DataType).trimmed() == "int")
            indexType = 2;
        if(v->getAttribute(v->DataType).trimmed() == "float")
            indexType = 1;
        if(v->getAttribute(v->DataType).trimmed() == "boolean")
            indexType = 3;

        cbxType->setCurrentIndex(indexType);

        currentRow++;
        //falta relacionar os stateVariable
    }
}



void DialogArgument::setArgumentList(QList<BrisaArgument*> argumentListA){
    //argumentList = argumentListA;
    argumentList.clear();
    if(!argumentListA.isEmpty()){
        foreach(BrisaArgument* argument, argumentListA){
            argumentList.append(argument);
            qDebug() << "passed getARGUMENT: " + argument->getAttribute(argument->ArgumentName) ;
        }
    }else{
        qDebug() << "withreturn argumentList";
        ui->table->clear();
        QStringList labels;
        labels.append("Argument");
        labels.append("StateVariable");
        labels.append("DefaultValue");
        labels.append("Direction");
        labels.append("SendEvents");

        labels.append("Type");

        ui->table->setHorizontalHeaderLabels(labels);
        currentTableRow = 0;

    }
}

QList<BrisaArgument*> DialogArgument::getArgumentList(){
    return this->argumentList;
}




void DialogArgument::setAction(QString actionNameA){
    this->actionName = actionNameA;
}

void DialogArgument::on_btnInsert_clicked()
{
    qDebug() << "INSERT SOLICITED";
    ui->table->insertRow(currentTableRow);
    QTableWidgetItem* argumentItem = new QTableWidgetItem();
    ui->table->setItem(currentTableRow,0,argumentItem);
    QTableWidgetItem* stateVariableItem = new QTableWidgetItem();
    ui->table->setItem(currentTableRow,1,stateVariableItem);
    QTableWidgetItem* defaultValueItem = new QTableWidgetItem();
    //defaultValueItem->setText("0");
    ui->table->setItem(currentTableRow,2,defaultValueItem);

    QComboBox* cbxDirection = new QComboBox();
    QStringList directions;
    directions.append("in");
    directions.append("out");
    cbxDirection->addItems(directions);
    ui->table->setCellWidget(currentTableRow,3,cbxDirection);
    cbxDirection->setCurrentIndex(0);
    qDebug() << "insering cbx direction";

    QComboBox* cbxSendEvents = new QComboBox();
    QStringList sendEvents;
    sendEvents.append("Yes");
    sendEvents.append("No");
    cbxSendEvents->addItems(sendEvents);
    ui->table->setCellWidget(currentTableRow,4,cbxSendEvents);
    cbxSendEvents->setCurrentIndex(0);
    qDebug() << "insering cbxSendEvents";

    QComboBox* cbxType = new QComboBox();
    QStringList types;
    types.append("string");
    types.append("int");
    types.append("float");
    types.append("boolean");
    cbxType->addItems(types);
    ui->table->setCellWidget(currentTableRow,5,cbxType);
    cbxType->setCurrentIndex(1);
    qDebug() << "insering cbxType";

    qDebug() << currentTableRow;
    connect(cbxType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_typeChanged(int)));
    currentTableRow++;
}



void DialogArgument::setStateVariables(QList<BrisaStateVariable*> stateVariableListA){
    this->stateVariableList.clear();
    foreach(BrisaStateVariable* stateVariable, stateVariableListA)
        stateVariableList.append(stateVariable);
}

QList<BrisaStateVariable*> DialogArgument::getStateVariables(){
    return this->stateVariableList;
}


int DialogArgument::validateInformation(){
    ui->table->clearSelection();
    for(int i = 0; i < ui->table->rowCount(); i++){
        for(int j = 0; j< ui->table->rowCount(); j++){
            if(j != i){
                ui->table->item(i,1)->setSelected(true);
                ui->table->item(j,1)->setSelected(true);
                if( (!ui->table->item(i,0)->text().isEmpty()) && (ui->table->item(i,0)->text() == ui->table->item(j,0)->text()) )
                    return -1;
                if( (!ui->table->item(i,1)->text().isEmpty()) && (ui->table->item(i,1)->text() == ui->table->item(j,1)->text()))
                    return 0;
            }
        }
        if((!ui->table->item(i,0)->text().isEmpty()) && (ui->table->item(i,1)->text().isEmpty()))
            return 2;
    }
    return 1;
}

void DialogArgument::on_buttonBox_accepted()
{
    argumentList.clear();
    stateVariableList.clear();
    qDebug() << "insering itens acepted";
    for(int i = 0; i < ui->table->rowCount() ; i++){
       if(validateInformation() == 1){
           if((!ui->table->item(i,0)->text().isEmpty()) || (!ui->table->item(i,1)->text().isEmpty())){
               qDebug() << "PASSED INSERING STATEVARIABLE";
               QString argumentName = ui->table->item(i,0)->text();
               //if (!ui->table->item(i,0)->text().isEmpty()){
                    BrisaArgument* argument = new BrisaArgument();
                    argument->setAttribute(argument->ArgumentName, argumentName);
                    argument->setAttribute(argument->RelatedStateVariable, ui->table->item(i,1)->text());
                    qDebug() << "setting direction:";
                    qDebug() << "BEFORE COMBO";
                    QComboBox *combo = (QComboBox*) ui->table->cellWidget(i,3);
                    qDebug() << "AFTER COMBO";
                    qDebug() << "combo:" + combo->itemText(combo->currentIndex());
                    argument->setAttribute( argument->Direction,combo->itemText(combo->currentIndex()) == "in" ? "in":"out");
                    qDebug() << "added direction";
                    argumentList.append(argument);
                    qDebug() << "appended argument";
                //}
               QComboBox *comboEvent = (QComboBox*) ui->table->cellWidget(i,4);
               qDebug() << "getting sendEvent";
               QString sendEvent = comboEvent->itemText(comboEvent->currentIndex());
               qDebug() << sendEvent;
               QComboBox *comboType = (QComboBox*) ui->table->cellWidget(i,5);
               QString dataType = comboType->itemText(comboType->currentIndex());
               qDebug() << "getting dataType "+ dataType ;
               BrisaStateVariable* stateVariable = new BrisaStateVariable(sendEvent.toLower(),ui->table->item(i,1)->text(),dataType,ui->table->item(i,2)->text());
               qDebug() << "instance";
               stateVariableList.append(stateVariable);
           }else
               currentTableRow--;
           accept();                      
        }else{
            if(validateInformation() == -1){
                QMessageBox::information(0,"Related Repeated Argument","There are one or more argument's name repeateds");
                return;
            }
            if(validateInformation() == 0){
                QMessageBox::information(0,"Related Repeated StateVariable","There are one or more state variable's name repeateds");
                return;
            }
            if(validateInformation() == 2){
                QMessageBox::information(0,"State Variable Blank!","The State Variable Value can't be blank!");
                return;
            }
        }
    }
}




void DialogArgument::on_btnRemove_clicked()
{
    if(ui->table->selectedItems().count() >= 1){
        ui->table->removeRow(ui->table->currentRow());
        currentTableRow--;
    }
}

void DialogArgument::on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn);
    Q_UNUSED(previousRow);
    if(currentColumn == 1)
        ui->table->item(currentRow,1)->setText(ui->table->item(currentRow,0)->text());
}
