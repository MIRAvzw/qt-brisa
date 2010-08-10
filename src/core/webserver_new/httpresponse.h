#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include "httpversion.h"
#include <QHash>

class HttpResponse
{
public:
    HttpResponse(const HttpVersion &httpVersion, int statusCode = 200,
                 const QByteArray &reasonPhrase = "OK");

    HttpVersion httpVersion() const;
    void setHttpVersion(const HttpVersion &version);

    int statusCode() const;
    bool setStatusCode(int st);
    bool setStatusCode(int st, const QByteArray &reasonPhrase);

    QByteArray reasonPhrase() const;
    void setReasonPhrase(const QByteArray &reasonPhrase);

    QByteArray body() const;
    void setBody(const QByteArray &body);

    QHash<QByteArray, QByteArray> headers() const;
    void setHeader(const QByteArray &name, const QByteArray &value);
    void removeHeader(const QByteArray &name);
    QByteArray header(const QByteArray &name) const;

private:
    HttpVersion m_httpVersion;
    int m_statusCode;
    QByteArray m_reasonPhrase;

    QHash<QByteArray, QByteArray> m_headers;

    QByteArray m_body;
};

#endif // HTTPRESPONSE_H
