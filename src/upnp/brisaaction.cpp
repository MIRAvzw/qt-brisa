/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaaction.h
 * Created:
 * Description: Defines the BrisaAction class.
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
#include "brisaaction.h"
#include "brisaservice.h"
#include <QDebug>

using namespace Brisa;

BrisaAction::BrisaAction(QString name, BrisaService *service, QObject *parent):
	QObject(parent),
    name(name),
    service(service)
{

}

BrisaAction::BrisaAction(QString name, BrisaService *service, const QMetaMethod &method, QObject *parent):
	QObject(parent),
    name(name),
    service(service),
    method(method)
{

}

BrisaAction::BrisaAction(const BrisaAction &action) :
                         QObject(action.parent()),
                         name(action.getName()),
                         service(action.getService())
{
    this->method = action.getMethod();
    QList<BrisaArgument *> argumentList = action.getArgumentList();
    foreach (BrisaArgument *argument, argumentList) {
        this->argumentList.append(new BrisaArgument(*argument));
    }
}


BrisaAction::~BrisaAction()
{
    qDeleteAll(this->argumentList);
    this->argumentList.clear();
}

void BrisaAction::addArgument(QString name, QString direction, QString relatedStateVariable)
{
    BrisaArgument *argumentSwap = new BrisaArgument(name, direction, relatedStateVariable);
    this->argumentList.append(argumentSwap);
}

void BrisaAction::addArgument(BrisaArgument *argumentA)
{
    this->argumentList.append(argumentA);
}

bool BrisaAction::removeArgument(BrisaArgument* argumentA)
{
	return this->argumentList.removeOne(argumentA);
}

void BrisaAction::addArguments(const QList<BrisaArgument*> arguments)
{
    for (QList<BrisaArgument*>::const_iterator i = arguments.begin(); i != arguments.end(); ++i) {
        this->addArgument(*i);
    }
}

void BrisaAction::setName(QString name)
{
    this->name = name;
}

QString BrisaAction::getName() const
{
    return this->name;
}

void BrisaAction::setService(BrisaService *service)
{
    this->service = service;
}

BrisaService* BrisaAction::getService() const
{
    return this->service;
}

BrisaStateVariable* BrisaAction::getStateVariable(const QString &name) const
{
    if (!this->service) {
        qDebug() << this->getName() << " action couldn't find its related Service.";
        return 0;
    }

    BrisaStateVariable *stateVariable = service->getVariable(name);
    if (!stateVariable) {
        qDebug() << this->getName() << " action couldn't find the State Variable.";
    }

    return stateVariable;
}

QList<BrisaArgument *> BrisaAction::getArgumentList() const
{
    return this->argumentList;
}

void BrisaAction::clearArgumentList()
{
    this->argumentList.clear();
}

bool BrisaAction::call(BrisaInArgument *inArguments, BrisaOutArgument *&outArguments)
{
    // Checking IN variables
    for (BrisaInArgument::const_iterator i = inArguments->begin(); i != inArguments->end(); ++i) {
        BrisaArgument *arg = this->getInArgument(i.key());
        if (!arg) {
            qDebug() << "Error: action " << this->getName() << " has no IN argument named '" << i.key() << "'.";
            return false;
        }
    }

    // use the run() invocation.
    if (this->method.methodIndex() >= 0) { // checking if action has a QMetaMethod specified
        bool execResult = this->method.invoke(this->service,
                                              Qt::DirectConnection,
                                              Q_RETURN_ARG(BrisaOutArgument *, outArguments),
                                              Q_ARG(BrisaInArgument *, inArguments),
                                              Q_ARG(BrisaAction *, this));
        if (!execResult) {
            qDebug() << "Error invoking defined action expressed by the service method " << this->method.signature();
            return false;
        }
    } else {
        qDebug() << "Error: there is not method to be invoked by this action.";
        return false;
    }

    // Check OUT variables
    for (BrisaOutArgument::const_iterator i = outArguments->begin(); i != outArguments->end(); ++i) {
        BrisaArgument *arg = this->getOutArgument(i.key());
        if (!arg) {
            qDebug() << "Error: action " << this->getName() << " has no OUT expected argument named '" << i.key() << "'.";
            return false;
        }
    }
	
    return true;
}

BrisaArgument* BrisaAction::getInArgument(const QString &name)
{
    return this->getArgument(name, "in");
}

BrisaArgument* BrisaAction::getOutArgument(const QString &name)
{
    return this->getArgument(name, "out");
}

BrisaArgument* BrisaAction::getArgument(const QString &name, const QString &direction)
{
    foreach (BrisaArgument *argument, this->getArgumentList()) {
        if (argument->getAttribute(BrisaArgument::Direction) == direction && argument->getAttribute(BrisaArgument::ArgumentName) == name) {
                return argument;
        }
    }

    return 0;
}

void BrisaAction::setMethod(const QMetaMethod &method, BrisaService *service)
{
    this->method = method;
	this->setService(service);
}

QMetaMethod BrisaAction::getMethod() const
{
    return this->method;
}
