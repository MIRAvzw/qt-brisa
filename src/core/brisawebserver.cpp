/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisawebserver.cpp
 * Created:
 * Description: Implementation of BrisaWebServer class.
 * Authors: Andre Dieb Martins <andre.dieb@gmail.com> @since 2009
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
 *
 * BRisa-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "brisawebserver.h"
using namespace BrisaCore;

/*
 * Reimplemented from libQxt.
 */
inline QString extractPathLevel(QxtWebRequestEvent *event);

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


BrisaWebFile::BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath, QObject *parent) :
        QxtAbstractWebService(sm, parent)
{
    file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw "Could not open file for read.";
}

BrisaWebFile::~BrisaWebFile()
{
    delete file;
}

void BrisaWebFile::pageRequestedEvent(QxtWebRequestEvent *event)
{
    QxtWebPageEvent *c =
            new QxtWebPageEvent(event->sessionID, event->requestID, file->readAll());
    c->contentType = "text/xml";
    postEvent(c);
    file->reset();
}

BrisaWebStaticContent::BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
                              QString content,
                              QObject *parent) :
                            	  QxtWebSlotService(sm, parent)
{
    this->content = new QString(content);
}

BrisaWebStaticContent::~BrisaWebStaticContent()
{
    delete content;
}

void BrisaWebStaticContent::index(QxtWebRequestEvent *event)
{
    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, content->toUtf8()));
}


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


BrisaWebserver::BrisaWebserver(const QHostAddress &host, quint16 port)
{
    QxtHttpSessionManager(this);
    rootService = new BrisaWebServiceProvider(this, this);

    setPort(port);
    setListenInterface(host);
    setConnector(HttpServer);
    setStaticContentService(rootService);
}

BrisaWebserver::~BrisaWebserver()
{
    delete rootService;
}

int BrisaWebserver::newSession()
{
    return QxtHttpSessionManager::newSession();
}

void BrisaWebserver::addService(QString path, QxtWebServiceDirectory *service)
{
    rootService->addService(path, service);
}

void BrisaWebserver::incomingRequest(quint32 requestID, const QHttpRequestHeader &header, QxtWebContent *deviceContent)
{
    QxtHttpSessionManager::incomingRequest(requestID, header, deviceContent);
    qDebug() << requestID << " Request";
    qDebug() << "Method: " << header.method();
    qDebug() << "URI: " << header.path();
}

void BrisaWebserver::publishFile(QString publishPath, QString filePath)
{
    // Publishing a file to the root
    rootService->addFile(publishPath, filePath);
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
