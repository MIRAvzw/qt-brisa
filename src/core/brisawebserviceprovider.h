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

#include "brisaglobal.h"

#if !defined(_BRISAWEBSERVICEPROVIDER_H) && !defined(USE_NEW_BRISA_WEBSERVER)
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

namespace Brisa {

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
