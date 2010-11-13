/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisawizard.cpp
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


#include <QtGui>
#include <QFile>
#include <QUuid>
#include <QDir>
#include <QApplication>
#include "brisawizard.h"
#include "dialogargument.h"

QDir BrisaWizard::directory(QDir::home());
static bool wasAccept = false;

 BrisaWizard::BrisaWizard(QWidget *parent)
     : QWizard(parent)
 {
     introPage = new IntroPage(this);
     addPage(introPage);
     devicePage = new DevicePage(this);
     addPage(devicePage);
     servicePage = new ServicePage(this);
     addPage(servicePage);
     actionPage = new ActionPage(this);
     addPage(actionPage);

     setPixmap(QWizard::BannerPixmap, QPixmap(":/images/brisaLogo.png"));
     setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/brisaLogo.png"));

     setWindowTitle(tr("Brisa Wizard"));
     //serviceNameList = new QStringList();
     connect(this,SIGNAL(currentIdChanged(int)),actionPage,SLOT(on_actionPage(int)));
     connect(this,SIGNAL(currentIdChanged(int)),servicePage,SLOT(on_servicePage(int)));
     connect(this,SIGNAL(currentIdChanged(int)),devicePage,SLOT(on_devicePage(int)));
 }

 BrisaWizard::~BrisaWizard(){
    introPage->deleteLater();
    devicePage->deleteLater();
    servicePage->deleteLater();
    actionPage->deleteLater();

    qDebug()<< "aqui";
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

     const_cast<QDir &>(directory).setPath(field("devicePath").toString());

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

         block += "#include \"" + className.toLower().toAscii() + ".h\" \n";

         //TODO permitir que o usuário escolha se deseja uma UI ?
         block += "#include \"ui_" + className.toLower().toAscii() + ".h\" \n";
        //END TODO
         foreach(BrisaService* service, serviceList){
             QString serviceName = service->getAttribute(service->ServiceId);
             block += "#include \"" + serviceName.toLower().toAscii() + ".h\" \n";
         }

         block += "\n" + className.toAscii() + "::" + className.toAscii() + "(QWidget *parent) :\n"
             "\tQMainWindow(parent),\n"
             "\tui(new Ui::" + className.toAscii() + "),\n"
             "\t" + varBrisaDevice.toAscii() + "(DEVICE_TYPE, DEVICE_FRIENDLY_NAME,\n"
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
           "\t" + serviceNameClass.toAscii()+"* " +serviceNameVar.toAscii() + " = new " + serviceNameClass.toAscii() + "(); \n"
           "\t" + serviceNameVar.toAscii() + "->setDescriptionFile(\"" +serviceName.toAscii() +".xml\"); \n"
           "\t" + varBrisaDevice.toAscii() + ".addService(" + serviceNameVar.toAscii() +");\n"
           "\t" + varBrisaDevice.toAscii() + ".start();\n\n";
        }


         // Especificações das operações vem aqui \/

        foreach(BrisaService* service, serviceList)
            foreach(BrisaStateVariable* v, service->getStateVariableList())
                block += "\t" + v->getAttribute(v->Name).toAscii() + " = " + varBrisaDevice.toAscii() + ".getServiceByType(\"urn:schemas-upnp-org:service:" + service->getAttribute(service->ServiceId).toAscii() + ":1\")->getVariable(\"" + v->getAttribute(v->Name).toAscii() + "\");\n";


        foreach(BrisaService* service, serviceList){
            //QString serviceName = service->getAttribute(service->ServiceId);
            foreach(BrisaAction* action, service->getActionList()){
                foreach(BrisaArgument* argument, action->getArgumentList()){
                    if(!stateVariableList.contains(argument->getAttribute(argument->RelatedStateVariable))){
                        stateVariableList.append(argument->getAttribute(argument->RelatedStateVariable));
                        if(argument->getAttribute(argument->Direction) == "in"){
                            block += "\tconnect(" + argument->getAttribute(argument->RelatedStateVariable).toAscii() + ",SIGNAL(changed(BrisaStateVariable*)),this,SLOT(on" +argument->getAttribute(argument->RelatedStateVariable).toAscii()  + "Change(BrisaStateVariable*)));\n";
                        }
                    }

                }
            }
        }
         if((inArguments.count() == 0) && (outArguments.count() > 0))
             block += "\ttestingResponse();\n";
         block += "}\n\n"+
            className.toAscii() + "::~" + className.toAscii() + "()\n"
            "{\n"
            "\tdelete ui;\n"
            "}\n\n"
            "void " + className.toAscii() + "::changeEvent(QEvent *e)\n"
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
                             block += "void "+className.toAscii()+"::on"+argument->getAttribute(argument->RelatedStateVariable).toAscii()+"Change(BrisaStateVariable* v){\n"
                                      "\tqDebug() << \"receiving " + argument->getAttribute(argument->RelatedStateVariable).toAscii()+" change value to:\" + v->getValue().toString();\n";
                             if(((inArguments.count() > 0) && (outArguments.count() > 0)) || ((outArguments.count() > 0) && (inArguments.count() == 0)))
                                if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                                    block += "\ttestingResponse();\n";
                             block += "}\n";

                         }
                     }
                 }
                 block += "void " + className.toAscii() +  "::" + action->getName().toAscii() + "(){\n\n}\n";
             }
         }

         if((inArguments.count() > 0) && (outArguments.count() > 0)){
             block += "void " + className.toAscii() + "::testingResponse(){\n"
                  "\tif( !"+ inArguments.at(0)->getAttribute(inArguments.at(0)->RelatedStateVariable).toAscii() + "->getValue().toString().isEmpty() ";
             for (int i = 1; i < inArguments.count(); i++){
                 BrisaArgument* argument = inArguments.at(i);
                 if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                    block += "&& !" + argument->getAttribute(argument->RelatedStateVariable).toAscii() + "->getValue().toString().isEmpty()";
             }
             block += "){\n";

             foreach(BrisaArgument* a, outArguments){
                 block+="\t\t"+a->getAttribute(a->RelatedStateVariable).toAscii() +"->setAttribute(BrisaStateVariable::Value,QString("+
                        inArguments.at(0)->getAttribute(inArguments.at(0)->RelatedStateVariable).toAscii() + "->getValue().toString() ";
                 for(int i = 1; i< inArguments.count(); i++){
                     BrisaArgument* argument = inArguments.at(i);
                     if(!argument->getAttribute(argument->ArgumentName).isEmpty())
                        block += "+ " + argument->getAttribute(argument->RelatedStateVariable).toAscii() + "->getValue().toString()";
                 }
                 block += "));\n"
                          "\t}\n"
                          "}";
             }
         }

         if((inArguments.count() == 0) && (outArguments.count() > 0)){
             block += "void " + className.toAscii() + "::testingResponse(){\n";
             foreach(BrisaArgument* argument, outArguments){
                 block += "\t" + argument->getAttribute(argument->RelatedStateVariable).toAscii() + "->setAttribute(BrisaStateVariable::Value, \"testing return of action " + serviceList[0]->getActionList().at(0)->getName().toAscii() + "\");\n";
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
"#ifndef " + className.toUpper().toAscii() + "_H\n"
"#define " + className.toUpper().toAscii() + "_H\n\n"
"#include <QMainWindow>\n"
"#include <BRisa/BrisaUpnp/BrisaAction>\n"
"#include <BRisa/BrisaUpnp/BrisaDevice>\n\n"


"using namespace BrisaUpnp;\n"





"#define DEVICE_TYPE              \"" + field("deviceType").toString().toAscii() + "\"\n"
"#define DEVICE_FRIENDLY_NAME     \""+ field("friendlyName").toString().toAscii()  + "\"\n"
"#define DEVICE_MANUFACTURER      \"" + field("manufacturer").toString().toAscii()  + "\"\n"
"#define DEVICE_MANUFACTURER_URL  \""+field("manufacturerUrl").toString().toAscii() + "\"\n"
"#define DEVICE_MODEL_DESCRIPTION \"" + field("modelDesciption").toString().toAscii()  + "\"\n"
"#define DEVICE_MODEL_NAME        \""+ field("modelName").toString().toAscii()  +"\" \n"
"#define DEVICE_MODEL_NUMBER      \"" + field("modelNumber").toString().toAscii()  + "\"\n"
"#define DEVICE_MODEL_URL         \"" + field("modelUrl").toString().toAscii() + "\"\n"
"#define DEVICE_SERIAL_NUMBER     \"" +field("deviceSerial").toString().toAscii() + "\"\n"
"#define DEVICE_UDN               \"uuid:" + uuidDevice + "\"\n\n"

"namespace Ui {\n"
    "\tclass " + className.toAscii() + ";\n"
"}\n\n"

"class " + className.toAscii() + " : public QMainWindow {\n"
    "\tQ_OBJECT\n"
"public:\n" +
    "\t" + className.toAscii() + "(QWidget *parent = 0);\n"
    "\t~" + className.toAscii() + "();\n\n"



"protected:\n"
    "\tvoid changeEvent(QEvent *e);\n\n"

"private:\n"
    "\tUi::"+ className.toAscii() +" *ui;\n"
    "\tBrisaDevice "+ varBrisaDevice.toAscii() +";\n";

stateVariableList.clear();
foreach(BrisaService* service, serviceList){
    QString serviceName = service->getAttribute(service->ServiceId);
    foreach(BrisaStateVariable* v, service->getStateVariableList()){
                if(!stateVariableList.contains(v->getAttribute(v->Name))){
                    stateVariableList.append(v->getAttribute(v->Name));
                    block += "\tBrisaStateVariable *" + v->getAttribute(v->Name).toAscii() + ";\n";
                }
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
                    block += "\t void on"+argument->getAttribute(argument->RelatedStateVariable).toAscii()+"Change(BrisaStateVariable*);\n";
                }
            }
        }
        block += "\t void " + action->getName().toAscii() + "();\n";
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
        block += "\t"+service->getAttribute(service->ServiceId).toLower().toAscii() + ".cpp";
        if(index != serviceList.count()){
            block += "\\ \n";
        }
        index++;
    }

block += "\n\n"
        "HEADERS += "+ className.toLower().toAscii() + ".h";
        if(!serviceList.count() == 0)
            block += "\\ \n";
        index = 1;
        foreach(BrisaService* service, serviceList){
            block += "\t"+service->getAttribute(service->ServiceId).toLower().toAscii() + ".h";
            if(index != serviceList.count()){
                block += "\\ \n";
            }
            index++;
        }
block += "\n\n"
         "RESOURCES +=";
         index = 1;
         foreach(BrisaService* service, serviceList){
             block += "\t"+service->getAttribute(service->ServiceId).toAscii() + ".xml";
             if(index != serviceList.count()){
                 block += "\\ \n";
             }
             index++;
         }
block +=   "\nFORMS += "+ className.toLower().toAscii() + ".ui\n";

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
         "  <class>" + className.toAscii() + "</class>\n"
         "  <widget class=\"QMainWindow\" name=\"" + className.toAscii() + "\" >\n"
         "   <property name=\"geometry\">\n"
         "     <rect>\n"
         "       <x>0</x>\n"
         "       <y>0</y>\n"
         "       <width>400</width>\n"
         "       <height>300</height>\n"
         "     </rect>\n"
         "   </property>\n"
         "   <property name=\"windowTitle\">\n"
         "    <string>" + className.toAscii() + "</string>\n"
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
        "\t" + className.toAscii() + " w;\n"
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
           "#ifndef " + serviceName.toUpper().toAscii() + "_H\n"
           "#define " + serviceName.toUpper().toAscii() + "_H\n\n"
           "#define SERVICE_TYPE \""+ service->getAttribute(service->ServiceType).toAscii() +"\"\n"
           "#define SERVICE_ID \"" + service->getAttribute(service->ServiceId).toAscii() + "\"\n"
           "#define SERVICE_XML_PATH \"/" + service->getAttribute(service->FileAddress).toAscii() + "\"\n"
           "#define SERVICE_CONTROL \"/" + service->getAttribute(service->ControlUrl).toAscii() +"\"\n"
           "#define SERVICE_EVENT_SUB \"/" + service->getAttribute(service->EventSubUrl).toAscii() +"\"\n"
           "#include <BRisa/BrisaUpnp/BrisaAction>\n"
           "#include <BRisa/BrisaUpnp/BrisaService>\n"
           "#include <BRisa/BrisaUpnp/brisastatevariable.h>\n"
           "#include <QtDebug>\n\n"
           "using BrisaUpnp::BrisaService;\n"
           "using BrisaUpnp::BrisaAction;\n"
           "using BrisaUpnp::BrisaStateVariable;\n\n"
           "// The Service\n"
           "class " + serviceNameClass.toAscii() + " : public BrisaService\n"
           "{\n"
           "\tQ_OBJECT\n"
           "public:\n"
           "\t" + serviceNameClass.toAscii() +"();\n";
        qDebug() << "passed out action it";

        foreach(BrisaAction* action, service->getActionList()){
               qDebug() << "passed in action it";
               block += "\tQ_INVOKABLE\n"
                "\tBrisaOutArgument* "+ action->getName().toLower().toAscii() + "(BrisaInArgument* const inArguments, BrisaAction* const action);\n";
            }
            block +=
                    "};\n"
                    "#endif //" + serviceName.toUpper().toAscii() +"_H";



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
         block += "#include \"" + serviceName.toLower().toAscii() + ".h\"\n\n";
         block += serviceNameClass.toAscii() + "::" + serviceNameClass.toAscii() + "():BrisaService(SERVICE_TYPE,\n"
                  "\tSERVICE_ID,SERVICE_XML_PATH,SERVICE_CONTROL,SERVICE_EVENT_SUB){}\n\n";


         foreach(BrisaAction* action, service->getActionList()){
             qDebug() << "passed action argument setting";
             block +="BrisaOutArgument* " + serviceNameClass.toAscii() +"::" + action->getName().toLower().toAscii() + "(BrisaInArgument* const inArguments, BrisaAction* const action){\n"
                 "\tBrisaOutArgument *outArg = new BrisaOutArgument();\n";
             foreach(BrisaArgument *argument, action->getArgumentList()){
                 if(argument->getAttribute(argument->Direction) == "in"){
                    if(argument->getAttribute(argument->ArgumentName).isEmpty())
                        block += "\taction->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable).toAscii() + "\")->setAttribute(BrisaStateVariable::Value,\"" + action->getName().toAscii() + "\");\n";
                    else
                        block += "\taction->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable).toAscii() + "\")->setAttribute(BrisaStateVariable::Value,inArguments->value(\"" +  argument->getAttribute(argument->RelatedStateVariable).toAscii() + "\"));\n";
                  }else
                    block += "\toutArg->insert(\"" +  argument->getAttribute(argument->RelatedStateVariable).toAscii() + "\", action->getStateVariable(\"" +  argument->getAttribute(argument->RelatedStateVariable).toAscii() + "\")->getAttribute(BrisaStateVariable::Value));\n";
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
             "#define DEVICE_TYPE  \"" + field("deviceType").toString().toAscii() + "\"\n";
    foreach(BrisaService* service, serviceList)
        block += "#define SERVICE_TYPE \"" + service->getAttribute(service->ServiceType).toAscii() + "\"\n";
    block += "#define DEVICE_UDN   \"uuid:" + uuidDevice + "\"\n\n"
             "using namespace BrisaUpnp;\n\n"
             "namespace Ui {\n"
             "\tclass " + className.toAscii() + "ControlPoint;\n"
             "}\n\n"
             "class " + className.toAscii() + "ControlPoint : public QMainWindow {\n"
             "\tQ_OBJECT\n\n"
             "public:\n"
             "\t" + className.toAscii() + "ControlPoint(QWidget *parent = 0);\n"
             "\t~" + className.toAscii() + "ControlPoint();\n\n"
             "protected:\n"
             "\tvoid changeEvent(QEvent *e);\n\n"
             "private:\n"
             "\tUi::" + className.toAscii() + "ControlPoint *ui;\n"
             "\tBrisaControlPoint *" + deviceName + ";\n"
             "\tQList<BrisaControlPointDevice *> " + deviceName + "Devices;\n";
    foreach(BrisaService *service, serviceList){
        QString serviceName = service->getAttribute(service->ServiceId);
        foreach(BrisaAction* action, service->getActionList()){
            block += "\tvoid _" + action->getName().toAscii() + "(BrisaControlPointDevice *d";
            int i = 0;
            foreach(BrisaArgument* argument, action->getArgumentList()){
                BrisaStateVariable* v = service->getStateVariableList().at(i);
                qDebug() << "direction to controlpoint.h " + argument->getAttribute(argument->Direction).toAscii() ;
                if(argument->getAttribute(argument->Direction) == "in"){
                    if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                        if( (v->getAttribute(v->DataType) != "string") && (v->getAttribute(v->DataType) != "boolean"))
                            block += ", " + v->getAttribute(v->DataType).toAscii() + " " + v->getAttribute(v->Name).toAscii();
                        else
                            block += ", " + QString(v->getAttribute(v->DataType) == "string"? "QString":"bool").toAscii() + " " + v->getAttribute(v->Name).toAscii();
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
            "  <class>" + className.toAscii() + "ControlPoint</class>\n"
            "  <widget class=\"QMainWindow\" name=\"" + className.toAscii() + "ControlPoint\" >\n"
            "   <property name=\"geometry\">\n"
            "     <rect>\n"
            "       <x>0</x>\n"
            "       <y>0</y>\n"
            "       <width>400</width>\n"
            "       <height>300</height>\n"
            "     </rect>\n"
            "   </property>\n"
            "   <property name=\"windowTitle\">\n"
            "    <string>" + className.toAscii() + "ControlPoint</string>\n"
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
            className.toAscii() + "ControlPoint::" + className.toAscii() + "ControlPoint(QWidget *parent) :\n"
            "\tQMainWindow(parent),ui(new Ui::" + className.toAscii() + "ControlPoint),\n\t" + deviceName + "(new BrisaControlPoint)\n"
            "{\n"
            "\tui->setupUi(this);\n\n"
            "\tconnect(this->" + deviceName + ",SIGNAL(deviceFound(BrisaControlPointDevice*)),this,SLOT(onNewDevice(BrisaControlPointDevice*)));\n"
            "\tconnect(this->" + deviceName + ",SIGNAL(deviceGone(QString)),this,SLOT(onRemovedDevice(QString)));\n"
            "\t" + deviceName + "->start()\n;"
            "\t" + deviceName + "->discover();\n"
            "}\n\n" +
            className.toAscii() + "ControlPoint::~" + className.toAscii() + "ControlPoint()\n"
            "{\n"
            "\tdelete ui;\n"
            "}\n\n"
            "void " + className.toAscii() + "ControlPoint::changeEvent(QEvent *e)\n"
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
            "void " + className.toAscii() + "ControlPoint::restart(){\n" +
            "\t" + deviceName + "->stop();\n" +
            "\t" + deviceName + "->start();\n" +
            "\t" + deviceName + "->discover();\n"
            "}\n\n"
            "void " + className.toAscii() + "ControlPoint::onNewDevice(BrisaControlPointDevice *c){\n"
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
            "void " + className.toAscii() + "ControlPoint::onRemovedDevice(QString udn){\n" +
            "\t" + deviceName + "Devices.removeOne(getDeviceByUDN(udn));\n"
            "\tqDebug() << \"item removed\";\n"
            "\tqDebug() << udn;\n"
            "\trestart();\n"
            "}\n\n"
            "BrisaControlPointDevice* " + className.toAscii() + "ControlPoint::getDeviceByUDN(QString UDN)\n"
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
                    "void " + className.toAscii() + "ControlPoint::_" + action->getName().toAscii() + "(BrisaControlPointDevice *c";
            int i = 0;
            foreach(BrisaArgument* argument, action->getArgumentList()){
                BrisaStateVariable* v = service->getStateVariableList().at(i);
                if(argument->getAttribute(argument->Direction) == "in"){
                    if(!argument->getAttribute(argument->ArgumentName).isEmpty()){
                        if( (v->getAttribute(v->DataType) != "string") && (v->getAttribute(v->DataType) != "boolean"))
                            block += ", " + v->getAttribute(v->DataType).toAscii() + " " + v->getAttribute(v->Name).toAscii();
                        else
                            block += ", " + QString(v->getAttribute(v->DataType) == "string"? "QString":"bool").toAscii() + " " + v->getAttribute(v->Name).toAscii();
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
                        block += "\tparams[\"" + v->getAttribute(v->Name).toAscii() + "\"] = ";
                        if(v->getAttribute(v->DataType) != "string")
                            block += "str.number(" + v->getAttribute(v->Name).toAscii()+");\n";
                        else
                            block += v->getAttribute(v->Name).toAscii() +";\n";
                    }
                }
                i++;
            }
            block += "\tservice->call(\"" + action->getName().toAscii() + "\",params);\n"
                     "}\n\n";
        }
    }
    int i = 0;
    block += "void " + className.toAscii() + "ControlPoint::testing(BrisaControlPointDevice *c){\n"
             "\t_" + serviceList[0]->getActionList().value(0)->getName().toAscii() + "(c";
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
            "void " + className.toAscii() + "ControlPoint::serviceCall(BrisaOutArgument result, QString action){\n"
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
            "\t" + className.toAscii() + "ControlPoint w;\n"
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

    QStringList paths;
    paths.append(QString(field("devicePath").toString() + "/" + field("deviceName").toString() + "/" + field("projectName").toString() + ".pro").toAscii());
    if(field("generateControlPointYES").toString() == "true")
        paths.append(QString(field("devicePath").toString() + "/" + field("deviceName").toString() + "ControlPoint/" + field("deviceName").toString() + "ControlPoint.pro").toAscii());
    brisaprojectwizard::setProjectPaths(paths);
    wasAccept = true;
    serviceList.clear();
    listAction.clear();
    paths.clear();
    QDialog::accept();


}

 void BrisaWizard::generateDevice(){

 }

 void BrisaWizard::generateService(){

 }

 bool BrisaWizard::wasAcceptedWizard(){
     return wasAccept;
 }

