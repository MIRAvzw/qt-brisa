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

#ifndef _BRISAACTION_H
#define _BRISAACTION_H

#include "brisaargument.h"
#include "brisaglobal.h"

#include <QString>
#include <QList>
#include <QMap>
#include <QObject>

namespace BrisaUpnp {

class BrisaService;
class BrisaStateVariable;

class BRISA_UPNP_EXPORT BrisaAction : public QObject
{
    Q_OBJECT

    public:
        BrisaAction(QString name="", BrisaService *service = 0, QObject *parent = 0);
        BrisaAction(const BrisaAction &action);
        virtual ~BrisaAction();

        void setName(QString name);
        QString getName() const;

        void setService(BrisaService *service);
        BrisaService *getService() const;

        BrisaStateVariable *getStateVariable(const QString &name) const;

        QList<BrisaArgument*> getArgumentList() const;

        void addArgument(QString name = "", QString direction = "",
                         QString relatedStateVariable = "");
        void addArgument(BrisaArgument *argumentA);
        void addArguments(const QList<BrisaArgument*> argumentA);

        void clearArgumentList();

        bool call(const QMap<QString, QString> &inArguments, QMap<QString, QString> &outArguments);

    protected:
        virtual QMap<QString, QString> run(const QMap<QString, QString> &inArguments);

    private:
        BrisaArgument *getInArgument(const QString &name);
        BrisaArgument *getOutArgument(const QString &name);
        BrisaArgument *getArgument(const QString &name, const QString &direction);

        QList<BrisaArgument*> argumentList;
        QString name;

        BrisaService *service;
};

}

#endif /* _BRISAACTION_H */
