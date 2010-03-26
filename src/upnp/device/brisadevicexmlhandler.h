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

#ifndef _BRISADEVICEXMLHANDLER_H
#define _BRISADEVICEXMLHANDLER_H

#include <QXmlStreamWriter>
#include <QString>
#include <QFile>
#include <QtDebug>

#include "brisaglobal.h"

namespace BrisaUpnp {

class BrisaDevice;

class BRISA_UPNP_EXPORT BrisaDeviceXMLHandler
{
    public:
        void xmlGenerator(BrisaDevice *device, QFile *file);

    private:
        void writeDevice(BrisaDevice *device);

        QXmlStreamWriter *writer;
};

}

#endif /* _BRISADEVICEXMLHANDLER_H */

