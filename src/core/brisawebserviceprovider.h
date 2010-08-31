#include "brisaglobal.h"

#ifndef USE_NEW_BRISA_WEBSERVER

#ifndef _BRISAWEBSERVICEPROVIDER_H
#define _BRISAWEBSERVICEPROVIDER_H

#include <QtCore>
#include <QtNetwork>
#include "QxtHttpSessionManager"
#include <QxtWebServiceDirectory>
#include <QxtWebSlotService>
#include <QxtWebPageEvent>
#include <QxtWebContent>

#include "brisawebstaticcontent.h"
#include "brisawebfile.h"

namespace BrisaCore {

/*!
 *  \brief The BrisaWebServiceProvider class works as web service manager for the web server.
 *
 *  The BrisaWebServiceProvider has convenience methods for managing web services, like addFile()
 *  and addContent(). It also keeps track of all files and content stored into the web service.
 */
class BRISA_CORE_EXPORT BrisaWebServiceProvider: public QxtWebServiceDirectory {
Q_OBJECT

public:
    /*!
     *  Constructor for BrisaWebServiceProvider
     *
     *  \param sm \a empty
     *  \param parent \a empty
     */
    BrisaWebServiceProvider(QxtAbstractWebSessionManager *sm, QObject *parent);

    /*!
     *  Destructor for BrisaWebServiceProvider.
     */
    ~BrisaWebServiceProvider();

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
    void indexRequested(QxtWebRequestEvent *event);

private:
    BrisaWebStaticContent *root;
    QxtAbstractWebSessionManager *sessionManager;
    QList<BrisaWebFile*> files;
    QList<BrisaWebStaticContent*> content;
};

}

#endif /* _BRISAWEBSERVICEPROVIDER_H */

#endif // USE_NEW_BRISA_WEBSERVER
