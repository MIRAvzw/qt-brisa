/* brisa-c++
 *
 * This file is part of brisa-c++.
 *
 * brisa-c++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * brisa-c++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with brisa-c++.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _BRISAICON_H
#define _BRISAICON_H

#include <QString>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaIcon
{
    public:
        BrisaIcon(QString mimetype = "", QString width = "", QString height = "",
                  QString depth = "", QString url = "");

        typedef enum {Mimetype,
                      Width,
                      Height,
                      Depth,
                      Url} xmlIconTags;

        void setAttribute(xmlIconTags key, QString v);
        QString getAttribute(xmlIconTags key);
        void clear();

    private:
        QString mimetype;
        QString width;
        QString height;
        QString depth;
        QString url;
        QString attribute;
};

}

#endif /* BRISAICON_H_ */
