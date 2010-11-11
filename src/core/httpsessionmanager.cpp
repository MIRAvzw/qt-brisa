#include "httpsessionmanager.h"
#include "httpsession.h"

HttpSessionManager::HttpSessionManager(HttpServer *parent) :
    QThread(parent),
    server(parent)
{
}

void HttpSessionManager::run()
{
    connect(this, SIGNAL(newConnection(int)), this, SLOT(onNewConnection(int)));

    exec();
}

void HttpSessionManager::addSession(int socketDescriptor)
{
    emit newConnection(socketDescriptor);
}

void HttpSessionManager::onNewConnection(int socketDescriptor)
{
    bool created = false;

    mutex.lock();


    if (pool.size()) {
        pool.back()->setSession(socketDescriptor);
        created = true;
    }

    mutex.unlock();

    if (!created) {
        HttpSession *s = server->factory().generateSessionHandler(this);
        s->setSession(socketDescriptor);
    }
}

void HttpSessionManager::releaseSession(HttpSession *session)
{
    mutex.lock();

    pool.append(session);

    mutex.unlock();
}
