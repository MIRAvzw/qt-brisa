:mod:`webserver` --- Webserver facilities
==========================================

.. module: webserver
    :synopsis: Using Brisa to create WebServers

.. index:: webserver

Creating a simple Web Service using Qt BRisa
--------------------------------------------------

BRisa framework can be used to help you create your own web service. This section will demonstrate how to do this by showing the basics steps to create a simple web service. Although it is a simple web service, the following example covers the basics about using BRisa for this purpose.

We are going to use the following classes from the BrisaCore module:

	* BrisaWebServer
	* BrisaWebServiceProvider
	* BrisaWebService

BrisaWebServer , BrisaWebServiceProvider and BrisaWebService classes are implemented using `libqxt <http://www.libqxt.org/>`_, which has also other uses.

Let us begin by starting a Web Server creating an instance of BrisaWebServer, passing an IP address and a port number (you can use BrisaCore network functions to obtain these)
::
	BrisaWebServer *webserver = new BrisaWebserver(QHostAddress(ipAddress), port);

After that we need something to manage our services, thats where the BrisaWebServiceProvider comes in, we build it passing the BrisaWebServer we have just created. 
::
	BrisaWebServiceProvider *webserviceManager = new BrisaWebServiceProvider(webserver, this);

And then we call the "addService" method from BrisaWebService to add the *webserviceManager* to the root of the *webserver*, passing the desired url path. A BrisaWebServiceProvider itself is a webservice. It just doesn't emits the signals we want. 
::
    
	webserver->addService("hello", webserviceManager);

Now we can create the webservice (or webservices) passing our *webserver* to tie everything up.
::
	 BrisaWebService *hello = new BrisaWebService(webserver, this);

And after that we call the "addService" method from the *webserviceManager* object we created, passing the url path we want for our webservice. So our service will be in the path "IP:PORT/hello/world".
::
   
    webserviceManager->addService("world", hello);

When a request arrives at our webservice two signals are emmited:
::
    void genericRequestReceived(const QString &method,
                                const QMultiHash<QString, QString> &headers,
                                const QByteArray &requestContent,
                                int sessionId,
                                int requestId);
::
    
    void genericRequestReceived(BrisaWebService *service,
                                QMultiHash<QString, QString>,
                                QString requestContent);

So, simply connect one (or both) of the signals to a slot and treat the request the way you want to. If you want to answer the request, simply call one of the "respond()" methods from BrisaWebService.
