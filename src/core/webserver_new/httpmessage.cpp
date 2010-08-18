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
