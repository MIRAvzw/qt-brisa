#include "brisaglobal.h"

#ifndef _BRISA_WEB_FILE_H
#define _BRISA_WEB_FILE_H

#include <QtCore>

#ifdef USE_NEW_BRISA_WEBSERVER

#include "brisawebservice.h"

#else // !USE_NEW_BRISA_WEBSERVER

#include <QxtWebSlotService>
#include <QxtWebPageEvent>

#endif // USE_NEW_BRISA_WEBSERVER

namespace BrisaCore {

#ifdef USE_NEW_BRISA_WEBSERVER

    class BRISA_CORE_EXPORT BrisaWebFile: public BrisaWebService
    {
    Q_OBJECT
    public:
        BrisaWebFile(const QString &filePath = QString(), QObject parent = 0);
        ~BrisaWebFile();

        QString fileName() const;
        void setFile(const QString &fileName);

    protected:
        void onRequest(const HttpRequest &request, BrisaWebserverSession *session);

    private:
        QString m_fileName;
    };

#else // !USE_NEW_BRISA_WEBSERVER

/*!
 *  \brief Adds a file to the web server.
 *
 *  Use this class to store a file into the web server. If the BrisaWebFile is stored using a
 *  BrisaWebServiceProvider, it's url path will be of "IP:PORT/SERVICENAME/yourfile". if it's stored
 *  using the BrisaWebServer convenience method \a "publishFile()", it's url path will be
 *  "IP:PORT/yourfile".
 */

class BRISA_CORE_EXPORT BrisaWebFile: public QxtAbstractWebService
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
    BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath,
            QObject *parent = 0);

    /*!
     *  Destructor for BrisaWebFile.
     */
    ~BrisaWebFile();

    /*!
     *  Reimplemented from libQxt. When a request is received the BrisaWebFile will reply the stored
     *  file.
     *
     *  \param event \a empty
     */
    void pageRequestedEvent(QxtWebRequestEvent *event);

private:
    QFile *file;
};

}

#endif // USE_NEW_BRISA_WEBSERVER

#endif /* _BRISA_WEB_FILE_H */
