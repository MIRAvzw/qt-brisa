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

#ifdef USE_NEW_BRISA_WEBSERVER

#include "brisawebserversession.h"
#include "httpresponse.h"

using namespace BrisaCore;

BrisaWebFile::BrisaWebFile(const QString &fileName, QObject *parent) :
        BrisaWebService(parent),
        m_fileName(fileName)
{
}

BrisaWebFile::~BrisaWebFile()
{
}

QString BrisaWebFile::fileName() const
{
    return m_fileName;
}

void BrisaWebFile::setFile(const QString &fileName)
{
    m_fileName = fileName;
}

void BrisaWebFile::onRequest(const HttpRequest &request,
                             BrisaWebserverSession *session)
{
    HttpResponse response(request.httpVersion());

    QFile *file = new QFile(m_fileName);
    file->open(QIODevice::ReadOnly);
    //    response.setHeader("CONTENT-TYPE", ); // TODO
    response.setHeader("CONTENT-LENGTH", QByteArray::number(file->size()));

    response.setEntityBody(file);

    session->respond(response);
}

#else // !USE_NEW_BRISA_WEBSERVER

using namespace BrisaCore;

BrisaWebFile::BrisaWebFile(QxtAbstractWebSessionManager *sm, QString filePath,
        QObject *parent) :
    QxtAbstractWebService(sm, parent) {
    file = new QFile(filePath);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        throw "Could not open file for read.";
}

BrisaWebFile::~BrisaWebFile() {
    delete file;
}

void BrisaWebFile::pageRequestedEvent(QxtWebRequestEvent *event) {
    QxtWebPageEvent *c = new QxtWebPageEvent(event->sessionID,
            event->requestID, file->readAll());
    c->contentType = "text/xml";
    postEvent(c);
    file->reset();
}

#endif // USE_NEW_BRISA_WEBSERVER
