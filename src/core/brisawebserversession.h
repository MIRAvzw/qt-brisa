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

#if !defined(BRISAWEBSERVERSESSION_H) && defined(USE_NEW_BRISA_WEBSERVER)
#define BRISAWEBSERVERSESSION_H

#include "webserver_new/httpsession.h"

namespace BrisaCore
{
    class BrisaWebserver;
}

namespace BrisaCore {

class BrisaWebserverSession : public HttpSession
{
Q_OBJECT
public:
    BrisaWebserverSession(int socketDescriptor, BrisaWebserver *server);
    ~BrisaWebserverSession();

    int isRequestSupported(const HttpRequest &request) const;

protected:
    bool hasEntityBody(const HttpRequest &request) throw(HttpResponse);
    bool atEnd(const HttpRequest &request, const QByteArray &buffer) throw(HttpResponse);
    HttpResponse onRequest(const HttpRequest &request);

private:
    BrisaWebserver *server;
    int entitySize;
};

} // namespace BrisaCore

#endif // BRISAWEBSERVERSESSION_H