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

#include <QtDebug>
#include <QUrl>

#include "brisaservice.h"
#include "brisaservicexmlhandler.h"

using namespace BrisaUpnp;

#define SOAP_ERROR_TEMPLATE "<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n"                   \
                            "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"" \
                            "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n"\
                            "<s:Body>\r\n"                                                      \
                            "<s:Fault>\r\n"                                                     \
                            "<faultcode>s:Client</faultcode>\r\n"                               \
                            "<faultstring>UPnPError</faultstring>\r\n"                          \
                            "<detail>\r\n"                                                      \
                            "<UPnPError xmlns=\"urn:schemas-upnp-org:control-1-0\">\r\n"        \
                            "<errorCode>%1</errorCode>\r\n"                                     \
                            "<errorDescription>%2</errorDescription>\r\n"                       \
                            "</UPnPError>\r\n"                                                  \
                            "</detail>\r\n"                                                     \
                            "</s:Fault>\r\n"                                                    \
                            "</s:Body>\r\n"                                                     \
                            "</s:Envelope>\r\n"

/*!
 *  \class BrisaUpnp::BrisaService brisaservice.h BrisaUpnp/BrisaService
 *  \brief UPnP service abstraction.
 *
 *  BrisaService provides a convinient way to create UPnP services. BrisaService itself contains a
 *  webservice, so integration with the webserver is simple. You can simply create your service
 *  actions with BrisaAction, then create a new BrisaService with the proper information and simply
 *  call \a addAction() with the previously created actions. The next step is to add your service
 *   to the device.
 */

/*!
 *  Constructs a BrisaService with the given parent.
 */
BrisaService::BrisaService(QObject *parent) : BrisaAbstractService(parent)
{
}

/*!
 *  Constructs a BrisaService with the given service information.
 */
BrisaService::BrisaService(const QString &serviceType, const QString &serviceId,
                           const QString &scpdUrl, const QString &controlUrl,
                           const QString &eventSubUrl, const QString &host,
                           QObject *parent) :
    BrisaAbstractService(serviceType, serviceId, scpdUrl, controlUrl, eventSubUrl, host, parent)
{
}

/*!
 *  Copy constructor.
 */
BrisaService::BrisaService(BrisaService &serv) : BrisaAbstractService(serv)
{
}

/*!
 * Destructor.
 */
BrisaService::~BrisaService()
{
    delete webService;

    for (QMap<QString, BrisaWebService *>::iterator i = childWebServices.begin();
         i != childWebServices.end(); ++i) {
        delete i.value();
    }
    childWebServices.clear();
}

/*!
 *  This method is called when a valid SOAP action request is parsed by a BrisaActionXmlParser.
 */
void BrisaService::call(const QString &method,
                        const QMap<QString, QString> &param)
{
    for (QList<BrisaAction *>::iterator i = this->actionList.begin(); i != actionList.end(); ++i) {
        if ((*i)->getName() == method) {
            qDebug() << "BrisaService: Callback" << method;

            // call the action
            QMap<QString, QString> outArgs;
            if (!(*i)->call(param, outArgs)) {
                qDebug() << "An error has occurred during the" << (*i)->getName() << "callback.";
                // Usually, the error will be from the UPnP service client.
                // When it is a mistake of the developer, there is a debug message telling that
                // emitted at BrisaAction::call.
                respondError(402, "Invalid Args");

                return;
            }

            this->respondAction((*i)->getName(), outArgs);
            return;
        }
    }

    qDebug() << "BrisaService: Unknown callback: " << method;
    respondError(401, "Invalid Action");
}

/*!
 *  This method creates all the webservice related stuff. It creates a URL for the control path,
 *  another url for the event path, and publishs the service description XML file.
 */
void BrisaService::buildWebServiceTree(QxtAbstractWebSessionManager *sessionManager)
{
    webService = new BrisaWebServiceProvider(sessionManager, this);

    BrisaWebService *control = new BrisaWebService(sessionManager, this);
    webService->addService(controlUrl.section('/',-1), control);

    BrisaEventController *event = new BrisaEventController(sessionManager, &stateVariableList, this);
    webService->addService(eventSubUrl.section('/',-1), event);

    webService->addFile(scpdUrl.section('/',-1), scpdFilePath);

    QObject::connect(control, SIGNAL(genericRequestReceived(const QString &,
                                                            const QMultiHash<QString, QString> &,
                                                            const QByteArray &,
                                                            int,
                                                            int)),
                     this, SLOT(parseGenericRequest(const QString &,
                                                    const QMultiHash<QString, QString> &,
                                                    const QByteArray &,
                                                    int,
                                                    int)));

    childWebServices.insert(controlUrl.section('/',-1), control);
    childWebServices.insert(eventSubUrl.section('/',-1), event);

    this->parseDescriptionFile();
}

/*!
 *  Returns the requested BrisaStateVariable, if the variable doesn't exists it return 0.
 */
BrisaStateVariable *BrisaService::getVariable(const QString &variableName)
{
    for (QList<BrisaStateVariable *>::iterator i = this->stateVariableList.begin();
         i != this->stateVariableList.end(); ++i) {
        if ((*i)->getAttribute(BrisaStateVariable::Name) == variableName)
            return *i;
    }

    return 0;
}

/*!
 *  Returns the web service.
 */
BrisaWebServiceProvider *BrisaService::getWebService()
{
    return webService;
}

/*!
 * Parses the genericRequestReceived() signal coming from the webservice.
 */
void BrisaService::parseGenericRequest(const QString &method,
                                       const QMultiHash<QString, QString> &headers,
                                       const QByteArray &requestContent,
                                       int sessionId,
                                       int requestId)
{
    Q_UNUSED(headers);
    Q_UNUSED(sessionId);
    Q_UNUSED(requestId);

    if (method != "POST")
        return;

    BrisaActionXmlParser actionXmlParser;

    actionXmlParser.setXmlContent(requestContent);

    if (actionXmlParser.parseSOAP()) {
        //If servicetype is incorrect
        if (actionXmlParser.serviceType != serviceType)
            return;

        call(actionXmlParser.method, actionXmlParser.args);
    } else {
        qDebug() << "BrisaService: Invalid SOAP xml format.";
        respondError(401,"Invalid Action");
    }
}

/*!
 *  This method is called when a action is executed with no problems.
 */
void BrisaService::respondAction(const QString &actionName, const QMap<QString, QString> &outArgs)
{
    QByteArray message("<?xml version=\"1.0\"  encoding=\"utf-8\"?>\r\n"
                       "<s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\""
                       "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n"
                       "<s:Body>\r\n"
                       "<u:" + actionName.toUtf8() + "Response xmlns:u=\""
                        + serviceType.toUtf8() + "\">\r\n");

    for (QMap<QString, QString>::const_iterator i = outArgs.begin();
         i != outArgs.end(); ++i) {
        message.append("<" + i.key() + ">" + i.value() + "</" + i.key() + ">\r\n");
    }

    message.append("</u:" + actionName + "Response>\r\n"
                   "</s:Body>\r\n"
                   "</s:Envelope>\r\n");
    childWebServices.value(controlUrl.section('/',-1))->respond(message);

    qDebug() << "BrisaService finished responding action.";
}

/*!
 * Responds a SOAP error message in case of a problem occuring while performing the action.
 */
void BrisaService::respondError(int errorCode, const QString &errorString)
{
    QString message = QString(SOAP_ERROR_TEMPLATE).arg(QString::number(errorCode)).arg(errorString);
    childWebServices.value(controlUrl.section('/',-1))->respond(message.toUtf8());
}

/*!
 * Sets the service file path.
 */
void BrisaService::setDescriptionFile(const QString &scpdFilePath)
{
    this->scpdFilePath = scpdFilePath;
}

/*!
 *  Parses the service description file.
 */
void BrisaService::parseDescriptionFile()
{
    if (this->scpdFilePath.isEmpty())
        return;

    QFile file;
    file.setFileName(this->scpdFilePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    BrisaServiceXMLHandler handler;
    handler.parseService(this, &file);

    file.close();

    this->connectVariablesEventSignals();
}

/*!
 *  Connects the changed signals for event controlling purposes.
 */
void BrisaService::connectVariablesEventSignals()
{
    BrisaEventController *event =
        dynamic_cast<BrisaEventController *>(childWebServices.value(eventSubUrl.section('/', -1)));

    if (!event)
        return;

    foreach (BrisaStateVariable *s, this->stateVariableList) {
        if (s->sendEvents()) {
            QObject::connect(s, SIGNAL(changed(BrisaStateVariable *)),
                             event, SLOT(variableChanged(BrisaStateVariable *)));
        }
    }
}

