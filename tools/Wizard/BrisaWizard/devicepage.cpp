#include "devicepage.h"

DevicePage::DevicePage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Device"));
     setSubTitle(tr("Specify basic information about the device"));
     setPixmap(QWizard::LogoPixmap, QPixmap(":/images/brisaLogo.png"));

     gridBox = new QGridLayout;

     deviceTypeLabel = new QLabel(tr("Device &Type"));
     deviceTypeLine = new QLineEdit();
     deviceTypeLabel->setBuddy(deviceTypeLine);

     gridBox->addWidget(deviceTypeLabel,0,0);
     gridBox->addWidget(deviceTypeLine,0,1);

     friendlyNameLabel = new QLabel(tr("&Friendly Name"));
     friendlyNameLine = new QLineEdit();
     friendlyNameLabel->setBuddy(friendlyNameLine);

     gridBox->addWidget(friendlyNameLabel,1,0);
     gridBox->addWidget(friendlyNameLine,1,1);

     manufacturerLabel = new QLabel(tr("&Manufacturer Name"));
     manufacturerLine = new QLineEdit();
     manufacturerLabel->setBuddy(manufacturerLine);

     gridBox->addWidget(manufacturerLabel,2,0);
     gridBox->addWidget(manufacturerLine,2,1);

     manufacturerUrlLabel = new QLabel(tr("Manufactturer &Url"));
     manufacturerUrlLine = new QLineEdit();
     manufacturerUrlLabel->setBuddy(manufacturerUrlLine);

     gridBox->addWidget(manufacturerUrlLabel,3,0);
     gridBox->addWidget(manufacturerUrlLine,3,1);

     modelDesciptionLabel = new QLabel(tr("Model &Description"));
     modelDesciptionLine = new QLineEdit();
     modelDesciptionLabel->setBuddy(modelDesciptionLine);

     gridBox->addWidget(modelDesciptionLabel,4,0);
     gridBox->addWidget(modelDesciptionLine,4,1);


     modelNameLabel = new QLabel(tr("Model &Name"));
     modelNameLine = new QLineEdit();
     modelNameLabel->setBuddy(modelNameLine);

     gridBox->addWidget(modelNameLabel,5,0);
     gridBox->addWidget(modelNameLine,5,1);

     modelNumberLabel = new QLabel(tr("Model Num&ber"));
     modelNumberLine = new QLineEdit();
     modelNumberLabel->setBuddy(modelNumberLine);

     gridBox->addWidget(modelNumberLabel,6,0);
     gridBox->addWidget(modelNumberLine,6,1);

     modelUrlLabel = new QLabel(tr("Model U&rl"));
     modelUrlLine = new QLineEdit();
     modelUrlLabel->setBuddy(modelUrlLine);

     gridBox->addWidget(modelUrlLabel,7,0);
     gridBox->addWidget(modelUrlLine,7,1);

     deviceSerialLabel = new QLabel(tr("Device &Serial Number"));
     deviceSerialLine = new QLineEdit();
     deviceSerialLabel->setBuddy(deviceSerialLine);

     gridBox->addWidget(deviceSerialLabel,8,0);
     gridBox->addWidget(deviceSerialLine,8,1);


     registerField("deviceType*",deviceTypeLine);
     registerField("friendlyName*",friendlyNameLine);
     registerField("manufacturer*",manufacturerLine);
     registerField("manufacturerUrl*",manufacturerUrlLine);
     registerField("modelDesciption*",modelDesciptionLine);
     registerField("modelName*",modelNameLine);
     registerField("modelNumber*",modelNumberLine);
     registerField("modelUrl*",modelUrlLine);
     registerField("deviceSerial*",deviceSerialLine);

     setLayout(gridBox);
 }


 void DevicePage::on_devicePage(int){

     deviceTypeLine->setText("urn:schemas-upnp-org:device:" + field("deviceName").toString() + ":1");
     friendlyNameLine->setText(field("deviceName").toString() +" Device");
     manufacturerLine->setText("Brisa Corp.");
     manufacturerUrlLine->setText("https://garage.maemo.org/projects/brisa");
     modelDesciptionLine->setText("An UPnP "+field("deviceName").toString() +" Device");
     modelNameLine->setText(field("deviceName").toString() + " Device");
     modelNumberLine->setText("1.0");
     modelUrlLine->setText("https://garage.maemo.org/projects/brisa");
     deviceSerialLine->setText("1.0");

     deviceTypeLine->setCursorPosition(0);
     friendlyNameLine->setCursorPosition(0);
     manufacturerLine->setCursorPosition(0);
     manufacturerUrlLine->setCursorPosition(0);
     modelDesciptionLine->setCursorPosition(0);
     modelNameLine->setCursorPosition(0);
     modelNumberLine->setCursorPosition(0);
     modelUrlLine->setCursorPosition(0);
     deviceSerialLine->setCursorPosition(0);


 }
