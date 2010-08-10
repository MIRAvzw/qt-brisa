#include "webserver.h"
#include "webserversession.h"
#include "webresource.h"

WebServer::WebServer(const QHostAddress &address, quint16 port,
                     QObject *parent) :
    HttpServer(address, port, parent)
{
}

HttpSession *WebServer::incomingConnection(int socketDescriptor)
{
    return new WebServerSession(socketDescriptor, this);
}

void WebServer::publishFile(const WebResourceIdentifier &uri, const WebResource &resource)
{
    if (!uri.uri.isEmpty()) {
        mutex.lock();
        handle[uri] = resource;
        mutex.unlock();
    }
}

WebResource WebServer::resource(const WebResourceIdentifier &uri) const
{
    return handle.value(uri);
}
