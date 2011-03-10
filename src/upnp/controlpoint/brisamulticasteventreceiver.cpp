#include "brisamulticasteventreceiver.h"

using namespace Brisa;

BrisaMulticastEventReceiver::BrisaMulticastEventReceiver(QObject *parent) :
        QObject(parent)
{
    this->udpListener = new BrisaUdpListener("239.255.255.246", 7900,
                                       "BrisaMulticastEventReceiver",
                                       parent);
    connect(this->udpListener, SIGNAL(readyRead()), this, SLOT(read()));
}

BrisaMulticastEventReceiver::~BrisaMulticastEventReceiver()
{
    delete this->udpListener;
}

void BrisaMulticastEventReceiver::start()
{
    this->udpListener->start();
}

void BrisaMulticastEventReceiver::read()
{
    while (this->udpListener->hasPendingDatagrams()) {
        this->message.resize(udpListener->pendingDatagramSize());
        this->udpListener->readDatagram(this->message.data(), this->message.size());
        formatMessage();
    }
}

void BrisaMulticastEventReceiver::formatMessage()
{
    QString newMessage = QString(message);
    QString header = "";
    QString body = "";
    QString temp;
    int i = 0;
    while (i < newMessage.size()) {
        temp = "";
        do {
            temp.append(newMessage[i]);
            i++;
        } while (!temp.endsWith("\r\n"));
        if (temp == "\r\n") {
            break;
        }
        header.append(temp);
    }
    if (i == newMessage.size()) {
        qWarning() << "Bad formated multicast message!";
        return;
    }
    QHttpRequestHeader requestHeader(header);
    bool castOk = 0;
    const int length = requestHeader.value("CONTENT-LENGTH").toInt(&castOk);
    if (!castOk) {
        qWarning() << "CONTENT-LENGTH is not ok on multicast message.";
        return;
    }
    for (; i < newMessage.size(); i++) {
        body.append(newMessage[i]);
    }
    if (length != body.size()) {
        qWarning() << "Value for CONTENT-LENGTH is wrong.";
        return;
    }
    this->attributes["USN"] =  requestHeader.value("USN");
    this->attributes["SVCID"] = requestHeader.value("SVCID");
    this->attributes["NT"] = requestHeader.value("NT");
    this->attributes["NTS"] = requestHeader.value("NTS");
    this->attributes["SEQ"] = requestHeader.value("SEQ");
    this->attributes["LVL"] = requestHeader.value("LVL");
    //TODO: use BOOTID.UPNP.ORG
//    this->attributes["BOOTID.UPNP.ORG"] = requestHeader.value("BOOTID.UPNP.ORG");
    parseBody(body.toUtf8());
    emit multicastReceived(attributes);
}

void BrisaMulticastEventReceiver::parseBody(QByteArray body)
{
    QDomDocument doc("body");
    body.replace(":e", "");
    doc.setContent(body);
    QString xmlns = doc.documentElement().attribute("xmlns");
    QDomNode node = doc.documentElement().firstChild().firstChild();
    QString variableName = node.toElement().tagName();
    QString newValue = node.toElement().text();
    this->attributes["xmlns"] = xmlns;
    this->attributes["variableName"] = variableName;
    this->attributes["newValue"] = newValue;
}
