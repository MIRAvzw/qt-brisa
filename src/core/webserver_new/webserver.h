#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "httpserver.h"
#include <QMutex>
#include "webresource.h"

class WebServer : public HttpServer
{
Q_OBJECT
public:
    explicit WebServer(const QHostAddress &address = QHostAddress::Any,
                       quint16 port = 0, QObject *parent = 0);
    void publishFile(const WebResourceIdentifier &uri, const WebResource &resource);
    WebResource resource(const WebResourceIdentifier &uri) const;

signals:

public slots:

protected:
    HttpSession *incomingConnection(int socketDescriptor);

private:
    QMutex mutex;
    QHash<WebResourceIdentifier, WebResource> handle;
};

#endif // WEBSERVER_H
