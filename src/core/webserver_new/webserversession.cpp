#include "webserversession.h"
#include <QFile>
#include "webserver.h"

#define DBG_PREFIX "WebServerConnection: "

static const QByteArray notFound =
        "<html>"
        " <head>"
        "  <title>404 - Not Found</title>"
        " </head>"
        " <body>"
        "  <h1>Not found</h1>"
        " </body>"
        "</html>";

WebServerSession::WebServerSession(int socketDescriptor,
                                         WebServer *parent) :
    HttpSession(socketDescriptor, parent),
    server(parent)
{
    qDebug(DBG_PREFIX "nova conexão web");
}

void WebServerSession::onRequest(HttpRequest request)
{
    qDebug(DBG_PREFIX "respondendo request");
    HttpResponse response(request.httpVersion());
    qDebug() << request.uri();
    WebResource resource = server->resource(WebResourceIdentifier(request.uri(), request.header("Host")));
    if (resource.fileName.isEmpty()) {
        resource = server->resource(WebResourceIdentifier(request.uri()));
    }
    if (QFile::exists(resource.fileName)) {
        QFile file(resource.fileName);
        file.open(QIODevice::ReadOnly);

        if (!resource.contentType.isEmpty())
            response.setHeader("Content-Type", resource.contentType);

        response.setBody(file.readAll());

        writeResponse(response);
    } else {
        response.setStatusCode(404, "Not Found");

        response.setHeader("Content-Type", "text/html");
        response.setBody(notFound);

        writeResponse(response);
    }
}
