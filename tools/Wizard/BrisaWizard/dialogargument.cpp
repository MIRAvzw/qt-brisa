#include "dialogargument.h"
#include "ui_dialogargument.h"
#include "QComboBox"
#include <QDebug>
#include <QMessageBox>

int currentSTableRow;
int currentATableRow;
int currentRTableRow;

QStringList relatedStateVariableList;
QStringList relatedArgumentList;

DialogArgument::DialogArgument(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogArgument)
{
    ui->setupUi(this);
    relatedStateVariableList.clear();
    relatedArgumentList.clear();
    currentATableRow = 0;
    currentRTableRow = 0;
    currentSTableRow = 0;
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
    ui->tb_relationship->setColumnWidth(0,300);
    ui->tb_relationship->setColumnWidth(1,300);
    foreach(BrisaArgument* a, argumentList){
        qDebug() << a->getAttribute(a->ArgumentName);
        qDebug() << "getting argument";
    }
    int currentRow = 0;
    currentATableRow = 0;
    currentRTableRow = 0;
    currentSTableRow = 0;
    foreach(BrisaArgument* argument, argumentList){
        qDebug() << currentRow;
        //if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
            ui->tb_argument->insertRow(currentRow);
            QTableWidgetItem* argumentItem = new QTableWidgetItem();
            argumentItem->setText(argument->getAttribute(argument->ArgumentName));
            ui->tb_argument->setItem(currentRow,0,argumentItem);


        /*QTableWidgetItem* relatedStateVariableItem = new QTableWidgetItem(argument->getAttribute(argument->RelatedStateVariable));
        ui->tb_argument->setItem(currentRow,1,relatedStateVariableItem);*/

            QComboBox* cbxDirection = new QComboBox();
            QStringList directions;
            directions.append("in");
            directions.append("out");
            cbxDirection->addItems(directions);
            ui->tb_argument->setCellWidget(currentRow,1,cbxDirection);
            qDebug() << "GETTING DIRECTION:" + argument->getAttribute(argument->Direction);
            cbxDirection->setCurrentIndex(argument->getAttribute(argument->Direction).trimmed() == "in"? 0 : 1);
        //}
        //QTableWidgetItem *argumentItem = new QTableWidgetItem();
        //argumentItem->setText(argument->getAttribute(argument->ArgumentName));
        ui->tb_relationship->insertRow(currentRow);
        ui->tb_relationship->setColumnWidth(1,500);
        QTableWidgetItem *argumentRelation = new QTableWidgetItem();
        argumentRelation->setText(argument->getAttribute(argument->ArgumentName));
        argumentRelation->setData(Qt::UserRole,QVariant::fromValue(argument));
        ui->tb_relationship->setItem(currentRow,0,argumentRelation);

        QTableWidgetItem *variableItem = new QTableWidgetItem();
        variableItem->setText(argument->getAttribute(argument->RelatedStateVariable));
        relatedStateVariableList.append(argument->getAttribute(argument->RelatedStateVariable));

        foreach(BrisaStateVariable* v, stateVariableList){
            if(v->getAttribute(v->Name) == argument->getAttribute(argument->RelatedStateVariable))
                variableItem->setData(Qt::UserRole,QVariant::fromValue(v));
        }

        ui->tb_relationship->setItem(currentRow,1,variableItem);
        currentRow++;

    }

    currentRow = 0;

    foreach(BrisaStateVariable *v, stateVariableList){

        ui->tb_stateVariable->insertRow(currentRow);
        QTableWidgetItem* nameVariableItem = new QTableWidgetItem();
        nameVariableItem->setText(v->getAttribute(v->Name));
        ui->tb_stateVariable->setItem(currentRow,0,nameVariableItem);

        QTableWidgetItem* defaultValueItem = new QTableWidgetItem();
        defaultValueItem->setText(v->getAttribute(v->DefaultValue));
        ui->tb_stateVariable->setItem(currentRow,1,defaultValueItem);

        QComboBox* cbxEvent = new QComboBox();
        QStringList events;
        events.append("Yes");
        events.append("No");
        cbxEvent->addItems(events);
        ui->tb_stateVariable->setCellWidget(currentRow,2,cbxEvent);
        qDebug() << "GETTING SEVENT:";
        qDebug() << v->sendEventsChange();
        cbxEvent->setCurrentIndex( v->sendEventsChange() == true? 0 : 1 );


        QComboBox* cbxType = new QComboBox();
        QStringList types;
        types.append("string");
        types.append("float");
        types.append("int");
        types.append("boolean");
        cbxType->addItems(types);
        ui->tb_stateVariable->setCellWidget(currentRow,3,cbxType);
        qDebug() << "GETTING type:" + v->getAttribute(v->DataType);
        int indexType = 0;
        if(v->getAttribute(v->DataType).trimmed() == "int")
            indexType = 2;
        if(v->getAttribute(v->DataType).trimmed() == "float")
            indexType = 1;
        if(v->getAttribute(v->DataType).trimmed() == "boolean")
            indexType = 3;
        cbxType->setCurrentIndex(indexType);

        if(!relatedStateVariableList.contains(v->getAttribute(v->Name))){
            ui->tb_relationship->insertRow(ui->tb_relationship->currentRow()+1);
            QTableWidgetItem *variableItem = new QTableWidgetItem();
            variableItem->setText(v->getAttribute(v->Name));
            variableItem->setData(Qt::UserRole,QVariant::fromValue(v));
            ui->tb_relationship->setItem(ui->tb_relationship->currentRow()+1,1,variableItem);
        }

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
        ui->tb_argument->clear();
        QStringList labels;
        labels.append("Argument");
        //labels.append("StateVariable");
        //labels.append("DefaultValue");
        labels.append("Direction");
        //labels.append("SendEvents");

        labels.append("Type");

        ui->tb_argument->setHorizontalHeaderLabels(labels);
        currentATableRow = 0;

    }
}

QList<BrisaArgument*> DialogArgument::getArgumentList(){
    return this->argumentList;
}




void DialogArgument::setAction(QString actionNameA){
    this->actionName = actionNameA;
}

void DialogArgument::on_btnInsert_argument_clicked()
{
    qDebug() << "INSERT SOLICITED";
    ui->tb_argument->insertRow(currentATableRow);
    QTableWidgetItem* argumentItem = new QTableWidgetItem();
    ui->tb_argument->setItem(currentATableRow,0,argumentItem);

    QComboBox* cbxDirection = new QComboBox();
    QStringList directions;
    directions.append("in");
    directions.append("out");
    cbxDirection->addItems(directions);
    ui->tb_argument->setCellWidget(currentATableRow,1,cbxDirection);
    cbxDirection->setCurrentIndex(0);
    qDebug() << "insering cbx direction";


    qDebug() << currentATableRow;
    currentATableRow++;
}



void DialogArgument::setStateVariables(QList<BrisaStateVariable*> stateVariableListA){
    this->stateVariableList.clear();
    foreach(BrisaStateVariable* stateVariable, stateVariableListA)
        stateVariableList.append(stateVariable);
    currentSTableRow = 0;
}

QList<BrisaStateVariable*> DialogArgument::getStateVariables(){
    return this->stateVariableList;
}


int DialogArgument::validateInformation(){
    ui->tb_argument->clearSelection();
    for(int i = 0; i < ui->tb_argument->rowCount(); i++){
        for(int j = 0; j< ui->tb_argument->rowCount(); j++){
            if(j != i){
                ui->tb_argument->item(i,1)->setSelected(true);
                ui->tb_argument->item(j,1)->setSelected(true);
                if( (!ui->tb_argument->item(i,0)->text().isEmpty()) && (ui->tb_argument->item(i,0)->text() == ui->tb_argument->item(j,0)->text()) )
                    return -1;
                if( (!ui->tb_argument->item(i,1)->text().isEmpty()) && (ui->tb_argument->item(i,1)->text() == ui->tb_argument->item(j,1)->text()))
                    return 0;
            }
        }
        if((!ui->tb_argument->item(i,0)->text().isEmpty()) && (ui->tb_argument->item(i,1)->text().isEmpty()))
            return 2;
    }
    return 1;
}

void DialogArgument::on_buttonBox_accepted()
{
    argumentList.clear();
    stateVariableList.clear();
    qDebug() << "insering itens acepted";
    qDebug() << ui->tb_relationship->rowCount();
    for(int i = 0; i < ui->tb_relationship->rowCount() ; i++){
        qDebug() << "BEFORE ADD ARGUMENT ACEPTE";
        BrisaArgument *argument = ui->tb_relationship->item(i,0)->data(Qt::UserRole).value<BrisaArgument*>();
        if(!argumentList.contains(argument))
            argumentList.append(argument);
        qDebug() << "INSTANCE STATEVAR ACEPT";
        BrisaStateVariable* v= ui->tb_relationship->item(i,1)->data(Qt::UserRole).value<BrisaStateVariable*>();
        qDebug() << "BEFORE ADD STATEVAR ACEPT";
        if(!stateVariableList.contains(v))
            stateVariableList.append(v);
        accept();

    }
}




void DialogArgument::on_btnRemove_clicked()
{

}

void DialogArgument::on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(previousColumn);
    Q_UNUSED(previousRow);
    if(currentColumn == 1)
        ui->tb_argument->item(currentRow,1)->setText(ui->tb_argument->item(currentRow,0)->text());
}

void DialogArgument::on_pushButton_clicked()
{

}

void DialogArgument::on_btninsert_stateVariable_clicked()
{
    qDebug() << "INSERT SOLICITED";
    ui->tb_stateVariable->insertRow(currentSTableRow);
    QTableWidgetItem* stateVariableItem = new QTableWidgetItem();
    ui->tb_argument->setItem(currentATableRow,0,stateVariableItem);
    QTableWidgetItem* defaultValueItem = new QTableWidgetItem();
    //defaultValueItem->setText("0");
    ui->tb_stateVariable->setItem(currentSTableRow,1,defaultValueItem);


    QComboBox* cbxSendEvents = new QComboBox();
    QStringList sendEvents;
    sendEvents.append("Yes");
    sendEvents.append("No");
    cbxSendEvents->addItems(sendEvents);
    ui->tb_stateVariable->setCellWidget(currentSTableRow,2,cbxSendEvents);
    cbxSendEvents->setCurrentIndex(0);
    qDebug() << "insering cbxSendEvents";

    QComboBox* cbxType = new QComboBox();
    QStringList types;
    types.append("string");
    types.append("int");
    types.append("float");
    types.append("boolean");
    cbxType->addItems(types);
    ui->tb_stateVariable->setCellWidget(currentSTableRow,3,cbxType);
    cbxType->setCurrentIndex(1);
    qDebug() << "insering cbxType";

    qDebug() << currentSTableRow;
    connect(cbxType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_typeChanged(int)));
    currentSTableRow++;
}


void DialogArgument::on_btn_relationship_clicked()
{

    foreach(QTableWidgetItem *itemArgument,ui->tb_argument->selectedItems()){
        int argumentRow = itemArgument->row();
        int stateVariableRow = ui->tb_stateVariable->selectedItems().at(0)->row();
        QString argumentName = ui->tb_argument->item(argumentRow,0)->text();
        QString variableName = ui->tb_stateVariable->item(stateVariableRow,0)->text();
        if(!relatedArgumentList.contains(argumentName)){
            ui->tb_relationship->insertRow(currentRTableRow);
            relatedArgumentList.append(argumentName);
            //relatedStateVariableList.append(variableName);
            QComboBox *comboEvent = (QComboBox*) ui->tb_stateVariable->cellWidget(stateVariableRow,2);
            qDebug() << "getting sendEvent";
            QString sendEvent = comboEvent->itemText(comboEvent->currentIndex());
            qDebug() << sendEvent;
            QComboBox *comboType = (QComboBox*) ui->tb_stateVariable->cellWidget(stateVariableRow,3);
            QString type = comboType->itemText(comboType->currentIndex());
            QComboBox *comboDirection = (QComboBox*) ui->tb_argument->cellWidget(argumentRow,1);
            QString direction = comboDirection->itemText(comboDirection->currentIndex());
            qDebug() << "direction:" + direction;
            qDebug() << "type:" +type;
            QTableWidgetItem *argumentRelation = new QTableWidgetItem();
            argumentRelation->setText(itemArgument->text());
            BrisaArgument* argument = new BrisaArgument(ui->tb_argument->item(argumentRow,0)->text(),direction,ui->tb_stateVariable->item(stateVariableRow,0)->text());
            qDebug() << argument;
            argumentRelation->setData(Qt::UserRole,QVariant::fromValue(argument));
            ui->tb_relationship->setItem(currentRTableRow,0,argumentRelation);
            QTableWidgetItem *stateVariableRelation = new QTableWidgetItem();
            stateVariableRelation->setText(ui->tb_stateVariable->selectedItems().at(0)->text());
            BrisaStateVariable *variable = new BrisaStateVariable(sendEvent.toLower(),ui->tb_stateVariable->item(stateVariableRow,0)->text(),type,ui->tb_stateVariable->item(stateVariableRow,1)->text());
            qDebug() << variable;
            stateVariableRelation->setData(Qt::UserRole,QVariant::fromValue(variable));
            qDebug() << ui->tb_relationship->currentRow();
            qDebug() << currentRTableRow;
            ui->tb_relationship->setItem(currentRTableRow,1,stateVariableRelation);
            currentRTableRow++;
        }
    }
        //qDebug() << ui->tb_relationship->item(0)->text().section("->",0,0);//.section("->",0,0);


}

void DialogArgument::on_btnRemove_argument_clicked()
{
    if(ui->tb_argument->selectedItems().count() >= 1){
            ui->tb_argument->removeRow(ui->tb_argument->currentRow());
            --currentATableRow;
    }
}

void DialogArgument::on_btnRemove_stateVariable_clicked()
{
    if(ui->tb_stateVariable->selectedItems().count() >= 1){
            ui->tb_stateVariable->removeRow(ui->tb_stateVariable->currentRow());
            --currentSTableRow;
    }
}

void DialogArgument::on_btn_remove_clicked()
{
    if(ui->tb_relationship->selectedItems().count() >= 1){
            if (relatedArgumentList.contains(ui->tb_relationship->item(ui->tb_relationship->currentRow(),0)->text()))
                relatedArgumentList.removeOne(ui->tb_relationship->item(ui->tb_relationship->currentRow(),0)->text());
            if (relatedStateVariableList.contains(ui->tb_relationship->item(ui->tb_relationship->currentRow(),1)->text()))
                relatedStateVariableList.removeOne(ui->tb_relationship->item(ui->tb_relationship->currentRow(),1)->text());
            ui->tb_relationship->removeRow(ui->tb_relationship->currentRow());
            --currentRTableRow;
    }

}

void DialogArgument::on_btn_add_clicked()
{
    if(ui->tb_stateVariable->selectedItems().count() >= 1){
        int stateVariableRow = ui->tb_stateVariable->selectedItems().at(0)->row();
        QString variableName = ui->tb_stateVariable->item(stateVariableRow,0)->text();
        if((!relatedStateVariableList.contains(variableName)) ){
            relatedStateVariableList.append(variableName);
            ui->tb_relationship->insertRow(currentRTableRow);
            QComboBox *comboEvent = (QComboBox*) ui->tb_stateVariable->cellWidget(stateVariableRow,2);
            qDebug() << "getting sendEvent";
            QString sendEvent = comboEvent->itemText(comboEvent->currentIndex());
            qDebug() << sendEvent;
            QComboBox *comboType = (QComboBox*) ui->tb_stateVariable->cellWidget(stateVariableRow,3);
            QString type = comboType->itemText(comboType->currentIndex());
            qDebug() << "type:" +type;
            QTableWidgetItem *argumentRelation = new QTableWidgetItem();
            argumentRelation->setText("");
            argumentRelation->setData(Qt::UserRole, QVariant::fromValue(new BrisaArgument("","in",variableName)));
            ui->tb_relationship->setItem(currentRTableRow,0,argumentRelation);
            QTableWidgetItem *stateVariableRelation = new QTableWidgetItem();
            stateVariableRelation->setText(ui->tb_stateVariable->selectedItems().at(0)->text());
            BrisaStateVariable *variable = new BrisaStateVariable(sendEvent.toLower(),ui->tb_stateVariable->item(stateVariableRow,0)->text(),type,ui->tb_stateVariable->item(stateVariableRow,1)->text());
            qDebug() << variable;
            stateVariableRelation->setData(Qt::UserRole,QVariant::fromValue(variable));
            ui->tb_relationship->setItem(currentRTableRow,1,stateVariableRelation);
            currentRTableRow++;
        }
    }
}

