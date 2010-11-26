/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstractservice.h
 * Created:
 * Description: This file defines the BrisaAbstractService class.
 * Authors: Name <email> @since 2009
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
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

#ifndef _BRISASERVICE_H
#define _BRISASERVICE_H

#include "brisaabstractservice.h"
#include "brisaglobal.h"

namespace Brisa {

/*!
 *  \class Brisa::BrisaControlPointService brisacontrolpointservice.h BrisaUpnp/BrisaControlPointService
 *
 *  \brief BrisaControlPointService is the class that implements action control in UPnP
 *  Architecture
 *
 *  It performs the action requests it's used in control point part, so that the user can make
 *  action calls.
 *
 *  BrisaControlPointService is a BrisaAbstractService.
 */
class BRISA_UPNP_EXPORT BrisaControlPointService: public BrisaAbstractService {
Q_OBJECT

public:

    /*!
     *  Constructs an empty BrisaControlPointService
     *
     *  \param parent \a empty
     */
    BrisaControlPointService(QObject *parent = 0);

    /*!
     *  Constructs a BrisaControlPointService with the passed attributes.
     *
     *  \param serviceType \a empty
     *  \param serviceId \a empty
     *  \param scpdUrl \a empty
     *  \param controlUrl \a empty
     *  \param eventSubUrl \a empty
     *  \param host \a empty
     *  \param parent \a empty
     */
    BrisaControlPointService(const QString &serviceType,
            const QString &serviceId = "", const QString &scpdUrl = "",
            const QString &controlUrl = "", const QString &eventSubUrl = "",
            const QString &host = "", QObject *parent = 0);

    /*!
     *  Constructs a copy of \a serv.
     *
     *  \param serv \a empty
     */
    BrisaControlPointService(BrisaControlPointService &service);

    /*!
     *  Initializes the BrisaControlPointService from the parse of \a xml that is a xml description
     *  file containing the service information.
     *
     *  \param xml \a empty
     */
    void parseFromXml(QTemporaryFile *xml);

    /*!
     *  Call the \a method, with the passed \a param from a service, this action is performed by a
     *  webservice request.
     *
     *  \param method method to be called
     *  \param param map with the parameters to be passed
     */
    void call(const QString &method, BrisaInArgument &param);

private slots:
    /*!
     *  Gets the method return and emits the returned value and the lastMethod called.
     */
    void getResponse();

private:
    /*!
     *  \property lastMethod
     *
     *  \brief String representing the method that was called to emit to the user.
     */
    QString lastMethod;
};

}

#endif /* BrisaControlPointService_H_ */

