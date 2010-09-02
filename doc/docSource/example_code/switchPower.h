#ifndef _SWITCHPOWER_H_
#define _SWITCHPOWER_H_

#define SERVICE_TYPE "urn:schemas-upnp-org:service:SwitchPower:1"
#define SERVICE_ID "SwitchPower"
#define SERVICE_XML_PATH "/SwitchPower/SwitchPower-scpd.xml"
#define SERVICE_CONTROL "/SwitchPower/control"
#define SERVICE_EVENT_SUB "/SwitchPower/eventSub"

#include <BrisaUpnp/BrisaAction>
#include <BrisaUpnp/BrisaService>
#include <QtDebug>

using namespace BrisaUpnp;

// The Actions
class GetStatus : public BrisaAction
{
    public:
        GetStatus(BrisaService *service) : BrisaAction("GetStatus", service) {}

    private:
        QMap<QString, QString> run(const QMap<QString, QString> &inArguments)
        {
            Q_UNUSED(inArguments)

            QMap<QString, QString> outArgs;
            outArgs.insert("ResultStatus", this->getStateVariable("Status")
                                               ->getAttribute(BrisaStateVariable::Value));
            return outArgs;
        }
};

class GetTarget : public BrisaAction
{
    public:
        GetTarget(BrisaService *service) : BrisaAction("GetTarget", service) {}

    private:
        QMap<QString, QString> run(const QMap<QString, QString> &inArguments)
        {
            Q_UNUSED(inArguments)

            QMap<QString, QString> outArgs;
            outArgs.insert("RetTargetValue", this->getStateVariable("Target")
                                                 ->getAttribute(BrisaStateVariable::Value));
            return outArgs;
        }
};

class SetTarget : public BrisaAction
{
    public:
        SetTarget(BrisaService *service) : BrisaAction("SetTarget", service) {}

    private:
        QMap<QString, QString> run(const QMap<QString, QString> &inArguments)
        {
            this->getStateVariable("Target")->setAttribute(BrisaStateVariable::Value,
                                                           inArguments["NewTargetValue"]);
            this->getStateVariable("Status")->setAttribute(BrisaStateVariable::Value,
                                                           inArguments["NewTargetValue"]);

            QMap<QString, QString> outArgs;
            return outArgs;
        }
};

// The Service
class SwitchPower : public BrisaService
{
    public:
        SwitchPower() : BrisaService(SERVICE_TYPE,
                                     SERVICE_ID,
                                     SERVICE_XML_PATH,
                                     SERVICE_CONTROL,
                                     SERVICE_EVENT_SUB)
        {
            addAction(new SetTarget(this));
            addAction(new GetTarget(this));
            addAction(new GetStatus(this));
        }
};

#endif /* _SWITCHPOWER_H_ */
