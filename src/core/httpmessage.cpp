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

#include "httpmessage.h"
#include <QBuffer>

using namespace Brisa;

HttpMessage::HttpMessage(HttpVersion httpVersion) :
        m_httpVersion(httpVersion),
        m_entityBody(NULL)
{
}

HttpMessage::HttpMessage(const HttpMessage &m) :
        m_httpVersion(m.m_httpVersion),
        m_headers(m.m_headers),
        m_entityBody(m.m_entityBody),
        m_range(m.m_range)
{
    m.m_entityBody = NULL;
}

HttpMessage::~HttpMessage()
{
    if (m_entityBody)
        m_entityBody->deleteLater();
}

void HttpMessage::setHttpVersion(const HttpVersion &version)
{
    m_httpVersion = version;
}

void HttpMessage::setHeader(const QByteArray &name, const QByteArray &value)
{
    if (!name.isEmpty()) {
        if (!value.isNull())
            // sets the value
            m_headers[name.toUpper()] = value;
        else
            // erases the header
            m_headers.remove(name.toUpper());
    }
}

void HttpMessage::setEntityBody(const QByteArray &body)
{
    if (m_entityBody && !dynamic_cast<QBuffer *>(m_entityBody)) {
        m_entityBody->deleteLater();
        m_entityBody = NULL;
    }

    if (m_entityBody)
        m_entityBody->close();
    else
        m_entityBody = new QBuffer;

    static_cast<QBuffer *>(m_entityBody)->setData(body);

    m_entityBody->open(QIODevice::ReadOnly);
}

bool HttpMessage::setEntityBody(QIODevice *bodyDevice)
{
    if (!bodyDevice->isReadable() || bodyDevice->isSequential())
        return false;

    if (m_entityBody)
        m_entityBody->deleteLater();

    m_entityBody = bodyDevice;
    m_entityBody->setParent(NULL);

    return true;
}

void HttpMessage::clear()
{
    m_headers.clear();

    if (m_entityBody)
        delete m_entityBody;

    m_range.first = 0;
    m_range.second = 0;

    m_entityBody = NULL;
}

void HttpMessage::setRange(const QPair<qlonglong, qlonglong> &range)
{
    m_range = range;
}
