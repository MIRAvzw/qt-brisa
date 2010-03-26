/* brisa-c++
 *
 * Copyright (C) 2009 Andre Dieb Martins <andre.dieb@gmail.com>
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "brisawebserver.h"

using namespace BrisaCore;

/*!
 *  \class BrisaCore::BrisaWebService brisawebserver.h BrisaCore/BrisaWebService
 *  \brief Web service abstraction class
 *
 *  BrisaWebService is used to receive and respond UPnP action and event requests. Currently this
 *  class is used mostly with BrisaService and BrisaEventController.
 *
 *  \sa BrisaUpnp::BrisaService , BrisaUpnp::BrisaEventController
 */

/*!
 *  \fn BrisaWebService::BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent = 0)
 *  Constructor for BrisaWebService
 */

/*!
 *  \fn BrisaWebService::~BrisaWebService()
 *  Destructor for BrisaWebService
 */

/*!
 *  \fn void BrisaWebService::pageRequestedEvent(QxtWebRequestEvent *event)
 *
 *  Reimplemented from libQxt.
 *  This method receives all web service requests and emits a genericRequestReceived() signal. If
 *  the request method is of "POST" type, the web service will reply a default message.
 */

/*!
 *  \fn void BrisaWebService::respond(QByteArray response)
 *
 *  Responds \a response to the session and request ID currently stored in BrisaWebService, if using
 *  this method the response must be synchronous because the request and session ID can change
 *  quickly.
 */

/*!
 *  \fn void BrisaWebService::respond(const QByteArray &response, const int &sessionId,
                                      const int &requestId)
 *
 *  Reimplements respond().
 *  We recommend using this method given the fact that it supports asynchronous requests.
 */

/*!
 *  \fn void BrisaWebService::respond(const QHttpResponseHeader &response)
 *
 *  Reimplements respond()
 *  This method responds only a HTTP header to the session and request ID stored in BrisaWebService
 */

/*!
 *  \fn void BrisaWebService::respond(const QHttpResponseHeader &response, const int &sessionId,
                                      const int &requestId)
 *
 *  Reimplements respond().
 *  This method responds only a HTTP header using the given session and request ID.
 */

/*!
 *  \fn void BrisaWebService::genericRequestReceived(const QString &method,
                                                     const QMultiHash<QString, QString> &headers,
                                                     const QByteArray &requestContent,
                                                     int sessionId,
                                                     int requestId)
 *
 *  This signal is emmited when BrisaWebService receives a request.
 */

/*!
 *  \fn void BrisaWebService::genericRequestReceived(BrisaWebService *service,
                                                     QMultiHash<QString, QString>,
                                                     QString requestContent)
 *
 *  Reimplements genericRequestReceived()
 *  This signal is emmited when BrisaWebService receives a request, the main difference is that this
 *  signal has a pointer to the class that is emmiting the signal.
 */

/*!
 *  \class BrisaCore::BrisaWebFile brisawebserver.h BrisaCore/BrisaWebFile
 *  \brief Adds a file to the web server.
 *
 *  Use this class to store a file into the web server. If the BrisaWebFile is stored using a
 *  BrisaWebServiceProvider, it's url path will be of "IP:PORT/SERVICENAME/yourfile". if it's stored
 *  using the BrisaWebServer convenience method \a "publishFile()", it's url path will be
 *  "IP:PORT/yourfile".
 */

/*!
 *  \fn BrisaWebFile::BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath,
                                   QObject *parent = 0)
 *
 *  Constructor for BrisaWebFile. It creates a QFile with the given file path.
 */

/*!
 *  \fn BrisaWebFile::~BrisaWebFile()
 *
 *  Destructor for BrisaWebFile.
 */

/*!
 *  \fn void BrisaWebFile::pageRequestedEvent(QxtWebRequestEvent *event)
 *
 *  Reimplemented from libQxt. When a request is received the BrisaWebFile will reply the stored
 *  file.
 */

/*!
 *  \class BrisaCore::BrisaWebStaticContent brisawebserver.h BrisaCore/BrisaWebStaticContent
 *  \brief The BrisaWebStaticContent class stores a QString into the web server.
 *
 *  Use this class to store static content in the web server using a string format.
 */

/*!
 *  \fn BrisaWebStaticContent::BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
                                                     QString content,
                                                     QObject *parent = 0)
 *
 *  Constructor for BrisaWebStaticContent. Stores the given QString.
 */

/*!
 *  \fn BrisaWebStaticContent::~BrisaWebStaticContent()
 *
 *  Destructor for BrisaWebStaticContent.
 */

/*!
 *  \fn void index(QxtWebRequestEvent *event)
 *
 *  This method is called by BrisaWebServiceProvider, it replys the stored content.
 */

/*!
 *  \class BrisaCore::BrisaWebServiceProvider brisawebserver.h BrisaCore/BrisaWebServiceProvider
 *  \brief The BrisaWebServiceProvider class works as web service manager for the web server.
 *
 *  The BrisaWebServiceProvider has convenience methods for managing web services, like addFile()
 *  and addContent(). It also keeps track of all files and content stored into the web service.
 */

/*!
 *  \fn BrisaWebServiceProvider::BrisaWebServiceProvider(QxtAbstractWebSessionManager *sm,
                                                         QObject *parent)
 *
 *  Constructor for BrisaWebServiceProvider
 */

/*!
 *  \fn BrisaWebServiceProvider::~BrisaWebServiceProvider()
 *
 *  Destructor for BrisaWebServiceProvider.
 */

/*!
 *  \fn void indexRequested(QxtWebRequestEvent *event)
 *
 *  Reimplemented from libQxt.
 *  This method calls the BrisaWebStaticContent \a index() method.
 */

/*!
 *  Call this method to add a BrisaWebFile to the web service.
 */
void BrisaWebServiceProvider::addFile(const QString path, QString filePath)
{
    BrisaWebFile *f = new BrisaWebFile(sessionManager, filePath, this);
    files.append(f);
    addService(path, f);
}

/*!
 *  Call this method to add a BrisaWebStaticContent to the web service.
 */
void BrisaWebServiceProvider::addContent(const QString path, QString content)
{
    BrisaWebStaticContent *c = new BrisaWebStaticContent(sessionManager, content, this);
    this->content.append(c);
    addService(path, c);
}

/*!
 *  \class BrisaCore::BrisaWebserver brisawebserver.h BrisaCore/BrisaWebserver
 *  \brief The BrisaWebserver class is a web server implementation.
 *
 *  BrisaWebServer implements a Web Server using libQxt.
 */

/*!
 *  Constructor for BrisaWebServer
 */
BrisaWebserver::BrisaWebserver(const QHostAddress &host, quint16 port)
{
    QxtHttpSessionManager(this);
    rootService = new BrisaWebServiceProvider(this, this);

    setPort(port);
    setListenInterface(host);
    setConnector(HttpServer);
    setStaticContentService(rootService);
}

/*!
 *  Destructor for BrisaWebServer
 */
BrisaWebserver::~BrisaWebserver()
{
    delete rootService;
}

/*!
 *  Creates a new session and returns the session number.
 */
int BrisaWebserver::newSession()
{
    return QxtHttpSessionManager::newSession();
}

/*!
 *  Adds a service to the web server. The service url path will be added to the root of the server.
 */
void BrisaWebserver::addService(QString path, QxtWebServiceDirectory *service)
{
    rootService->addService(path, service);
}

/*!
 *  \internal
 *  This method dumps request information to the screen.
 */
void BrisaWebserver::incomingRequest(quint32 requestID, const QHttpRequestHeader &header, QxtWebContent *deviceContent)
{
    QxtHttpSessionManager::incomingRequest(requestID, header, deviceContent);
    qDebug() << requestID << " Request";
    qDebug() << "Method: " << header.method();
    qDebug() << "URI: " << header.path();
}

/*!
 *  Publishes a file to the root.
 */
void BrisaWebserver::publishFile(QString publishPath, QString filePath)
{
    // Publishing a file to the root
    rootService->addFile(publishPath, filePath);
}

/*!
 * \internal
 * Reimplemented from libQxt.
 */
static QString extractPathLevel(QxtWebRequestEvent *event)
{
    QString path = event->url.path();
    int pos = path.indexOf("/", 1); // the path always starts with /
    if (pos == -1)
        event->url.setPath(""); // cue to redirect to /service/
    else
        event->url.setPath(path.mid(pos));
    return path.mid(1, pos - 1);
}

/*!
 * \internal
 * Reimplemented from libQxt.
 */
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
