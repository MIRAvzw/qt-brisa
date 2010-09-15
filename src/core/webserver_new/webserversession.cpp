#include "webserversession.h"

WebServerSession::WebServerSession(int socketDescriptor, QObject *parent) :
        HttpSession(socketDescriptor, parent)
{
}

int WebServerSession::isRequestSupported(const HttpRequest &request) const
{
    if (request.method() != "GET")
        return HttpResponse::NOT_IMPLEMENTED;

    return 0;
}

bool WebServerSession::hasEntityBody(const HttpRequest &r) throw(HttpResponse)
{
    return false;
}

bool WebServerSession::atEnd(const HttpRequest &, const QByteArray &) throw(HttpResponse)
{
}

HttpResponse WebServerSession::onRequest(const HttpRequest &request)
{
    HttpResponse response(request.httpVersion(), HttpResponse::OK, true);

    response.setEntityBody("<html>"
                           " <head><title>Hello World</title></head>"
                           " <body>"
                           "  <h1>It's working</h1>"
                           "  <p>Your vinipsmakerWork-based server is working properly<br/>"
                           "     You should configure-it now</p>"
                           " </body>"
                           "</html>");

    return response;
}
