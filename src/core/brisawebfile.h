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

#include "brisawebservice.h"

namespace Brisa {

    class BRISA_CORE_EXPORT BrisaWebFile: public Brisa::BrisaWebService
    {
    Q_OBJECT
    public:
        BrisaWebFile(const QString &filePath = QString(), QObject *parent = 0);
        ~BrisaWebFile();

        QString fileName() const;
        void setFile(const QString &fileName);

        QByteArray contentType() const;
        void setContentType(const QByteArray &);

        bool useChunkedEntities() const;
        void setUseChunkedEntities(bool);

    protected:
        void onRequest(const HttpRequest &request, BrisaWebserverSession *session);

    private:
        QString m_fileName;
        QByteArray m_contentType;
        bool m_useChunkedEntities;
    };

    inline QString BrisaWebFile::fileName() const
    {
        return m_fileName;
    }

    inline QByteArray BrisaWebFile::contentType() const
    {
        return m_contentType;
    }

    inline bool BrisaWebFile::useChunkedEntities() const
    {
        return m_useChunkedEntities;
    }

}

#endif /* _BRISA_WEB_FILE_H */
