#ifndef HTTPVERSION_H
#define HTTPVERSION_H

#include <QtGlobal>

class HttpVersion
{
public:
    HttpVersion(int httpVersionMajor = 1, int httpVersionMinor = 1);

    int major() const;
    int minor() const;

    void setMajor(int);
    void setMinor(int);

    bool operator==(qreal);
    HttpVersion &operator=(qreal);

//    QByteArray operator() const;

private:
    int m_major;
    int m_minor;
};

inline int HttpVersion::minor() const
{
    return m_minor;
}

#endif // HTTPVERSION_H
