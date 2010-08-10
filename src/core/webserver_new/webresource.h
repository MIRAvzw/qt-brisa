#ifndef WEBRESOURCE_H
#define WEBRESOURCE_H

#include <QByteArray>

class WebResourceIdentifier
{
public:
    WebResourceIdentifier() {}
    WebResourceIdentifier(const QByteArray &uri, const QByteArray &host = QByteArray());
    WebResourceIdentifier(const char *uri, const QByteArray &host = QByteArray());
    WebResourceIdentifier(const char *uri, const char *host);

    bool operator==(const WebResourceIdentifier &r) const;

    QByteArray host;
    QByteArray uri;
};

class WebResource
{
public:
    WebResource() {}
    WebResource(const QString &fileName, const QByteArray &contentType = QByteArray()) :
            fileName(fileName),
            contentType(contentType)
    {
    }
    WebResource(const char *fileName, const QByteArray &contentType = QByteArray()) :
            fileName(fileName),
            contentType(contentType)
    {
    }
    WebResource(const char *fileName, const char *contentType) :
            fileName(fileName),
            contentType(contentType)
    {
    }

    QString fileName;
    QByteArray contentType;
};

inline WebResourceIdentifier::WebResourceIdentifier(const QByteArray &uri, const QByteArray &host) :
    host(host),
    uri(uri)
{
}

inline WebResourceIdentifier::WebResourceIdentifier(const char *uri, const QByteArray &host) :
    host(host),
    uri(uri)
{
}

inline WebResourceIdentifier::WebResourceIdentifier(const char *uri, const char *host) :
        host(host),
        uri(uri)
{
}

inline bool WebResourceIdentifier::operator==(const WebResourceIdentifier &r) const
{
    return (this->host == r.host) && (this->uri == r.uri);
}

inline uint qHash(const WebResourceIdentifier &r)
{
    uint sum = qChecksum(r.host.constData(), r.host.size());
    sum += qChecksum(r.uri.constData(), r.uri.size());
    return sum;
}

#endif // WEBRESOURCE_H
