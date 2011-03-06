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

#ifndef _BRISAACTION_H
#define _BRISAACTION_H
#include "brisaglobal.h"
#include "brisaargument.h"

#include <QString>
#include <QList>
#include <QMap>
#include <QObject>
#include <QMetaMethod>

typedef QMap<QString, QString> BrisaInArgument, BrisaOutArgument;

namespace Brisa {

class BrisaService;
class BrisaStateVariable;

/*!
 * \class Brisa::BrisaAction brisaaction.h BrisaUpnp/BrisaAction
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
class BRISA_UPNP_EXPORT BrisaAction: public QObject {
Q_OBJECT

public:
    /*!
     * Constructs an action with given \a name, \a parent and \a service that it is related to.
     */
    BrisaAction(QString name = "", BrisaService *service = 0, QObject *parent = 0);

    /*!
     * Constructs an action with given \a name, \a parent and \a service and a method to be invoked
	 * when the action is executed.
     */
	BrisaAction(QString name, BrisaService *service, const QMetaMethod &method, QObject *parent);

    /*!
     * Constructs a new action based on \a action.
     */
    BrisaAction(const BrisaAction &action);

    /*!
     * Destroys the action. It has to be overridden for properly destroying the
     * derived actions when necessary.
     */
    virtual ~BrisaAction();

    /*!
     * Sets a new name to the action.
     */
    void setName(QString name);
    /*!
     * Returns the action's name.
     */
    QString getName() const;

    /*!
     * Sets a new service for this action.
     */
    void setService(BrisaService *service);
    /*!
     * Returns the service that this action is related to.
     */
    BrisaService* getService() const;

    /*!
     * Returns the related service's state variable with the given \a name. If it cannot find its
     * related service or the state variable, then it returns a null pointer.
     */
    BrisaStateVariable* getStateVariable(const QString &name) const;

    /*!
     * Returns this action's list of arguments.
     */
    QList<BrisaArgument*> getArgumentList() const;

    /*!
     * Adds an argument with given \a name, \a direction and \a relatedStateVariable
     * to this action's list of arguments.
     */
    void addArgument(QString name = "", QString direction = "",
            QString relatedStateVariable = "");
    /*!
     * Adds given \a argument to this action's list of arguments.
     */
    void addArgument(BrisaArgument *argumentA);
    /*!
     * Adds given list of \a arguments to this action's list of arguments.
     */
    void addArguments(const QList<BrisaArgument*> argumentA);


    /*!
     * Clears this action's argument list.
     */
    void clearArgumentList();
	 
    /*!
     * Remove given \a argument from this action's list of arguments.
     */

    bool removeArgument(BrisaArgument* argumentA);

    /*!
     * Validates \a inArguments, \a outArguments and runs the action. \a outArguments
     * is an output parameter. This method returns true in case of successful
     * running of the action, else returns false.
     */
    bool call(/*const */BrisaInArgument *inArguments, BrisaOutArgument *&outArguments);

    /*!
     * Sets the method to be invoked when the action is executed.
     */
    void setMethod(const QMetaMethod &method, BrisaService *service);

    /*!
     * Returns the method to be invoked when the action is executed.
     */
    QMetaMethod getMethod() const;

private:

    /*!
     * Returns the related input argument with the given \a name.
     */
    BrisaArgument *getInArgument(const QString &name);

    /*!
     * Returns the related output argument with the given \a name.
     */
    BrisaArgument *getOutArgument(const QString &name);

    /*!
     * Returns the related argument with the given \a name and \a direction.
     */
    BrisaArgument *getArgument(const QString &name, const QString &direction);

    /*!
     * \property argumentList
     *
     * \brief list of related arguments
     */
    QList<BrisaArgument*> argumentList;

    /*!
     * \property name
     *
     * \brief action's name
     */
    QString name;

    /*!
     * \property service
     *
     * \brief the service that this action is related to
     */
    BrisaService *service;

    /*!
     * \property method
     *
     * \brief action's method from the related service to be invoked then this action
     * is executed.
     */
    QMetaMethod method;

};

}

#endif /* _BRISAACTION_H */
