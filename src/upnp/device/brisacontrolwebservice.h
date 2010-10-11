#if !defined(BRISACONTROLWEBSERVICE_H) && defined USE_NEW_BRISA_WEBSERVER
#define BRISACONTROLWEBSERVICE_H

#include "brisawebservice.h"
#include "brisaaction.h"

namespace BrisaUpnp {

    class BrisaControlWebService : public BrisaCore::BrisaWebService
{
Q_OBJECT
public:
    explicit BrisaControlWebService(const QString &serviceType = QString(), QObject *parent = 0);

signals:
    void requestReceived(QString xml, BrisaInArgument args, ::BrisaCore::BrisaWebserverSession *server);
    void invalidRequest(::BrisaCore::BrisaWebserverSession *server);

protected:
    void onRequest(const HttpRequest &request, ::BrisaCore::BrisaWebserverSession *session);

private:
    QString serviceType;
};

}

#endif // BRISACONTROLWEBSERVICE_H
