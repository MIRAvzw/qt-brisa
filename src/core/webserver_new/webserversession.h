#ifndef WEBSERVERSESSION_H
#define WEBSERVERSESSION_H

#include "httpsession.h"

class WebServerSession : public HttpSession
{
Q_OBJECT
public:
    WebServerSession(int socketDescriptor, QObject *parent = NULL);
    int isRequestSupported(const HttpRequest &request) const;

protected:
    bool hasEntityBody(const HttpRequest &request) throw(HttpResponse);
    bool atEnd(const HttpRequest &request, const QByteArray &buffer) throw(HttpResponse);
    HttpResponse onRequest(const HttpRequest &request);
};

#endif // WEBSERVERSESSION_H
