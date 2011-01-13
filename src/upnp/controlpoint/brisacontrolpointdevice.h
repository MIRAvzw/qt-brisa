/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisacontrolpointdevice.h
 * Created:
 * Description: Implementation of BrisaControlPoint class.
 * Authors:                                                 @since 2009
 *           Jeysibel de Sousa Dantas <jeysibel@gmail.com>  @since 06/04/2010
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

#ifndef _BRISACONTROLPOINTDEVICE_H
#define _BRISACONTROLPOINTDEVICE_H

#include <QString>
#include <QList>
#include <QXmlDefaultHandler>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QtDebug>
#include <QObject>

#include "brisaicon.h"
#include "brisacontrolpointservice.h"
#include "brisadevicexmlhandlercp.h"
#include "brisaglobal.h"

namespace Brisa {

/*!
 *  \class Brisa::BrisaControlPointDevice brisacontrolpointdevice.h BrisaUpnp/BrisaControlPointDevice
 *
 *  \brief Class that implements the devices that control point part is going to handle.
 */
class BRISA_UPNP_EXPORT BrisaControlPointDevice: public QObject {
Q_OBJECT

public:

    /*!
     *  Constructor to BrisaControlPointDevice, when it makes use of this constructor the device's
     *  attributes should be set.
     *  \param parent \a empty
     */
    BrisaControlPointDevice(QObject *parent = 0);

    /*!
     *  Constructor for BrisaControlPointDevice that receives a xml file containing the device
     *  description, so that the device's attributes can be initialized.
     *  \param xml \a empty
     *  \param url \a empty
     *  \param parent \a empty
     */
    BrisaControlPointDevice(QTemporaryFile *xml, QUrl *url,
                    QObject *parent = 0);

    /*!
     *  Constructor for BrisaControlPointDevice that receives another object of the same type and
     *  copy it's attributes.
     */
    BrisaControlPointDevice(BrisaControlPointDevice &dev, QObject *parent = 0);

    /*!
     *  Constructor where all device's attributes are passed as parameter.
     *  \param udn \a empty
     *  \param deviceType \a empty
     *  \param friendlyName \a empty
     *  \param manufacturer \a empty
     *  \param manufacturerURL \a empty
     *  \param modelDescription \a empty
     *  \param modelName \a empty
     *  \param modelNumber \a empty
     *  \param modelURL \a empty
     *  \param serialNumber \a empty
     *  \param upc \a empty
     *  \param presentationURL \a empty
     *  \param parent \a empty
     */
    BrisaControlPointDevice(QString udn,
                            QString deviceType = "",
                            QString friendlyName = "",
                            QString manufacturer = "",
                            QString manufacturerURL = "",
                            QString modelDescription = "",
                            QString modelName = "",
                            QString modelNumber = "",
                            QString modelURL = "",
                            QString serialNumber = "",
                            QString UPC = "",
                            QString presentationURL = "",
                            QObject *parent = 0);

    /*!
     *    Destructor
     */
    virtual ~BrisaControlPointDevice();

    /*!
     *  \enum Brisa::BrisaControlPointDevice::xmlTags
     *  \brief This enum specifies the devices attributes that are going to be set/get
     *  \param Udn  Unique Device Name. Universally-unique identifier for the device.
     *  \param Major  Major version of the UPnP Device Architecture.
     *  \param Minor  Minor version of the UPnP Device Architecture.
     *  \param UrlBase  Defines the base URL. Used to construct fully-qualified URLs.
     *  \param DeviceType  UPnP device type. Single URI.
     *  \param FriendlyName  Short description for end user.
     *  \param Manufacturer  Manufacturer's name.
     *  \param ManufacturerUrl  Web site for Manufacturer.
     *  \param ModelDescription  Long description for end user.
     *  \param ModelName  Model name. Should be less then 32 characters.
     *  \param ModelNumber  Model number. Should be less then 32 characters.
     *  \param ModelUrl  Web site for model.
     *  \param SerialNumber  Serial number. Should be less then 64 characters
     *  \param Upc  Universal Product Code. 12-digit, all-numeric code that identifies the consumer package.
     *  \param PresentationUrl  URL to presentation for device.
     *  \param FileAddress  Device's file address.
     *  \sa setAttribute(xmlTags key, QString v), getAttribute(xmlTags key)
     */
    typedef enum {
        Udn,
        udn,
        Major,
        major,
        Minor,
        minor,
        UrlBase,
        urlBase,
        DeviceType,
        deviceType,
        FriendlyName,
        friendlyName,
        Manufacturer,
        manufacturer,
        ManufacturerUrl,
        manufacturerUrl,
        ModelDescription,
        modelDescription,
        ModelName,
        modelName,
        ModelNumber,
        modelNumber,
        ModelUrl,
        modelUrl,
        SerialNumber,
        serialNumber,
        Upc,
        upc,
        PresentationUrl,
        presentationUrl,
        FileAddress,
        fileAddress
    } xmlTags;

    /*!
     *  Gets an attribute by key
     *  \param key attribute key
     *  \return attribute value
     */
    QString getAttribute(xmlTags key);

    /*!
     *  Set a device's attribute
     *  \param key attribute key
     *  \param value new attribute value
     */
    void setAttribute(xmlTags key, QString value);

    /*!
     *  Add an icon to device's icon list.
     *  \param icon icon to add
     */
    void addIcon(BrisaIcon *icon);

    /*!
     *  Add service to device's service list.
     *  \param service service to add
     */
    void addService(BrisaControlPointService *service);

    /*!
     *  Add a device to device's embedded device list.
     *  \param device device to add
     */
    void addDevice(BrisaControlPointDevice *device);

    /*!
     *  Gets device's icon list
     *  \return icon list
     */
    QList<BrisaIcon*> getIconList();

    /*!
     *  Gets device's service list
     *  \return service list
     */
    QList<BrisaControlPointService*> &getServiceList();

    /*!
     *  Gets device's embedded device list
     *  \return embedded list
     */
    QList<BrisaControlPointDevice*> getEmbeddedDeviceList();

    /*!
     *  Gets a service by id.
     *  \param serviceId service id
     *  \return service with corresponding id
     */
    BrisaControlPointService *getServiceById(QString serviceId);

    /*!
     *  Check the device's service list and return the service that has the passed \serviceType
     *  \param serviceType type of the service
     *  \return service with corresponding type
     */
    BrisaControlPointService *getServiceByType(QString serviceType);

    /*!
     *  Clear device's attributes.
     */
    void clear();

    /*!
     *  Send icons download request to QNetworkAccessManager. After download is finished
     *  the downloaded icons images are added to the BrisaIcons objects in device icons list and a
     *  onReadyDownloadIcons(BrisaControlPointDevice) signal is emitted by downloader method.
     */
    void downloadIcons();

signals:
    void onReadyDownloadIcons(BrisaControlPointDevice*);

public slots:
    void downloadFinished();

private:
    /*!
     *  \property iconList
     *  \brief Device's icon list.
     */
    QList<BrisaIcon*> iconList;

    /*!
     *  \property serviceList
     *  \brief Device's service list.
     */
    QList<BrisaControlPointService*> serviceList;

    /*!
     *  \property embeddedDeviceList
     *  \brief Device's embedded device list.
     */
    QList<BrisaControlPointDevice*> embeddedDeviceList;

    int downloaded;

    QString _major;
    QString _minor;
    QString _urlBase;
    QString _deviceType;
    QString _friendlyName;
    QString _manufacturer;
    QString _manufacturerUrl;
    QString _modelDescription;
    QString _modelName;
    QString _modelNumber;
    QString _modelUrl;
    QString _serialNumber;
    QString _udn;
    QString _upc;
    QString _presentationUrl;
    QString _fileAddress;
};

}

#endif /* _BRISACONTROLPOINTDEVICE_H */

