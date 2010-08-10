#include "httpresponse.h"

HttpResponse::HttpResponse(const HttpVersion &httpVersion, int statusCode,
                           const QByteArray &reasonPhrase) :
    m_httpVersion(httpVersion),
    m_statusCode(statusCode),
    m_reasonPhrase(reasonPhrase)
{
}

int HttpResponse::statusCode() const
{
    return m_statusCode;
}

QByteArray HttpResponse::reasonPhrase() const
{
    return m_reasonPhrase;
}

QHash<QByteArray, QByteArray> HttpResponse::headers() const
{
    return m_headers;
}

QByteArray HttpResponse::body() const
{
    return m_body;
}

void HttpResponse::setBody(const QByteArray &body)
{
    m_body = body;
}

bool HttpResponse::setStatusCode(int st, const QByteArray &reasonPhrase)
{
    m_statusCode = st;
    m_reasonPhrase = reasonPhrase;
    return true;
}

void HttpResponse::setHeader(const QByteArray &name, const QByteArray &value)
{
    m_headers[name] = value;
}

QByteArray HttpResponse::header(const QByteArray &name) const
{
    return m_headers.value(name);
}

HttpVersion HttpResponse::httpVersion() const
{
    return m_httpVersion;
}
