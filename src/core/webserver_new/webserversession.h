#ifndef WEBSERVERSESSION_H
#define WEBSERVERSESSION_H

#include "httpsession.h"

class WebServer;

class WebServerSession : public HttpSession
{
Q_OBJECT
public:
    explicit WebServerSession(int socketDescriptor, WebServer *parent = 0);

signals:

public slots:

protected:
    void onRequest(HttpRequest request);

private:
    WebServer *server;
};

#endif // WEBSERVERSESSION_H
