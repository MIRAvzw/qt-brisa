#include <QtCore>
#include <QtDebug>
#include <BrisaCore/BrisaWebserver>


int main(int argc, char **argv) {
    QCoreApplication a(argc, argv);
    BrisaCore::BrisaWebserver webserver(QHostAddress(QString("127.0.0.1")), 1234);

    qDebug() << "Publishing a file.\n";

    webserver.publishFile("test_webserver.cpp", "test_webserver.cpp");

    qDebug() << "Starting webserver...\n";

    if (!webserver.start())
    {
        qDebug() << "Failed starting webserver.\n";
        return -1;
    }
    else
        qDebug() << "Finished starting...\n";

    return a.exec();
}

