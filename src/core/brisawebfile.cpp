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

#include "brisawebfile.h"

#include "brisawebserversession.h"
#include "httpresponse.h"
#include <QScopedPointer>

using namespace Brisa;

BrisaWebFile::BrisaWebFile(const QString &fileName, QObject *parent) :
        BrisaWebService(parent),
        m_fileName(fileName),
        m_useChunkedEntities(false)
{
}

BrisaWebFile::~BrisaWebFile()
{
}

void BrisaWebFile::setFile(const QString &fileName)
{
    m_fileName = fileName;
}

void BrisaWebFile::setContentType(const QByteArray &cT)
{
    m_contentType = cT;
}

void BrisaWebFile::setUseChunkedEntities(bool u)
{
    m_useChunkedEntities = u;
}

void BrisaWebFile::onRequest(const HttpRequest &request,
                             BrisaWebserverSession *session)
{
    HttpResponse response(request.httpVersion());

    QScopedPointer<QFile> file(new QFile(m_fileName));
    file->open(QIODevice::ReadOnly);

    const qint64 fileSize = file->size();

    if (!m_contentType.isEmpty())
        response.setHeader("CONTENT-TYPE", m_contentType);

    if (request.header("ACCEPT-RANGES") == "bytes")
        response.setHeader("ACCEPT-RANGES", "bytes");

    if (!request.header("RANGE").isEmpty()) {
        QByteArray rangeHeader = request.header("RANGE");

        // from begin of range to the end of the file
        if (rangeHeader.indexOf('-') == -1) {
            // 6 = QByteArray("bytes=").size()
            QByteArray firstBytePos = rangeHeader
                                      .mid(rangeHeader.indexOf("bytes=") + 6);

            bool ok;
            qlonglong firstByte = firstBytePos.toLongLong(&ok);

            if (ok) {
                response.setRange(QPair<qlonglong, qlonglong>(firstByte,
                                                              fileSize - 1));
                response.setStatusCode(HttpResponse::PARTIAL_CONTENT);
            }
        } else {
            QByteArray firstBytePos = rangeHeader
                                      .mid(rangeHeader.indexOf("bytes=") + 6,
                                           rangeHeader.indexOf('-') - 6);
            QByteArray lastBytePos = rangeHeader.mid(rangeHeader.indexOf('-') + 1);

            // has initial bytePos
            if (!firstBytePos.isEmpty()) {
                bool ok[2];
                qlonglong firstByte = firstBytePos.toLongLong(ok);
                qlonglong lastByte = lastBytePos.toLongLong(ok + 1);

                if (ok[0]) {
                    if (ok[1]) {
                        if (firstByte < lastByte) {
                            response.setRange(QPair<qlonglong, qlonglong>(firstByte,
                                                                          lastByte));
                            response.setStatusCode(HttpResponse::PARTIAL_CONTENT);
                        }
                    } else {
                        response.setRange(QPair<qlonglong, qlonglong>(firstByte,
                                                                      fileSize - 1));
                    }
                }
            } else {
                bool ok;
                qlonglong lastBytes = lastBytePos.toLongLong(&ok);

                if (ok) {
                    response.setRange(QPair<qlonglong, qlonglong>(fileSize - lastBytes,
                                                                  fileSize - 1));
                    response.setStatusCode(HttpResponse::PARTIAL_CONTENT);
                }
            }
        }
    }

    response.setEntityBody(file.take());

    session->respond(response, m_useChunkedEntities);
}
