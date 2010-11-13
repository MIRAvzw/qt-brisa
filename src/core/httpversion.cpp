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

#include "httpversion.h"

HttpVersion::HttpVersion(int httpVersionMajor, int httpVersionMinor) :
        m_major(httpVersionMajor),
        m_minor(httpVersionMinor)
{
}

// a non-trivial constructor :)
// the commented code also works, but isn't a good code (slow,
// difficult ro understand, ...), I made it only for fun
HttpVersion::HttpVersion(const QByteArray &str) :
//        m_major((str.indexOf('/') != -1) && (str.indexOf('.', str.indexOf('/')) != -1) ?
//                str.mid(str.indexOf('/') + 1, str.indexOf('.', str.indexOf('/')) -
//                        str.indexOf('/') - 1).toInt() : 1),
//        m_minor((str.indexOf('/') != -1) && (str.indexOf('.', str.indexOf('/'))) ?
//                str.mid(str.indexOf('.', str.indexOf('/')) + 1).toInt() : 0)
        m_major(0),
        m_minor(0)
{
    if (!str.startsWith("HTTP/"))
        return;
    int indexOfSlash = str.indexOf('/');
    if (indexOfSlash != -1) {
        int indexOfDot = str.indexOf('.', indexOfSlash);
        if (indexOfDot != -1) {
            bool ok[2];

            int tmp[] =
            {str.mid(indexOfSlash + 1, indexOfDot - indexOfSlash - 1).toInt(ok),
             str.mid(indexOfDot + 1).toInt(ok + 1)};

            if (ok[0] && ok[1]) {
                m_major = tmp[0];
                m_minor = tmp[1];
            }
        }
    }
}

HttpVersion &HttpVersion::operator =(qreal version)
{
    m_major = version;
    m_minor = static_cast<int>(version * 10) % 10;
    return *this;
}
