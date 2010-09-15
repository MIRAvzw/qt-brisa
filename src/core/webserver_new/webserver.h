#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "httpserver.h"

class WebServer : public HttpServer
{
public:
    WebServer(const QHostAddress &address, quint16 port, QObject *parent = NULL);

protected:
    HttpSession *incomingConnection(int socketDescriptor);
};

#endif // WEBSERVER_H
