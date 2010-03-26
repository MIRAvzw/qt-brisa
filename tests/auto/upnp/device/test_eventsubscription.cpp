#include "brisaeventsubscription.h"

#include <QString>
#include <QList>
#include <QObject>
#include <QtTest/QtTest>

using namespace BrisaUpnp;

class TestEventSubscription : public QObject
{
    Q_OBJECT

private:
    BrisaEventSubscription *subscription;
    QStringList callbacks;

private slots:

    void initTestCase()
    { qDebug("Starting EventSubscription Test"); }

    void init()
    {
        callbacks.append("http://subscription.test.brisa/controlpoint/callback/");
        callbacks.append("http://subscription.test.brisa/controlpoint/anotherCallback/");

        subscription = new BrisaEventSubscription("sid", callbacks, 1800);
    }


    void renew();
    void hasExpired();

    void getNextSeq();
    void getSid();
    void getCallbackUrls();

    void getAcceptSubscriptionResponse();

    void cleanup()
    {
        delete subscription;
    }

    void cleanupTestCase()
    {
        qDebug("test finished");
    }
};

void TestEventSubscription::getSid()
{
    QVERIFY(subscription->getSid() == "sid");
}

void TestEventSubscription::getCallbackUrls()
{
    QVERIFY(subscription->getCallbackUrls() == callbacks);
}

void TestEventSubscription::renew()
{
    qDebug("Started renew test");
    delete subscription;
    subscription = new BrisaEventSubscription("sid", callbacks, -1);
    sleep(1);
    QVERIFY(!subscription->hasExpired());

    subscription->renew();
    sleep(1);
    QVERIFY(!subscription->hasExpired());


    subscription->renew(5);
    sleep(1);
    QVERIFY(!subscription->hasExpired());
    sleep(4);
    QVERIFY(subscription->hasExpired());


    delete subscription;
    subscription = new BrisaEventSubscription("sid", callbacks, 1);
    sleep(1);
    QVERIFY(subscription->hasExpired());

    subscription->renew(5);
    sleep(2);
    QVERIFY(!subscription->hasExpired());
    sleep(3);
    QVERIFY(subscription->hasExpired());

    qDebug("renew is working properly");
}

void TestEventSubscription::hasExpired()
{
    delete subscription;
    subscription = new BrisaEventSubscription("sid", callbacks, -1);
    sleep(1);
    QVERIFY(!subscription->hasExpired());
    qDebug("Passed infinite timeout test");

    delete subscription;
    subscription = new BrisaEventSubscription("sid", callbacks, 0);
    QVERIFY(subscription->hasExpired());
    qDebug("Passed 0 seconds timeout test");

    delete subscription;
    subscription = new BrisaEventSubscription("sid", callbacks, 5);
    sleep(5);
    QVERIFY(subscription->hasExpired());
    sleep(1);
    QVERIFY(subscription->hasExpired());
    qDebug("Passed 5 seconds timeout test");
}

void TestEventSubscription::getNextSeq()
{
    QVERIFY(subscription->getNextSeq() == 0);
    qDebug("passed first event message test");

    QVERIFY(subscription->getNextSeq() == 1);
    QVERIFY(subscription->getNextSeq() == 2);
    QVERIFY(subscription->getNextSeq() == 3);

    for (quint32 i = 4; i < 4294967295L; ++i) {
        if (i % 0x1FFFFFFF == 0) {
            qDebug("Test running!");
        }
        subscription->getNextSeq();
    }

    QVERIFY(subscription->getNextSeq() == 4294967295L);

    // 4294967295 -> 1
    QVERIFY(subscription->getNextSeq() == 1);
    QVERIFY(subscription->getNextSeq() == 2);
    QVERIFY(subscription->getNextSeq() == 3);
}

void TestEventSubscription::getAcceptSubscriptionResponse()
{
    QHttpResponseHeader header = subscription->getAcceptSubscriptionResponse();
    QVERIFY(header.isValid());

    // HTTP version
    QCOMPARE(header.majorVersion(), 1);
    QCOMPARE(header.minorVersion(), 1);
    qDebug("HTTP version correct");

    // Status code
    QCOMPARE(header.statusCode(), 200);
    QVERIFY(header.reasonPhrase() == "OK");
    qDebug("HTTP status code and reason phrase correct");

    // Keys
    QStringList keys = header.keys();
    QCOMPARE(keys.removeDuplicates(), 0);
    QCOMPARE(keys.size(), 4);

    QVERIFY(header.hasKey("DATE"));
    QVERIFY(header.hasKey("SERVER"));
    QVERIFY(header.hasKey("SID"));
    QVERIFY(header.hasKey("TIMEOUT"));

    qDebug("Header keys are correct");

    // DATE
    QCOMPARE(header.value("DATE").size(), 29);
    QString dateString = header.value("DATE");
    QVERIFY(dateString.endsWith(" GMT"));

    QDateTime date = QDateTime::fromString(dateString.remove(" GMT"),
                                           "ddd, dd MMM yyyy HH:mm:ss");
    QVERIFY(date.isValid());

    qDebug("DATE value is correct");

    // SERVER
    QVERIFY(header.value("SERVER").contains(" UPnP/1.0 "));
    qDebug("SERVER value is correct");

    // SID
    QVERIFY(header.value("SID").startsWith("uuid:"));
    QVERIFY(header.value("SID") == "uuid:sid");
    qDebug("SID value is correct");

    // TIMEOUT
    if (header.value("TIMEOUT") != "infinite") {
        QVERIFY(header.value("TIMEOUT").startsWith("Second-"));
        QVERIFY(header.value("TIMEOUT").size() != QString("Second-").size());

        QString timeout = header.value("TIMEOUT").replace("Second-","");
        QVERIFY(timeout == "1800");

        int timeoutInt = -1;
        timeoutInt = timeout.toInt();
        QVERIFY(timeoutInt > -1);
    }

    qDebug("TIMEOUT value is correct");
}

QTEST_MAIN(TestEventSubscription)
#include "test_eventsubscription.moc"

