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

#ifndef _BRISAEVENTMESSAGE_H
#define _BRISAEVENTMESSAGE_H

#include <QObject>
#include <QList>
#include <QHttpRequestHeader>

#include "brisastatevariable.h"
#include "brisaeventsubscription.h"
#include "brisaglobal.h"

using namespace BrisaCore;

namespace BrisaUpnp {

class BRISA_UPNP_EXPORT BrisaEventMessage : public QObject
{
    Q_OBJECT

    public:
        BrisaEventMessage(BrisaEventSubscription &subscription,
                          const QList<BrisaStateVariable *> *variables,
                          QObject *parent = 0);

        QHttpRequestHeader getMessageHeader() const;
        QByteArray getMessageBody() const;

    public slots:

    signals:

    private slots:

    private:
        const QList<BrisaStateVariable *> *VARIABLES;
        const int SEQ;

        BrisaEventSubscription &subscription;
};

}

#endif /* _BRISAEVENTMESSAGE_H */
