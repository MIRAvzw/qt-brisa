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
 */

#include "brisaaction.h"
#include "brisaservice.h"
#include <QDebug>

using namespace BrisaUpnp;

/*!
 * \class BrisaUpnp::BrisaAction brisaaction.h BrisaUpnp/BrisaAction
 *
 * \brief Template method class that represents each service's action.
 * 
 * Create a class derived from BrisaAction and reimplement the method run().
 * That method is the one which is called when this action is invoked and
 * defines the action's behavior.
 *
 * The method run() receives a QMap<QString, QString> with the input arguments.
 * They are organized as key -- the argument name -- and value -- the argument
 * value. It has to return a QMap<QString, QString> with the output arguments
 * organized the same way.
 *
 * If any of the returned output arguments is not defined in the service
 * description file, BrisaAction will show an error message at the debug
 * output stream and send an error message to the control point.
 */

/*!
 * \property argumentList
 *
 * \brief list of related arguments
 */

/*!
 * \property name
 *
 * \brief action's name
 */

/*!
 * \property service
 *
 * \brief the service that this action is related to
 */

/*!
 * Constructs an action with given \a name, \a parent and \a service that it is related to.
 */
BrisaAction::BrisaAction(QString name, BrisaService *service, QObject *parent) :
    QObject(parent),
    name(name),
    service(service)
{
}

/*!
 * Constructs a new action based on \a action.
 */
BrisaAction::BrisaAction(const BrisaAction &action) :
    QObject(action.parent()),
    name(action.getName()),
    service(action.getService())
{
    QList<BrisaArgument *> argumentList = action.getArgumentList();

    foreach(BrisaArgument *a, argumentList) {
        this->argumentList.append(new BrisaArgument(*a));
    }
}

/*!
 * Destroys the action. It has to be overridden for properly destroying the
 * derived actions when necessary.
 */
BrisaAction::~BrisaAction()
{
    foreach(BrisaArgument *a, this->argumentList) {
        delete a;
    }

    this->argumentList.clear();
}

/*!
 * Adds an argument with given \a name, \a direction and \a relatedStateVariable
 * to this action's list of arguments.
 */
void BrisaAction::addArgument(QString name, QString direction, QString relatedStateVariable)
{
    BrisaArgument *argumentSwap = new BrisaArgument(name, direction, relatedStateVariable);
    argumentList.append(argumentSwap);
}

/*!
 * Adds given \a argument to this action's list of arguments.
 */
void BrisaAction::addArgument(BrisaArgument *argumentA)
{
    argumentList.append(argumentA);
}

/*!
 * Adds given list of \a arguments to this action's list of arguments.
 */
void BrisaAction::addArguments(const QList<BrisaArgument*> arguments)
{
    for(QList<BrisaArgument*>::const_iterator i = arguments.begin();
        i != arguments.end(); ++i) {
        this->addArgument(*i);
    }
}

/*!
 * Sets a new name to the action.
 */
void BrisaAction::setName(QString name)

{
    this->name = name;
}

/*!
 * Returns the action's name.
 */
QString BrisaAction::getName() const
{
    return this->name;
}

/*!
 * Sets a new service for this action.
 */
void BrisaAction::setService(BrisaService *service)
{
    this->service = service;
}

/*!
 * Returns the service that this action is related to.
 */
BrisaService *BrisaAction::getService() const
{
    return this->service;
}

/*!
 * Returns the related service's state variable with the given \a name. If it cannot find its
 * related service or the state variable, then it returns a null pointer.
 */
BrisaStateVariable *BrisaAction::getStateVariable(const QString &name) const
{
    BrisaService *service = this->getService();

    if (!service) {
        qDebug() << this->getName() << "action couldn't find its related Service";
        return 0;
    }

    BrisaStateVariable *stateVariable = service->getVariable(name);
    if (!stateVariable)
        qDebug() << this->getName() << "action couldn't find the State Variable";

    return stateVariable;
}

/*!
 * Returns this action's list of arguments.
 */
QList<BrisaArgument *> BrisaAction::getArgumentList() const
{
    return this->argumentList;
}

/*!
 * Clears this action's argument list.
 */
void BrisaAction::clearArgumentList()
{
    this->argumentList.clear();
}

/*!
 * Validates \a inArguments, \a outArguments and runs the action. \a outArguments
 * is an output parameter. This method returns true in case of successful
 * running of the action, else returns false.
 */
bool BrisaAction::call(const QMap<QString, QString> &inArguments, QMap<QString, QString> &outArguments)
{
    // Check IN variables
    for (QMap<QString, QString>::const_iterator i = inArguments.begin(); i != inArguments.end(); ++i) {
        BrisaArgument *arg = this->getInArgument(i.key());
        if (!arg) {
            qDebug() << this->getName() << "action has no IN argument called" << i.key();
            return false;
        }
    }

    // run
    QMap<QString, QString> outArgs = this->run(inArguments);

    // Check OUT variables
    for (QMap<QString, QString>::const_iterator i = outArgs.begin(); i != outArgs.end(); ++i) {
        BrisaArgument *arg = this->getOutArgument(i.key());
        if (!arg) {
            qDebug() << this->getName() << "action has no OUT argument called" << i.key();
            return false;
        }
    }

    // set output argument list as the one passed by the BRisa's user
    outArguments = outArgs;

    return true;
}

/*!
 * Returns the related input argument with the given \a name.
 */
BrisaArgument *BrisaAction::getInArgument(const QString &name)
{
    return this->getArgument(name, "in");
}

/*!
 * Returns the related output argument with the given \a name.
 */
BrisaArgument *BrisaAction::getOutArgument(const QString &name)
{
    return this->getArgument(name, "out");
}

/*!
 * Returns the related argument with the given \a name and \a direction.
 */
BrisaArgument *BrisaAction::getArgument(const QString &name, const QString &direction)
{
    foreach(BrisaArgument *a, this->getArgumentList()) {
        if (a->getAttribute(BrisaArgument::Direction) == direction
            && a->getAttribute(BrisaArgument::ArgumentName) == name) {
            return a;
        }
    }

    return 0;
}

/*!
 * The actual action. This method must be reimplemented for each user's action.
 * It receives \a inArguments as input arguments and must return the right
 * output arguments as described in the service's description file.
 */
QMap<QString, QString> BrisaAction::run(const QMap<QString, QString> &inArguments)
{
    Q_UNUSED(inArguments)

    QMap<QString, QString> out;
    return out;
}

