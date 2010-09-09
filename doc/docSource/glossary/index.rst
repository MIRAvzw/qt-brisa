.. _glossary-index:

##########
 Glossary
##########

This is a basic glossary defining the most common words that will appear in this documentation. It is recommend reading it first.

.. glossary::

	BRisa Project
		BRisa is a project focused on the development of UPnP technologies. It provides an API to building UPnP devices,
		services and control points. BRisa project is released in MIT License (Python version) and in LGPL License (Qt version).

	Qt BRisa
		Brisa project version developed at `Laboratory of Embedded Systems and Pervasive Computing <http://embedded.ufcg.edu.br>`_,
		financed by `INdT <http://www.indt.org.br>`_. UPnP framework for Qt.

	UPnP
		Short for Universal Plug and Play, a protocol defined by the UPnP Forum. The UPnP architecture offers pervasive peer-to-peer
		network connectivity of PCs of all form, intelligent appliances, and wireless devices. The UPnP architecture is a
		distributed, open networking architecture that leverages TCP/IP and the Web to enable seamless proximity networking	in addition
		to control and data transfer among networked devices in the home, office, and everywhere in between. Documents can be found
		at `http://www.upnp.org <http://www.upnp.org>`_.

	device
		For our purposes, when referring to a device, we will be referring to a UPnP device. This is one of the key concepts of the
		`UPnP Architecture <http://upnp.org/specs/arch/UPnP-arch-DeviceArchitecture-v1.0.pdf>`_ and it's used to make reference to
		some machine or gadget in the network capable of providing services and advertising its presence.

	service
		For our purposes, a service should be considered an UPnP service, in other words, it is a logical functional unit capable of
		exposing actions and modeling a device state through the use of state variables. For example, a Door device could have a
		service called ControlDoor which would expose Door state (Open or Closed) and UPnP actions responsible for opening and closing
		the Door.

	control point
		An entity of the UPnP network capable of controlling devices by retrieving device and services descriptions, sending actions
		to services, etc.
