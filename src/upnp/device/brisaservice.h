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

#include <brisaglobal.h>
#include "brisaabstractservice.h"
#include "brisaeventcontroller.h"
#include "brisaactionxmlparser.h"

namespace Brisa {
    class BrisaWebserver;

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

}

#endif /* BRISASERVICE_H_ */
