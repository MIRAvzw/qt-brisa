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

const int HttpMessage::chunkSize = 64;

HttpMessage::HttpMessage(HttpVersion httpVersion) :
        m_httpVersion(httpVersion),
        m_entityBodyDevice(NULL)
{
}

HttpMessage::~HttpMessage()
{
    if (m_entityBodyDevice)
        m_entityBodyDevice->deleteLater();
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
            m_headers[name] = value;
        else
            // erases the header
            m_headers.remove(name);
    }
}

qint64 HttpMessage::entityBody(QIODevice *device) const
{
    if (!device->isWritable())
        return -1;

    qint64 numberByteWritten = 0;

    if (m_entityBodyDevice) {
        m_entityBodyDevice->seek(0);
        while (!m_entityBodyDevice->atEnd())
            numberByteWritten += device->write(m_entityBodyDevice->read(chunkSize));
    } else {
        numberByteWritten += device->write(m_entityBody);
    }

    return numberByteWritten;
}

void HttpMessage::setEntityBody(const QByteArray &body)
{
    if (m_entityBodyDevice) {
        m_entityBodyDevice->deleteLater();
        m_entityBodyDevice = NULL;
    }
    m_entityBody = body;
}

bool HttpMessage::setEntityBody(QIODevice *bodyDevice)
{
    if (!bodyDevice->isReadable() || bodyDevice->isSequential())
        return false;

    if (m_entityBodyDevice) {
        m_entityBodyDevice->deleteLater();
        m_entityBodyDevice = NULL;
    } else {
        m_entityBody.clear();
    }

    m_entityBodyDevice = bodyDevice;
    m_entityBodyDevice->setParent(NULL);

    return true;
}
