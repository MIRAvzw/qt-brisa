:mod:`ssdpserver` --- SSDP Server implementation
===========================================

.. module: ssdpserver
    :synopsis: SSDP stack implementation for UPnP devices.

Brisa Qt provides SSDP server (Simple Service Discovery
Protocol) class which can be used on the device's side for annoucing the device, its embedded devices and all services..

BrisaSSDPServer class
-----------------
Implementation of a SSDP Server.

Attributes
^^^^^^^^^^^
The attribute of the BrisaSSDPServer class are:

* running - Bool to tell if server is running or not
* SSDP_ADDR - SSDP address
* SSDP_PORT - SSDP port
* S_SSDP_PORT - QString port, used in bind
* udpSocket - Udp Socket to join multicast group

Methods and Slots
^^^^^^^^

.. function:: isRunning()

    Returns True if the BrisaSSDPServer is running, False otherwise.

.. function:: start()

    Call this method to join the multicast group and start listening for UPnP msearch responses.

.. function:: stop()

    Sends bye bye notifications and stops the BrisaSSDPServer.

.. function:: doNotify(const QString &usn, const QString &location, const QString &st,
                        const QString &server, const QString &cacheControl)

    Sends a UPnP notify alive message to the multicast group with the given information.

.. function:: doByeBye(const QString &usn, const QString &st)

    Sends a UPnP notify byebye message to the multicast group with the given information.

.. function:: datagramReceived()

    This slot is called when the readyRead() signal is emmited by the QUdpSocket listening to incoming messages.

.. function:: msearchReceived(QHttpRequestHeader *datagram, QHostAddress *senderIp,
                              quint16 senderPort)

    Emits msearchRequestReceived if the incoming message is a valid msearch.

.. function:: respondMSearch(const QString &senderIp, quint16 senderPort,
                             const QString &cacheControl, const QString &date,
                             const QString &location, const QString &server,
                             const QString &st, const QString &usn)

    Connect this slot to a proper signal to get synchronous response for msearch requests.

