:mod:`config` --- Configuration facilities
==========================================

.. module: config
    :synopsis: Configuration Facility

Qt BRisa provides a very simple configuration API, just like BRisa Python does.

You can create Configuration Managers using the BrisaConfigurationManager class (from BrisaCore). Using this class you are able to set and get parameters in an easy way. Also, you can save the configuration and use it later.

Here is an example on how to use BrisaConfigurationManager class

Before writing your Qt BRisa applications
-----------------------------------------
Whenever you are going to write a Qt BRisa application you need to change the .pro file in the project folder adding the following lines:
::
        CONFIG += BRISA
        BRISA += upnp core utils


Using the Built-In Configuration Manager
----------------------------------------
::

    QString configPath("./");

    // Generating my own configuration
    QHash<QString,QString> state;
    state["brisaPython.owner"] = "owner1";
    state["brisaPython.version"] = "0.10.0";
    state["brisaPython.encoding"] = "utf-8'";
    state["brisaC++.owner"] = "owner2";
    state["brisaC++.version"] = "0.1.0";
    state["brisaC++.encoding"] = "utf-8";

    // Creating a  BrisaConfigurationManager object using the generated configuration
    BrisaConfigurationManager *myConfig = new BrisaConfigurationManager(configPath, state);

    // Saving the config manager
    myConfig->save();

    // Checking brisaC++.owner parameter value and changing it
    qDebug() << "value: " << myConfig->getParameter("brisaC++","owner");
    myConfig->setParameter("brisaC++", "owner", "newOwner");

    myConfig->save();

    // Updating the config
    myConfig->update();

    qDebug() << "value: " << myConfig->getParameter("brisaC++","owner");


The output should be
::
    value:  "owner2" 
    value:  "newOwner"



