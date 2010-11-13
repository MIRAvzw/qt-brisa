/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: devicepage.cpp
 * Created: 11/13/2010
 * Description: Implements the page where the device info will be setted.
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
