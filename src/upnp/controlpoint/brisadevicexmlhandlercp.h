/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisadevicexmlhandlercp.cpp
 * Created:
 * Description: Definition of BrisaDeviceParserContext,BrisaDeviceXMLHandlerCP and
 * BrisaServiceFetcher  classes.
 * Authors: Name <email> @since 2009
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
 *
 * BRisa-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _BRISADEVICEXMLHANDLER_H
#define _BRISADEVICEXMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QXmlSimpleReader>
#include <QXmlStreamWriter>
#include <QXmlInputSource>
#include <QXmlAttributes>
#include <QMainWindow>
#include <QIODevice>
#include <QString>
#include <QtDebug>
#include <QtCore>
#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTemporaryFile>

#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisaglobal.h"

namespace BrisaUpnp {

class BrisaControlPointDevice;

/*!
 *  \enum BrisaUpnp::BrisaDeviceXMLHandlerCP::SaxParserState
 *
 *  \brief This enum specifies the devices attributes that are going to be set/get
 *
 *  \param Start  Beginning state in the parser.
 *  \param Root  Root tag in xml.
 *  \param SpecVersion  Tag to start editing spec version in device.
 *  \param SpecVersionMajor  Tag where the state is to edit the major spec version
 *  \param SpecVersionMinor  Tag where the state is to edit the major spec version
 *  \param UrlBase  Tag to edit urlBase.
 *  \param Device  Tag to signal the edit begin of device's attributes.
 *  \param DeviceType  Tag to edit device type.
 *  \param DeviceFriendlyName  Tag to edit deviceFriendlyName
 *  \param Manufacturer  Tag to edit Manufacturer's name.
 *  \param ManufacturerUrl  Tag to edit Web site for Manufacturer.
 *  \param ModelDescription  Tag to edit the long description for end user.
 *  \param ModelName  Tag to edit Model name.
 *  \param ModelNumber  Tag to edit Model number.
 *  \param ModelUrl  Tag to edit Web site for model.
 *  \param SerialNumber  Tag to edit Serial number.
 *  \param Udn  Tag to edit Unique Device Name.
 *  \param Upc  Tag to edit Universal Product Code.
 *  \param IconList  Tag to signal the start the beginning of the addition of icons.
 *  \param Icon  Tag to signal the start of icon's parameter edition.
 *  \param IconMimetype  Tag to edit context's icon's myme type.
 *  \param IconWidth  Tag to edit context's icon's width.
 *  \param IconHeight  Tag to edit context's icon's height.
 *  \param IconDepth  Tag to edit context's icon's depth.
 *  \param IconUrl  Tag to edit context's icon's url.
 *  \param PresentationUrl  Tag to edit URL to presentation for device.
 *  \param DeviceList  Tag to signal the embedded devices addition.
 *  \param ServiceList  Tag to signal services addition.
 *  \param Service  Tag to start context's service's attributes edition.
 *  \param ServiceType  Tag to edit the service's type.
 *  \param ServiceId  Tag to edit the service's id.
 *  \param ServiceType  Tag to edit the service's type.
 *  \param ServiceScpdUrl  Tag to edit service's scpd url.
 *  \param ServiceControlUrl  Tag to edit service's control url.
 *  \param ServiceEventSubUrl  Tag to edit service's eventsub url.
 *  \param Finished  Tag to signal the reading is done.
 *  \param Error  Tag to signal an error in the parser.
 *
 *  \sa setAttribute(xmlTags key, QString v), getAttribute(xmlTags key)
 */
typedef enum {
	Start,
	Root,
	SpecVersion,
	SpecVersionMajor,
	SpecVersionMinor,
	UrlBase,
	Device,
	DeviceType,
	DeviceFriendlyName,
	Manufacturer,
	ManufacturerUrl,
	ModelDescription,
	ModelName,
	ModelUrl,
	SerialNumber,
	Udn,
	Upc,
	IconList,
	Icon,
	IconMimetype,
	IconWidth,
	IconHeight,
	IconDepth,
	IconUrl,
	PresentationUrl,
	DeviceList,
	ServiceList,
	Service,
	ServiceType,
	ServiceId,
	ServiceScpdUrl,
	ServiceControlUrl,
	ServiceEventSubUrl,
	Finished,
	Error = -1
} SaxParserState;

/*!
 *  \internal
 *
 *  \class BrisaDeviceParserContext
 *
 *  Represents a parsing context, defined by a parent, a build target device, service and icon.
 */
class BRISA_UPNP_EXPORT BrisaDeviceParserContext {
public:

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::BrisaDeviceParserContext(BrisaDeviceParserContext *parent,
	 *                                                           BrisaControlPointDevice *target)
	 *  Constructor that receives the parser and the target that is going to be set.
	 */
	BrisaDeviceParserContext(BrisaDeviceParserContext *parent = 0,
			BrisaControlPointDevice *target = 0) :
		stateSkip(0), state(Root), parent(parent), device(target), service(0),
				icon(0) {
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::getIcon()
	 *  \return context's icon.
	 */
	inline BrisaIcon *getIcon(void) {
		return icon;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::getDevice()
	 *  \return context's device.
	 */
	inline BrisaControlPointDevice *getDevice(void) {
		return device;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::getService()
	 *  \return context's service.
	 */
	inline BrisaControlPointService *getService(void) {
		return service;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::setIcon(BrisaIcon *icon)
	 *  Sets context's icon to \a icon.
	 *  \param icon icon
	 */
	inline void setIcon(BrisaIcon *icon) {
		this->icon = icon;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::setDevice(BrisaControlPointDevice *device)
	 *  Sets context's device to \a device.
	 *  \param device device
	 */
	inline void setDevice(BrisaControlPointDevice *device) {
		this->device = device;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::setService(BrisaControlPointService *service)
	 *  Sets context's service to \a service.
	 *  \param service service
	 */
	inline void setService(BrisaControlPointService *service) {
		this->service = service;
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::hasParent()
	 *  \return true if context's parent different than zero.
	 */
	inline bool hasParent(void) {
		return (parent != 0);
	}

	/*!
	 *  \internal
	 *  \fn BrisaDeviceParserContext::getParent()
	 *  \return context's parent.
	 */
	inline BrisaDeviceParserContext *getParent(void) {
		return parent;
	}

	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::stateSkip
	 *  \brief incremented when a xml tag that isn't a recognized by UPnP architecture is find in xml.
	 */
	int stateSkip;

	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::state
	 *  \brief The actual state in the reading.
	 */
	SaxParserState state;

private:
	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::parent
	 *  \brief Same object, the parent of one context
	 */
	BrisaDeviceParserContext *parent;

	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::device
	 *  \brief BrisaControlPointDevice that is going to have it's attributes set.
	 */
	BrisaControlPointDevice *device;

	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::service
	 *  \brief Service that is going to be generated to be added by the device.
	 */
	BrisaControlPointService *service;

	/*!
	 *  \internal
	 *  \property BrisaDeviceParserContext::icon
	 *  \brief Icon that is going to be generated to be added by the device.
	 */
	BrisaIcon *icon;
};

/*!
 *  \class BrisaUpnp::BrisaDeviceXMLHandlerCP brisadevicexmlhandlercp.h BrisaUpnp/BrisaDeviceXMLHandlerCP
 *
 *  \brief BrisaDeviceXMLHandlerCP creates a device from a xml description file, with all it's
 *  attributes, it lets it ready to be used.
 */
class BRISA_UPNP_EXPORT BrisaDeviceXMLHandlerCP: public QXmlDefaultHandler {
public:

	/*!
	 *  Method that initializes device attributes from a temporary file.
	 *  \param device device
	 *  \param tmp temporary file
	 */
	void parseDevice(BrisaControlPointDevice *device, QTemporaryFile *tmp);

protected:

	/*!
	 *  Method inherited from QXmlDefaultHandler it's called in every beginning tag, depending on tag
	 *  the context state passes to a different state so that it can process separately. It's
	 *  important to say that in each state it performs a different action.
	 */
	bool startElement(const QString &namespaceURI, const QString &localName,
			const QString &qName, const QXmlAttributes &attributes);

	/*!
	 *  Method that is called in the tag end, this method add the attribute to the device so that
	 *  attributes can be initialized in device. It's important to say that in each state it performs a
	 *  different action.
	 */
	bool endElement(const QString &namespaceURI, const QString &localName,
			const QString &qName);

	/*!
	 *  Method that set properly the attribute value to \str value that it is the content between the
	 *  beginning tag and the finish one. It's important to say that in each state it performs a
	 *  different action.
	 */
	bool characters(const QString &str);

private:

	/*!
	 *  \property writer
	 *  \brief Object that write changes to a xml file.
	 */
	QXmlStreamWriter *writer;

	/*!
	 *  \property reader
	 *  \brief Object that do the xml parse.
	 */
	QXmlSimpleReader *reader;

	/*!
	 *  \property input
	 *  \brief input source that reader is going to use in the parser.
	 */
	QXmlInputSource *input;

	/*!
	 *  \property context
	 *  \brief Used to see what reading is going to be done and set device's attributes.
	 */
	BrisaDeviceParserContext *context;
};

/*!
 *  \internal
 *
 *  \class BrisaServiceFetcher
 *
 *  \brief Class that generates the service by downloading the xml description file, reading,
 *  and initializing services attributes.
 */
class BRISA_UPNP_EXPORT BrisaServiceFetcher: public QObject {
Q_OBJECT

public:
	/*!
	 *  \internal
	 *  \fn BrisaServiceFetcher::BrisaServiceFetcher(BrisaControlPointService *service, QString location,
	 *                                               QObject *parent)
	 *  \brief BrisaServiceFetcher constructor, receives the \a service that is going to be set, the
	 *  \a location to download xml, and a QObject as parent.
	 */
	BrisaServiceFetcher(BrisaControlPointService *service, QString location,
			QObject *parent = 0) :
		QObject(parent), location(location), service(service) {
		eventLoop = new QEventLoop();
		downloader = new QNetworkAccessManager();

		connect(this, SIGNAL(fetchFinished()), eventLoop, SLOT(quit()));
		connect(downloader, SIGNAL(finished(QNetworkReply*)), this,
				SLOT(downloadFinished(QNetworkReply*)));
		service = NULL;
		error = false;
	}

	/*!
	 *  \internal
	 *  \fn BrisaServiceFetcher::~BrisaServiceFetcher()
	 *  \brief Destructor.
	 */
	~BrisaServiceFetcher() {
		delete downloader;
		delete eventLoop;
	}

	/*!
	 *  \internal
	 *  \fn BrisaServiceFetcher::fetch()
	 *  \brief Start the xml download and initializes the event loop
	 *  \return true if any error occurred
	 */
	bool fetch(void) {
		downloader->get(QNetworkRequest(location));
		eventLoop->exec();

		return error;
	}

private:
	/*!
	 *  \internal
	 *  \property BrisaServiceFetcher::eventLoop
	 *  \brief Guarantees that flow of execution will only continue after the xml download is finished.
	 */
	QEventLoop *eventLoop;

	/*!
	 *  \internal
	 *  \property BrisaServiceFetcher::downloader
	 *  \brief Do the xml download from network.
	 */
	QNetworkAccessManager *downloader;

	/*!
	 *  \internal
	 *  \property BrisaServiceFetcher::location
	 *  \brief Location to download the xml file.
	 */
	QString location;

	/*!
	 *  \internal
	 *  \property BrisaServiceFetcher::service
	 *  \brief service that is going to have the parameters set.
	 */
	BrisaControlPointService *service;

	/*!
	 *  \internal
	 *  \property BrisaServiceFetcher::error
	 *  \brief Flag to detect a error in service fetch.
	 */
	bool error;

signals:
	/*!
	 *  \internal
	 *  \fn BrisaServiceFetcher::fetchFinished()
	 *  \brief Signal emitted when the service fetch is finished.
	 */
	void fetchFinished(void);

private slots:
	/*!
	 *  \internal
	 *  \fn BrisaServiceFetcher::downloadFinished(QNetworkReply *reply)
	 *  \brief When download is finished, this slop write the download content into a temporary file
	 *  and tells the service parameter to be generate from it that means it initializes the service
	 *  too.
	 *  \param reply \a empty
	 */
	void downloadFinished(QNetworkReply *reply) {
		QTemporaryFile *scpd = new QTemporaryFile();

		if (!scpd->open()) {
			qDebug() << "Failed to open scpd file for writing";
			error = true;
			emit
			fetchFinished();
			return;
		}

		scpd->write(reply->readAll());
		scpd->seek(0);
		service->parseFromXml(scpd);

		scpd->remove();
		delete scpd;
		emit fetchFinished();
	}

};

}

#endif /* _BRISADEVICEXMLHANDLER_H */

