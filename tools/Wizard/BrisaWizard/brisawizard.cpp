/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include <QtGui>
#include <QFile>
#include <QUuid>
#include <QDir>
#include <QApplication>
#include "brisawizard.h"
#include "dialogargument.h"


QList<BrisaAction *> listAction;
static QDir directory(QDir::home());
//QStringList serviceNameList;
//QList<BrisaService*> serviceList;
QStringList stateVariableList;


 BrisaWizard::BrisaWizard(QWidget *parent)
     : QWizard(parent)
 {
     IntroPage* introPage = new IntroPage(this);
     addPage(introPage);
     DevicePage *devicePage = new DevicePage(this);
     addPage(devicePage);
     ServicePage *servicePage = new ServicePage(this);
     addPage(servicePage);
     ActionPage *actionPage = new ActionPage(this);
     addPage(actionPage);

     setPixmap(QWizard::BannerPixmap, QPixmap(":/images/brisaLogo.png"));
     setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/brisaLogo.png"));

     setWindowTitle(tr("Brisa Wizard"));
     //serviceNameList = new QStringList();
     connect(this,SIGNAL(currentIdChanged(int)),actionPage,SLOT(on_actionPage(int)));
     connect(this,SIGNAL(currentIdChanged(int)),servicePage,SLOT(on_servicePage(int)));
     connect(this,SIGNAL(currentIdChanged(int)),devicePage,SLOT(on_devicePage(int)));
 }


 void BrisaWizard::accept()
 {

     serviceList = ServicePage::getServiceList();

     QByteArray deviceName = field("deviceName").toString().toAscii();

     if(field("projectName").toString().isEmpty())
         field("projectName").setValue(field("deviceName").toString());

     QByteArray block;

     QString tempDeviceName = deviceName;
     QString firstCharClass = tempDeviceName.remove(1,tempDeviceName.length());
     tempDeviceName = deviceName;
     QString  lastCharsClass = tempDeviceName.remove(0,1);
     qDebug() << "class 1:" + firstCharClass;
     qDebug() << "class len:" + lastCharsClass;
     QString className = firstCharClass.toUpper() + lastCharsClass.toLower();
     QString varBrisaDevice = firstCharClass.toLower() + lastCharsClass;

     directory.setPath(field("devicePath").toString());

     qDebug() << directory.path();

     qDebug() << directory.mkdir(directory.absolutePath());

     QString path = directory.absolutePath() + "/" + deviceName;

     qDebug() << directory.mkdir(path);

     QList<BrisaArgument*> inArguments, outArguments;
     foreach(BrisaArgument* a, serviceList[0]->getActionList().at(0)->getArgumentList()){
         if(a->getAttribute(a->Direction) == "out")
             outArguments.append(a);
         else
             inArguments.append(a);
     }

         block += "#include \"" + className.toLower() + ".h\" \n";

         //TODO permitir que o usuário escolha se deseja uma UI ?
         block += "#include \"ui_" + className.toLower() + ".h\" \n";
        //END TODO
         foreach(BrisaService* service, serviceList){
             QString serviceName = service->getAttribute(service->ServiceId);
             block += "#include \"" + serviceName.toLower() + ".h\" \n";
         }

         block += "\n" + className + "::" + className + "(QWidget *parent) :\n"
             "\tQMainWindow(parent),\n"
             "\tui(new Ui::" + className + "),\n"
             "\t" + varBrisaDevice + "(DEVICE_TYPE, DEVICE_FRIENDLY_NAME,\n"
                         "\t\tDEVICE_MANUFACTURER, DEVICE_MANUFACTURER_URL,\n"
                         "\t\tDEVICE_MODEL_DESCRIPTION, DEVICE_MODEL_NAME, DEVICE_MODEL_NUMBER,\n"
                         "\t\tDEVICE_MODEL_URL, DEVICE_SERIAL_NUMBER, getCompleteUuid())\n"
         "{\t\n"
             "\tui->setupUi(this);\n";
        foreach(BrisaService* service, serviceList){
            QString serviceName = service->getAttribute(service->ServiceId);
            QString tempServiceName = serviceName;
            QString firstCharService = tempServiceName.remove(1,tempServiceName.length());
            tempServiceName = serviceName;
            QString lastCharsService = tempServiceName.remove(0,1);
            QString serviceNameClass = firstCharService.toUpper() +lastCharsService;
            QString serviceNameVar = firstCharService.toLower() + lastCharsService;
            block +=
           "\t" + serviceNameClass+"* " +serviceNameVar + " = new " + serviceNameClass + "(); \n"
           "\t" + serviceNameVar + "->setDescriptionFile(\"" +serviceName +".xml\"); \n"
           "\t" + varBrisaDevice + ".addService(" + serviceNameVar +");\n"
           "\t" + varBrisaDevice + ".start();\n\n";
        }


         // Especificações das operações vem aqui \/

        foreach(BrisaService* service, serviceList)
            foreach(BrisaStateVariable* v, service->getStateVariableList())
                block += "\t" + v->getAttribute(v->Name) + " = " + varBrisaDevice + ".getServiceByType(\"urn:schemas-upnp-org:service:" + service->getAttribute(service->ServiceId) + ":1\")->getVariable(\"" + v->getAttribute(v->Name) + "\");\n";


        foreach(BrisaService* service, serviceList){
            //QString serviceName = service->getAttribute(service->ServiceId);
            foreach(BrisaAction* action, service->getActionList()){
                foreach(BrisaArgument* argument, action->getArgumentList()){
                    if(!stateVariableList.contains(argument->getAttribute(argument->RelatedStateVariable))){
                        stateVariableList.append(argument->getAttribute(argument->RelatedStateVariable));
                        if(argument->getAttribute(argument->Direction) == "in"){
                            block += "\tconnect(" + argument->getAttribute(argument->RelatedStateVariable) + ",SIGNAL(changed(BrisaStateVariable*)),this,SLOT(on" +argument->getAttribute(argument->RelatedStateVariable)  + "Change(BrisaStateVariable*)));\n";
                        }
                    }

                }
            }
        }
         if((inArguments.count() == 0) && (outArguments.count() > 0))
             block += "\ttestingResponse();\n";
         block += "}\n\n"+
            className + "::~" + className + "()\n"
            "{\n"
            "\tdelete ui;\n"
            "}\n\n"
            "void " + className + "::changeEvent(QEvent *e)\n"
            "{\n"
             "\tQMainWindow::changeEvent(e);\n"
             "\tswitch (e->type()) {\n"
             "\tcase QEvent::LanguageChange:\n"
                 "\t\tui->retranslateUi(this);\n"
                 "\tbreak;\n"
             "\tdefault:\n"
                 "\tbreak;\n"
             "\t}\n"
         "}\n"


         "\n //define your device's methods \n\n";


         stateVariableList.clear();
         foreach(BrisaService* service, serviceList){
             QString serviceName = service->getAttribute(service->ServiceId);
             foreach(BrisaAction* action, service->getActionList()){
                 foreach(BrisaArgument* argument, action->getArgumentList()){
                     if(argument->getAttribute(argument->Direction) == "in"){
                         if(!stateVariableList.contains(argument->getAttribute(argument->RelatedStateVariable))){
                             stateVariableList.append(argument->getAttribute(argument->RelatedStateVariable));
                             block += "void "+className+"::on"+argument->getAttribute(argument->RelatedStateVariable)+"Change(BrisaStateVariable* v){\n"
                                      "\tqDebug() << \"receiving " + argument->getAttribute(argument->RelatedStateVariable)+" change value to:\" + v->getValue().toString();\n";
                             if(((inArguments.count() > 0) && (outArguments.count() > 0)) || ((outArguments.count() > 0) && (inArguments.count() == 0)))
                                if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                                    block += "\ttestingResponse();\n";
                             block += "}\n";

                         }
                     }
                 }
                 block += "void " + className +  "::" + action->getName() + "(){\n\n}\n";
             }
         }

         if((inArguments.count() > 0) && (outArguments.count() > 0)){
             block += "void " + className + "::testingResponse(){\n"
                  "\tif( !"+ inArguments.at(0)->getAttribute(inArguments.at(0)->RelatedStateVariable) + "->getValue().toString().isEmpty() ";
             for (int i = 1; i < inArguments.count(); i++){
                 BrisaArgument* argument = inArguments.at(i);
                 if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                    block += "&& !" + argument->getAttribute(argument->RelatedStateVariable) + "->getValue().toString().isEmpty()";
             }
             block += "){\n";

             foreach(BrisaArgument* a, outArguments){
                 block+="\t\t"+a->getAttribute(a->RelatedStateVariable) +"->setAttribute(BrisaStateVariable::Value,QString("+
                        inArguments.at(0)->getAttribute(inArguments.at(0)->RelatedStateVariable) + "->getValue().toString() ";
                 for(int i = 1; i< inArguments.count(); i++){
                     BrisaArgument* argument = inArguments.at(i);
                     if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                        block += "+ " + argument->getAttribute(argument->RelatedStateVariable) + "->getValue().toString()";
                 }
                 block += "));\n"
                          "\t}\n"
                          "}";
             }
         }

         if((inArguments.count() == 0) && (outArguments.count() > 0)){
             block += "void " + className + "::testingResponse(){\n";
             foreach(BrisaArgument* argument, outArguments){
                 block += "\t" + argument->getAttribute(argument->RelatedStateVariable) + "->setAttribute(BrisaStateVariable::Value, \"testing return of action " + serviceList[0]->getActionList().at(0)->getName() + "\");\n";
             }
             block += "}\n";
         }

         QFile *implementationFile = new QFile(path  + "/" +  deviceName.toLower() + ".cpp");
              if (!implementationFile->open(QFile::WriteOnly | QFile::Text)) {
                  QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                       QObject::tr("Cannot write file %1:\n%2")
                                       .arg(implementationFile->fileName())
                                       .arg(implementationFile->errorString()));
                  return;
              }
              implementationFile->write(block);
              implementationFile->close();
              block.clear();
              //End of the implementation file




QByteArray uuidDevice = QUuid::createUuid().toString().remove("{").remove("}").toAscii();
block +=
"#ifndef " + className.toUpper() + "_H\n"
"#define " + className.toUpper() + "_H\n\n"
"#include <QMainWindow>\n"
"#include <BRisa/BrisaUpnp/BrisaAction>\n"
"#include <BRisa/BrisaUpnp/BrisaDevice>\n\n"


"using namespace BrisaUpnp;\n"





"#define DEVICE_TYPE              \"" + field("deviceType").toString() + "\"\n"
"#define DEVICE_FRIENDLY_NAME     \""+ field("friendlyName").toString()  + "\"\n"
"#define DEVICE_MANUFACTURER      \"" + field("manufacturer").toString()  + "\"\n"
"#define DEVICE_MANUFACTURER_URL  \""+field("manufacturerUrl").toString() + "\"\n"
"#define DEVICE_MODEL_DESCRIPTION \"" + field("modelDesciption").toString()  + "\"\n"
"#define DEVICE_MODEL_NAME        \""+ field("modelName").toString()  +"\" \n"
"#define DEVICE_MODEL_NUMBER      \"" + field("modelNumber").toString()  + "\"\n"
"#define DEVICE_MODEL_URL         \"" + field("modelUrl").toString() + "\"\n"
"#define DEVICE_SERIAL_NUMBER     \"" +field("deviceSerial").toString() + "\"\n"
"#define DEVICE_UDN               \"uuid:" + uuidDevice + "\"\n\n"

"namespace Ui {\n"
    "\tclass " + className + ";\n"
"}\n\n"

"class " + className + " : public QMainWindow {\n"
    "\tQ_OBJECT\n"
"public:\n" +
    "\t" + className + "(QWidget *parent = 0);\n"
    "\t~" + className + "();\n\n"



"protected:\n"
    "\tvoid changeEvent(QEvent *e);\n\n"

"private:\n"
    "\tUi::"+ className +" *ui;\n"
    "\tBrisaDevice "+ varBrisaDevice +";\n";

stateVariableList.clear();
foreach(BrisaService* service, serviceList){
    QString serviceName = service->getAttribute(service->ServiceId);
    foreach(BrisaStateVariable* v, service->getStateVariableList()){
        //foreach(BrisaArgument *argument, action->getArgumentList()){
                if(!stateVariableList.contains(v->getAttribute(v->Name))){
                    stateVariableList.append(v->getAttribute(v->Name));
                    block += "\tBrisaStateVariable *" + v->getAttribute(v->Name) + ";\n";
                }
        //}
    }
}

block +=
    "signals:\n\n"
    "public slots:\n";
stateVariableList.clear();
foreach(BrisaService* service, serviceList){
    foreach(BrisaAction* action, service->getActionList()){
        foreach(BrisaArgument* argument, action->getArgumentList()){
            if(argument->getAttribute(argument->Direction) == "in"){
                if(!stateVariableList.contains(argument->getAttribute(argument->RelatedStateVariable))){
                    stateVariableList.append(argument->getAttribute(argument->RelatedStateVariable));
                    block += "\t void on"+argument->getAttribute(argument->RelatedStateVariable)+"Change(BrisaStateVariable*);\n";
                }
            }
        }
        block += "\t void " + action->getName() + "();\n";
    }
}
if(((inArguments.count() > 0) && (outArguments.count() > 0)) || ((inArguments.count() == 0) && (outArguments.count() > 0)) ){
    block += "\t //this method test the return of action\n"
            "\t void testingResponse();\n";
}
block += "};\n\n"
      "#endif //" + deviceName.toUpper() + "_H";


              QFile *headerFile = new QFile(path + "/" + deviceName.toLower() + ".h");
                   if (!headerFile->open(QFile::WriteOnly | QFile::Text)) {
                       QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                            QObject::tr("Cannot write file %1:\n%2")
                                            .arg(headerFile->fileName())
                                            .arg(headerFile->errorString()));
                       return;
                   }

                   headerFile->write(block);
                   headerFile->close();
                   block.clear();

     //end of header device file


                  block=+
"QT += network \\ \n"
   "\txml\n"
"TARGET = "+ deviceName +"\n"
"CONFIG += QT \\ \n"
   "\tBRISA\n"
"CONFIG += qt \\ \n"
   "\tqxt\n"
"QT += core \\ \n"
   "\tnetwork \\ \n"
   "\txml\n"
"BRISA += upnp \\ \n"
   "\tcore \\ \n"
   "\tutils\n"
"QXT += core \\ \n"
   "\tweb\n"
"TEMPLATE = app\n\n"
"SOURCES += main.cpp \\ \n"+
   "\t" + deviceName.toLower() + ".cpp \\ \n";
    int index = 1;
    foreach(BrisaService* service, serviceList){
        block += "\t"+service->getAttribute(service->ServiceId).toLower() + ".cpp";
        if(index != serviceList.count()){
            block += "\\ \n";
        }
        index++;
    }

block += "\n\n"
        "HEADERS += "+ className.toLower() + ".h";
        if(!serviceList.count() == 0)
            block += "\\ \n";
        index = 1;
        foreach(BrisaService* service, serviceList){
            block += "\t"+service->getAttribute(service->ServiceId).toLower() + ".h";
            if(index != serviceList.count()){
                block += "\\ \n";
            }
            index++;
        }
block += "\n\n"
         "RESOURCES +=";
         index = 1;
         foreach(BrisaService* service, serviceList){
             block += "\t"+service->getAttribute(service->ServiceId) + ".xml";
             if(index != serviceList.count()){
                 block += "\\ \n";
             }
             index++;
         }
block +=   "\nFORMS += "+ className.toLower() + ".ui\n";

                            QFile *projectFile = new QFile(path + "/" + field("projectName").toString() + ".pro");
                                 if (!projectFile->open(QFile::WriteOnly | QFile::Text)) {
                                     QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                                          QObject::tr("Cannot write file %1:\n%2")
                                                          .arg(projectFile->fileName())
                                                          .arg(projectFile->errorString()));
                                     return;
                                 }

                                 projectFile->write(block);
                                 projectFile->close();
                                 block.clear();

block +=
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        "<ui version=\"4.0\">\n"
         "  <class>" + className + "</class>\n"
         "  <widget class=\"QMainWindow\" name=\"" + className + "\" >\n"
         "   <property name=\"geometry\">\n"
         "     <rect>\n"
         "       <x>0</x>\n"
         "       <y>0</y>\n"
         "       <width>400</width>\n"
         "       <height>300</height>\n"
         "     </rect>\n"
         "   </property>\n"
         "   <property name=\"windowTitle\">\n"
         "    <string>"+className+"</string>\n"
         "   </property>\n"
         "   <widget class=\"QMenuBar\" name=\"menuBar\"/>\n"
         "   <widget class=\"QToolBar\" name=\"mainToolBar\"/>\n"
         "   <widget class=\"QWidget\" name=\"centralWidget\"/>\n"
         "   <widget class=\"QStatusBar\" name=\"statusBar\"/>\n"
         "  </widget>\n"
         " <layoutDefault spacing=\"6\" margin=\"11\"/>\n"
         " <pixmapfunction></pixmapfunction>\n"
         " <resources/>\n"
         " <connections/>\n"
        "</ui>";


    QFile *uiDeviceFile = new QFile(path + "/" + deviceName.toLower() + ".ui");
         if (!uiDeviceFile->open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                  QObject::tr("Cannot write file %1:\n%2")
                                  .arg(uiDeviceFile->fileName())
                                  .arg(uiDeviceFile->errorString()));
             return;
         }

         uiDeviceFile->write(block);
         uiDeviceFile->close();
         block.clear();

block +=
        "#include <QtGui/QApplication>\n"
        "#include \""+ deviceName.toLower() +".h\"\n\n"
        "int main(int argc, char *argv[])\n"
        "{\n"
        "\tQApplication a(argc, argv);\n"
        "\t" + className + " w;\n"
        "\tw.show();\n"
        "\treturn a.exec();\n"
        "}";

        QFile *mainDeviceFile = new QFile(path + "/main.cpp");
             if (!mainDeviceFile->open(QFile::WriteOnly | QFile::Text)) {
                 QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                      QObject::tr("Cannot write file %1:\n%2")
                                      .arg(mainDeviceFile->fileName())
                                      .arg(mainDeviceFile->errorString()));
                 return;
             }

             mainDeviceFile->write(block);
             mainDeviceFile->close();
             block.clear();

foreach(BrisaService* service, serviceList){

    QString serviceName = service->getAttribute(service->ServiceId);
    QString tempServiceName = serviceName;
    QString firstCharService = tempServiceName.remove(1,tempServiceName.length());
    tempServiceName = serviceName;
    QString lastCharsService = tempServiceName.remove(0,1);
    QString serviceNameClass = firstCharService.toUpper() +lastCharsService;
    QDomDocument doc;
    QDomProcessingInstruction startText = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
    doc.appendChild(startText);
    QDomElement scpd = doc.createElement("scpd");
    scpd.setAttribute("xmlns","urn:schemas-upnp-org:service-1-0");
    doc.appendChild(scpd);
    QDomElement specVersion = doc.createElement("specVersion");
    scpd.appendChild(specVersion);
    QDomElement major = doc.createElement("major");
    specVersion.appendChild(major);
    QDomText t = doc.createTextNode("1");
    major.appendChild(t);
    QDomElement minor = doc.createElement("minor");
    specVersion.appendChild(minor);
    t= doc.createTextNode("0");
    minor.appendChild(t);
    QDomElement actionListXML = doc.createElement("actionList");
    scpd.appendChild(actionListXML);
    stateVariableList.clear();
    foreach(BrisaAction* action, service->getActionList()){
        QDomElement actionXML = doc.createElement("action");
        actionListXML.appendChild(actionXML);
        QDomElement actionNameXML = doc.createElement("name");
        actionXML.appendChild(actionNameXML);
        t = doc.createTextNode(action->getName());
        actionNameXML.appendChild(t);
        QDomElement argumentListXML = doc.createElement("argumentList");
        actionXML.appendChild(argumentListXML);
        foreach(BrisaArgument* argument, action->getArgumentList()){
            if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                QDomElement argumentXML = doc.createElement("argument");
                argumentListXML.appendChild(argumentXML);
                QDomElement argumentNameXML = doc.createElement("name");
                argumentXML.appendChild(argumentNameXML);
                t = doc.createTextNode(argument->getAttribute(argument->ArgumentName));
                argumentNameXML.appendChild(t);
                QDomElement argumentDirectionXML = doc.createElement("direction");
                argumentXML.appendChild(argumentDirectionXML);
                t = doc.createTextNode(argument->getAttribute(argument->Direction));
                argumentDirectionXML.appendChild(t);
                QDomElement argumentRelelatedStateVariableXML = doc.createElement("RelatedStateVariable");
                argumentXML.appendChild(argumentRelelatedStateVariableXML);
                t = doc.createTextNode(argument->getAttribute(argument->RelatedStateVariable));
                argumentRelelatedStateVariableXML.appendChild(t);
            }
        }
    }
    QDomElement serviceStateTableXML = doc.createElement("serviceStateTable");
    scpd.appendChild(serviceStateTableXML);
    foreach(BrisaStateVariable *v, service->getStateVariableList()){
        QDomElement stateVariableXML = doc.createElement("stateVariable");
        if(!stateVariableList.contains(v->getAttribute(v->Name))){
            stateVariableList.append(v->getAttribute(v->Name));
            stateVariableXML.setAttribute("sendEvents",QString(v->sendEventsChange()== true ? "yes" : "no"));
            serviceStateTableXML.appendChild(stateVariableXML);
            QDomElement stateVariableNameXML = doc.createElement("name");
            stateVariableXML.appendChild(stateVariableNameXML);
            t = doc.createTextNode(v->getAttribute(v->Name));
            stateVariableNameXML.appendChild(t);
            QDomElement stateVariabledataTypeXML = doc.createElement("dataType");
            stateVariableXML.appendChild(stateVariabledataTypeXML);
            t = doc.createTextNode(v->getAttribute(v->DataType));
            stateVariabledataTypeXML.appendChild(t);
            if(!v->getAttribute(v->DefaultValue).isEmpty()){
                QDomElement stateVariableDefaultValue = doc.createElement("defaultValue");
                stateVariableXML.appendChild(stateVariableDefaultValue);
                t = doc.createTextNode(v->getAttribute(v->DefaultValue));
                stateVariableDefaultValue.appendChild(t);
            }
        }
    }

    QFile *xmlFile = new QFile(path  + "/" +  serviceName + ".xml");
         if (!xmlFile->open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                  QObject::tr("Cannot write file %1:\n%2")
                                  .arg(xmlFile->fileName())
                                  .arg(xmlFile->errorString()));
             return;
         }

         xmlFile->write(doc.toByteArray(4));
         xmlFile->close();
         block.clear();

         block +=
           "#ifndef " + serviceName.toUpper() + "_H\n"
           "#define " + serviceName.toUpper() + "_H\n\n"
           "#define SERVICE_TYPE \""+ service->getAttribute(service->ServiceType) +"\"\n"
           "#define SERVICE_ID \"" + service->getAttribute(service->ServiceId) + "\"\n"
           "#define SERVICE_XML_PATH \"/" + service->getAttribute(service->FileAddress) + "\"\n"
           "#define SERVICE_CONTROL \"/" + service->getAttribute(service->ControlUrl) +"\"\n"
           "#define SERVICE_EVENT_SUB \"/" + service->getAttribute(service->EventSubUrl) +"\"\n"
           "#include <BRisa/BrisaUpnp/BrisaAction>\n"
           "#include <BRisa/BrisaUpnp/BrisaService>\n"
           "#include <BRisa/BrisaUpnp/brisastatevariable.h>\n"
           "#include <QtDebug>\n\n"
           "using BrisaUpnp::BrisaService;\n"
           "using BrisaUpnp::BrisaAction;\n"
           "using BrisaUpnp::BrisaStateVariable;\n\n"
           "// The Service\n"
           "class " + serviceNameClass + " : public BrisaService\n"
           "{\n"
           "\tQ_OBJECT\n"
           "public:\n"
           "\t" + serviceNameClass +"();\n";
        qDebug() << "passed out action it";

        foreach(BrisaAction* action, service->getActionList()){
               qDebug() << "passed in action it";
               block += "\tQ_INVOKABLE\n"
                "\tBrisaOutArgument* "+ action->getName().toLower().toAscii() + "(BrisaInArgument* const inArguments, BrisaAction* const action);\n";
            }
            block +=
                    "};\n"
                    "#endif //" + serviceName.toUpper() +"_H";



        QFile *headerServiceFile = new QFile(path  + "/" +  serviceName.toLower() + ".h");
         if (!headerServiceFile->open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                  QObject::tr("Cannot write file %1:\n%2")
                                  .arg(headerServiceFile->fileName())
                                  .arg(headerServiceFile->errorString()));
             return;
         }

         headerServiceFile->write(block);
         headerServiceFile->close();
         block.clear();
         block += "#include \"" + serviceName.toLower() + ".h\"\n\n";
         block += serviceNameClass + "::" + serviceNameClass + "():BrisaService(SERVICE_TYPE,\n"
                  "\tSERVICE_ID,SERVICE_XML_PATH,SERVICE_CONTROL,SERVICE_EVENT_SUB){}\n\n";


         foreach(BrisaAction* action, service->getActionList()){
             qDebug() << "passed action argument setting";
             block +="BrisaOutArgument* " + serviceNameClass +"::" + action->getName().toLower().toAscii() + "(BrisaInArgument* const inArguments, BrisaAction* const action){\n"
                 "\tBrisaOutArgument *outArg = new BrisaOutArgument();\n";
             foreach(BrisaArgument *argument, action->getArgumentList()){
                 if(argument->getAttribute(argument->Direction) == "in"){
                    if(argument->getAttribute(argument->ArgumentName).isEmpty())
                        block += "\taction->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable) + "\")->setAttribute(BrisaStateVariable::Value,\"" + action->getName() + "\");\n";
                    else
                        block += "\taction->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable) + "\")->setAttribute(BrisaStateVariable::Value,inArguments->value(\"" +  argument->getAttribute(argument->RelatedStateVariable) + "\"));\n";
                  }else
                    block += "\toutArg->insert(\"" +  argument->getAttribute(argument->RelatedStateVariable) + "\", action->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable) + "\")->getAttribute(BrisaStateVariable::Value));\n";
             }
             block += "\treturn outArg;\n"
                   "}\n\n";
         }

         QFile *sourceServiceFile = new QFile(path  + "/" +  serviceName.toLower() + ".cpp");
         if (!sourceServiceFile->open(QFile::WriteOnly | QFile::Text)) {
             QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                                  QObject::tr("Cannot write file %1:\n%2")
                                  .arg(sourceServiceFile->fileName())
                                  .arg(sourceServiceFile->errorString()));
             return;
         }

         sourceServiceFile->write(block);
         sourceServiceFile->close();
         block.clear();
}//END FOREACH SERVICE

qDebug() << "generate : ? " + field("generateControlPointYES").toString();
if(field("generateControlPointYES").toString() == "true"){
    path = path + "ControlPoint" ;
    
    qDebug() << directory.mkdir(path);
    
    
    block += "#ifndef " + deviceName.toUpper() + "CONTROLPOINT_H\n"
             "#define " + deviceName.toUpper() + "CONTROLPOINT_H\n\n"
             "#include <QMainWindow>\n"
             "#include <BRisa/BrisaUpnp/BrisaControlPoint>\n\n"
             "#define DEVICE_TYPE  \"" + field("deviceType").toString() + "\"\n";
    foreach(BrisaService* service, serviceList)
        block += "#define SERVICE_TYPE \"" + service->getAttribute(service->ServiceType) + "\"\n";
    block += "#define DEVICE_UDN   \"uuid:" + uuidDevice + "\"\n\n"
             "using namespace BrisaUpnp;\n\n"
             "namespace Ui {\n"
             "\tclass " + className + "ControlPoint;\n"
             "}\n\n"
             "class " + className + "ControlPoint : public QMainWindow {\n"
             "\tQ_OBJECT\n\n"
             "public:\n"
             "\t" + className + "ControlPoint(QWidget *parent = 0);\n"
             "\t~" + className + "ControlPoint();\n\n"
             "protected:\n"
             "\tvoid changeEvent(QEvent *e);\n\n"
             "private:\n"
             "\tUi::" + className + "ControlPoint *ui;\n"
             "\tBrisaControlPoint *" + deviceName + ";\n"
             "\tQList<BrisaControlPointDevice *> " + deviceName + "Devices;\n";
    foreach(BrisaService *service, serviceList){
        QString serviceName = service->getAttribute(service->ServiceId);
        foreach(BrisaAction* action, service->getActionList()){
            block += "\tvoid _" + action->getName() + "(BrisaControlPointDevice *d";
            int i = 0;
            foreach(BrisaArgument* argument, action->getArgumentList()){
                BrisaStateVariable* v = service->getStateVariableList().at(i);
                qDebug() << "direction to controlpoint.h " + argument->getAttribute(argument->Direction) ;
                if(argument->getAttribute(argument->Direction) == "in"){
                    if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                        if( (v->getAttribute(v->DataType) != "string") && (v->getAttribute(v->DataType) != "boolean"))
                            block += ", " + v->getAttribute(v->DataType) + " " + v->getAttribute(v->Name);
                        else
                            block += ", " + QString(v->getAttribute(v->DataType) == "string"? "QString":"bool") + " " + v->getAttribute(v->Name);
                    }
                }
                i++;
            }
            block += ");\n";
        }
    }


    block +=
            "\tBrisaControlPointDevice *getDeviceByUDN(QString UDN);\n"
            "\tvoid restart();\n"
            "\tvoid testing(BrisaControlPointDevice *c);\n\n"
            "public slots:\n"
            "\tvoid onNewDevice(BrisaControlPointDevice *c);\n"
            "\tvoid onRemovedDevice(QString Udn);\n"
            "\tvoid serviceCall(BrisaOutArgument result, QString action);\n\n"
            "private slots:\n\n"
            "};\n"
            "#endif //" + deviceName.toUpper() + "CONTROLPOINT_H";
    QFile *headerControlPointFile = new QFile(path  + "/" +  deviceName.toLower() + "controlpoint.h");
    if (!headerControlPointFile->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(headerControlPointFile->fileName())
                             .arg(headerControlPointFile->errorString()));
        return;
    }

    headerControlPointFile->write(block);
    headerControlPointFile->close();
    block.clear();
    block +=
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<ui version=\"4.0\">\n"
            "  <class>" + className + "ControlPoint</class>\n"
            "  <widget class=\"QMainWindow\" name=\"" + className + "ControlPoint\" >\n"
            "   <property name=\"geometry\">\n"
            "     <rect>\n"
            "       <x>0</x>\n"
            "       <y>0</y>\n"
            "       <width>400</width>\n"
            "       <height>300</height>\n"
            "     </rect>\n"
            "   </property>\n"
            "   <property name=\"windowTitle\">\n"
            "    <string>"+className+"ControlPoint</string>\n"
            "   </property>\n"
            "   <widget class=\"QMenuBar\" name=\"menuBar\"/>\n"
            "   <widget class=\"QToolBar\" name=\"mainToolBar\"/>\n"
            "   <widget class=\"QWidget\" name=\"centralWidget\"/>\n"
            "   <widget class=\"QStatusBar\" name=\"statusBar\"/>\n"
            "  </widget>\n"
            " <layoutDefault spacing=\"6\" margin=\"11\"/>\n"
            " <pixmapfunction></pixmapfunction>\n"
            " <resources/>\n"
            " <connections/>\n"
            "</ui>";


    QFile *uiControlPointFile = new QFile(path + "/" + deviceName.toLower() + "controlpoint.ui");
    if (!uiControlPointFile->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(uiControlPointFile->fileName())
                             .arg(uiControlPointFile->errorString()));
        return;
    }

    uiControlPointFile->write(block);
    uiControlPointFile->close();
    block.clear();

    block +=
            "#include \"" + deviceName.toLower() + "controlpoint.h\"\n"
            "#include \"ui_" + deviceName.toLower() + "controlpoint.h\"\n"
            "#include <QMessageBox>\n\n" +
            className + "ControlPoint::" + className + "ControlPoint(QWidget *parent) :\n"
            "\tQMainWindow(parent),ui(new Ui::" + className + "ControlPoint),\n\t" + deviceName + "(new BrisaControlPoint)\n"
            "{\n"
            "\tui->setupUi(this);\n\n"
            "\tconnect(this->" + deviceName + ",SIGNAL(deviceFound(BrisaControlPointDevice*)),this,SLOT(onNewDevice(BrisaControlPointDevice*)));\n"
            "\tconnect(this->" + deviceName + ",SIGNAL(deviceGone(QString)),this,SLOT(onRemovedDevice(QString)));\n"
            "\t" + deviceName + "->start()\n;"
            "\t" + deviceName + "->discover();\n"
            "}\n\n" +
            className + "ControlPoint::~" + className + "ControlPoint()\n"
            "{\n"
            "\tdelete ui;\n"
            "}\n\n"
            "void " + className + "ControlPoint::changeEvent(QEvent *e)\n"
            "{\n"
            "\tQMainWindow::changeEvent(e);\n"
            "\tswitch (e->type()) {\n"
            "\tcase QEvent::LanguageChange:\n"
            "\t\tui->retranslateUi(this);\n"
            "\t\tbreak;\n"
            "\tdefault:\n"
            "\t\tbreak;\n"
            "\t}\n"
            "}\n\n"
            "void " + className + "ControlPoint::restart(){\n" +
            "\t" + deviceName + "->stop();\n" +
            "\t" + deviceName + "->start();\n" +
            "\t" + deviceName + "->discover();\n"
            "}\n\n"
            "void " + className + "ControlPoint::onNewDevice(BrisaControlPointDevice *c){\n"
            "\tif(c->getAttribute(BrisaControlPointDevice::DeviceType).compare(DEVICE_TYPE))\n"
            "\t\treturn;\n\n"
            "\tfor(int i = 0; i <" + deviceName + "Devices.size(); i++) {\n"
            "\t\tif(" + deviceName + "Devices[i]->getAttribute(BrisaControlPointDevice::Udn) == c->getAttribute(BrisaControlPointDevice::Udn)) {\n"
            "\t\t\t" + deviceName  + "Devices[i] = c;\n"
            "\t\t\treturn;\n"
            "\t\t}\n"
            "\t}\n"
            "\tthis->" + deviceName + "Devices.append(c);\n"
            "\tthis->testing(c);\n"
            "}\n\n"
            "//this slot remove device from device list if the device leave\n"
            "void " + className + "ControlPoint::onRemovedDevice(QString udn){\n" +
            "\t" + deviceName + "Devices.removeOne(getDeviceByUDN(udn));\n"
            "\tqDebug() << \"item removed\";\n"
            "\tqDebug() << udn;\n"
            "\trestart();\n"
            "}\n\n"
            "BrisaControlPointDevice* " + className + "ControlPoint::getDeviceByUDN(QString UDN)\n"
            "{\n"
            "\tfor(int i = 0; i < "+ deviceName + "Devices.size(); i++)\n"
            "\t\tif(UDN.compare(" + deviceName + "Devices[i]->getAttribute(BrisaControlPointDevice::Udn)) == 0)\n"
            "\t\t\treturn " + deviceName + "Devices[i];\n"
            "\treturn NULL;"
            "}\n\n";



    foreach(BrisaService* service, serviceList ){
        QString serviceName = service->getAttribute(service->ServiceId);
        foreach(BrisaAction* action, service->getActionList()) {
            block +=
                    "void " + className + "ControlPoint::_" + action->getName() + "(BrisaControlPointDevice *c";
            int i = 0;
            foreach(BrisaArgument* argument, action->getArgumentList()){
                BrisaStateVariable* v = service->getStateVariableList().at(i);
                if(argument->getAttribute(argument->Direction) == "in"){
                    if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                        if( (v->getAttribute(v->DataType) != "string") && (v->getAttribute(v->DataType) != "boolean"))
                            block += ", " + v->getAttribute(v->DataType) + " " + v->getAttribute(v->Name);
                        else
                            block += ", " + QString(v->getAttribute(v->DataType) == "string"? "QString":"bool") + " " + v->getAttribute(v->Name);
                    }
                }
                i++;
            }
            block += "){\n"
                     "\tBrisaControlPointService *service = c->getServiceByType(SERVICE_TYPE);\n"
                     "\tconnect(service, SIGNAL(requestFinished(BrisaOutArgument,QString)), this, SLOT(serviceCall(BrisaOutArgument, QString)));\n"
                     "\tQMap<QString,QString> params;\n"
                     "\tQString str;\n";

            i = 0;
            foreach(BrisaArgument* argument, action->getArgumentList()){
                BrisaStateVariable* v = service->getStateVariableList().at(i);
                if(argument->getAttribute(argument->Direction) == "in"){
                    if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                        block += "\tparams[\"" + v->getAttribute(v->Name) + "\"] = ";
                        if(v->getAttribute(v->DataType) != "string")
                            block += "str.number("+ v->getAttribute(v->Name)+");\n";
                        else
                            block += v->getAttribute(v->Name)+";\n";
                    }
                }
                i++;
            }
            block += "\tservice->call(\""+ action->getName() +"\",params);\n"
                     "}\n\n";
        }
    }
    int i = 0;
    block += "void "+className+"ControlPoint::testing(BrisaControlPointDevice *c){\n"
             "\t_"+serviceList[0]->getActionList().value(0)->getName()+"(c";
    foreach(BrisaArgument *a, serviceList[0]->getActionList().value(0)->getArgumentList()){
        BrisaStateVariable *v = serviceList[0]->getStateVariableList().at(i);
        if(!a->getAttribute(a->ArgumentName).isEmpty()){
            if(a->getAttribute(a->Direction) == "in"){
                if(v->getAttribute(v->DataType) != "string")
                    block += ",1";
                else
                    block += ",\"testing\"";
            }
        }
        i++;
    }
    block += ");\n"
             "}\n\n";

    block +=
            "//this method returns result after action on Device\n"
            "void " + className + "ControlPoint::serviceCall(BrisaOutArgument result, QString action){\n"
            "\tQ_UNUSED(action);\n"
            "\tqDebug() << result;\n"
            "}\n\n"
            "//define your methods here";

    QFile *sourceControlPointFile = new QFile(path  + "/" +  deviceName.toLower() + "controlpoint.cpp");
    if (!sourceControlPointFile->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(sourceControlPointFile->fileName())
                             .arg(sourceControlPointFile->errorString()));
        ;
    }

    sourceControlPointFile->write(block);
    sourceControlPointFile->close();
    block.clear();
    block +=
            "QT       += network xml\n"
            "TARGET = " + deviceName + "ControlPoint\n"
            "TEMPLATE = app\n\n\n"


            "CONFIG += QT BRISA\n"
            "CONFIG += qt qxt\n"
            "QT += core network xml\n"
            "BRISA += upnp core utils\n"
            "QXT += core web\n\n\n"

            "SOURCES += main.cpp\\ \n"
            "\t" + deviceName.toLower() + "controlpoint.cpp\n"

            "HEADERS  += " + deviceName.toLower() + "controlpoint.h\n"

            "FORMS    +=" + deviceName.toLower() + "controlpoint.ui\n";

    QFile *proControlPointFile = new QFile(path  + "/" +  deviceName + "ControlPoint.pro");
    if (!proControlPointFile->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(proControlPointFile->fileName())
                             .arg(proControlPointFile->errorString()));
        ;
    }

    proControlPointFile->write(block);
    proControlPointFile->close();
    block.clear();

    block +=
            "#include <QtGui/QApplication>\n"
            "#include \""+ deviceName.toLower() +"controlpoint.h\"\n\n"
            "int main(int argc, char *argv[])\n"
            "{\n"
            "\tQApplication a(argc, argv);\n"
            "\t" + className + "ControlPoint w;\n"
            "\tw.show();\n"
            "\ta.exec();\n"
            "}";

    QFile *mainControlPointFile = new QFile(path + "/main.cpp");
    if (!mainControlPointFile->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(0, QObject::tr("Brisa Wizard"),
                             QObject::tr("Cannot write file %1:\n%2")
                             .arg(mainControlPointFile->fileName())
                             .arg(mainControlPointFile->errorString()));
        return;
    }

    mainControlPointFile->write(block);
    mainControlPointFile->close();
    block.clear();



  }

    QFile file("info.path");

    QDir::setCurrent(QApplication::applicationDirPath());
    qDebug()<< QDir::currentPath();
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(QString( field("devicePath").toString() + "/" + field("deviceName").toString() + "/" + field("projectName").toString() + ".pro").toAscii() );
        if(field("generateControlPointYES").toString() == "true")
            file.write("\n" + QString(field("devicePath").toString() + "/" + field("deviceName").toString() + "ControlPoint/" + field("deviceName").toString() + "ControlPoint.pro").toAscii() );
    }

    QDialog::accept();

}

 void BrisaWizard::generateDevice(){

 }

 void BrisaWizard::generateService(){

 }

