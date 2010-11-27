#ifndef BRISACONTROLWEBSERVICE_H
#define BRISACONTROLWEBSERVICE_H

#include "brisawebservice.h"
#include "brisaaction.h"

namespace Brisa {

    class BrisaControlWebService : public BrisaWebService
{
Q_OBJECT
public:
    explicit BrisaControlWebService(const QString &serviceType = QString(), QObject *parent = 0);

signals:
    void requestReceived(QString xml, BrisaInArgument args, BrisaWebserverSession *server);
    void invalidRequest(BrisaWebserverSession *server);

protected:
    void onRequest(const HttpRequest &request, BrisaWebserverSession *session);

private:
    QString serviceType;
};

}

#endif // BRISACONTROLWEBSERVICE_H
