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

    class BRISA_CORE_EXPORT BrisaWebFile: public ::BrisaCore::BrisaWebService
    {
    Q_OBJECT
    public:
        BrisaWebFile(const QString &filePath = QString(), QObject *parent = 0);
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

#endif // USE_NEW_BRISA_WEBSERVER

}

#endif /* _BRISA_WEB_FILE_H */
