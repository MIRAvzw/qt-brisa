#include "brisawebstaticcontent.h"

using namespace BrisaCore;

BrisaWebStaticContent::BrisaWebStaticContent(QxtAbstractWebSessionManager *sm,
                              QString content,
                              QObject *parent) :
                            	  QxtWebSlotService(sm, parent)
{
    this->content = new QString(content);
}

BrisaWebStaticContent::~BrisaWebStaticContent()
{
    delete content;
}

void BrisaWebStaticContent::index(QxtWebRequestEvent *event)
{
    postEvent(new QxtWebPageEvent(event->sessionID, event->requestID, content->toUtf8()));
}
