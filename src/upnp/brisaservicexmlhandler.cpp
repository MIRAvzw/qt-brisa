/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaservicexmkhandler.cpp
 * Created:
 * Description: This file implements the BrisaServiceXMLHandler class.
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

#include "brisaservicexmlhandler.h"
#include "brisaabstractservice.h"

using namespace BrisaUpnp;

BrisaServiceXMLHandler::BrisaServiceXMLHandler() : QXmlDefaultHandler()
{
}
BrisaServiceXMLHandler::~BrisaServiceXMLHandler()
{
    delete context;
//    delete actionSwap;
//    delete stateVariableSwap;
//    delete argumentSwap;
//    delete writer;
}

void BrisaServiceXMLHandler::parseService(BrisaAbstractService *service,
        QIODevice *scpd) {
    context = new BrisaServiceParserContext(NULL, service);
    input = new QXmlInputSource(scpd);
    reader = new QXmlSimpleReader();

    context->state = ServiceStart;
    context->stateSkip = 0;

    reader->setContentHandler(this);
    reader->setErrorHandler(this);
    qDebug() << "Brisa Service XML Handler: " << service->getAttribute(BrisaAbstractService::ServiceType);
    reader->parse(input);

    delete input;
    delete reader;
}

bool BrisaServiceXMLHandler::startElement(const QString &, const QString &,
        const QString &qName, const QXmlAttributes &attribute) {
    switch (context->state) {
    case ServiceStart:
        if (qName == "scpd")
            context->state = Scpd;
        else
            context->state = ServiceError;
        break;

    case Scpd:
        if (qName == "specVersion")
            context->state = ServiceSpecVersion;
        else if (qName == "actionList")
            context->state = ActionList;
        else if (qName == "serviceStateTable")
            context->state = ServiceStateTable;
        else
            context->stateSkip++;
        break;

    case ServiceSpecVersion:
        if (qName == "major")
            context->state = ServiceSpecVersionMajor;
        else if (qName == "minor")
            context->state = ServiceSpecVersionMinor;
        else
            context->stateSkip++;
        break;

    case ActionList:
        if (qName == "action") {
            context->state = Action;
        } else
            context->stateSkip++;
        break;

    case Action:
        if (!context->getAction())
            context->setAction(new BrisaAction());

        if (qName == "name")
            context->state = ActionName;
        else if (qName == "argumentList")
            context->state = ArgumentList;
        else
            context->stateSkip++;
        break;

    case ArgumentList:
        if (qName == "argument")
            context->state = Argument;
        else
            context->stateSkip++;
        break;

    case Argument:
        if (!context->getArgument())
            context->setArgument(new BrisaArgument());
        if (qName == "name")
            context->state = ArgumentName;
        else if (qName == "direction")
            context->state = ArgumentDirection;
        else if (qName == "relatedStateVariable")
            context->state = RelatedStateVariable;
        else
            context->stateSkip++;
        break;

    case ServiceStateTable:
        if (qName == "stateVariable")
            context->state = StateVariable;
        if (!context->getStateVariable()) {
            context->setStateVariable(new BrisaStateVariable());
            context->getStateVariable()->setAttribute(
                    BrisaStateVariable::SendEvents, attribute.value(
                            "sendEvents"));
        } else
            context->stateSkip++;
        break;

    case StateVariable:
        if (qName == "name")
            context->state = StateVariableName;
        else if (qName == "dataType")
            context->state = StateVariableDataType;
        else if (qName == "defaultValue")
            context->state = StateVariableDefaultValue;
        else if (qName == "allowedValueList")
            context->state = StateVariableAllowedValueList;
        else if (qName == "allowedValueRange")
            context->state = StateVariableAllowedValueRange;
        else
            context->stateSkip++;
        break;

    case StateVariableAllowedValueList:
        if (qName == "allowedValue")
            context->state = StateVariableAllowedValue;
        else
            context->stateSkip++;
        break;

    case StateVariableAllowedValueRange:
        if (qName == "minimum")
            context->state = StateVariableAllowedValueRangeMinimum;
        else if (qName == "maximum")
            context->state = StateVariableAllowedValueRangeMaximum;
        else if (qName == "step")
            context->state = StateVariableAllowedValueRangeStep;
        else
            context->stateSkip++;
        break;

    case ServiceSpecVersionMajor:
    case ServiceSpecVersionMinor:
    case ActionName:
    case ArgumentName:
    case ArgumentDirection:
    case RelatedStateVariable:
    case StateVariableName:
    case StateVariableDataType:
    case StateVariableDefaultValue:
    case StateVariableAllowedValue:
    case StateVariableAllowedValueRangeMinimum:
    case StateVariableAllowedValueRangeMaximum:
    case StateVariableAllowedValueRangeStep:
        break;

    default:
        context->stateSkip++;
        break;
    }

    return true;
}

bool BrisaServiceXMLHandler::characters(const QString &str) {

    qDebug() << "Brisa Service XML Handler char: " << str << " " << context->getService()->getAttribute(BrisaAbstractService::ServiceType);
    switch (context->state) {
    case ServiceSpecVersionMajor:
        context->getService()->setAttribute(BrisaAbstractService::Major, str);
        break;

    case ServiceSpecVersionMinor:
        context->getService()->setAttribute(BrisaAbstractService::Minor, str);
        break;

    case ActionName:
        context->getAction()->setName(str);
        break;

    case ArgumentName:
        context->getArgument()->setAttribute(BrisaArgument::ArgumentName, str);
        break;

    case ArgumentDirection:
        context->getArgument()->setAttribute(BrisaArgument::Direction, str);
        break;

    case RelatedStateVariable:
        context->getArgument()->setAttribute(
                BrisaArgument::RelatedStateVariable, str);
        break;

    case StateVariableName:
        context->getStateVariable()->setAttribute(BrisaStateVariable::Name, str);
        break;

    case StateVariableDataType:
        context->getStateVariable()->setAttribute(BrisaStateVariable::DataType,
                str);
        break;

    case StateVariableDefaultValue:
        context->getStateVariable()->setAttribute(
                BrisaStateVariable::DefaultValue, str);
        break;

    case StateVariableAllowedValue:
        context->getStateVariable()->addAllowedValue(str);
        break;

    case StateVariableAllowedValueRangeMinimum:
        context->getStateVariable()->setAttribute(BrisaStateVariable::Minimum,
                str);
        break;
    case StateVariableAllowedValueRangeMaximum:
        context->getStateVariable()->setAttribute(BrisaStateVariable::Maximum,
                str);
        break;

    case ServiceStart:
    case Scpd:
    case ServiceSpecVersion:
    case ActionList:
    case Action:
    case ArgumentList:
    case Argument:
    case ServiceStateTable:
    case StateVariable:
    case StateVariableAllowedValueList:
    case StateVariableAllowedValueRange:
    case StateVariableAllowedValueRangeStep:
    case ServiceError:
    case ServiceFinished:
        break;
    }

    return true;
}

bool BrisaServiceXMLHandler::endElement(const QString &, const QString &,
        const QString &qName) {

    qDebug() << "Brisa Service XML Handler end: " << qName;
    Q_UNUSED(qName);

    if (context->stateSkip) {
        context->stateSkip--;
        return true;
    }

    switch (context->state) {

    case Scpd:
        context->state = ServiceFinished;
        break;

    case ServiceSpecVersion:
    case ActionList:
    case ServiceStateTable:
        context->state = Scpd;
        break;

    case ServiceSpecVersionMajor:
    case ServiceSpecVersionMinor:
        context->state = ServiceSpecVersion;
        break;

    case Action: {
        // check if there is another action with the same name of this one
        BrisaAction *contextAction = context->getAction();
        BrisaAbstractService *contextService = context->getService();
        BrisaAction *actionLikeThis = contextService->getAction(
                contextAction->getName());

        if (actionLikeThis) {
            actionLikeThis->addArguments(contextAction->getArgumentList());

            contextAction->clearArgumentList();
            //so it won't delete the arguments in the heap those are pointed to by actionLikeThis
            //during its destruction
            delete contextAction;
        } else {
            context->getService()->addAction(contextAction);
        }

        context->setAction(NULL);
        context->state = ActionList;
        break;
    }

    case ActionName:
    case ArgumentList:
        context->state = Action;
        break;

    case Argument:
        context->getAction()->addArgument(context->getArgument());
        context->setArgument(NULL);
        context->state = ArgumentList;
        break;

    case ArgumentName:
    case ArgumentDirection:
    case RelatedStateVariable:
        context->state = Argument;
        break;

    case StateVariable:
        context->getService()->addStateVariable(context->getStateVariable());
        context->setStateVariable(NULL);
        context->state = ServiceStateTable;
        break;

    case StateVariableName:
    case StateVariableDataType:
    case StateVariableDefaultValue:
    case StateVariableAllowedValueList:
    case StateVariableAllowedValueRange:
        context->state = StateVariable;
        break;

    case StateVariableAllowedValue:
        context->state = StateVariableAllowedValueList;
        break;

    case StateVariableAllowedValueRangeMinimum:
    case StateVariableAllowedValueRangeMaximum:
    case StateVariableAllowedValueRangeStep:
        context->state = StateVariableAllowedValueRange;
        break;

    case ServiceStart:
    case ServiceFinished:
    case ServiceError:
        break;
    }

    return true;
}
