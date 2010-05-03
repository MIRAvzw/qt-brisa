#include "brisawebfile.h"

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
