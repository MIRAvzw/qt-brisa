#ifndef _BRISAWEBSERVICE_H
#define _BRISAWEBSERVICE_H

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

}

#endif /* _BRISAWEBSERVICE_H */
