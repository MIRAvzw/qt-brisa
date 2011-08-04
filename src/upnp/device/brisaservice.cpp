/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaservice.cpp
 * Created:
 * Description: Implements BrisaService class.
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

#include <QtDebug>
#include <QUrl>

#include "brisawebfile.h"
#include "brisacontrolwebservice.h"
#include "brisawebserversession.h"

// TODO: move the include directive to the begin of the file
#include "brisaservice.h"
#include "brisaservicexmlhandler.h"

#define PRE_ACTION_SIG "preAction(BrisaInArgument*const,BrisaAction*const,QString&)"
#define POST_ACTION_SIG "postAction(BrisaInArgument*const,BrisaOutArgument*const,BrisaAction*const,QString&)"
#define FAILURE_ACTION_SIG "handleActionFailure(BrisaInArgument*const,BrisaAction*const,QString&)"
#define ACTION_IN "(BrisaInArgument*const,BrisaAction*const)"
#define ACTION_OUT "BrisaOutArgument*"
#define PRE_ACTION_OUT "int"
#define POST_ACTION_OUT "int"
#define FAILURE_ACTION_OUT "int"

using namespace Brisa;

static const QString SOAP_ERROR_TEMPLATE = "<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n"
                                           "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\""
                                           " s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n"
                                           "<s:Body>\r\n"
                                           "<s:Fault>\r\n"
                                           "<faultcode>s:Client</faultcode>\r\n"
                                           "<faultstring>UPnPError</faultstring>\r\n"
                                           "<detail>\r\n"
                                           "<UPnPError xmlns=\"urn:schemas-upnp-org:control-1-0\">\r\n"
                                           "<errorCode>%1</errorCode>\r\n"
                                           "<errorDescription>%2</errorDescription>\r\n"
                                           "</UPnPError>\r\n"
                                           "</detail>\r\n"
                                           "</s:Fault>\r\n"
                                           "</s:Body>\r\n"
                                           "</s:Envelope>\r\n";
BrisaService::BrisaService(QObject *parent) :
    BrisaAbstractService(parent) {
}

BrisaService::BrisaService(const QString &serviceType,
        const QString &serviceId, const QString &scpdUrl,
        const QString &controlUrl, const QString &eventSubUrl,
        const QString &host, QObject *parent) :
    BrisaAbstractService(serviceType, serviceId, scpdUrl, controlUrl,
            eventSubUrl, host, parent) {
}

BrisaService::BrisaService(BrisaService &serv) :
    QObject(NULL),
    BrisaAbstractService(serv)
{
}

BrisaService::~BrisaService() {
    qDeleteAll(this->childWebServices);
    childWebServices.clear();
}

void BrisaService::call(const QString &method, BrisaInArgument param, BrisaWebserverSession *session)
{
    for (QList<BrisaAction *>::iterator i = this->actionList.begin(); i != actionList.end(); ++i) {
        BrisaAction *action = *i;
        if (action->getName() == method) {
            int prePostActionReturn = 0;
            QString errorDescription = "";
            // executing preMethod if available
            if (this->preActionMethod.methodIndex() >= 0) {
                if (!this->preActionMethod.invoke(this,
                                                  Qt::DirectConnection,
                                                  Q_RETURN_ARG(int, prePostActionReturn),
                                                  Q_ARG(BrisaInArgument *, &param),
                                                  Q_ARG(BrisaAction *, action),
                                                  Q_ARG(QString, errorDescription)))
                {
                    qDebug() << "Error invoking preAction method. Continuing...";
                }
            } else {
                qDebug() << "Warning: preAction method not found, continuing...";
            }

            if (prePostActionReturn == 0) {
                // call the action
                BrisaOutArgument *outArguments;

                if (!action->call(&param, outArguments)) {
                    qDebug() << "An error has occurred during the " << action->getName() << " callback.";
                    if (!outArguments) {
                        delete outArguments;
                    }

                    if (this->handleActionFailureMethod.methodIndex() >= 0) {
                        int handleFailureActionMethodReturn = 0;
                        if (!this->handleActionFailureMethod.invoke(this,
                                                                    Qt::DirectConnection,
                                                                    Q_RETURN_ARG(int, handleFailureActionMethodReturn),
                                                                    Q_ARG(BrisaInArgument *, &param),
                                                                    Q_ARG(BrisaAction *, action),
                                                                    Q_ARG(QString, errorDescription)))
                        {
                            qDebug() << "Error invoking handleActionFailure method. Continuing...";
                            respondError(session, UPNP_ACTION_FAILED);
                            return;
                        }
                        respondError(session, handleFailureActionMethodReturn,
                                     "Error specified by UPnP vendor: "
                                     + errorDescription);
                        return;
                    }

                    qDebug() << "handleActionFailure method not implemented in service, returning default error.";
                    this->respondError(session, UPNP_ACTION_FAILED);
                    return;
                }

                // avoiding segmentation fault...
                if (!outArguments) {
                    outArguments = new BrisaOutArgument();
                }

                // executing postMethod if available
                if (this->postActionMethod.methodIndex() >= 0) {
                    if (!this->postActionMethod.invoke(this,
                                                       Qt::DirectConnection,
                                                       Q_RETURN_ARG(int, prePostActionReturn),
                                                       Q_ARG(BrisaInArgument *, &param),
                                                       Q_ARG(BrisaOutArgument *, outArguments),
                                                       Q_ARG(BrisaAction *, action),
                                                       Q_ARG(QString, errorDescription)))
                    {
                        qDebug() << "Error invoking postAction method.";
                    }

                    if (prePostActionReturn != 0) {
                        qDebug() << "Warning: postAction service method returned non-zero, sending UPnP error code " << prePostActionReturn;
                        delete outArguments;
                        respondError(session, prePostActionReturn, errorDescription);
                        return;
                    }
                } else {
                    qDebug() << "Warning: postAction method not found, continuing...";
                }

                // send response.
                this->respondAction(session, outArguments, action->getName());
                delete outArguments;
                return;
            } else { // preAction returned non-zero
                qDebug() << "Warning: preAction method returned non-zero value, it returned " << prePostActionReturn << " with description " << errorDescription;
                respondError(session, prePostActionReturn, errorDescription);
                return;
            }
        }
    }

    qDebug() << "BrisaService: Unknown callback: " << method;
    respondError(session, UPNP_INVALID_ACTION);
}

void BrisaService::buildWebServiceTree(BrisaWebserver *sessionManager)
{
    BrisaWebService *control = new BrisaControlWebService(serviceType);

    connect(control, SIGNAL(requestReceived(QString,BrisaInArgument,BrisaWebserverSession*)),
            this, SLOT(call(QString,BrisaInArgument,BrisaWebserverSession*)));
    connect(control, SIGNAL(invalidRequest(BrisaWebserverSession*)),
            this, SLOT(onInvalidRequest(BrisaWebserverSession*)));

    BrisaEventController *event = new BrisaEventController(sessionManager,
                                                           &stateVariableList,
                                                           this);

    sessionManager->addService((serviceId + '/' + controlUrl.section('/', -1)).toUtf8(), control);

    sessionManager->addService((serviceId + '/' + eventSubUrl.section('/', -1)).toUtf8(), event);

    sessionManager->addService((serviceId + '/' + scpdUrl.section('/', -1)).toUtf8(),
                               new BrisaWebFile(scpdFilePath, this));

    childWebServices.insert(controlUrl.section('/', -1), control);
    childWebServices.insert(eventSubUrl.section('/', -1), event);

    parseDescriptionFile();
}

void BrisaService::onInvalidRequest(BrisaWebserverSession *session)
{
    respondError(session, UPNP_INVALID_ACTION);
}

BrisaStateVariable *BrisaService::getVariable(const QString &variableName) {
    for (QList<BrisaStateVariable *>::iterator i =
            this->stateVariableList.begin(); i != this->stateVariableList.end(); ++i) {
        if ((*i)->getAttribute(BrisaStateVariable::Name) == variableName)
            return *i;
    }

    return 0;
}

void BrisaService::onRequest(const HttpRequest &request, BrisaWebserverSession *session)
{
    if (request.method() != "POST") {
        session->respond(HttpResponse(request.httpVersion(), HttpResponse::BAD_REQUEST, true));
    }

    BrisaActionXmlParser actionXmlParser;

    {
        QIODevice *xml = request.entityBody();
        xml->seek(0);
        actionXmlParser.setXmlContent(xml->readAll());
    }

    if (actionXmlParser.parseSOAP()) {
        //If servicetype is incorrect
        if (actionXmlParser.serviceType != serviceType)
            return;

        call(actionXmlParser.method, actionXmlParser.args, session);
    } else {
        qDebug() << "BrisaService: Invalid SOAP xml format.";
        respondError(session, UPNP_INVALID_ACTION);
    }
}

inline void BrisaService::respondAction(BrisaWebserverSession *session, const BrisaOutArgument *outArgs, const QString &actionName)
{
    QByteArray message("<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n"
                       "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\""
                       " s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n"
                       "<s:Body>\r\n"
                       "<u:" + actionName.toUtf8() + "Response xmlns:u=\"" + serviceType.toUtf8() + "\">\r\n");

    for (QMap<QString, QString>::const_iterator i = outArgs->begin(); i != outArgs->end(); ++i) {
        message.append("<" + i.key() + ">" + i.value() + "</" + i.key()
                + ">\r\n");
    }

    message.append("</u:" + actionName + "Response>\r\n"
        "</s:Body>\r\n"
        "</s:Envelope>\r\n");

    // TODO: if the connection should br closed, set the flag in the HttpResponse constructor
    HttpResponse r(HttpVersion(1, 1), HttpResponse::OK);
    r.setHeader("CONTENT-LENGTH", QByteArray::number(message.size()));
    r.setEntityBody(message);
    session->respond(r);
}

inline void BrisaService::respondError(BrisaWebserverSession *session, int errorCode, QString errorDescription)
{
    if (errorDescription == "") {
            errorDescription = this->errorCodeToString(errorCode);
    }
    QString message = SOAP_ERROR_TEMPLATE.arg(QString::number(errorCode),
                                              this->errorCodeToString(errorCode));

    // TODO: if the connection should br closed, set the flag in the HttpResponse constructor
    HttpResponse r(HttpVersion(1, 1), HttpResponse::OK);
    r.setHeader("CONTENT-LENGTH", QByteArray::number(message.size()));
    r.setEntityBody(message.toUtf8());
    session->respond(r);
}

void BrisaService::setDescriptionFile(const QString &scpdFilePath) {
    this->scpdFilePath = scpdFilePath;
}

QString BrisaService::getDescriptionFile() {
    return this->scpdFilePath;
}

void BrisaService::parseDescriptionFile() {
    if (this->scpdFilePath.isEmpty())
        return;

    // TODO: Change this to only pass the file (this->scdpFilePath) and make the 
    // BrisaServiceXMLHandler class open the file when parseService method
    // is called.
    QFile file;
    file.setFileName(this->scpdFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    BrisaServiceXMLHandler *serviceXMLHandler = new BrisaServiceXMLHandler();
    serviceXMLHandler->parseService(this, &file);
    delete serviceXMLHandler;

    file.close();

    this->bindActionsToServiceMethods();
    this->connectVariablesEventSignals();
    this->setDefaultValues();
}

void BrisaService::connectVariablesEventSignals() {
    BrisaEventController *event = dynamic_cast<BrisaEventController *>
									(childWebServices.value(eventSubUrl.section('/', -1)));

    if (!event) {
        return;
	}

    foreach (BrisaStateVariable *stateVar, this->stateVariableList) {
        if (stateVar->sendEventsChange()) {
            QObject::connect(stateVar,
                             SIGNAL(changed(BrisaStateVariable *)),
                             event,
                             SLOT(variableChanged(BrisaStateVariable *)));
        }
    }
}

void BrisaService::setDefaultValues() {
    foreach (BrisaStateVariable *stateVar, this->stateVariableList) {
        stateVar->setAttribute(BrisaStateVariable::Value, stateVar->getAttribute(BrisaStateVariable::DefaultValue));
    }
}

void BrisaService::bindActionsToServiceMethods() {
    const QMetaObject *meta = this->metaObject();
	QMetaMethod method;

	// binding preAction method
    int methodIndex = meta->indexOfMethod(PRE_ACTION_SIG);
    if (methodIndex >= 0) {
		method = meta->method(methodIndex);
		if (strcmp(method.typeName(), PRE_ACTION_OUT) == 0) {
			this->preActionMethod = method;
			qDebug() << "Binding method " << PRE_ACTION_SIG << " of service ID " << this->serviceId;
		}
    }

	// binding postAction method
    methodIndex = meta->indexOfMethod(POST_ACTION_SIG);
    if (methodIndex >= 0) {
		method = meta->method(methodIndex);
		if (strcmp(method.typeName(), POST_ACTION_OUT) == 0) {
			this->postActionMethod = method;
			qDebug() << "Binding method " << POST_ACTION_SIG << " of service ID " << this->serviceId;
		}
    }

	// binding handleActionFailure method
    methodIndex = meta->indexOfMethod(FAILURE_ACTION_SIG);
    if (methodIndex >= 0) {
		method = meta->method(methodIndex);
		if (strcmp(method.typeName(), FAILURE_ACTION_OUT) == 0) {
			this->handleActionFailureMethod = method;
			qDebug() << "Binding method " << FAILURE_ACTION_SIG << " of service ID " << this->serviceId;
		}
    }

	// binding service actions methods
    for (QList<BrisaAction *>::iterator i = this->actionList.begin(); i != actionList.end(); ++i) {
		BrisaAction *action = *i;
    	QString actionName = action->getName();
    	QString methodName = actionName.toLower();

		int methodIndex = meta->indexOfMethod(qPrintable(methodName + ACTION_IN));

    	if (methodIndex < 0) {
        	qDebug() << "Error: no method named " << methodName << " was found in the "
            	     << "specified service class definition that matches with expected "
                	 << "signature " << ACTION_OUT << " " << methodName << ACTION_IN << "."
					 << "It was not possible to bind action " << actionName << " to "
					 << methodName;
			continue;
	    }
    
	    QMetaMethod method = meta->method(methodIndex);
	    if (strcmp(method.typeName(), ACTION_OUT) == 0) {
			qDebug() << "Binding method " << methodName << " of service ID " << this->serviceId
					 << " to service action " << actionName;
			action->setMethod(method, this);
	    } else {
			qDebug() << "Error: method named " << methodName << " has wrong prototype. "
	        		 << "It is expected a method prototype that matches with the prototype "
	             	 << "'" << ACTION_OUT << " " << methodName << ACTION_IN << "'. It was "
	             	 << "found a method with prototype '" << method.typeName()
	                 << " " << methodName << ACTION_IN;
		}
	}
}
