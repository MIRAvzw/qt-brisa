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

#include "brisawebstaticcontent.h"
#include "brisawebserversession.h"

using namespace Brisa;

BrisaWebStaticContent::BrisaWebStaticContent(const QByteArray &content,
                                             QObject *parent) :
        BrisaWebService(parent),
        m_content(content)
{
}

BrisaWebStaticContent::~BrisaWebStaticContent()
{
}

QByteArray BrisaWebStaticContent::content() const
{
    return m_content;
}

void BrisaWebStaticContent::setContent(const QByteArray &content)
{
    m_content = content;
}

QByteArray BrisaWebStaticContent::contentType() const
{
    return m_contentType;
}

void BrisaWebStaticContent::setContentType(const QByteArray &contentType)
{
    m_contentType = contentType;
}

void BrisaWebStaticContent::onRequest(const HttpRequest &request,
                                      BrisaWebserverSession *session)
{
    HttpResponse response(request.httpVersion());

    response.setHeader("CONTENT-TYPE", m_contentType);
    response.setHeader("CONTENT-LENGTH", QByteArray::number(m_content.size()));
    response.setEntityBody(m_content);

    session->respond(response);
}
