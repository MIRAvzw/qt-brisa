#ifdef USE_NEW_BRISA_WEBSERVER
#include "brisacontrolwebservice.h"
#include "brisaactionxmlparser.h"

BrisaControlWebService::BrisaControlWebService(const QString &serviceType, QObject *parent) :
    BrisaWebService(parent),
    serviceType(serviceType)
{
}

void BrisaControlWebService::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    if (request.method() != "POST")
        return;

    BrisaActionXmlParser actionXmlParser;

    actionXmlParser.setXmlContent(request.entityBody());

    if (actionXmlParser.parseSOAP()) {
        //If servicetype is incorrect
        if (actionXmlParser.serviceType != serviceType)
            return;

//        this->call(actionXmlParser.method, actionXmlParser.args);
        emit requestReceived(actionXmlParser.method, actionXmlParser.args, session);
    } else {
        qDebug() << "BrisaService: Invalid SOAP xml format.";
//        this->respondError(UPNP_INVALID_ACTION);
        emit invalidRequest(session);
    }
}

#endif
