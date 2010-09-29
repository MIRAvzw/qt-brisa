/**
  * Creating a simples control point using BRisa Qt
  */

#ifndef CONTROL_POINT_H
#define CONTROL_POINT_H

#include <BrisaUpnp/BrisaControlPoint> // To create the Control Point
#include <QList>    // To store the devices
#include <QString>
#include <QtDebug>  // For debugging purposes
#include <QTextStream>  // For receiving the commands
#include <QCoreApplication>
#include <iostream>

#define BINARY_LIGHT_TYPE    "urn:schemas-upnp-org:device:BinaryLight:1"  //The binary light type 
#define SERVICE_SWITCH_POWER "urn:schemas-upnp-org:service:SwitchPower:1" //Service that contains the actions we use

using namespace BrisaUpnp;

class HandleCmds : public QThread
{
    Q_OBJECT
    public:
        void run() {            
            QTextStream stream(stdin);
            do{
                QString line;
                QCoreApplication::processEvents();
                std::cout << ">>> ";
                line = stream.readLine();
                if(line == "exit") {
                    emit leave();
                    running = false;
                } else if(line == "list") {
                    emit list();
                } else if(line == "help"){
                    emit help();
                } else if(line == "get_target"){
                    emit getTarget();
                } else if(line == "get_status"){
                    emit getStatus();
                } else if(line == "turn on"){
                    emit turnOn();
                } else if(line == "turn off"){
                    emit turnOff();
                } else {
                    if (line.split(" ").size() == 2) {
                        if(line.split(" ")[0] == "set_light") {
                            emit setLight(line.split(" ")[1].toInt());
                        } else {
                            qDebug() << "Wrong usage, try 'help' to see the commands";
                        }
                    } else {
                        qDebug() << "Wrong usage, try 'help' to see the commands";
                    }
                }
            } while(running);
        }

    private:
        void setRunningCmds(bool running) { this->running = running; }
        
        bool running;

    signals:
        void leave();
        void list();
        void help();
        void setLight(int i);
        void turnOn();
        void turnOff();
        void getTarget();
        void getStatus();
};

class ControlPoint : BrisaControlPoint
{
    Q_OBJECT
    public:
        ControlPoint();
        ~ControlPoint();


    private:
        QString listServices(BrisaControlPointDevice *dev);
        QString listEmbeddedDevices(BrisaControlPointDevice *dev);

        QList <BrisaControlPointDevice*> devices;
        BrisaControlPointDevice *selected;
        bool runningHandleCmds;
        HandleCmds *handle;

    private slots:
        void help();
        void setLight(int index);
        void getTarget();
        void getStatus();
        void turnOn();
        void turnOff();
        void exit();
        void list();
        void setTargetResponse(QString response, QString method);
        void getTargetResponse(QString response, QString method);
        void getStatusResponse(QString response, QString method);
        void onNewDevice(BrisaControlPointDevice *dev);
        void onRemovedDevice(QString desc);
		void requestError(QString errorMessage, QString methodName); 
};

#endif
