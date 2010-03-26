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

#ifndef _BRISAWEBSERVER_H
#define _BRISAWEBSERVER_H

#include <QtCore>
#include <QtNetwork>
#include <QxtHttpSessionManager>
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#include "brisaglobal.h"

#define DEFAULT_PAGE "<html><body><h1>BRisa WebServer!\n</body></html>"

namespace BrisaCore {

class BRISA_CORE_EXPORT BrisaWebService  : public QxtWebServiceDirectory
{
    Q_OBJECT

    public:
        BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent = 0) :
            QxtWebServiceDirectory(sm, parent) {}

        ~BrisaWebService() {}

    public slots:
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

        void respond(QByteArray response)
        {
            this->respond(response, this->sessionID, this->requestID);
        }
        void respond(const QByteArray &response, const int &sessionId, const int &requestId)
        {
            this->postEvent(new QxtWebPageEvent(sessionId, requestId, response));
        }
        void respond(const QHttpResponseHeader &response)
        {
            this->respond(response, this->sessionID, this->requestID);
        }
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
        void genericRequestReceived(const QString &method,
                                    const QMultiHash<QString, QString> &headers,
                                    const QByteArray &requestContent,
                                    int sessionId,
                                    int requestId);
        void genericRequestReceived(BrisaWebService *service,
                                    QMultiHash<QString, QString>,
                                    QString requestContent);

    private:
        int sessionID;
        int requestID;
};


class BRISA_CORE_EXPORT BrisaWebFile : public QxtAbstractWebService
{
    Q_OBJECT

    public:
        BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath, QObject *parent = 0) :
            QxtAbstractWebService(sm, parent)
        {
            file = new QFile(filePath);
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
                throw "Could not open file for read.";
        }

        ~BrisaWebFile()
        {
            delete file;
        }

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


class BRISA_CORE_EXPORT BrisaWebStaticContent : public QxtWebSlotService
{
    Q_OBJECT

    public:
        BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
                              QString content,
                              QObject *parent = 0) :
            QxtWebSlotService(sm, parent)
        {
            this->content = new QString(content);
        }

        ~BrisaWebStaticContent()
        {
            delete content;
        }

    public slots:
        void index(QxtWebRequestEvent *event)
        {
            postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, content->toUtf8()));
        }

    private:
        QString *content;
};


class BRISA_CORE_EXPORT BrisaWebServiceProvider : public QxtWebServiceDirectory
{
    Q_OBJECT

    public:
        BrisaWebServiceProvider(QxtAbstractWebSessionManager *sm, QObject *parent) :
            QxtWebServiceDirectory(sm, parent)
        {
            root = new BrisaWebStaticContent(sm, DEFAULT_PAGE, this);
            sessionManager = sm;
        }

        ~BrisaWebServiceProvider()
        {
            delete root;
            while (!files.isEmpty())
                delete files.takeFirst();
        }

        void addFile(const QString path, QString filePath);
        void addContent(const QString path, QString content);
        void pageRequestedEvent(QxtWebRequestEvent *event);

    protected:
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


class BRISA_CORE_EXPORT BrisaWebserver : public QxtHttpSessionManager
{
    Q_OBJECT

    public:
        BrisaWebserver(const QHostAddress &host, quint16 port);
        ~BrisaWebserver();
        void publishFile(QString publishPath, QString filePath);
        void addService(QString path, QxtWebServiceDirectory *service);

    protected:
        void incomingRequest(quint32 requestID, const QHttpRequestHeader &header,
                             QxtWebContent *deviceContent);
        int newSession();

    private:
        BrisaWebServiceProvider *rootService;
};

};

#endif /* _BRISAWEBSERVER_H */
