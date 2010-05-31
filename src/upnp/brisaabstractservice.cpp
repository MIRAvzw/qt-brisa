/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaabstractservice.cpp
 * Created:
 * Description: This file implements the BrisaAbstractService class.
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
#include "brisaabstractservice.h"

using namespace BrisaUpnp;

BrisaAbstractService::BrisaAbstractService(QObject *parent) :QObject(parent) {

    this->http = new QtSoapHttpTransport(this);
    this->major = "1";
    this->minor = "0";
}

BrisaAbstractService::BrisaAbstractService(const QString &serviceType,
        const QString &serviceId, const QString &scpdUrl,
        const QString &controlUrl, const QString &eventSubUrl,
        const QString &host, QObject *parent) :
    QObject(parent), controlUrl(controlUrl), eventSubUrl(eventSubUrl),
            fileAddress(), scpdUrl(scpdUrl), serviceType(serviceType),
            serviceId(serviceId) {
    this->http = new QtSoapHttpTransport(this);
    this->major = "1";
    this->minor = "0";

    QUrl url(host);
    this->host = url.host();
    this->port = url.port();

    this->http->setHost(host, port);
}

BrisaAbstractService::BrisaAbstractService(BrisaAbstractService &serv) :
    QObject(serv.parent()),

    stateVariableList(serv.getStateVariableList()),

    controlUrl(serv.getAttribute(BrisaAbstractService::ControlUrl)),
            eventSubUrl(serv.getAttribute(BrisaAbstractService::EventSubUrl)),
            fileAddress(serv.getAttribute(BrisaAbstractService::FileAddress)),
            scpdUrl(serv.getAttribute(BrisaAbstractService::ScpdUrl)),
            serviceType(serv.getAttribute(BrisaAbstractService::ServiceType)),
            serviceId(serv.getAttribute(BrisaAbstractService::ServiceId)),

            host(serv.getAttribute(BrisaAbstractService::Host)), port(
                    serv.getAttribute(BrisaAbstractService::Port).toInt()) {
    this->major = serv.getAttribute(BrisaAbstractService::Major);
    this->minor = serv.getAttribute(BrisaAbstractService::Minor);

    this->actionList = serv.getActionList();
    // Copy serv's actions
    for (QList<BrisaAction *>::iterator it = this->actionList.begin(); it
            != this->actionList.end(); ++it) {
        *it = new BrisaAction(*(*it));
    }
}

BrisaAbstractService::~BrisaAbstractService() {
    for (QList<BrisaAction *>::iterator i = this->actionList.begin(); i
            != this->actionList.end(); ++i) {
        delete *i;
    }
    this->actionList.clear();

    for (QList<BrisaStateVariable *>::iterator i =
            this->stateVariableList.begin(); i != this->stateVariableList.end(); ++i) {
        delete *i;
    }
    this->stateVariableList.clear();
    delete http;
}

void BrisaAbstractService::setAttribute(xmlTags key, const QString &value) {
    switch (key) {
    case Major:
        this->major = value;
        break;
    case Minor:
        this->minor = value;
        break;
    case FileAddress:
        this->fileAddress = value;
        break;
    case ServiceType:
        this->serviceType = value;
        break;
    case ServiceId:
        this->serviceId = value;
        break;
    case ScpdUrl:
        this->scpdUrl = value;
        break;
    case ControlUrl:
        this->controlUrl = value;
        break;
    case EventSubUrl:
        this->eventSubUrl = value;
        break;
    case Host:
        this->host = value;
        this->http->setHost(host, port);
        break;
    case Port:
        this->port = value.toInt();
        this->http->setHost(host, port);
        break;
    }
}

QString BrisaAbstractService::getAttribute(xmlTags key) {
    switch (key) {
    case Major:
        return major;
        break;
    case Minor:
        return minor;
        break;
    case FileAddress:
        return this->fileAddress;
        break;
    case ServiceType:
        return this->serviceType;
        break;
    case ServiceId:
        return this->serviceId;
        break;
    case ScpdUrl:
        return this->scpdUrl;
        break;
    case ControlUrl:
        return this->controlUrl;
        break;
    case EventSubUrl:
        return this->eventSubUrl;
        break;
    case Host:
        return this->host;
        break;
    case Port:
        return QString::number(this->port);
        break;
    default:
        return QString();
        break;
    }
}

void BrisaAbstractService::addAction(const QString &name) {
    this->addAction(new BrisaAction(name));
}

void BrisaAbstractService::addAction(BrisaAction *action) {
    // must not add actions named as an already added action
    if (this->getAction(action->getName()))
        return;

    this->actionList.append(action);
}

BrisaAction *BrisaAbstractService::getAction(const QString &name) {
    for (QList<BrisaAction *>::iterator i = this->actionList.begin(); i
            != this->actionList.end(); ++i) {
        if ((*i)->getName() == name)
            return *i;
    }

    return 0;
}

QList<BrisaAction *> BrisaAbstractService::getActionList() {
    return this->actionList;
}

void BrisaAbstractService::addStateVariable(BrisaStateVariable *stateVariable) {
    this->stateVariableList.append(stateVariable);
}

void BrisaAbstractService::addStateVariable(const QString &sendEvents,
        const QString &name, const QString &datatype,
        const QString &defaultValue, const QString &maximum,
        const QString &minimum, const QString &step) {
    BrisaStateVariable *stateVariableSwap = new BrisaStateVariable(sendEvents,
            name, datatype, defaultValue, maximum, minimum, step);
    this->addStateVariable(stateVariableSwap);
}

const QList<BrisaStateVariable *> BrisaAbstractService::getStateVariableList() {
    return this->stateVariableList;
}

void BrisaAbstractService::clear() {
    this->controlUrl.clear();
    this->eventSubUrl.clear();
    this->fileAddress.clear();
    this->major.clear();
    this->minor.clear();
    this->scpdUrl.clear();
    this->serviceType.clear();
    this->serviceId.clear();

    this->host.clear();
    this->port = 0;
}

