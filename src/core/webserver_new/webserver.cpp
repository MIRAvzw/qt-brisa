#include "webserver.h"
#include "webserversession.h"

WebServer::WebServer(const QHostAddress &address, quint16 port, QObject *parent) :
        HttpServer(address, port, parent)
{
}

HttpSession *WebServer::incomingConnection(int socketDescriptor)
{
    return new WebServerSession(socketDescriptor);
}
