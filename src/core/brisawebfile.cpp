#include "brisawebfile.h"

#ifdef USE_NEW_BRISA_WEBSERVER

BrisaWebFile::BrisaWebFile(const QString &fileName, QObject *parent) :
        BrisaWebService(parent),
        m_fileName(fileName)
{
}

BrisaWebFile::~BrisaWebFile()
{
}

QString BrisaWebFile::fileName() const
{
    return m_fileName;
}

void BrisaWebFile::setFile(const QString &fileName)
{
    m_fileName = fileName;
}

void BrisaWebFile::onRequest(const HttpRequest &request,
                             BrisaWebserverSession *session)
{
    HttpResponse response(request.httpVersion());

//    response.setHeader("Content-Type", ); // TODO
    QFile *file = new QFile(m_fileName);
    file->open(QIODevice::ReadOnly);
    resoponse.setEntityBody(file);

    session->respond(response);
}

#else // !USE_NEW_BRISA_WEBSERVER

using namespace BrisaCore;

BrisaWebFile::BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath,
        QObject *parent) :
    QxtAbstractWebService(sm, parent) {
    file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw "Could not open file for read.";
}

BrisaWebFile::~BrisaWebFile() {
    delete file;
}

void BrisaWebFile::pageRequestedEvent(QxtWebRequestEvent *event) {
    QxtWebPageEvent *c = new QxtWebPageEvent(event->sessionID,
            event->requestID, file->readAll());
    c->contentType = "text/xml";
    postEvent(c);
    file->reset();
}

#endif // USE_NEW_BRISA_WEBSERVER
