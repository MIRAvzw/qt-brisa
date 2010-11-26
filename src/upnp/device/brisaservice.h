/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaservice.cpp
 * Created:
 * Description: Defines BrisaService class.
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
#ifndef BRISASERVICE_H_
#define BRISASERVICE_H_

#include "brisaglobal.h"
#include "brisaabstractservice.h"
#include "brisaeventcontroller.h"
#include "brisaactionxmlparser.h"

#ifdef USE_NEW_BRISA_WEBSERVER

namespace Brisa
{
    class BrisaWebserver;
}

#endif

namespace Brisa {

#ifdef USE_NEW_BRISA_WEBSERVER

    class BRISA_UPNP_EXPORT BrisaService: public BrisaAbstractService
    {
    Q_OBJECT
    public:

        BrisaService(QObject *parent = 0);

        BrisaService(const QString &serviceType,
                     const QString &serviceId = QString(),
                     const QString &scpdUrl = QString(),
                     const QString &controlUrl = QString(),
                     const QString &eventSubUrl = QString(),
                     const QString &host = QString(),
                     QObject *parent = 0);

        BrisaService(BrisaService &service);

        virtual ~BrisaService();

        BrisaStateVariable *getVariable(const QString &variableName);

        void buildWebServiceTree(BrisaWebserver *sessionManager);

        void setDescriptionFile(const QString &scpdFilePath);

        QString getDescriptionFile();

    protected:
        void onRequest(const HttpRequest &request, BrisaWebserverSession *session);

    private slots:
        void call(const QString &method, BrisaInArgument param, BrisaWebserverSession *);
        void onInvalidRequest(BrisaWebserverSession *session);

    private:

        void respondAction(BrisaWebserverSession *session, const BrisaOutArgument *outArgs, const QString &actionName /*= QString()*/);

        void respondError(BrisaWebserverSession *session, int errorCode, QString errorDescription = QString());

        void parseDescriptionFile();

        void connectVariablesEventSignals();

        void setDefaultValues();

        void bindActionsToServiceMethods();

        QMap<QString, BrisaWebService *> childWebServices;

        QString scpdFilePath;

        QMetaMethod preActionMethod;

        QMetaMethod postActionMethod;

        QMetaMethod handleActionFailureMethod;
    };

#else

/*!
 *  \class Brisa::BrisaService brisaservice.h BrisaUpnp/BrisaService
 *  \brief UPnP service abstraction.
 *
 *  BrisaService provides a convinient way to create UPnP services. BrisaService itself contains a
 *  webservice, so integration with the webserver is simple. You can simply create your service
 *  actions with BrisaAction, then create a new BrisaService with the proper information and simply
 *  call \a addAction() with the previously created actions. The next step is to add your service
 *   to the device.
 */
class BRISA_UPNP_EXPORT BrisaService: public BrisaAbstractService {
Q_OBJECT

public:

    /*!
     *  Constructs a BrisaService with the given parent.
     */
    BrisaService(QObject *parent = 0);

    /*!
     *  Constructs a BrisaService with the given service information.
     */
    BrisaService(const QString &serviceType,
                 const QString &serviceId = "",
                 const QString &scpdUrl = "",
                 const QString &controlUrl = "",
                 const QString &eventSubUrl = "",
                 const QString &host = "",
                 QObject *parent = 0);

    /*!
     *  Copy constructor.
     */
    BrisaService(BrisaService &service);

    /*!
     * Destructor.
     */
    ~BrisaService();

    /*!
     *  Returns the requested BrisaStateVariable, if the variable doesn't exists it return 0.
     */
    BrisaStateVariable *getVariable(const QString &variableName);

    /*!
     *  Returns the web service.
     */
    BrisaWebServiceProvider *getWebService();

    /*!
     *  This method creates all the webservice related stuff. It creates a URL for the control path,
     *  another url for the event path, and publishs the service description XML file.
     */
    void buildWebServiceTree(QxtAbstractWebSessionManager *sessionManager);

    /*!
     * Sets the service file path.
     */
    void setDescriptionFile(const QString &scpdFilePath);

    /*!
     *  Returns the service scpd path.
     */
    QString getDescriptionFile();



public slots:
    /*!
     * Parses the genericRequestReceived() signal coming from the webservice.
     */
    void parseGenericRequest(const QString &method,
                             const QMultiHash<QString, QString> &headers,
                             const QByteArray &requestContent,
                             int sessionId,
                             int requestId);

private:

    /*!
     *  This method is called when a valid SOAP action request is parsed by a BrisaActionXmlParser.
     */
    void call(const QString &method, BrisaInArgument &param);

    /*!
     *  This method is called when a action is executed with no problems.
     */
    void respondAction(const QString &actionName, const BrisaOutArgument *outArgs);

    /*!
     * Responds a SOAP error message in case of a problem occuring while performing the action.
     */
    void respondError(int errorCode, QString errorDescription = "");

    /*!
     *  Parses the service description file.
     */
    void parseDescriptionFile();

    /*!
     *  Connects the changed signals for event controlling purposes.
     */
    void connectVariablesEventSignals();

    /*!
     *  Set the DefaultValue as Value for all variables.
     */
    void setDefaultValues();

    /*!
     *  Bind defined actions in the scpd to service methods.
     */
    void bindActionsToServiceMethods();

    BrisaWebServiceProvider *webService;

    QMap<QString, BrisaWebService *> childWebServices;

    QString scpdFilePath;
   
    QMetaMethod preActionMethod;

    QMetaMethod postActionMethod;

    QMetaMethod handleActionFailureMethod;


	
};

#endif // USE_NEW_BRISA_WEBSERVER

}

#endif /* BRISASERVICE_H_ */
