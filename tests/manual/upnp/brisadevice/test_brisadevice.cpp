#include <QtCore>
#include <QCoreApplication>
#include <QtDebug>
#include <QList>
#include <BrisaUpnp/BrisaDevice>
#include <QDebug>

using namespace BrisaUpnp;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
//CREATING DEVICE WITH HAND ATTRIBUTES
    BrisaDevice Dev1("type1", "BrisaDevice", "Embedded", "Embedded.ufcg.edu.br", "model1", "Brisa",
                   "187", "Brisa.com", "123456", "uuid:udn", "upcBrisa", "Brisa.Presentation.com");
    Dev1.addIcon("mimetype1", "url1", "width1", "height1", "depth1");
    Dev1.addIcon("mimetype1", "url2", "width2", "height2", "depth2");
    Dev1.addService("serviceType1", "serviceId1", "scpdUrl1", "eventSubUrl1", "controlUrl1");
    Dev1.addService("serviceType2", "serviceId2", "scpdUrl2", "eventSubUrl2", "controlUrl2");
    Dev1.addEmbeddedDevice("type2", "Friendly Name1", "manufacturer1", "manufacturerUrl1",
                              "modelDescription1", "modelName1", "modelNumber1", "modelUrl1",
                              "serialNumber1", "uuid:udn1", "Upc1","presentationUrl.com1");
    Dev1.addEmbeddedDevice("type3", "Friendly Name2", "manufacturer2", "manufacturerUrl2",
                              "modelDescription2", "modelName2", "modelNumber2", "modelUrl2",
                              "serialNumber2", "uuid:udn2", "Upc2", "presentationUrl.com2");
//GENERATING THE XML DEVICE DESCRIPTION FILE WITH DEVICE OF MEMORY
    Dev1.xmlGenerator();
//CREATING DEVICE WITH XML DEVICE DESCRIPTION FILE
    BrisaDevice  Dev2;
    Dev2.deviceGenerator(Dev1.getAttribute(BrisaDevice::FileAddress));
    qDebug() << "\n-----------------------------ROOT DEVICE--------------------------------------";
    qDebug() << "DeviceType = " << Dev2.getAttribute(BrisaDevice::DeviceType);
    qDebug() << "FriendlyName = " << Dev2.getAttribute(BrisaDevice::FriendlyName);
    qDebug() << "Manufacturer = " << Dev2.getAttribute(BrisaDevice::Manufacturer);
    qDebug() << "ManufacturerUrl = " << Dev2.getAttribute(BrisaDevice::ManufacturerUrl);
    qDebug() << "ModelDescription = " << Dev2.getAttribute(BrisaDevice::ModelDescription);
    qDebug() << "ModelName = " << Dev2.getAttribute(BrisaDevice::ModelName);
    qDebug() << "ModelNumber = " << Dev2.getAttribute(BrisaDevice::ModelNumber);
    qDebug() << "ModelUrl = " << Dev2.getAttribute(BrisaDevice::ModelUrl);
    qDebug() << "SerialNumber = " << Dev2.getAttribute(BrisaDevice::SerialNumber);
    qDebug() << "Udn = " << Dev2.getAttribute(BrisaDevice::Udn);
    qDebug() << "Upc = " << Dev2.getAttribute(BrisaDevice::Upc);
    qDebug() << "PresentationUrl = " << Dev2.getAttribute(BrisaDevice::PresentationUrl);
    qDebug() << "---------------------------------------------------------------------------------";
//PRINTING THE ICONS OF DEVICE ROOT
    qDebug() << "\n";
    QList<BrisaIcon> iconList = Dev2.getIconList();
    for(int i =0 ; i < iconList.size() ; i++)
    {
        qDebug() << "\n--------------------------"<<"ICON"<<i+1<<"--------------------------------";
        qDebug() << "MimeType = " << iconList[i].getAttribute(BrisaIcon::Mimetype);
        qDebug() << "Url = " << iconList[i].getAttribute(BrisaIcon::Url);
        qDebug() << "Width = " << iconList[i].getAttribute(BrisaIcon::Width);
        qDebug() << "Height = " << iconList[i].getAttribute(BrisaIcon::Height);
        qDebug() << "Depth = " << iconList[i].getAttribute(BrisaIcon::Depth);
        qDebug() << "-----------------------------------------------------------------------------";
    }
//PRINTING TTHE SERVICES OF DEVICE ROOT
    qDebug() << "\n";
    QList<BrisaService*> serviceList = Dev2.getServiceList();
    for(int j =0 ; j < serviceList.size() ; j++)
    {
        qDebug() << "\n--------------------------"<<"SERVICE"<<j+1<<"-----------------------------";
        qDebug() << "ServiceType = " << serviceList[j]->getAttribute(BrisaService::ServiceType);
        qDebug() << "ServiceId = " << serviceList[j]->getAttribute(BrisaService::ServiceId);
        qDebug() << "ScpdUrl = " << serviceList[j]->getAttribute(BrisaService::ScpdUrl);
        qDebug() << "EventSubUrl = " << serviceList[j]->getAttribute(BrisaService::EventSubUrl);
        qDebug() << "controlUrl = " << serviceList[j]->getAttribute(BrisaService::ControlUrl);
        qDebug() << "-----------------------------------------------------------------------------";
    }
//PRINTING TTHE EMBEDDED DEVICES OF DEVICE ROOT
    qDebug() << "\n";
    QList<BrisaDevice*> embeddedDeviceList = Dev2.getEmbeddedDeviceList();
    for(int k =0 ; k < embeddedDeviceList.size() ; k++)
    {
        qDebug() << "\n------------------"<<"EMBEDDED DEVICE"<<k+1<<"-----------------------------";
        qDebug() << "DeviceType = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::DeviceType);
        qDebug() << "FriendlyName = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::FriendlyName);
        qDebug() << "Manufacturer = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::Manufacturer);
        qDebug() << "ManufacturerUrl = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::ManufacturerUrl);
        qDebug() << "ModelDescription = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::ModelDescription);
        qDebug() << "ModelName = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::ModelName);
        qDebug() << "ModelNumber = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::ModelNumber);
        qDebug() << "ModelUrl = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::ModelUrl);
        qDebug() << "SerialNumber = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::SerialNumber);
        qDebug() << "Udn = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::Udn);
        qDebug() << "Upc = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::Upc);
        qDebug() << "PresentationUrl = " << embeddedDeviceList[k]->getAttribute(BrisaDevice::PresentationUrl);
        qDebug() << "-----------------------------------------------------------------------------";
    }

    return app.exec();
}

