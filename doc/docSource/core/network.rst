:mod:`network` --- Network facilities
======================================

.. module: network
    :synposis: Provides network related functions, such as getIp(interface) and getPort().

.. index:: network

Qt BRisa has some functions which can simplify networking related tasks.

.. function:: getValidIP()
You can use getValidIP function to retrieve an valid IP on any active network interface (eth0, wlan0 wlan1). The following example demonstrates how easy it is to use getValidIP function
::

    #include <BrisaNetwork>

    QString ip = getValidIP();

    It will return a QString containing a valid IP


.. function:: getPort()
You can get a random port between the specified range of UpnP protocol using the getPort function.
It will return a port number greater than 49152 and smaller than 65535 that is currently available 
::

    #include <BrisaNetwork>

    quint16 port = getPort();

This will return a quint16 containing a port number.

