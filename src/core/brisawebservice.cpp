#include "brisawebservice.h"
using namespace BrisaCore;

const QByteArray DEFAULT_PAGE = "<html><body><h1>BRisa WebServer!</h1></body></html>";

#ifdef USE_NEW_BRISA_WEBSERVER

BrisaWebService::BrisaWebService(QObject *)
{
}

BrisaWebService::~BrisaWebService()
{
}

void BrisaWebService::postRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    onRequest(request, session);
}

void BrisaWebService::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    emit genericRequestReceived(request, session);
}

#else

BrisaWebService::BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent) :
                QxtWebServiceDirectory(sm, parent)
{
}

void BrisaWebService::pageRequestedEvent(QxtWebRequestEvent *event)
{
    this->sessionID = event->sessionID;
    this->requestID = event->requestID;

    QByteArray requestContent("");
    if (event->content) {
         event->content->waitForAllContent();
         requestContent = event->content->readAll();
    }
    emit genericRequestReceived(event->method,
                                event->headers,
                                requestContent,
                                event->sessionID,
                                event->requestID);
    emit genericRequestReceived(this, event->headers, requestContent);

    if (event->method == "GET")
        postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, DEFAULT_PAGE));
}

void BrisaWebService::respond(QByteArray response)
{
    this->respond(response, this->sessionID, this->requestID);
}

void BrisaWebService::respond(const QByteArray &response, const int &sessionId, const int &requestId)
{
    this->postEvent(new QxtWebPageEvent(sessionId, requestId, response));
}

void BrisaWebService::respond(const QHttpResponseHeader &response)
{
    this->respond(response, this->sessionID, this->requestID);
}

void BrisaWebService::respond(const QHttpResponseHeader &response, const int &sessionId,
                     const int &requestId)
{
    QxtWebPageEvent *event = new QxtWebPageEvent(sessionId, requestId, "");

    event->status = response.statusCode();
    event->statusMessage = response.reasonPhrase().toAscii();

    // Set key-value pairs from header to event's headers
    // it is done because LibQxt's events cannot receive QHttpResponseHeaders
    QList<QPair<QString, QString> > headerValues = response.values();
    for (QList<QPair<QString, QString> >::iterator i = headerValues.begin();
    i != headerValues.end(); ++i) {
        event->headers.insertMulti(i->first, i->second);
    }

    this->postEvent(event);
}

#endif
