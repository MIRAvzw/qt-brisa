#include <tclap/CmdLine.h>
#include <string>
#include <iostream>
#include <BrisaCore/BrisaConfigurationManager>

using namespace BrisaCore;

#define BRISA_VERSION "0.1.0 \n Copyright (c) 2008-2009 BRisa Team"

BrisaConfigurationManager *manager;

void listSection(QString section)
{
    QHash<QString,QString> sectionDictionary = manager->items(section);

    if (sectionDictionary.size() == 0) {
        std::cout << "Section " << section.toStdString() << " does not exist" << std::endl;
        return;
    }

    std::cout << "===== Section " << section.toStdString() << " ===== " << std::endl;
    QString str("");

    QList<QString> sections = sectionDictionary.keys();
    qSort(sections.begin(), sections.end());

    for (int i = 0; i < sections.size(); ++i) {
    	str.append(sections[i]  + " : " + sectionDictionary.value(sections[i]) + "\n");
    }

    std::cout << str.toStdString() << std::endl;

}

int main(int argc, char *argv[])
{

    try {

        TCLAP::CmdLine cmd("Command description message", ' ', BRISA_VERSION);

        QString configPath("./");
        QHash<QString,QString> state;

        manager = new BrisaConfigurationManager(configPath,state);
        manager->setDirectAccess(true);
        manager->update();

        //add arguments that read a value from the command line.
        TCLAP::ValueArg<std::string> section("s", "section", "section name to set parameter on", \
                                             false, "", "string");
        cmd.add(section);
        TCLAP::ValueArg<std::string> parameter("p", "parameter", "parameter name to set value", \
                                               false, "", "string");
        cmd.add(parameter);
        TCLAP::ValueArg<std::string> items("i", "items", "print items of a section",false, \
                                           "", "string");
        cmd.add(items);

        //add arguments that name implies: simple, on/off, boolean switches
        TCLAP::SwitchArg deleteSwitch("d", "delete", "delete a section or a parameter", false);
        cmd.add(deleteSwitch);

        TCLAP::SwitchArg listSwitch("l", "list", "list all sections", false);
        cmd.add(listSwitch);

        TCLAP::UnlabeledValueArg<std::string> parValue("value", "value to set e given parameter", \
                                                       false, "", "string");
        cmd.add(parValue);

        //parse the command line
        cmd.parse(argc, argv);

        //values of command line
        std::string sec = section.getValue();
        std::string par = parameter.getValue();
        std::string item = items.getValue();

        bool del = deleteSwitch.getValue();
        bool list = listSwitch.getValue();
        //

        if (list) {

            std::cout << "Listing sections\n" << std::endl;

            QList<QString> list = manager->getSectionNames();
            foreach(QString section, list) {
                listSection(section);
                std::cout << "\n" << std::endl;
            }
            return 0;
        }

        if (item != "") {
            listSection( QString(item.c_str()) );
            return 0;
        }
        //options to set sections and parameters
        if ( (sec !=  "") and (par != "") ) {
            if (del) {
                std::cout << "Removing section " << sec << std::endl;
                if ( manager->removeSection(QString(sec.c_str())) )
                    std::cout << "section "<< sec << " does not exist" << std::endl;
            return 0;
            }

            std::string value = parValue.getValue();

            if (value == "") {
                std::cout << "Removing parameter " << par << " from section " << sec << std::endl;
                value = "None";
            }
            else {
                std::cout << "Setting parameter " << par << " in section " << sec \
                          << " to the value " << value << std::endl;
            }

            manager->setParameter(QString(sec.c_str()), QString(par.c_str()), QString(value.c_str()));
            return 0;
        }

        if ( (par != "") and (sec == "") ) {
            std::cout << "could not identify a parameter without a section name" << std::endl;
            return 0;
        }

        if ( (par == "") and (sec != "") ) {
            if (del) {
                std::cout << "Removing section " << sec << std::endl;
                if ( manager->removeSection(QString(sec.c_str())) )
                    std::cout << "section "<< sec << " does not exist" << std::endl;
                return 0;
            }
            std::cout << "could not identify action on section" << std::endl;
            return 0;
        }
        //

    }catch (TCLAP::ArgException &e) {  // catch any exceptions
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    return 0;
}
