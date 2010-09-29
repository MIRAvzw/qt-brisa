:mod:`service` --- BrisaService class
==============================================

.. module: service
    :synopsis: Service related functions and example

BrisaService class allows you to create UPnP services in an easy way. You only need to create your actions and add them to the BrisaService object. After that your service can be linked to any device you want.

Important Methods
^^^^^^^^^^^^
.. index:: BrisaService, addAction, getStateVariableList

BrisaService constructor. Receives service information.
::
	BrisaService(const QString &serviceType,
		const QString &serviceId = "",
		const QString &scpdUrl = "",
		const QString &controlUrl = "",
		const QString &eventSubUrl = "",
		const QString &host = "",
		QObject *parent = 0);

Method to add an action to the service.
::
	void addAction(BrisaAction *action);

This method returns the service's state variables list.
::
	const QList<BrisaStateVariable *> getStateVariableList();


Implementing a simple service.
-------------------------------

This section will show an example on how to create a simple service.

First thing you need to do is to write your scpd.xml file, like this one:

.. literalinclude:: ../../example_code/myservice-scpd.xml

Now create your service class and make it child of BrisaService class. You will need
to specify the service name, the service type and the scpd.xml file. Also you'll need to implement
your service actions. 

First, let's define the service informations we need
::
        #define SERVICE_TYPE "urn:schemas-upnp-org:service:MyService:1"
        #define SERVICE_ID "MyService"

After that, let's include the BrisaService and the BrisaAction libraries to create our own service and actions
::
       #include <BrisaAction>
       #include <BrisaService>
        
        using namespace BrisaUpnp;  

To create your actions you just need to implement a method with a specific signature for each BrisaAction you want and they will be automatically bind to the service by the framework. You can create your actions as slots or as methods. Slots are automatically bound to the service but if you define your actions as methods you'll need to mark them as Q_INVOKABLE as in the following example. Note that actions' names *must* be in lowercase.
::
        class MyService : public BrisaService
        {
            public:
                MyService() : BrisaService(SERVICE_TYPE,
                                           SERVICE_ID) { }

                Q_INVOKABLE
                BrisaOutArgument* actionname1(BrisaInArgument* const inArguments,
                                              BrisaAction* const action)
                {
                        Q_UNUSED(action);
                        BrisaOutArgument *outArgs = new BrisaOutArgument();
                        QString inArg = inArguments->value("ExampleInText");
                        outArgs->insert("TextOut", inArg + "Out!!");
                        return outArgs;
                }

            private:
                Q_INVOKABLE
                BrisaOutArgument* actionname2(BrisaInArgument* const inArguments,
                                              BrisaAction* const action)
                {
                       Q_UNUSED(action);
                       BrisaOutArgument *outArgs = new BrisaOutArgument();
                       QString inArg = inArguments->value("ExampleInText");
                       outArgs->insert("TextOut", inArg + "Out!!");
                       return outArgs;
                }
            private slots:
                BrisaOutArgument* actionname3(BrisaInArgument* const inArguments,
                                              BrisaAction* const action)
                {
                       Q_UNUSED(action);
                       BrisaOutArgument *outArgs = new BrisaOutArgument();
                       QString inArg = inArguments->value("ExampleInText");
                       outArgs->insert("TextOut", inArg + "Out!!");
                       return outArgs;
                }
			
        };

Now that we have our service class we can create a service from it in the following way
::
    MyService *myService = new MyService();
    myService->setDescriptionFile("myservice-scpd.xml");

When we add this service to some device and call device's start method all attributes of the service are going to be initialized.
