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

#include "brisawebserviceprovider.h"

#ifndef USE_NEW_BRISA_WEBSERVER

#define DEFAULT_PAGE "<html><body><h1>BRisa WebServer!</h1></body></html>\n"

using namespace BrisaCore;

/*
 * Reimplemented from libQxt.
 */
inline QString extractPathLevel(QxtWebRequestEvent *event);

BrisaWebServiceProvider::BrisaWebServiceProvider(
        QxtAbstractWebSessionManager *sm, QObject *parent) :
    QxtWebServiceDirectory(sm, parent)
{
    root = new BrisaWebStaticContent(sm, QByteArray(DEFAULT_PAGE), this);
    sessionManager = sm;
}

BrisaWebServiceProvider::~BrisaWebServiceProvider()
{
    delete root;
    while (!files.isEmpty())
        delete files.takeFirst();
}

void BrisaWebServiceProvider::addFile(const QString path, QString filePath)
{
    BrisaWebFile *f = new BrisaWebFile(sessionManager, filePath, this);
    files.append(f);
    addService(path, f);
}

void BrisaWebServiceProvider::addContent(const QString path, QString content)
{
    BrisaWebStaticContent *c = new BrisaWebStaticContent(sessionManager,
            content, this);
    this->content.append(c);
    addService(path, c);
}

void BrisaWebServiceProvider::indexRequested(QxtWebRequestEvent *event)
{
    //TODO: fix it
    root->index(event);
}

void BrisaWebServiceProvider::pageRequestedEvent(QxtWebRequestEvent *event)
{
    QString path = extractPathLevel(event);
    if (path.isEmpty()) {
        indexRequested(event);
    } else if (!service(path)) {
        unknownServiceRequested(event, path);
    } else {
        service(path)->pageRequestedEvent(event);
    }
}

inline QString extractPathLevel(QxtWebRequestEvent *event)
{
    QString path = event->url.path();
    // the path always starts with /
    int pos = path.indexOf("/", 1);
    if (pos == -1)
        // cue to redirect to /service/
        event->url.setPath("");
    else
        event->url.setPath(path.mid(pos));
    return path.mid(1, pos - 1);
}

#endif // USE_NEW_BRISA_WEBSERVER
