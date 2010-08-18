#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H

#include "httpversion.h"
#include <QHash>
#include <QIODevice>

class HttpMessage
{
public:
    HttpMessage(HttpVersion httpVersion);
    ~HttpMessage();

    HttpVersion httpVersion() const;
    void setHttpVersion(const HttpVersion &version);

    QByteArray header(const QByteArray &name) const;
    /*
      if value is null, the header is removed (if exists)
      */
    void setHeader(const QByteArray &name, const QByteArray &value);
    QHash<QByteArray, QByteArray> headers() const;
    QHash<QByteArray, QByteArray>::const_iterator headersBeginIterator() const;
    QHash<QByteArray, QByteArray>::const_iterator headersEndIterator() const;

    qint64 entitySize() const;
    QByteArray entityBody() const;
    /*
      returns the number of bytes written or -1 if some error occurs
      */
    qint64 entityBody(QIODevice *device) const;
    void setEntityBody(const QByteArray &body);
    /*
      the \p bodyDevice must be opened in readMode and must be
      random-acess (not sequencial) device

      takes ownership of bodyDevice if successful
      */
    bool setEntityBody(QIODevice *bodyDevice);

private:
    HttpVersion m_httpVersion;

    // the maximum number of headers should be 64
    QHash<QByteArray, QByteArray> m_headers;

    QByteArray m_entityBody;
    QIODevice *m_entityBodyDevice;

    // chunk is a term generally used in images processing, i need to discover
    // the ideal term to this variable and refactor it
    static const int chunkSize;
};

inline HttpVersion HttpMessage::httpVersion() const
{
    return m_httpVersion;
}

inline QByteArray HttpMessage::header(const QByteArray &name) const
{
    return m_headers.value(name);
}

inline QHash<QByteArray, QByteArray> HttpMessage::headers() const
{
    return m_headers;
}

inline QHash<QByteArray, QByteArray>::const_iterator HttpMessage::headersBeginIterator() const
{
    return m_headers.begin();
}

inline QHash<QByteArray, QByteArray>::const_iterator HttpMessage::headersEndIterator() const
{
    return m_headers.end();
}

inline qint64 HttpMessage::entitySize() const
{
    if (m_entityBodyDevice) {
        return m_entityBodyDevice->size();
    } else {
        return m_entityBody.size();
    }
}

inline QByteArray HttpMessage::entityBody() const
{
    if (m_entityBodyDevice)
        return m_entityBodyDevice->readAll();
    else
        return m_entityBody;
}

#endif // HTTPMESSAGE_H
