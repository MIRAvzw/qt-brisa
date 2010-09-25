#include "brisawebstaticcontent.h"
using namespace BrisaCore;

#ifdef USE_NEW_BRISA_WEBSERVER

BrisaWebStaticContent::BrisaWebStaticContent(const QByteArray &content,
                                             QObject parent) :
        BrisaWebService(parent),
        m_content(content)
{
}

BrisaWebStaticContent::~BrisaWebStaticContent()
{
}

QByteArray BrisaWebStaticContent::content() const
{
    return m_content;
}

void BrisaWebStaticContent::setContent(const QByteArray &content)
{
    m_content = content;
}

QByteArray BrisaWebStaticContent::contentType() const
{
    return m_contentType;
}

void BrisaWebStaticContent::setContentType(const QByteArray &contentType)
{
    m_contentType = contentType;
}

void BrisaWebStaticContent::onRequest(const HttpRequest &request,
                                      BrisaWebserverSession *session)
{
    HttpResponse response(request.httpVersion());

    response.setHeader("Content-Type", m_contentType);
    response.setEntityBody(content);

    session->respond(response);
}

#else // !USE_NEW_BRISA_WEBSERVER

BrisaWebStaticContent::BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
        QString content, QObject *parent) :
    QxtWebSlotService(sm, parent) {
    this->content = new QString(content);
}

BrisaWebStaticContent::~BrisaWebStaticContent() {
    delete content;
}

void BrisaWebStaticContent::index(QxtWebRequestEvent *event) {
    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID,
            content->toUtf8()));
}

#endif // USE_NEW_BRISA_WEBSERVER
