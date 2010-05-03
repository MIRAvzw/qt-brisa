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

using namespace BrisaUpnp;

BrisaAction::BrisaAction(QString name, BrisaService *service, QObject *parent) :
    QObject(parent), name(name), service(service) {
}

BrisaAction::BrisaAction(const BrisaAction &action) :
    QObject(action.parent()), name(action.getName()), service(
            action.getService()) {
    QList<BrisaArgument *> argumentList = action.getArgumentList();

    foreach(BrisaArgument *a, argumentList)
        {
            this->argumentList.append(new BrisaArgument(*a));
        }
}

BrisaAction::~BrisaAction() {
    foreach(BrisaArgument *a, this->argumentList)
        {
            delete a;
        }

    this->argumentList.clear();
}

void BrisaAction::addArgument(QString name, QString direction,
        QString relatedStateVariable) {
    BrisaArgument *argumentSwap = new BrisaArgument(name, direction,
            relatedStateVariable);
    argumentList.append(argumentSwap);
}

void BrisaAction::addArgument(BrisaArgument *argumentA) {
    argumentList.append(argumentA);
}

void BrisaAction::addArguments(const QList<BrisaArgument*> arguments) {
    for (QList<BrisaArgument*>::const_iterator i = arguments.begin(); i
            != arguments.end(); ++i) {
        this->addArgument(*i);
    }
}

void BrisaAction::setName(QString name)

{
    this->name = name;
}

QString BrisaAction::getName() const {
    return this->name;
}

void BrisaAction::setService(BrisaService *service) {
    this->service = service;
}

BrisaService *BrisaAction::getService() const {
    return this->service;
}

BrisaStateVariable *BrisaAction::getStateVariable(const QString &name) const {
    BrisaService *service = this->getService();

    if (!service) {
        qDebug() << this->getName()
                << "action couldn't find its related Service";
        return 0;
    }

    BrisaStateVariable *stateVariable = service->getVariable(name);
    if (!stateVariable)
        qDebug() << this->getName()
                << "action couldn't find the State Variable";

    return stateVariable;
}

QList<BrisaArgument *> BrisaAction::getArgumentList() const {
    return this->argumentList;
}

void BrisaAction::clearArgumentList() {
    this->argumentList.clear();
}

bool BrisaAction::call(const QMap<QString, QString> &inArguments, QMap<QString,
        QString> &outArguments) {
    // Check IN variables
    for (QMap<QString, QString>::const_iterator i = inArguments.begin(); i
            != inArguments.end(); ++i) {
        BrisaArgument *arg = this->getInArgument(i.key());
        if (!arg) {
            qDebug() << this->getName() << "action has no IN argument called"
                    << i.key();
            return false;
        }
    }

    // run
    QMap<QString, QString> outArgs = this->run(inArguments);

    // Check OUT variables
    for (QMap<QString, QString>::const_iterator i = outArgs.begin(); i
            != outArgs.end(); ++i) {
        BrisaArgument *arg = this->getOutArgument(i.key());
        if (!arg) {
            qDebug() << this->getName() << "action has no OUT argument called"
                    << i.key();
            return false;
        }
    }

    // set output argument list as the one passed by the BRisa's user
    outArguments = outArgs;

    return true;
}

BrisaArgument *BrisaAction::getInArgument(const QString &name) {
    return this->getArgument(name, "in");
}

BrisaArgument *BrisaAction::getOutArgument(const QString &name) {
    return this->getArgument(name, "out");
}

BrisaArgument *BrisaAction::getArgument(const QString &name,
        const QString &direction) {
    foreach(BrisaArgument *a, this->getArgumentList())
        {
            if (a->getAttribute(BrisaArgument::Direction) == direction
                    && a->getAttribute(BrisaArgument::ArgumentName) == name) {
                return a;
            }
        }

    return 0;
}

QMap<QString, QString> BrisaAction::run(
        const QMap<QString, QString> &inArguments) {
    Q_UNUSED(inArguments)

    QMap<QString, QString> out;
    return out;
}

