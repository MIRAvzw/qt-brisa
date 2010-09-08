#ifndef BRISAMULTICASTEVENTRECEIVER_H
#define BRISAMULTICASTEVENTRECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHttp>
#include <QDomDocument>

#ifdef Q_WS_X11
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <string.h>

#include "brisaglobal.h"

class BRISA_UPNP_EXPORT BrisaMulticastEventReceiver : public QObject
{
    Q_OBJECT
public:

    /*!
     * Constructor.
     */
    BrisaMulticastEventReceiver(QObject *parent = 0);

    /*!
     * Starts receiving the multicast events.
     */
    void start();

private slots:
    /*!
     * Reads the received multicast message.
     */
    void read();

    /*!
     * Formats the received multicast message and adds the attributes to a map.
     */
    void formatMessage();

signals:
    /*!
     * Signal emitted when a multicast message is received and fully formatted.
     *
     * \param attributes QMap containing the attributes of the message,
     * including the variable name ("variableName") and the new value
     * ("newValue").
     */
    void multicastReceived(QMap<QString, QString> attributes);

private:

    /*!
     * Parses the body of the multicast message.
     *
     * \param body body of the message to be parsed.
     */
    void parseBody(QByteArray body);

    /*!
     * Received multicast event message.
     */
    QByteArray message;

    /*!
     * Attributes of the multicast event.
     */
    QMap<QString, QString> attributes;

    /*!
     * Socket listening to 239.255.255.246:7900.
     */
    QUdpSocket *udpSocket;

};

#endif // BRISAMULTICASTEVENTRECEIVER_H
