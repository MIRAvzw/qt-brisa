:mod:`device` --- BrisaDevice class
============================================

.. module: device
    :synopsis: Device related functions and example


BrisaDevice class provides an easy and fast way to create UPnP devices. All you need to do is create a new BrisaDevice object and call its start() method to join the network and be visible to available control points.

Important Methods
^^^^^^^^^^
.. index:: addEmbeddedDevice

BrisaDevice constructor which should receive all device information on its arguments.
::
    void addEmbeddedDevice(const QString &deviceType = "",
			const QString &friendlyName = "",
			const QString &manufacturer = "",
			const QString &manufacturerURL = "",
			const QString &modelDescription = "",
			const QString &modelName = "",
			const QString &modelNumber = "",
			const QString &modelURL = "",
			const QString &serialNumber = "",
			const QString &UDN = "",
			const QString &UPC = "",
			const QString &presentationURL = "");

|


Call this function passing the BrisaDevice to be embedded and the embedded device will be announced when the root device joins the network.
::
    void addEmbeddedDevice(BrisaDevice *newEmbeddedDevice);

.. index:: addService, start (BrisaDevice method), stop (BrisaDevice method)
    
Method used to add a service to the device, you just need to pass a BrisaService object as the argument. The service will be automatically added to the device and the appropriate webserver urls paths will be created.
::
	void addService(BrisaService *serv)

Call this method to join the network and start the device.
::
	void start()

Stops the device and leaves the network sending ssdp messages for any embedded devices.
::
    void stop()




Creating a generic device
--------------------------

Here is a simple explanation on how creating a device and starting it. These are only basic steps to follow, you can check a more practical example at *Code Examples* section.

BrisaDevice constructor receives all information about a device, so it's a good idea to define the constants first.
::
	#define DEVICE_TYPE  "urn:schemas-upnp-org:device:MyDevice:1"
	#define DEVICE_FRIENDLY_NAME  "My Device Name"
	#define DEVICE_MANUFACTURER  "Brisa Team. Embedded Laboratory and INdT Brazil"
	#define DEVICE_MANUFACTURER_URL "https://garage.maemo.org/projects/brisa"
	#define DEVICE_MODEL_DESCRIPTION "An example device"
	#define DEVICE_MODEL_NAME  "My device model"
	#define DEVICE_MODEL_NUMBER "1.0"
	#define DEVICE_MODEL_URL "https://garage.maemo.org/projects/brisa"
	#define DEVICE_SERIAL_NUMBER  "1.0"

Then we can call the constructor passing the device informations we just defined
::
	BrisaDevice myDevice(DEVICE_TYPE,
                            DEVICE_FRIENDLY_NAME,
                            DEVICE_MANUFACTURER,
                            DEVICE_MANUFACTURER_URL,
                            DEVICE_MODEL_DESCRIPTION,
                            DEVICE_MODEL_NAME,
                            DEVICE_MODEL_NUMBER,
                            DEVICE_MODEL_URL,
                            DEVICE_SERIAL_NUMBER,
                            getCompleteUuid());
	// The getcompleteuuid() function returns a valid device udn automatically

We can now add our services to the device we just created (creation of services will be explained on the next section)
::
	myDevice.addService(myService);

And finally we start our device
::
	myDevice.start();

We're done! Now you know the basics steps of creating a device.
