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

#include "brisacontrolpointservice.h"
#include "brisaservicexmlhandler.h"

#include <QtDebug>
#include <QIODevice>

using namespace BrisaUpnp;

/*!
 *    \class BrisaUpnp::BrisaControlPointService brisacontrolpointservice.h BrisaUpnp/BrisaControlPointService
 *
 *    \brief BrisaControlPointService is the class that implements action control in UPnP
 *    Architecture
 *
 *    It performs the action requests it's used in control point part, so that the user can make
 *    action calls.
 *
 *    BrisaControlPointService is a BrisaAbstractService.
 */

/*!
 *    \property lastMethod
 *
 *    \brief String representing the method that was called to emit to the user.
 */

/*!
 *    Constructs an empty BrisaControlPointService
 */
BrisaControlPointService::BrisaControlPointService(QObject *parent) : BrisaAbstractService(parent)
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
}

/*!
 *    Constructs a BrisaControlPointService with the passed attributes.
 */
BrisaControlPointService::BrisaControlPointService(const QString &serviceType,
                                                   const QString &serviceId, const QString &scpdUrl,
                                                   const QString &controlUrl,
                                                   const QString &eventSubUrl, const QString &host,
                                                   QObject *parent) : 
    BrisaAbstractService(serviceType, serviceId, scpdUrl, controlUrl, eventSubUrl, host, parent)
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
}

/*!
 *    Constructs a copy of \a serv.
 */
BrisaControlPointService::BrisaControlPointService(BrisaControlPointService &serv) :
    BrisaAbstractService(serv)
{
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));
}

/*!
 *    Initializes the BrisaControlPointService from the parse of \a xml that is a xml description
 *    file containing the service information.
 */
void BrisaControlPointService::parseFromXml(QTemporaryFile *xml)
{
    BrisaServiceXMLHandler handler;
    handler.parseService(this, xml);
}

/*!
 *    Call the \a method, with the passed \a param from a service, this action is performed by a
 *    webservice request.
 */
void BrisaControlPointService::call(const QString &method, const QMap<QString, QString> &param)
{
    QtSoapMessage request;

    http.setAction("\"" + serviceType + "#" + method + "\"");

    request.setMethod(method, serviceType);

    foreach(QString s, param.keys()) {
        request.addMethodArgument(s, "", param.value(s));
    }

    lastMethod = method;
    this->http.submitRequest(request, this->controlUrl);
}

/*!
 *    Gets the method return and emits the returned value and the lastMethod called.
 */
void BrisaControlPointService::getResponse()
{
    const QtSoapMessage &message = http.getResponse();

    if (message.isFault()) {
        emit requestFinished("Error: " + message.faultString().toString(), lastMethod);
        return ;
    }

    emit requestFinished(message.returnValue().toString(), lastMethod);
}

