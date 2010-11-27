#include "brisacontrolwebservice.h"
#include "brisaactionxmlparser.h"
#include <httpresponse.h>

using namespace Brisa;

BrisaControlWebService::BrisaControlWebService(const QString &serviceType, QObject *parent) :
    BrisaWebService(parent),
    serviceType(serviceType)
{
}

void BrisaControlWebService::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    if (request.method() != "POST") {
        // TODO: close connection?
        HttpResponse r(request.httpVersion(), HttpResponse::METHOD_NOT_ALLOWED);
        return;
    }

    BrisaActionXmlParser actionXmlParser;

    {
        QIODevice *xml = request.entityBody();
        xml->seek(0);
        actionXmlParser.setXmlContent(xml->readAll());
    }

    if (actionXmlParser.parseSOAP()) {
        //If servicetype is incorrect
        if (actionXmlParser.serviceType != serviceType)
            return;

        emit requestReceived(actionXmlParser.method, actionXmlParser.args, session);
    } else {
        qDebug() << "BrisaService: Invalid SOAP xml format.";
        emit invalidRequest(session);
    }
}
