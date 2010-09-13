:mod:`ssdpclient` --- SSDP Client implementation
===========================================

.. module: ssdpclient
    :synopsis: SSDP stack implementantion for UPnP control points.

Qt BRisa provides a BrisaSSDPClient class which can be used by control points for receiving notification messages

BrisaSSDPClient class
-----------------
Implementation of a SSDP Client.

Attributes
^^^^^^^^^^^
The attribute of the BrisaSSDPClient class are:

* running - Boolean variable that holds server running state
* SSDP_ADDR - SSDP address
* SSDP_PORT - SSDP port
* S_SSDP_PORT - QString port, used in bind
* udpListener - Socket to join multicast group and listen to msearch notification

Methods and Slots
^^^^^^^^

.. function:: isRunning()

    Returns True if the BrisaSSDPClient is running, False otherwise.

.. function:: start()

    Connects to the MultiCast group and starts the client.

.. function:: stop()

    Stops the client.

.. function:: datagramReceived()

    Receives UDP datagrams from a QUdpSocket.

.. function:: notifyReceived(QHttpRequestHeader *datagram)

    Parses the UDP datagram received from "datagramReceived()".

