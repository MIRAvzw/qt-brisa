:mod:`service` --- BrisaControlPointService class
==============================================

.. module: service
    :synopsis: Service related classes and examples

Subscribing to unicast eventing.
--------------------------------
It's very simple to subscribe for service unicast eventing. You need to
select the service object that you want to subscribe, get the event proxy and call subscribe method passing
the subscription timeout as in the following code
::

	class ControlPoint : BrisaControlPoint
	
        public:
            ControlPoint() : BrisaControlPoint() {};
        
            void subscribe(BrisaControlPointService *service, int timeout = -1);
    
            void unsubscribe(BrisaControlPointService *service);

        public slots:
            void eventReceived(BrisaEventProxy *eventProxy, QMap<QString, QString> map));

Now implement these methods and the slot on the source file
::
    void ControlPoint::subscribe(BrisaControlPointService *service, int timeout)
    {
        BrisaEventProxy *subscription = this->getSubscriptionProxy(service);

        connect(subscription, SIGNAL(eventNotification(BrisaEventProxy *, QMap<QString, QString>)),
                this, SLOT(eventReceived(BrisaEventProxy *,QMap<QString, QString>)));

        subscription->subscribe(timeout);
    }

    void ControlPoint::eventReceived(BrisaEventProxy *eventProxy,QMap<QString, QString> map)
    {
        Q_UNUSED(subscription);

        qDebug() << "Event Message!";
        for(int i = 0; i < eventVariables.keys().size(); i++) {
            qDebug() << "State Variable: " << eventVariables.keys()[i];
            qDebug() << "Value: " << eventVariables[eventVariables.keys()[i]];
        }
    }

In order to unsubscribe for service unicast eventing, you need to
select the service object that you want to unsubscribe get the event Proxy and call 
the unsubscribe method
::

    void ControlPoint unsubscribe(BrisaService *service)
    {
        BrisaEventProxy *unsubscription = this->getSubscriptionProxy(service);

        unsubscription->unsubscribe();
    }
