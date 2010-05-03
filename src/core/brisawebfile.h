#ifndef _BRISA_WEB_FILE_H
#define _BRISA_WEB_FILE_H

#include <QtCore>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>

#include "brisaglobal.h"

namespace BrisaCore {

/*!
 *  \brief Adds a file to the web server.
 *
 *  Use this class to store a file into the web server. If the BrisaWebFile is stored using a
 *  BrisaWebServiceProvider, it's url path will be of "IP:PORT/SERVICENAME/yourfile". if it's stored
 *  using the BrisaWebServer convenience method \a "publishFile()", it's url path will be
 *  "IP:PORT/yourfile".
 */
class BRISA_CORE_EXPORT BrisaWebFile: public QxtAbstractWebService {
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

#endif /* _BRISA_WEB_FILE_H */
