#include "intropage.h"
#include <QTranslator>
#include <QDebug>

static QDir directory(QDir::home());

IntroPage::IntroPage(QWidget *parent)
     : QWizardPage(parent)
 {
     setTitle(tr("Brisa Project"));
     setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/brisaLogo.png"));

     label = new QLabel(tr("This wizard will generate a Brisa Project."));
     label->setWordWrap(true);
     QLabel *deviceNameLabel = new QLabel(tr("Device Name:"));
     deviceNameEdit = new QLineEdit();

     pathLabel = new QLabel(tr("Create in:       "));
     pathLineEdit = new QLineEdit(QDir::homePath());
     pathLineEdit->setDisabled(true);
     QLabel *projectNameLabel = new QLabel(tr("&Project Name:"));
     projectNameLineEdit = new QLineEdit;
     projectNameLabel->setBuddy(projectNameLineEdit);

     browserButton = new QPushButton("&Browse...");

     QGridLayout *deviceLayoutGrid = new QGridLayout;
     deviceLayoutGrid->addWidget(deviceNameLabel,0,0);
     deviceLayoutGrid->addWidget(deviceNameEdit,0,1);
     deviceLayoutGrid->addWidget(projectNameLabel,1,0);
     deviceLayoutGrid->addWidget(projectNameLineEdit,1,1);
     QHBoxLayout *pathLayoutH = new QHBoxLayout;
     pathLayoutH->addWidget(pathLabel);
     pathLayoutH->addWidget(pathLineEdit);
     pathLayoutH->addWidget(browserButton);
     deviceNameLabel->setBuddy(pathLineEdit);
     generateControlPointYES = new QCheckBox(tr("Generate Control Point"));

     registerField("projectName*",projectNameLineEdit);
     registerField("deviceName*",  deviceNameEdit);
     registerField("devicePath",  pathLineEdit);
     registerField("generateControlPointYES",generateControlPointYES);
     QVBoxLayout *mainBox = new QVBoxLayout;

     mainBox->addLayout(deviceLayoutGrid);
     mainBox->addLayout(pathLayoutH);
     mainBox->addWidget(generateControlPointYES);
     setLayout(mainBox);

     connect(browserButton, SIGNAL(clicked()), this, SLOT(changeDirectory()));
     connect(deviceNameEdit,SIGNAL(textChanged(QString)),this,SLOT(on_deviceNameChanged()));
     connect(deviceNameEdit,SIGNAL(editingFinished()),this,SLOT(on_deviceNameEditing_finished()));
     connect(projectNameLineEdit,SIGNAL(editingFinished()),this,SLOT(on_projectNameEditing_finished()));
     connect(projectNameLineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_projectNameChanged()));

 }

 void IntroPage::changeDirectory()
 {
     QString path = QFileDialog::getExistingDirectory (this, tr("Directory"), directory.path());
         if ( path.isNull() == false )
         {
             directory.setPath(path);
             pathLineEdit->setText(directory.absolutePath());
             on_deviceNameChanged();
         }

 }

 void IntroPage::on_deviceNameChanged()
 {
     projectNameLineEdit->setText(this->deviceNameEdit->text());

 }

 void IntroPage::on_projectNameChanged(){
     pathLineEdit->setText(directory.absolutePath() +"/" + this->projectNameLineEdit->text());
 }
