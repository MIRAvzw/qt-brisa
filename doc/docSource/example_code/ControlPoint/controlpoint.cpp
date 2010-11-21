#include "controlpoint.h"

ControlPoint::ControlPoint() : BrisaControlPoint()
{
    this->selected = NULL;
    handle = new HandleCmds();

    connect(this, SIGNAL(deviceFound(BrisaControlPointDevice*)), this, SLOT(onNewDevice(BrisaControlPointDevice*)), Qt::DirectConnection);
    connect(this, SIGNAL(deviceGone(QString)), this, SLOT(onRemovedDevice(QString)), Qt::DirectConnection);
    
    this->start();
    this->discover();

    connect(handle, SIGNAL(leave()), this, SLOT(exit()));
    connect(handle, SIGNAL(list()), this, SLOT(list()));
    connect(handle, SIGNAL(help()), this, SLOT(help()));
    connect(handle, SIGNAL(getTarget()), this, SLOT(getTarget()));
    connect(handle, SIGNAL(getStatus()), this, SLOT(getStatus()));
    connect(handle, SIGNAL(setLight(int)), this, SLOT(setLight(int)));
    connect(handle, SIGNAL(turnOn()), this, SLOT(turnOn()));
    connect(handle, SIGNAL(turnOff()), this, SLOT(turnOff()));

    handle->start();
}

ControlPoint::~ControlPoint()
{
    delete handle;
    this->stop();
}

void ControlPoint::onNewDevice(BrisaControlPointDevice *device)
{
    foreach(BrisaControlPointDevice *deviceInside, devices) {
        if(deviceInside->getAttribute(BrisaControlPointDevice::Udn)
            == device->getAttribute(BrisaControlPointDevice::Udn))
            return;
    }
    devices.append(device);
    device->downloadIcons();
    qDebug() << "Got new device " << device->getAttribute(BrisaControlPointDevice::Udn);
    qDebug() << "Type 'list' to see the whole list";    
}

void ControlPoint::onRemovedDevice(QString desc)
{
    foreach(BrisaControlPointDevice *dev, devices) {
        if(dev->getAttribute(BrisaControlPointDevice::Udn) == desc)
            devices.removeAll(dev);
            qDebug() << "Device is gone: " << desc;
    }
}

void ControlPoint::help() 
{
    qDebug() << "Available commands:";
    qDebug() << "exit";
    qDebug() << "help";
    qDebug() << "set_light <dev number>";
    qDebug() << "get_status";
    qDebug() << "get_target";
    qDebug() << "turn <on/off>";
    qDebug() << "stop";
    qDebug() << "list";
}

void ControlPoint::exit()
{
    handle->wait();
    handle->exit();
    QCoreApplication::exit();
}

void ControlPoint::list()
{
    int count = 0;
    foreach(BrisaControlPointDevice *dev, this->devices)
    {
        qDebug() << "Device no: " << count;
        qDebug() << "UDN: " << dev->getAttribute(BrisaControlPointDevice::Udn);
        qDebug() << "Name: " << dev->getAttribute(BrisaControlPointDevice::ModelName);
        qDebug() << "Device Type: " << dev->getAttribute(BrisaControlPointDevice::DeviceType);
        qDebug() << "Services: " << this->listServices(dev);
        qDebug() << "Embedded Devices: " << this->listEmbeddedDevices(dev);
        qDebug() << "";
        count++;  
    }
}

QString ControlPoint::listServices(BrisaControlPointDevice *device)
{
    QString services = "";
    QString separator = "";
    foreach(BrisaControlPointService *service, device->getServiceList()) {
        services += separator + service->getAttribute(BrisaControlPointService::ServiceType);
        separator = ", ";
    }
    return "[" + services + "]";
}

QString ControlPoint::listEmbeddedDevices(BrisaControlPointDevice *device)
{
    QString embeddedDevices = "";
    QString separator = "";
    foreach(BrisaControlPointDevice *embedded, device->getEmbeddedDeviceList()) {
        embeddedDevices += separator + embedded->getAttribute(BrisaControlPointDevice::DeviceType);
        separator = ", ";
    }
    return "[" + embeddedDevices + "]";
}

void ControlPoint::setLight(int index)
{
    if(this->devices.size() <= index) {
        qDebug() << "Binary Light Number not found. Please run list and check again.";
        return;
    }
    if(this->devices[index]->getAttribute(BrisaControlPointDevice::DeviceType)
        != BINARY_LIGHT_TYPE) {
        qDebug() << "Please, choose a Binary Light device";
        return;
    }    
    this->selected = this->devices[index];
}

void ControlPoint::getTarget()
{
    if(this->selected == NULL) {
        qDebug() << "Binary Light Device not select, please run 'set_light <dev_number>'";
        return;
    }
    QMap<QString, QString> param;
    BrisaControlPointService *service = this->selected->getServiceByType(SERVICE_SWITCH_POWER);
    connect(service, SIGNAL(requestFinished(BrisaOutArgument, QString)), this,
            SLOT(getTargetResponse(BrisaOutArgument, QString)));
    connect(service, SIGNAL(requestError(QString, QString)), this,
            SLOT(requestError(QString,QString)));
    service->call("GetTarget", param);
}

void ControlPoint::getTargetResponse(QString response, QString method)
{
    if(method == "GetTarget") {
        if(response == QString("0")) {
            qDebug() << "Binary Light target is off";
        } else if(response == QString("0")){
            qDebug() << "Binary Light target is on";
        } else {
            qDebug() << response;
        }       
    }
}

void ControlPoint::getStatus()
{
    if(this->selected == NULL) {
        qDebug() << "Binary Light Device not select, please run 'set_light <dev_number>'";
        return;
    }
    QMap<QString, QString> param;
    BrisaControlPointService *service = this->selected->getServiceByType(SERVICE_SWITCH_POWER);
    connect(service, SIGNAL(requestFinished(BrisaOutArgument, QString)), this,
            SLOT(getStatusResponse(BrisaOutArgument, QString)));
    connect(service, SIGNAL(requestError(QString, QString)), this,
            SLOT(requestError(QString,QString)));
    service->call("GetStatus", param);
}

void ControlPoint::getStatusResponse(BrisaOutArgument response, QString method)
{
    if(method == "GetStatus") {
        if(response == QString("0")) {
            qDebug() << "Binary Light status is off";
        } else {
            qDebug() << "Binary Light status is on";
        }        
    }
}

void ControlPoint::turnOn()
{
    if(this->selected == NULL) {
        qDebug() << "Binary Light Device not select, please run 'set_light <dev_number>'";
        return;
    }
    QMap<QString, QString> param;
    BrisaControlPointService *service = this->selected->getServiceByType(SERVICE_SWITCH_POWER);
    connect(service, SIGNAL(requestFinished(BrisaOutArgument, QString)), this,
            SLOT(setTargetResponse(BrisaOutArgument, QString)));
    connect(service, SIGNAL(requestError(QString, QString)), this,
            SLOT(requestError(QString,QString)));
    param["NewTargetValue"] = "1";
    service->call("SetTarget", param);
}

void ControlPoint::turnOff()
{
    if(this->selected == NULL) {
        qDebug() << "Binary Light Device not select, please run 'set_light <dev_number>'";
        return;
    }
    QMap<QString, QString> param;
    BrisaControlPointService *service = this->selected->getServiceByType(SERVICE_SWITCH_POWER);
    connect(service, SIGNAL(requestFinished(BrisaOutArgument, QString)), this,
            SLOT(setTargetResponse(BrisaOutArgument, QString)));
    connect(service, SIGNAL(requestError(QString, QString)), this,
            SLOT(requestError(QString,QString)));
    param["NewTargetValue"] = "0";
    service->call("SetTarget", param);
}

void ControlPoint::setTargetResponse(QString response, QString method)
{
    if(method == "SetTarget") {
        if(response == QString("")) 
            qDebug() << "Turning Binary Light to selected status";
        else
            qDebug() << response;
    }
}

void ControlPoint::requestError(QString errorMessage, QString methodName)
{
    QDebug() << errorMessage + " when calling " + methodName;
}
