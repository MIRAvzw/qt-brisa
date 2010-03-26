#include <QObject>
#include <QtTest/QtTest>
#include <BrisaCore/BrisaConfigurationManager>

using namespace BrisaCore;

class TestConfigurationManager : public QObject
{
    Q_OBJECT

private:
    BrisaConfigurationManager *manager;

private slots:

    void initTestCase()
    { qDebug("Starting ConfigurationManager Test"); }

    void init()
    {
        QString configPath("./");
        QHash<QString,QString> state;
        state["brisa.owner"] = "owner";
        state["brisa.version"] = "0.10.0";
        state["brisa.encoding"] = "utf-8'";

        manager = new BrisaConfigurationManager(configPath,state);
    }


    void setDirectAccess();
    void getDirectAccess();
    void getParameter();
    void setParameter();
    void update();

    void cleanupTestCase()
    { qDebug("test finished"); }
};

void TestConfigurationManager::getDirectAccess()
{
    QVERIFY(manager->getDirectAccess() == false);
}

void TestConfigurationManager::setDirectAccess()
{
    manager->setDirectAccess(true);
    QVERIFY(manager->getDirectAccess() == true);
}

void TestConfigurationManager::getParameter()
{
    QVERIFY(manager->getParameter("brisa","owner") == "owner");
}

void TestConfigurationManager::setParameter()
{
    manager->setParameter("brisa","owner","newOwner");
    QVERIFY(manager->getParameter("brisa","owner") == "newOwner");
}

void TestConfigurationManager::update()
{
    manager->setParameter("brisa","owner","newOwner");
    manager->save();
    manager->update();
    QVERIFY(manager->getParameter("brisa","owner") == "newOwner");
}

QTEST_MAIN(TestConfigurationManager)
#include "test_configurationmanager.moc"
