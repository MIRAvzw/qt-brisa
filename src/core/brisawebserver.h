/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa / BRisa-Qt
 * Filename: brisaconfig.cpp
 * Created:
 * Description: Definition of BrisaWebserver class.
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


#ifndef _BRISAWEBSERVER_H
#define _BRISAWEBSERVER_H

#include <QtCore>
#include <QtNetwork>
#include "QxtHttpSessionManager"
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#include "brisaglobal.h"

#define DEFAULT_PAGE "<html><body><h1>BRisa WebServer!\n</body></html>"

namespace BrisaCore {

    /*!
     *  \brief Web service abstraction class
     *
     *  BrisaWebService is used to receive and respond UPnP action and event requests. Currently this
     *  class is used mostly with BrisaService and BrisaEventController.
     *
     *  \sa BrisaUpnp::BrisaService , BrisaUpnp::BrisaEventController
     */
    class BRISA_CORE_EXPORT BrisaWebService  : public QxtWebServiceDirectory
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebService
         *
         *  \param sm Session manager
         *  \param parent parent
         */
        BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent = 0) :
                QxtWebServiceDirectory(sm, parent) {}

        /*!
         *  Destructor for BrisaWebService
         */
        ~BrisaWebService() {}

    public slots:
        /*!
         *
         *  This method receives all web service requests and emits a genericRequestReceived() signal. If
         *  the request method is of "POST" type, the web service will reply a default message.
         *
         *  Note: Reimplemented from libQxt.
         *
         *  \param event \a empty
         */
        void pageRequestedEvent(QxtWebRequestEvent *event)
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

        /*!
         *  Responds \a response to the session and request ID currently stored in BrisaWebService, if using
         *  this method the response must be synchronous because the request and session ID can change
         *  quickly.
         *
         *  \param response \a empty
         */
        void respond(QByteArray response)
        {
            this->respond(response, this->sessionID, this->requestID);
        }

        /*!
         *  Reimplements respond().
         *  We recommend using this method given the fact that it supports asynchronous requests.
         *
         *  \param response \a empty
         *  \param sessionId \a empty
         *  \param requestId \a empty
         */
        void respond(const QByteArray &response, const int &sessionId, const int &requestId)
        {
            this->postEvent(new QxtWebPageEvent(sessionId, requestId, response));
        }

        /*!
         *  Reimplements respond()
         *  This method responds only a HTTP header to the session and request ID stored in BrisaWebService
         *
         *  \param response \a empty
         */
        void respond(const QHttpResponseHeader &response)
        {
            this->respond(response, this->sessionID, this->requestID);
        }

        /*!
         *  Reimplements respond().
         *  This method responds only a HTTP header using the given session and request ID.
         *
         *  \param response \a empty
         *  \param sessionId \a empty
         *  \param requestId \a empty
         */
        void respond(const QHttpResponseHeader &response, const int &sessionId,
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

    signals:
        /*!
         *  This signal is emmited when BrisaWebService receives a request.
         *
         *  \param method \a empty
         *  \param headers \a empty
         *  \param requestContent \a empty
         *  \param sessionId \a empty
         *  \param requestId \a empty
         */
        void genericRequestReceived(const QString &method,
                                    const QMultiHash<QString, QString> &headers,
                                    const QByteArray &requestContent,
                                    int sessionId,
                                    int requestId);

        /*!
         *  Reimplements genericRequestReceived()
         *  This signal is emmited when BrisaWebService receives a request, the main difference is that this
         *  signal has a pointer to the class that is emmiting the signal.
         *
         *  \param service \a empty
         *  \param ? ?
         *  \param requestContent \a empty
         */
        void genericRequestReceived(BrisaWebService *service,
                                    QMultiHash<QString, QString>,
                                    QString requestContent);

    private:
        int sessionID;
        int requestID;
    };


    /*!
     *  \brief Adds a file to the web server.
     *
     *  Use this class to store a file into the web server. If the BrisaWebFile is stored using a
     *  BrisaWebServiceProvider, it's url path will be of "IP:PORT/SERVICENAME/yourfile". if it's stored
     *  using the BrisaWebServer convenience method \a "publishFile()", it's url path will be
     *  "IP:PORT/yourfile".
     */
    class BRISA_CORE_EXPORT BrisaWebFile : public QxtAbstractWebService
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebFile. It creates a QFile with the given file path.
         *
         *  \param sm \a empty
         *  \param filePath \a empty
         *  \param parent \a empty
         */
        BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath, QObject *parent = 0) :
                QxtAbstractWebService(sm, parent)
        {
            file = new QFile(filePath);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                throw "Could not open file for read.";
        }

        /*!
         *  Destructor for BrisaWebFile.
         */
        ~BrisaWebFile()
        {
            delete file;
        }

        /*!
         *  Reimplemented from libQxt. When a request is received the BrisaWebFile will reply the stored
         *  file.
         *
         *  \param event \a empty
         */
        void pageRequestedEvent(QxtWebRequestEvent *event)
        {
            QxtWebPageEvent *c =
                    new QxtWebPageEvent(event->sessionID, event->requestID, file->readAll());
            c->contentType = "text/xml";
            postEvent(c);
            file->reset();
        }

    private:
        QFile *file;
    };


    /*!
     *  \brief The BrisaWebStaticContent class stores a QString into the web server.
     *
     *  Use this class to store static content in the web server using a string format.
     */
    class BRISA_CORE_EXPORT BrisaWebStaticContent : public QxtWebSlotService
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebStaticContent. Stores the given QString.
         *
         *  \param sm \a empty
         *  \param content \a empty
         *  \param parent \a empty
         */
        BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
                              QString content,
                              QObject *parent = 0) :
        QxtWebSlotService(sm, parent)
        {
            this->content = new QString(content);
        }

        /*!
         *  Destructor for BrisaWebStaticContent.
         */
        ~BrisaWebStaticContent()
        {
            delete content;
        }

    public slots:
        /*!
         *  This method is called by BrisaWebServiceProvider, it replys the stored content.
         *
         *  \param event \a empty
         */
        void index(QxtWebRequestEvent *event)
        {
            postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, content->toUtf8()));
        }

    private:
        QString *content;
    };


    /*!
     *  \brief The BrisaWebServiceProvider class works as web service manager for the web server.
     *
     *  The BrisaWebServiceProvider has convenience methods for managing web services, like addFile()
     *  and addContent(). It also keeps track of all files and content stored into the web service.
     */
    class BRISA_CORE_EXPORT BrisaWebServiceProvider : public QxtWebServiceDirectory
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebServiceProvider
         *
         *  \param sm \a empty
         *  \param parent \a empty
         */
        BrisaWebServiceProvider(QxtAbstractWebSessionManager *sm, QObject *parent) :
                QxtWebServiceDirectory(sm, parent)
        {
            root = new BrisaWebStaticContent(sm, DEFAULT_PAGE, this);
            sessionManager = sm;
        }

        /*!
         *  Destructor for BrisaWebServiceProvider.
         */
        ~BrisaWebServiceProvider()
        {
            delete root;
            while (!files.isEmpty())
                delete files.takeFirst();
        }

        /*!
         *  Call this method to add a BrisaWebFile to the web service.
         *
         *  \param path \a empty
         *  \param filePath \a empty
         */
        void addFile(const QString path, QString filePath);

        /*!
         *  Call this method to add a BrisaWebStaticContent to the web service.
         *
         *  \param path \a empty
         *  \param content \a empty
         */
        void addContent(const QString path, QString content);
        /*!
         * Reimplemented from libQxt.
         */
        void pageRequestedEvent(QxtWebRequestEvent *event);

    protected:
        /*!
         *  Reimplemented from libQxt.
         *  This method calls the BrisaWebStaticContent \a index() method.
         *
         *  \param event \a empty
         */
        void indexRequested(QxtWebRequestEvent *event)
        {
            //TODO: fix it
            root->index(event);
        }

    private:
        BrisaWebStaticContent *root;
        QxtAbstractWebSessionManager *sessionManager;
        QList<BrisaWebFile*> files;
        QList<BrisaWebStaticContent*> content;
    };


    /*!
     *  \brief The BrisaWebserver class is a web server implementation.
     *
     *  BrisaWebServer implements a Web Server using libQxt.
     */
    class BRISA_CORE_EXPORT BrisaWebserver : public QxtHttpSessionManager
    {
        Q_OBJECT

    public:
        /*!
         *  Constructor for BrisaWebServer
         *
         *  \param host \a empty
         *  \param port \a empty
         */
        BrisaWebserver(const QHostAddress &host, quint16 port);

        /*!
         *  Destructor for BrisaWebServer
         */
        ~BrisaWebserver();

        /*!
         *  Publishes a file to the root.
         *
         *  \param publishPath \a empty
         *  \param filePath \a empty
         */
        void publishFile(QString publishPath, QString filePath);

        /*!
         *  Adds a service to the web server. The service url path will be added to the root of the server.
         *
         *  \param path \a empty
         *  \param service \a empty
         */
        void addService(QString path, QxtWebServiceDirectory *service);

    protected:
        /*!
         *  This method dumps request information to the screen.
         *
         *  \param requestID \a empty
         *  \param header \a empty
         *  \param deviceContent \a empty
         */
        void incomingRequest(quint32 requestID, const QHttpRequestHeader &header,
                             QxtWebContent *deviceContent);
        /*!
         *  Creates a new session and returns the session number.
         */
        int newSession();

    private:
        BrisaWebServiceProvider *rootService;
    };

};

#endif /* _BRISAWEBSERVER_H */
