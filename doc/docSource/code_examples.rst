**************
Code Examples
**************

Here we're going to show some examples that will help you understand better how to make applications using Qt BRisa.

-------------------------------
Creating a Binary Light Device
-------------------------------

This is the implementation of a Binary Light Device, which specifications
you can find `here
<http://upnp.org/standardizeddcps/documents/BinaryLight1.0cc.pdf>`_.

Before creating a Device it's good to create the service(s) it's going to use. So we're going to create a service called SwitchPower before creating the BinaryLightDevice.

Let's define the service's information at the beginning of the code.
::
        #define SERVICE_TYPE "urn:schemas-upnp-org:service:SwitchPower:1"
        #define SERVICE_ID "SwitchPower"
        #define SERVICE_XML_PATH "/SwitchPower/SwitchPower-scpd.xml"
        #define SERVICE_CONTROL "/SwitchPower/control"
        #define SERVICE_EVENT_SUB "/SwitchPower/eventSub"

After that, let's include the Brisa libraries that are used to create the Actions and the services.
::
        #include <BrisaAction>
        #include <BrisaService>
        
        using namespace BrisaUpnp;  
       
Now we should start implementing our SwitchPower service
::

                SwitchPower() : BrisaService(SERVICE_TYPE,
                                             SERVICE_ID,
                                             SERVICE_XML_PATH,
                                             SERVICE_CONTROL,
                                             SERVICE_EVENT_SUB) { }

                BrisaOutArgument* settarget(BrisaInArgument* const inArguments, BrisaAction* const action) {
                    getStateVariable("Target")->setAttribute(BrisaStateVariable::Value,
                                                                   inArguments["NewTargetValue"]);
                    getStateVariable("Status")->setAttribute(BrisaStateVariable::Value,
                                                                   inArguments["NewTargetValue"]);
        
                    BrisaOutArgument *outArgs = new BrisaOutArgument();
                    return outArgs;
                }

                BrisaOutArgument* gettarget(BrisaInArgument* const inArguments, BrisaAction* const action) {
                    Q_UNUSED(inArguments)

                    BrisaOutArgument *outArgs = new BrisaOutArgument();
                    outArgs->insert("RetTargetValue", getStateVariable("Target")
                                                 ->getAttribute(BrisaStateVariable::Value));
                    return outArgs;
                }

                BrisaOutArgument* getstatus(BrisaInArgument* const inArguments, BrisaAction* const action) {
                    Q_UNUSED(inArguments)

                    BrisaOutArgument *outArgs = new BrisaOutArgument();
                    outArgs->insert("ResultStatus", getStateVariable("Status")
                                                       ->getAttribute(BrisaStateVariable::Value));
                    return outArgs;
                }


Now it's time to start implementing our device. Let us include BrisaDevice class and our service header, define the namespace and our device informations.
::
        #include <BrisaDevice>
        #include "switchPower.h"
        
        using namespace BrisaUpnp;

        #define DEVICE_TYPE              "urn:schemas-upnp-org:device:BinaryLight:1"
        #define DEVICE_FRIENDLY_NAME     "Binary Light Device"
        #define DEVICE_MANUFACTURER      "Brisa Team. Embedded Laboratory and INdT Brazil"
        #define DEVICE_MANUFACTURER_URL  "https://garage.maemo.org/projects/brisa"
        #define DEVICE_MODEL_DESCRIPTION "An UPnP Binary Light Device"
        #define DEVICE_MODEL_NAME        "Binary Light Device"
        #define DEVICE_MODEL_NUMBER      "1.0"
        #define DEVICE_MODEL_URL         "https://garage.maemo.org/projects/brisa"
        #define DEVICE_SERIAL_NUMBER     "1.0"

It's time we start implementing our device! We need to create our header file with the slots, attributes and methods we are going to use. In this example our device will be a QWidget that contains a BrisaDevice and two BrisaStateVariable objects as attributes, but if you don't want to display a graphical interface to represent your device you can just make it child of BrisaDevice (instead of having a BrisaDevice attribute).
::
        class Device : public QWidget
        {
            Q_OBJECT
        
        public:
            Device(QWidget *parent = 0);
            ~Device();
                
        public slots:
            void statechanged(BrisaStateVariable *);
        
        private:
            BrisaDevice binaryLight;
            BrisaStateVariable *status;
            BrisaStateVariable *target;
            
        };

Now, our header file is ready and we have to start the implementation of the device class source file.
Here's its constructor
::
        Device::Device(QWidget *parent) : QWidget(parent)
        {                  
            this->binaryLight = new binaryLight(DEVICE_TYPE,
                                                DEVICE_FRIENDLY_NAME,
                                                DEVICE_MANUFACTURER,
                                                DEVICE_MANUFACTURER_URL,
                                                DEVICE_MODEL_DESCRIPTION,
                                                DEVICE_MODEL_NAME,
                                                DEVICE_MODEL_NUMBER,
                                                DEVICE_MODEL_URL,
                                                DEVICE_SERIAL_NUMBER,
                                                getCompleteUuid());
            SwitchPower *switchPower = new SwitchPower();
            switchPower->setDescriptionFile("SwitchPower-scpd.xml");
            this->binaryLight.addService(switchPower);
            this->binaryLight.start();
        
            this->status = binaryLight.getServiceByType("urn:schemas-upnp-org:service:SwitchPower:1")->
                           getVariable("Status");
            this->target = binaryLight.getServiceByType("urn:schemas-upnp-org:service:SwitchPower:1")->
                           getVariable("Target");
        
            connect(status, SIGNAL(changed(BrisaStateVariable *)), this,
                    SLOT(statechanged(BrisaStateVariable *)));
        }


And now we just need to implement our statechanged slot.
::
        void Widget::statechanged(BrisaStateVariable *var)
        {
            if(var->getAttribute(BrisaStateVariable::Value) == "1") {
                qDebug() << "Light Switched on";
            } else {
                qDebug() << "Light Switched off";
            }
        }

Our device is done and the last thing we need to do is initialize the device in the main file.
::
        #include <QtGui/QApplication>
        #include "light.h"
        
        int main(int argc, char *argv[])
        {
            QApplication a(argc, argv);
            Device dev;
            dev.show();

            return a.exec();
        }

Thats all it takes to implement the Binary Light Device.

You could follow these steps to implement any service/device, but remember that for
now you'll have to write the service's xml yourself.

You can downlaod easily each file click on the name to download the file :download:`light.h <example_code/light.h>`, :download:`light.cpp <example_code/light.cpp>`, :download:`switchPower.h <example_code/switchPower.h>`, :download:`main.cpp <example_code/main.cpp>`, :download:`BrisaBinaryLight.pro <example_code/BrisaBinaryLight.pro>`

and the service's xml :download:`Here <example_code/SwitchPower-scpd.xml>`.

--------------------------------
Creating a simple Control Point
--------------------------------

This is an example of a simple Control Point, in this example we will implement
a command line Control Point for Binary Light devices, but this will cover the basics of creating a control point.
This Control Point has the following features:

* Searching for devices
* Listing devices
* Handling events (new device located, removed device)

As we said above, our ControlPoint is a command line one, and we'll have to implement two things, 
the ControlPoint that will hold the devices and the thread to receive the commands.

The first thing to do is to include the libs we are going to use in our code.
::
    #include <BrisaControlPoint> // To create the Control Point
    #include <QList>    // To store the devices
    #include <QString>
    #include <QtDebug>  // For debugging purposes
    #include <QTextStream>  // For receiving the commands
    #include <QCoreApplication>
    #include <iostream>

Because our control point is interacting with Binary Light devices, we need to define the device type we are
communicating with and service that contains the actions we are going to use
::
    //The binary light type 
    #define BINARY_LIGHT_TYPE    "urn:schemas-upnp-org:device:BinaryLight:1"

    //Service that contains the actions we'll use
    #define SERVICE_SWITCH_POWER "urn:schemas-upnp-org:service:SwitchPower:1"

Now let's create and implement the ControlPoint class, we 
decided to make it a BrisaControlPoint itself, but you could have a BrisaControlPoint object to work as a control point
in another class of your choice if you'd want to.

Our Control Point class will show when devices enter or leave the network,
list devices to the user and it is going to interact with the devices by 
using the actions provided by them. In order to implement these features we are going to need
the following attributes, methods and slots
::
    class ControlPoint : BrisaControlPoint
    {
        Q_OBJECT
        public:
            ControlPoint();   //ControlPoint Constructor
            ~ControlPoint();  //ControlPoint Destructor
    
    
        private:
            QString listServices(BrisaControlPointDevice *dev);
            QString listEmbeddedDevices(BrisaControlPointDevice *dev);
    
            QList <BrisaControlPointDevice*> devices;  //List to store the devices
            BrisaControlPointDevice *selected;         //Device to interact
            HandleCmds *handle;                        //Thread that handle the commands
    
        private slots:
            void help();                 // Lists all commands
            void setLight(int index);    // Selects a device 
            void getTarget();            // Calls the getTarget action
            void getStatus();            // Calls the getStatus action   
            void turnOn();               // Turns on the light       
            void turnOff();              // Turns off the light
            void exit();                 // Exits the application
            void list();                 // Lists all the devices; 
            // Gets the SetTarget response  
            void setTargetResponse(QString response, QString method);
            // Gets the GetTarget response
            void getTargetResponse(QString response, QString method);
            // Gets the GetStatus response
            void getStatusResponse(QString response, QString method);
            //Slot used when a device joins the network.
            void onNewDevice(BrisaControlPointDevice *dev);
            //Slot used when a device leaves the network.
            void onRemovedDevice(QString desc);
            //Slot used to handle error
            void requestError(QString errorMessage, QString methodName);  
    };

Our Control Point header file is ready, so let us 
implement all methods and slots that were declared. The first important thing to
do is implementing the constructor method that is going to create all the necessary event connections and
start both the Device's discovery and the Thread commands.
::
    #include "controlpoint.h"
    
    ControlPoint::ControlPoint() : BrisaControlPoint()
    {
        this->selected = NULL;
        handle = new HandleCmds();
    
        connect(this, SIGNAL(deviceFound(BrisaControlPointDevice*)), this,
                            SLOT(onNewDevice(BrisaControlPointDevice*)), Qt::DirectConnection);
        connect(this, SIGNAL(deviceGone(QString)), this, SLOT(onRemovedDevice(QString)),
                             Qt::DirectConnection);
        
        this->start();
        this->discover();
    
        connect(handle, SIGNAL(leave()), this, SLOT(exit()));
        connect(handle, SIGNAL(list()), this, SLOT(list()));
        connect(handle, SIGNAL(help()), this, SLOT(help()));
        connect(handle, SIGNAL(getTarget()), this, SLOT(getTarget()));
        connect(handle, SIGNAL(getStatus()), this, SLOT(getStatus()));
        connect(handle, SIGNAL(setLight(int)), this, SLOT(setLight(int)));
        connect(handle, SIGNAL(turnOn()), this, SLOT(turnOn()));
        connect(handle, SIGNAL(turnOff()), this, SLOT(turnOff()));
    
        handle->start();
    }

The destructor is simples and will have the stop command for the discovery.
::
    ControlPoint::~ControlPoint()
    {
        delete handle;
        this->stop();
    }

To handle when a device comes or leave the network we show simple messages for the user 
and store/delete in/from the list.

.. literalinclude:: example_code/ControlPoint/controlpoint.cpp
    :lines: 32-51

Before continuing let us see quickly how to download device's icons if you need them in your control point.

BrisaControlPointDevice class has a method called downloadIcons which request the download of all its icons. When all downloads
are finished BrisaControlPointDevice will emit a onReadyDownloadIcons(BrisaControlPointDevice*) signal. So basically all you need to do is the following:

Create a slot which you are going to use to do whatever you want with devices icons. I'm calling my slot iconsDownloadFinished, but you can put any name you want. Inside your Control Point header file:
::
    public slots:
        void iconsDownloadFinished(BrisaControlPointDevice*)

And inside your source file call BrisaControlPointDevice downloadIcons() method when you find a device. Also, connect onReadyDownloadIcons(BrisaControlPointDevice*) signal to the slot you created, like this:
::
    device->downloadIcons();
    connect(device, SIGNAL(onReadyDownloadIcons(BrisaControlPointDevice*)), 
            this, SLOT(iconsDownloadFinished(BrisaControlPointDevice*)))

All BrisaIcons objects inside your BrisaControlPointDevice will now have a QIcon object with the icon's object. To access BrisaIcons objects you can use device 
getIconList() method and then BrisaIcon getIcon() to retrieve QIcon object related to that BrisaIcon!

.. literalinclude:: example_code/ControlPoint/controlpoint.cpp
    :lines: 53-123

Each of the action call functions (turn on, turn off, getTarget, getStatus) need a slot to receive
the action call response. The call itself is done in a simple way directly from the BrisaControlPointService.

.. literalinclude:: example_code/ControlPoint/controlpoint.cpp
    :lines: 125-224

The way on how we get the commands(Thread) is not implemented yet, but the implementaion is very simple.
On the header file we create the QThread, note that the signals are passed to the ControlPoint 
to perform the actions
::
    class HandleCmds : public QThread
    {
        Q_OBJECT
        public:
            void run() {            
                QTextStream stream(stdin);
                do{
                    QString line;
                    QCoreApplication::processEvents();
                    std::cout << ">>> ";
                    line = stream.readLine();
                    if(line == "exit") {
                        emit leave();
                        running = false;
                    } else if(line == "list") {
                        emit list();
                    } else if(line == "help"){
                        emit help();
                    } else if(line == "get_target"){
                        emit getTarget();
                    } else if(line == "get_status"){
                        emit getStatus();
                    } else if(line == "turn on"){
                        emit turnOn();
                    } else if(line == "turn off"){
                        emit turnOff();
                    } else {
                        if (line.split(" ").size() == 2) {
                            if(line.split(" ")[0] == "set_light") {
                                emit setLight(line.split(" ")[1].toInt());
                            } else {
                                qDebug() << "Wrong usage, try 'help' to see the commands";
                            }
                        } else {
                            qDebug() << "Wrong usage, try 'help' to see the commands";
                        }
                    }
                } while(running);
            }
    
        private:
            void setRunningCmds(bool running) { this->running = running; }
            
            bool running;
    
        signals:
            void leave();
            void list();
            void help();
            void setLight(int i);
            void turnOn();
            void turnOff();
            void getTarget();
            void getStatus();
    };

We already connected it in the Control Point when we were creating the control point constructor 
::
    HandleCmds *handle = new HandleCmds();    

    connect(handle, SIGNAL(leave()), this, SLOT(exit()));
    connect(handle, SIGNAL(list()), this, SLOT(list()));
    connect(handle, SIGNAL(help()), this, SLOT(help()));
    connect(handle, SIGNAL(getTarget()), this, SLOT(getTarget()));
    connect(handle, SIGNAL(getStatus()), this, SLOT(getStatus()));
    connect(handle, SIGNAL(setLight(int)), this, SLOT(setLight(int)));
    connect(handle, SIGNAL(turnOn()), this, SLOT(turnOn()));
    connect(handle, SIGNAL(turnOff()), this, SLOT(turnOff()));

    handle->start();

So our control point is done. We only need our main now

.. literalinclude:: example_code/ControlPoint/main.cpp
    :lines: 1-11

And that's how we create a simple control point using Qt BRisa.

You can find the code in:
    https://garage.maemo.org/plugins/scmsvn/viewcvs.php/qt/trunk/qt-brisa/doc/docSource/example_code/ControlPoint/?root=brisa.
    Just download ControlPoint.zip file.
