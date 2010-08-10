#include "httpversion.h"

HttpVersion::HttpVersion(int httpVersionMajor, int httpVersionMinor) :
        m_major(httpVersionMajor),
        m_minor(httpVersionMinor)
{
}

HttpVersion &HttpVersion::operator =(qreal version)
{
    m_major = version;
    m_minor = static_cast<int>(version * 10) % 10;
    return *this;
}
