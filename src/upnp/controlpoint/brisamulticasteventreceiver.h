#ifndef BRISAMULTICASTEVENTRECEIVER_H
#define BRISAMULTICASTEVENTRECEIVER_H

#include <QObject>
#include <QHttp>
#include <QDomDocument>

#include "brisaudplistener.h"
#include "brisaglobal.h"

namespace Brisa {

class BRISA_UPNP_EXPORT BrisaMulticastEventReceiver : public QObject
{
    Q_OBJECT
public:

    /*!
     * Constructor.
     *
     * \param parent parent
     */
    BrisaMulticastEventReceiver(QObject *parent = 0);

    /*!
     * Destructor
     */
    virtual ~BrisaMulticastEventReceiver();

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
    BrisaUdpListener *udpListener;

};

}

#endif // BRISAMULTICASTEVENTRECEIVER_H
