#ifndef LIGHT_H
#define LIGHT_H

#include <QtGui/QWidget>
#include <QString>
#include <QIcon>
#include <QtCore>
#include <QCoreApplication>
#include <QtDebug>
#include <BrisaUpnp/BrisaDevice>
#include <BrisaUtils/BrisaLog>
#include <QSplashScreen>
#include "ui_light.h"
#include "switchPower.h"


#define DEVICE_TYPE              "urn:schemas-upnp-org:device:BinaryLight:1"
#define DEVICE_FRIENDLY_NAME     "Binary Light Device"
#define DEVICE_MANUFACTURER      "Brisa Team. Embedded Laboratory and INdT Brazil"
#define DEVICE_MANUFACTURER_URL  "https://garage.maemo.org/projects/brisa"
#define DEVICE_MODEL_DESCRIPTION "An UPnP Binary Light Device"
#define DEVICE_MODEL_NAME        "Binary Light Device"
#define DEVICE_MODEL_NUMBER      "1.0"
#define DEVICE_MODEL_URL         "https://garage.maemo.org/projects/brisa"
#define DEVICE_SERIAL_NUMBER     "1.0"

using namespace BrisaUpnp;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void statechanged(BrisaStateVariable *);

private:
    BrisaDevice binaryLight;
    BrisaStateVariable *status;
    BrisaStateVariable *target;
    
    //METHODS FOR UDN CREATION
    QString createUdn();
    int get1RandomNumber();
    int get2RandomNumber();
    int get3RandomNumber();
};

#endif // LIGHT_H
