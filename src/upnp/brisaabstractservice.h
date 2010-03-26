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

#ifndef _BRISAABSTRACTSERVICE_H
#define _BRISAABSTRACTSERVICE_H

#include "brisaaction.h"
#include "brisastatevariable.h"
#include "brisaglobal.h"

#include <qtsoap.h>

#include <QMap>
#include <QString>
#include <QObject>

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaAbstractService : public QObject
{
    Q_OBJECT

    public:
        BrisaAbstractService(QObject *parent = 0);
        BrisaAbstractService(const QString &serviceType, const QString &serviceId = "",
                             const QString &scpdUrl = "", const QString &controlUrl = "",
                             const QString &eventSubUrl = "", const QString &host = "",
                             QObject *parent = 0);
        BrisaAbstractService(BrisaAbstractService &service);

        virtual ~BrisaAbstractService();

        typedef enum { Major,
                       Minor,
                       FileAddress,
                       ServiceType,
                       ServiceId,
                       ScpdUrl,
                       ControlUrl,
                       EventSubUrl,
                       Host,
                       Port } xmlTags;

        void setAttribute(xmlTags key, const QString &value);
        QString getAttribute(xmlTags key);

        void addAction(const QString &name);
        void addAction(BrisaAction *action);
        BrisaAction *getAction(const QString &name);
        QList<BrisaAction *> getActionList();

        void addStateVariable(BrisaStateVariable *stateVariable);
        void addStateVariable(const QString &sendEvents, const QString &name,
                              const QString &datatype, const QString &defaultValue,
                              const QString &maximum, const QString &minimum, const QString &step);
        const QList<BrisaStateVariable *> getStateVariableList();

        void clear();

    signals:
        void requestFinished(QString root, QString lastMethod);

    protected:
        virtual void call(const QString &method, const QMap<QString, QString> &param) = 0;

        QList<BrisaAction *> actionList;
        QList<BrisaStateVariable *> stateVariableList;

        QString controlUrl;
        QString eventSubUrl;
        QString fileAddress;
        QString major;
        QString minor;
        QString scpdUrl;
        QString serviceType;
        QString serviceId;

        QString host;
        int port;

        QtSoapHttpTransport http;
};

}

#endif /* _BRISAABSTRACTSERVICE_H */
