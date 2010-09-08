#include "brisamulticasteventreceiver.h"

BrisaMulticastEventReceiver::BrisaMulticastEventReceiver(QObject *parent) :
        QObject(parent)
{
    this->udpSocket = new QUdpSocket(parent);
    this->udpSocket->bind(QHostAddress("239.255.255.246"), 7900);

    connect(this->udpSocket, SIGNAL(readyRead()), this, SLOT(read()));
}

void BrisaMulticastEventReceiver::start()
{
    int fd;

    if (!udpSocket->bind(7900, QUdpSocket::ShareAddress |
                         QUdpSocket::ReuseAddressHint)) {
        qDebug() << "BrisaMulticastEventReceiver BIND FAIL!";
    }

    fd = udpSocket->socketDescriptor();
    struct ip_mreq mreq;
    memset(&mreq, 0, sizeof(struct ip_mreq));
    mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.246");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &mreq,
            sizeof(struct ip_mreq)) < 0) {
        qDebug() << "Brisa SSDP Client: Could not join MULTICAST group";
        return;
    }
}

void BrisaMulticastEventReceiver::read()
{
    this->message.resize(udpSocket->pendingDatagramSize());
    this->udpSocket->readDatagram(this->message.data(), this->message.size());
    formatMessage();
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
    }
    this->attributes["USN"] =  requestHeader.value("USN");
    this->attributes["SVCID"] = requestHeader.value("SVCID");
    this->attributes["NT"] = requestHeader.value("NT");
    this->attributes["NTS"] = requestHeader.value("NTS");
    this->attributes["SEQ"] = requestHeader.value("SEQ");
    this->attributes["LVL"] = requestHeader.value("LVL");
    this->attributes["BOOTID.UPNP.ORG"] = requestHeader.value("LVL");
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
