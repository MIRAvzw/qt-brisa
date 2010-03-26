#include <QtCore>
#include <QCoreApplication>
#include <QtDebug>
#include <BrisaUpnp/BrisaService>

using namespace BrisaUpnp;

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
//CREATING SERVICES WITH HAND ATTRIBUTES
    BrisaService serv;
    serv = BrisaService();

    serv.setAttribute(BrisaService::FileAddress,"SampleServiceDescription.xml");

    serv.addAction("ACTION1");
    serv.addAction("ACTION2");

    QList<BrisaAction> actionList1 = serv.getActionList();

    actionList1[0].addArgument("ARGUMENT1","IN","VARIABLE1");
    actionList1[0].addArgument("ARGUMENT2","OUT","VARIABLE2");
    actionList1[0].addArgument("ARGUMENT3","IN","VARIABLE3");

    actionList1[1].addArgument("ARGUMENT4","OUT","VARIABLE4");
    actionList1[1].addArgument("ARGUMENT5","IN","VARIABLE5");
    actionList1[1].addArgument("ARGUMENT6","OUT","VARIABLE6");

    serv.addStateVariable("TRUE","STATE1","TYPE1","0","100","0","1");
    serv.addStateVariable("FALSE","STATE2","TYPE2","5","100","0","1");
    serv.addStateVariable("FALSE","STATE3","TYPE3","10","100","0","1");
    serv.addStateVariable("TRUE","STATE4","TYPE4","20","100","0","1");

    QList<BrisaStateVariable> stateVariableList1 = serv.getStateVariableList();

    stateVariableList1[0].addAllowedValue("A");
    stateVariableList1[0].addAllowedValue("B");
    stateVariableList1[0].addAllowedValue("C");

    stateVariableList1[2].addAllowedValue("E");
    stateVariableList1[2].addAllowedValue("F");
    stateVariableList1[2].addAllowedValue("G");


//GENERATING THE XML SERVICE DESCRIPTION FILE WITH SERVICE OF MEMORY
    serv.xmlGenerator();

//CREATING SERVICE WITH XML SERVICE DESCRIPTION FILE
    BrisaService serv2;
    serv2.serviceGenerator(serv.getAttribute(BrisaService::FileAddress));

    QList<BrisaAction> actionList2 = serv2.getActionList();

    for(int i = 0; i< actionList2.size() ;i++)
    {
        qDebug() << "\n--------------------------ACTION-------------------------";
        qDebug() << actionList2[i].getActionName(BrisaAction::ACTIONNAME);

        QList<BrisaArgument> argumentList2 = actionList2[i].getArgumentList();

        for(int j=0; j < argumentList2.size(); j++)
        {
            qDebug() << "\n--------------------ARGUMENT----------------------------";
            qDebug() << argumentList2[j].getArgumentAttribute(BrisaArgument::ARGUMENTNAME);
            qDebug() << argumentList2[j].getArgumentAttribute(BrisaArgument::DIRECTION);
            qDebug() << argumentList2[j].getArgumentAttribute(BrisaArgument::RELATEDSTATEVARIABLE);
            qDebug() << "--------------END-OF-ARGUMENT----------------------------";
        }
        qDebug() << "----------------------END-OF-ACTION------------------------";
    }

    QList<BrisaStateVariable> stateVariableList2 = serv2.getStateVariableList();
    for(int k=0; k< stateVariableList2.size(); k++)
    {
        qDebug() <<  "\n----------------------STATE VARIABLE---------------------";
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::Name);
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::DataType);
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::DefaultValue);
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::SendEvents);

        QList<QString> allowedValueList2 = stateVariableList2[k].getAllowedValueList();

        for(int l=0;l< allowedValueList2.size();l++)
            {
                qDebug() << allowedValueList2[l];
            }

        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::Maximum);
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::Minimum);
        qDebug() << stateVariableList2[k].getAttribute(BrisaStateVariable::Step);
        qDebug() << "--------------------END-OF-STATE-VARIABLE------------------------";
    }
    return app.exec();
}


