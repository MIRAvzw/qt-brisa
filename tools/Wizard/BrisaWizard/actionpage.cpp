#include "actionpage.h"
#include "dialogargument.h"
#include <QMessageBox>

static int rowArgumentsRepeated;

ActionPage::ActionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Actions"));
    currentTableRow =0;
    setSubTitle(tr("Specify basic information about the actions of the service "));
    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/brisaLogo.png"));

    actionNameLabel = new QLabel(tr("&Action name:"));
    actionNameLineEdit = new QLineEdit;
    actionNameLabel->setBuddy(actionNameLineEdit);

    QVBoxLayout *mainBox = new QVBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *radioBox = new QHBoxLayout;
    QGridLayout *listGrid = new QGridLayout;
    addActionButton = new QPushButton(tr("       A&dd Action       "));
    QLabel *actionLabelList = new QLabel(tr("Actions"));
    QLabel *argumentLabelList = new QLabel(tr("Arguments"));
    QLabel *serviceLabelName = new QLabel(tr("Services"));
    serviceCbox = new QComboBox;
    qDebug()<<"adding items";
    //serviceCbox->addItems(serviceNameList); //continuar aqui FIXME


    actionListWidget = new QListWidget();
    argumentTableWidget = new QTableWidget(20,2);
    QStringList labels;
    labels.append("Argument");
    labels.append("Direction");
    argumentTableWidget->setHorizontalHeaderLabels(labels);
    QHBoxLayout *argumentBox = new QHBoxLayout;
    QLabel *argumentLabel = new QLabel(tr("Argument Name"));
    argumentEdit = new QLineEdit;
    argumentBox->addWidget(argumentLabel);
    argumentBox->addWidget(argumentEdit);
    QPushButton *delArgumentButton = new QPushButton("Remove Argument");
    removeActionButton = new QPushButton("Remove Action");
    removeActionButton->setEnabled(false);
    editArgumentsButton = new QPushButton("Edit Arguments");
    editArgumentsButton->setEnabled(false);
    repeatArgumentsButton =  new QPushButton("Repeat Arguments");
    repeatArgumentsButton->setEnabled(false);
    QHBoxLayout *nameBoxH = new QHBoxLayout;
    QVBoxLayout *nameBoxV = new QVBoxLayout;
    nameBoxH->addWidget(actionNameLabel);
    nameBoxH->addWidget(actionNameLineEdit);
    nameBoxH->addWidget(addActionButton);
    nameBoxV->addWidget(serviceLabelName);
    nameBoxV->addWidget(serviceCbox);
    nameBoxV->addLayout(nameBoxH);
    QHBoxLayout *boxActionListH = new QHBoxLayout;
    boxActionListH->addWidget(actionListWidget);
    QVBoxLayout* actionButtonLayoutV = new QVBoxLayout();
    actionButtonLayoutV->addWidget(editArgumentsButton);
    actionButtonLayoutV->addWidget(repeatArgumentsButton);
    actionButtonLayoutV->addWidget(removeActionButton);
    boxActionListH->addLayout(actionButtonLayoutV);
    nameBoxV->addLayout(boxActionListH);

    mainBox->addLayout(nameBoxV);

   connect(addActionButton,SIGNAL(clicked()),this,SLOT(on_addActionButton_clicked()));

   connect(editArgumentsButton,SIGNAL(clicked()),this,SLOT(on_EditArgumentsButton_clicked()));

   connect(removeActionButton,SIGNAL(clicked()),this,SLOT(on_RemoveActionButton_clicked()));


   connect(actionListWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(on_actionChange(QModelIndex)));
   layout->addLayout(mainBox);

    connect(actionNameLineEdit,SIGNAL(editingFinished()),this, SLOT(on_actionNameLineEdit_edited()));

   connect(serviceCbox,SIGNAL(activated(int)),this,SLOT(on_selectedService(int)));
    //Importante   \/
    registerField("actions*",  actionListWidget);
    setLayout(layout);
    actionNameLineEdit->setEnabled(false);
    addActionButton->setEnabled(false);
    connect(repeatArgumentsButton,SIGNAL(clicked()),this,SLOT(on_repeatArgumentsButton_clicked()));
    connect(actionListWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_actionListWidget_DoubleClicked()));

}

void ActionPage::on_repeatArgumentsButton_clicked(){
    int response = QMessageBox::information(this,tr("Atention!"),
                 tr("When you apply same arguments to others actions, certify than other actions haven't any arguments, because their argument list will clean. Are you sure this?"),
                 QMessageBox::No,QMessageBox::Ok);
    if(response == QMessageBox::Ok){
       BrisaAction* action = actionListWidget->currentItem()->data(Qt::UserRole).value<BrisaAction*>();
       int currentRow = actionListWidget->currentRow();
       rowArgumentsRepeated = currentRow;
       for(int i = 0; i< actionListWidget->count(); i++){
           if(i != currentRow){
               qDebug() << "INSTANCE ACTION";
               BrisaAction* currentAction = actionListWidget->item(i)->data(Qt::UserRole).value<BrisaAction*>();
               BrisaArgument* argument = action->getArgumentList().value(i);
               currentAction->clearArgumentList();
               currentAction->addArguments(action->getArgumentList());
           }
       }
       repeatArgumentsButton->setEnabled(false);
   }
}

void ActionPage::on_EditArgumentsButton_clicked(){
    on_actionListWidget_DoubleClicked();
}

void ActionPage::on_actionListWidget_DoubleClicked(){
    DialogArgument* dialogArgument = new DialogArgument();
    dialogArgument->setWindowTitle("Editing Argument List of Action " + actionListWidget->currentItem()->text());
    qDebug() << "arrive before actionMap insert";
    dialogArgument->setAction(actionListWidget->currentItem()->text());
    BrisaService* service = serviceCbox->itemData(serviceCbox->currentIndex(),Qt::UserRole).value<BrisaService*>();
    dialogArgument->setStateVariables(service->getStateVariableList());
    BrisaAction* action = actionListWidget->currentItem()->data(Qt::UserRole).value<BrisaAction*>();

    qDebug() << "arguments of action:\n";
    foreach(BrisaArgument* argument, action->getArgumentList())
        qDebug() << argument->getAttribute(argument->ArgumentName);
    dialogArgument->setArgumentList(action->getArgumentList());
    dialogArgument->updateTableWidget();
    if(dialogArgument->exec()){

        qDebug() << "accepted";
        foreach(BrisaArgument* argument, dialogArgument->getArgumentList())
            qDebug() << argument->getAttribute(argument->ArgumentName);

        action->clearArgumentList();
        QList<BrisaArgument*> argumentList = dialogArgument->getArgumentList();
        action->addArguments(argumentList);
        qDebug() << argumentList.count();// + " qtd argumentlist";
        qDebug() << actionListWidget->count();// + " qtd actionListWidget";
        if((action->getArgumentList().count() >= 1) && (actionListWidget->count() > 1) && (actionListWidget->currentRow() != rowArgumentsRepeated)){
            repeatArgumentsButton->setEnabled(true);
        }
        //editArgumentsButton->setEnabled(true);
        service->clearStateVariableList();
        foreach(BrisaStateVariable *stateVariable, dialogArgument->getStateVariables())
            service->addStateVariable(stateVariable);

    }
}

void ActionPage::on_actionPage(int id){
    if(id == 3){
        serviceCbox->clear();
        //actionListWidget->setFocus();
        actionNameLineEdit->setFocus();

        serviceList = ServicePage::getServiceList();

        foreach(BrisaService* service, serviceList){
            serviceCbox->addItem(service->getAttribute(service->ServiceId),QVariant::fromValue(service));
            qDebug() << service->getAttribute(service->ServiceId);
        }

        if(!serviceList.isEmpty()){
            actionNameLineEdit->setEnabled(true);
            addActionButton->setEnabled(true);
        }


    }
}



void ActionPage::on_selectedService(int i){
    actionListWidget->clear();
    BrisaService* service = serviceCbox->itemData(i,Qt::UserRole).value<BrisaService*>();
    qDebug() << "passed here" + service->getAttribute(service->ServiceId);
    foreach(BrisaAction* action,service->getActionList()){
        qDebug() <<"passed into mapservice";
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::UserRole,QVariant::fromValue(action));
        item->setText(action->getName());
        actionListWidget->addItem(item);
    }

}

void ActionPage::on_actionChange(QModelIndex i){
   Q_UNUSED(i);
   editArgumentsButton->setEnabled(true);
   BrisaAction* action = actionListWidget->currentItem()->data(Qt::UserRole).value<BrisaAction*>();
   qDebug() << rowArgumentsRepeated;
   if((action->getArgumentList().count() >= 1) && (actionListWidget->count() > 1) && (actionListWidget->currentRow() != rowArgumentsRepeated))
       repeatArgumentsButton->setEnabled(true);
   else
       repeatArgumentsButton->setEnabled(false);
}



void ActionPage::on_actionNameLineEdit_edited(){
    on_addActionButton_clicked();
}


void ActionPage::on_addActionButton_clicked()
{
    QString actionName = actionNameLineEdit->text().trimmed(); //verificar se o cara colocar espaco vazio
   if( (actionListWidget->findItems(actionName,Qt::MatchCaseSensitive).count() == 0) && (!actionNameLineEdit->text().isEmpty()) ){
       QString serviceSelected = serviceCbox->itemText(serviceCbox->currentIndex());
       QListWidgetItem *item = new QListWidgetItem();

       BrisaAction *action = new BrisaAction(actionName,0,0);
       item->setData(Qt::UserRole, QVariant::fromValue(action));
       item->setText(actionName);

       qDebug() << "arrive here adding action";

       qDebug() << "adding action:" + serviceSelected;
       BrisaService* service = serviceCbox->itemData(serviceCbox->currentIndex(),Qt::UserRole).value<BrisaService*>();
       service->addAction(action);
       // qDebug() << "after adding action:" + serviceSelected->getAttribute(serviceSelected->ServiceId);
       actionListWidget->addItem(item);
       actionNameLineEdit->clear();
       actionListWidget->setFocus();
       actionNameLineEdit->setFocus();

       removeActionButton->setEnabled(true);

       //actionListWidget->setItemSelected(actionListWidget->currentItem(),true);
    }
}

void ActionPage::on_RemoveActionButton_clicked(){
    if(actionListWidget->selectedItems().count() == 1){
        //QString action = actionListWidget->currentItem()->text();
        qDebug() <<"passed 1";
        BrisaService* service= serviceCbox->itemData(serviceCbox->currentIndex(), Qt::UserRole).value<BrisaService*>();
        //qDebug() << "removing:" + serviceSelected;
        qDebug() << "clearning actionList";
        service->clearActionList();
        qDebug() << "removing item from ListWidget";
        qDebug() << actionListWidget->takeItem(actionListWidget->currentRow());
        for(int i = 0; i < actionListWidget->count(); i++){
            qDebug() << "adding item to ListWidget";
            BrisaAction* action = actionListWidget->currentItem()->data(Qt::UserRole).value<BrisaAction*>();
            service->addAction(action);
        }

        if(actionListWidget->count() == 0)
            removeActionButton->setEnabled(false);

        qDebug() <<"passed 2";


       qDebug() << "passed before 2";

       qDebug() << "actions: ";
       foreach(BrisaAction* action, service->getActionList()){
           qDebug() << action->getName();
       }
   }
}
