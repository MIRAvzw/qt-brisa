/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Authors: Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com> 2010
 *
 * Copyright (C) <2010> <Pervasive Computing Laboratory @ Federal
 * University of Alagoas>
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

#ifndef _BRISAWEBSERVICE_H
#define _BRISAWEBSERVICE_H

#include <QtCore>
#include <QtNetwork>
#include "brisaglobal.h"

#ifdef USE_NEW_BRISA_WEBSERVER

#include "httprequest.h"

#else

#include "QxtHttpSessionManager"
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#endif // USE_NEW_BRISA_WEBSERVER

namespace BrisaCore {

#ifdef USE_NEW_BRISA_WEBSERVER

class BrisaWebserverSession;

class BRISA_CORE_EXPORT BrisaWebService: virtual public QObject
{
Q_OBJECT
public:
    BrisaWebService(QObject *parent = 0);
    virtual ~BrisaWebService();

    void postRequest(const HttpRequest &request, BrisaWebserverSession *session);

signals:
    void genericRequestReceived(HttpRequest, BrisaWebserverSession *session);

protected:
    virtual void onRequest(const HttpRequest &request, BrisaWebserverSession *session);
    QByteArray path()
    {
        return m_path;
    }

private:
    QByteArray m_path;

    friend class BrisaWebserver;
};

#else // !USE_NEW_BRISA_WEBSERVER

/*!
 *  \brief Web service abstraction class
 *
 *  BrisaWebService is used to receive and respond UPnP action and event requests. Currently this
 *  class is used mostly with BrisaService and BrisaEventController.
 *
 *  \sa BrisaUpnp::BrisaService , BrisaUpnp::BrisaEventController
 */
class BRISA_CORE_EXPORT BrisaWebService: public QxtWebServiceDirectory {
Q_OBJECT

public:
    /*!
     *  Constructor for BrisaWebService
     *
     *  \param sm Session manager
     *  \param parent parent
     */
    BrisaWebService(QxtAbstractWebSessionManager *sm, QObject *parent = 0);

    /*!
     *  Destructor for BrisaWebService
     */
    ~BrisaWebService() {
    }

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
    void pageRequestedEvent(QxtWebRequestEvent *event);

    /*!
     *  Responds \a response to the session and request ID currently stored in BrisaWebService, if using
     *  this method the response must be synchronous because the request and session ID can change
     *  quickly.
     *
     *  \param response \a empty
     */
    void respond(QByteArray response);

    /*!
     *  Reimplements respond().
     *  We recommend using this method given the fact that it supports asynchronous requests.
     *
     *  \param response \a empty
     *  \param sessionId \a empty
     *  \param requestId \a empty
     */
    void respond(const QByteArray &response, const int &sessionId,
            const int &requestId);

    /*!
     *  Reimplements respond()
     *  This method responds only a HTTP header to the session and request ID stored in BrisaWebService
     *
     *  \param response \a empty
     */
    void respond(const QHttpResponseHeader &response);

    /*!
     *  Reimplements respond().
     *  This method responds only a HTTP header using the given session and request ID.
     *
     *  \param response \a empty
     *  \param sessionId \a empty
     *  \param requestId \a empty
     */
    void respond(const QHttpResponseHeader &response, const int &sessionId,
            const int &requestId);

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
    void genericRequestReceived(const QString &method, const QMultiHash<
            QString, QString> &headers, const QByteArray &requestContent,
            int sessionId, int requestId);

    /*!
     *  Reimplements genericRequestReceived()
     *  This signal is emmited when BrisaWebService receives a request, the main difference is that this
     *  signal has a pointer to the class that is emmiting the signal.
     *
     *  \param service \a empty
     *  \param ? ?
     *  \param requestContent \a empty
     */
    void genericRequestReceived(BrisaWebService *service, QMultiHash<QString,
            QString> , QString requestContent);

private:
    int sessionID;
    int requestID;
};
#endif // USE_NEW_BRISA_WEBSERVER

}

#endif /* _BRISAWEBSERVICE_H */
