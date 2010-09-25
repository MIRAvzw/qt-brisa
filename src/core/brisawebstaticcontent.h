#include "brisaglobal.h"

#ifndef _BRISAWEBSTATICCONTENT_H
#define _BRISAWEBSTATICCONTENT_H

#include <QtCore>
#include <QtNetwork>
#include "brisawebservice.h"

#ifndef USE_NEW_BRISA_WEBSERVER

#include "QxtHttpSessionManager"
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#endif // USE_NEW_BRISA_WEBSERVER

namespace BrisaCore {

#ifdef USE_NEW_BRISA_WEBSERVER

    class BrisaWebStaticContent: public BrisaWebService
    {
    Q_OBJECT
    public:
        BrisaWebStaticContent(const QByteArray &content = "", QObject parent = 0);
        ~BrisaWebStaticContent();

        QByteArray content() const;
        void setContent(const QByteArray &content);

        QByteArray contentType() const;
        void setContentType(const QByteArray &contentType);

    protected:
        void onRequest(const HttpRequest &request, BrisaWebserverSession *session);

    private:
        QByteArray m_content;
        QByteArray m_contentType;
    };

#else // !USE_NEW_BRISA_WEBSERVER

/*!
 *  \brief The BrisaWebStaticContent class stores a QString into the web server.
 *
 *  Use this class to store static content in the web server using a string format.
 */
class BRISA_CORE_EXPORT BrisaWebStaticContent: public QxtWebSlotService {
Q_OBJECT

public:
    /*!
     *  Constructor for BrisaWebStaticContent. Stores the given QString.
     *
     *  \param sm \a empty
     *  \param content \a empty
     *  \param parent \a empty
     */
    BrisaWebStaticContent(QxtAbstractWebSessionManager *sm, QString content,
            QObject *parent = 0);

    /*!
     *  Destructor for BrisaWebStaticContent.
     */
    ~BrisaWebStaticContent();

public slots:
    /*!
     *  This method is called by BrisaWebServiceProvider, it replys the stored content.
     *
     *  \param event \a empty
     */
    void index(QxtWebRequestEvent *event);

private:
    QString *content;
};

#endif // USE_NEW_BRISA_WEBSERVER

}

#endif /* _BRISAWEBSTATICCONTENT_H */
