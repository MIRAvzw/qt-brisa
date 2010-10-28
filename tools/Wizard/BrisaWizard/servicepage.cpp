#include "servicepage.h"

static QStringList serviceNameList;
static QList<BrisaService*> serviceList;
static int rowArgumentsRepeated = -1;


ServicePage::ServicePage(QWidget *parent)
     : QWizardPage(parent)
 {

     setTitle(tr("Services"));
     setSubTitle(tr("Specify basic information about the services provided by the device"));
     setPixmap(QWizard::LogoPixmap, QPixmap(":/images/brisaLogo.png"));
     serviceLabel = new QLabel(tr("Service &Name"));
     serviceEdit = new QLineEdit();
     serviceLabel->setBuddy(serviceEdit);
     serviceListWidget = new QListWidget();
     addServiceButton = new QPushButton(tr("&add"));
     //const QKeySequence *k = new QKeySequence(QKeySequence("&a"));
     addServiceButton->setShortcut(QKeySequence("Alt+a"));
     mainBox = new QVBoxLayout();
     serviceTypeLineEdit = new QLineEdit();
     serviceIDLineEdit = new QLineEdit();
     serviceXMLPathLineEdit = new QLineEdit();
     serviceControlLineEdit = new QLineEdit();
     eventSubLineEdit = new QLineEdit();

     QLabel *serviceTypeLabel = new QLabel(tr("Service &Type:"));
     QLabel *serviceIDLabel = new QLabel(tr("Service &ID:"));
     QLabel *serviceXMLPathLabel = new QLabel(tr("Service &XML Path:"));
     QLabel *serviceControlLabel = new QLabel(tr("Service &Control:"));
     QLabel *eventSubLabel = new QLabel(tr("Event &Sub:"));
     serviceTypeLabel->setBuddy(serviceTypeLineEdit);
     serviceIDLabel->setBuddy(serviceIDLineEdit);
     serviceXMLPathLabel->setBuddy(serviceXMLPathLineEdit);
     serviceControlLabel->setBuddy(serviceControlLineEdit);
     eventSubLabel->setBuddy(eventSubLineEdit);
     QGridLayout *serviceLayoutGrid = new QGridLayout;

     serviceLayoutGrid->addWidget(serviceLabel,0,0);
     serviceLayoutGrid->addWidget(serviceEdit,0,1);
     serviceLayoutGrid->addWidget(serviceTypeLabel,1,0);
     serviceLayoutGrid->addWidget(serviceTypeLineEdit,1,1);
     serviceLayoutGrid->addWidget(serviceIDLabel,2,0);
     serviceLayoutGrid->addWidget(serviceIDLineEdit,2,1);
     serviceLayoutGrid->addWidget(serviceXMLPathLabel,3,0);
     serviceLayoutGrid->addWidget(serviceXMLPathLineEdit,3,1);
     serviceLayoutGrid->addWidget(serviceControlLabel,4,0);
     serviceLayoutGrid->addWidget(serviceControlLineEdit,4,1);
     serviceLayoutGrid->addWidget(eventSubLabel,5,0);
     serviceLayoutGrid->addWidget(eventSubLineEdit,5,1);
     QFrame *serviceFrame = new QFrame;
     QHBoxLayout *serviceLayoutH = new QHBoxLayout;
     QSpacerItem *spacerButton = new QSpacerItem(400,0,QSizePolicy::Maximum);

     serviceLayoutH->addSpacerItem(spacerButton);
     serviceLayoutH->addWidget(addServiceButton);

     QVBoxLayout *serviceLayoutFrameV = new QVBoxLayout;
     serviceLayoutFrameV->addLayout(serviceLayoutGrid);

     serviceLayoutFrameV->addLayout(serviceLayoutH);
     serviceFrame->setLayout(serviceLayoutFrameV);
     mainBox->addWidget(serviceFrame);
     mainBox->addWidget(serviceListWidget);
     QHBoxLayout *serviceLayoutH2 = new QHBoxLayout;
     QSpacerItem *spacerButton2 = new QSpacerItem(350,0,QSizePolicy::Maximum);
     removeServiceButton = new QPushButton(tr("Remove"));
     serviceLayoutH2->addSpacerItem(spacerButton2);
     serviceLayoutH2->addWidget(removeServiceButton);
     mainBox->addLayout(serviceLayoutH2);

     registerField("services*", serviceListWidget);

     setLayout(mainBox);

     connect(addServiceButton,SIGNAL(clicked()),this,SLOT(on_addServiceButton_clicked()));
     connect(serviceEdit,SIGNAL(editingFinished()),this,SLOT(on_serviceEditing_finished()));
     connect(removeServiceButton,SIGNAL(clicked()),this,SLOT(on_removeButton_clicked()));

 }

 void ServicePage::on_removeButton_clicked(){
     if(serviceList.removeOne(serviceListWidget->currentItem()->data(Qt::UserRole).value<BrisaService*>()))
         serviceListWidget->takeItem(serviceListWidget->currentRow());

 }

 void ServicePage::on_servicePage(int currentPage){
     if(currentPage == 2){
            serviceEdit->setText(field("deviceName").toString()+"Actions");
            serviceTypeLineEdit->setText("urn:schemas-upnp-org:service:"+field("deviceName").toString()+"Actions:1");
            serviceIDLineEdit->setText(field("deviceName").toString()+"Actions");
            serviceXMLPathLineEdit->setText(field("deviceName").toString()+"Actions/"+field("deviceName").toString()+"Actions.xml");
            serviceControlLineEdit->setText(field("deviceName").toString()+"Actions/control");
            eventSubLineEdit->setText(field("deviceName").toString()+"Actions/eventSub");
            serviceListWidget->setFocus(Qt::MouseFocusReason);
     }
 }

 void ServicePage::on_serviceEditing_finished(){
     qDebug() << "actiuns?"+ serviceEdit->text().section(serviceEdit->text(),serviceEdit->text().length(),serviceEdit->text().length()-7);
     QString service = serviceEdit->text();
     qDebug() << "SERVICE:" + service.endsWith("Actions");
     if(!service.endsWith("Actions"))
         serviceEdit->setText(serviceEdit->text()+"Actions");
     serviceTypeLineEdit->setText("urn:schemas-upnp-org:service:"+serviceEdit->text()+":1");
     serviceIDLineEdit->setText(serviceEdit->text());
     serviceXMLPathLineEdit->setText(serviceEdit->text()+"/"+serviceEdit->text()+".xml");
     serviceControlLineEdit->setText(serviceEdit->text()+"/control");
     eventSubLineEdit->setText(serviceEdit->text()+"/eventSub");


     serviceTypeLineEdit->setCursorPosition(0);
     serviceIDLineEdit->setCursorPosition(0);
     serviceXMLPathLineEdit->setCursorPosition(0);
     serviceControlLineEdit->setCursorPosition(0);
     eventSubLineEdit->setCursorPosition(0);


 }

 void ServicePage::on_addServiceButton_clicked()
 {
     QString serviceName = serviceEdit->text().trimmed();
     if( (serviceListWidget->findItems(serviceName,Qt::MatchCaseSensitive).count() == 0) && (!(serviceName.isEmpty()) ))
     {
         QListWidgetItem *item = new QListWidgetItem();
         BrisaService* service = new BrisaService(serviceTypeLineEdit->text(),serviceIDLineEdit->text(),"urn:schemas-upnp-org:service-1-0",serviceControlLineEdit->text(),eventSubLineEdit->text());
         service->setAttribute(service->FileAddress,serviceXMLPathLineEdit->text());
         serviceList.append(service);
         item->setData(Qt::UserRole,QVariant::fromValue(service));
         item->setText(serviceName);
         serviceListWidget->addItem(item);
         serviceNameList.append(serviceName);
         qDebug()<< serviceName;
         qDebug() << serviceNameList.count();
         serviceEdit->clear();
         serviceControlLineEdit->clear();
         eventSubLineEdit->clear();
         serviceXMLPathLineEdit->clear();
         serviceIDLineEdit->clear();
         serviceTypeLineEdit->clear();

         serviceListWidget->setFocus();
     }

 }

 QList<BrisaService*> ServicePage::getServiceList(){
     return serviceList;
 }

 QStringList ServicePage::getServiceNameList(){
     return serviceNameList;
 }

