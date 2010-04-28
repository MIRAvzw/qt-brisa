#include "brisawebserviceprovider.h"

using namespace BrisaCore;

/*
 * Reimplemented from libQxt.
 */
inline QString extractPathLevel(QxtWebRequestEvent *event);

BrisaWebServiceProvider::BrisaWebServiceProvider(QxtAbstractWebSessionManager *sm, QObject *parent) :
        QxtWebServiceDirectory(sm, parent)
{
    root = new BrisaWebStaticContent(sm, DEFAULT_PAGE, this);
    sessionManager = sm;
}

BrisaWebServiceProvider::~BrisaWebServiceProvider()
{
    delete root;
    while (!files.isEmpty())
        delete files.takeFirst();
}

void BrisaWebServiceProvider::addFile(const QString path, QString filePath)
{
    BrisaWebFile *f = new BrisaWebFile(sessionManager, filePath, this);
    files.append(f);
    addService(path, f);
}

void BrisaWebServiceProvider::addContent(const QString path, QString content)
{
    BrisaWebStaticContent *c = new BrisaWebStaticContent(sessionManager, content, this);
    this->content.append(c);
    addService(path, c);
}

void BrisaWebServiceProvider::indexRequested(QxtWebRequestEvent *event)
{
    //TODO: fix it
    root->index(event);
}

void BrisaWebServiceProvider::pageRequestedEvent(QxtWebRequestEvent *event)
{
    QString path = extractPathLevel(event);
    if (path.isEmpty()) {
        indexRequested(event);
    }
    else if (!service(path)) {
        unknownServiceRequested(event, path);
    }
    else {
        service(path)->pageRequestedEvent(event);
    }
}

inline QString extractPathLevel(QxtWebRequestEvent *event)
{
    QString path = event->url.path();
    // the path always starts with /
    int pos = path.indexOf("/", 1);
    if (pos == -1)
        // cue to redirect to /service/
        event->url.setPath("");
    else
        event->url.setPath(path.mid(pos));
    return path.mid(1, pos - 1);
}
