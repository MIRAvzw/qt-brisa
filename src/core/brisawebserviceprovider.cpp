#include "brisawebserviceprovider.h"

using namespace BrisaCore;

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
