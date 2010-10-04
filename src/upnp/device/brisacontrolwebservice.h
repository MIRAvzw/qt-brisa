#if !defined(BRISACONTROLWEBSERVICE_H) && defined USE_NEW_BRISA_WEBSERVER
#define BRISACONTROLWEBSERVICE_H

#include "brisawebservice.h"

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

#endif // BRISACONTROLWEBSERVICE_H
