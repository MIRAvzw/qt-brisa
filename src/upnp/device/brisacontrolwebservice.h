#if !defined(BRISACONTROLWEBSERVICE_H) && defined USE_NEW_BRISA_WEBSERVER
#define BRISACONTROLWEBSERVICE_H

#include "brisawebservice.h"
#include "brisaaction.h"

namespace BrisaUpnp {

    class BrisaControlWebService : public Brisa::BrisaWebService
{
Q_OBJECT
public:
    explicit BrisaControlWebService(const QString &serviceType = QString(), QObject *parent = 0);

signals:
    void requestReceived(QString xml, BrisaInArgument args, Brisa::BrisaWebserverSession *server);
    void invalidRequest(Brisa::BrisaWebserverSession *server);

protected:
    void onRequest(const HttpRequest &request, Brisa::BrisaWebserverSession *session);

private:
    QString serviceType;
};

}

#endif // BRISACONTROLWEBSERVICE_H
