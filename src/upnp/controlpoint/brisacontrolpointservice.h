/* brisa-c++
 *
 * Copyright (C) 2009 Andre Dieb Martins <andre.dieb@gmail.com>
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
 */

#ifndef _BRISASERVICE_H
#define _BRISASERVICE_H

#include "brisaabstractservice.h"
#include "brisaglobal.h"

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaControlPointService : public BrisaAbstractService
{
    Q_OBJECT

    public:
        BrisaControlPointService(QObject *parent = 0);
        BrisaControlPointService(const QString &serviceType, const QString &serviceId = "",
                                 const QString &scpdUrl = "", const QString &controlUrl = "",
                                 const QString &eventSubUrl = "", const QString &host = "",
                                 QObject *parent = 0);
        BrisaControlPointService(BrisaControlPointService &service);

        void parseFromXml(QTemporaryFile *xml);


        void call(const QString &method, const QMap<QString, QString> &param);

    private slots:
        void getResponse();

    private:
        QString lastMethod;
};

}

#endif /* BrisaControlPointService_H_ */

