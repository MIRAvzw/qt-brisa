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
 *
 */

#ifndef BRISASERVICE_H_
#define BRISASERVICE_H_

#include "brisaabstractservice.h"
#include "brisaglobal.h"
#include "brisaeventcontroller.h"
#include "brisaactionxmlparser.h"

#include <BrisaCore>

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaService : public BrisaAbstractService
{
    Q_OBJECT

    public:
        BrisaService(QObject *parent = 0);
        BrisaService(const QString &serviceType, const QString &serviceId = "",
                     const QString &scpdUrl = "", const QString &controlUrl = "",
                     const QString &eventSubUrl = "", const QString &host = "",
                     QObject *parent = 0);
        BrisaService(BrisaService &service);
        ~BrisaService();

        BrisaStateVariable *getVariable(const QString &variableName);

        BrisaWebServiceProvider *getWebService();
        void buildWebServiceTree(QxtAbstractWebSessionManager *sessionManager);

        void setDescriptionFile(const QString &scpdFilePath);

    public slots:
        void parseGenericRequest(const QString &method,
                                 const QMultiHash<QString, QString> &headers,
                                 const QByteArray &requestContent,
                                 int sessionId,
                                 int requestId);

    private:
        void call(const QString &method, const QMap<QString, QString> &param);

        void respondAction(const QString &actionName, const QMap<QString, QString> &outArgs);
        void respondError(int errorCode, const QString &errorString);

        void parseDescriptionFile();
        void connectVariablesEventSignals();

        BrisaWebServiceProvider *webService;

        QMap<QString, BrisaWebService *> childWebServices;

        QString scpdFilePath;
};

}

#endif /* BRISASERVICE_H_ */
