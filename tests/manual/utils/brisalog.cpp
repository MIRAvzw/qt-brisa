#include <BrisaUtils/BrisaLog>
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /* Initialize logging module */
    brisaLogInitialize();

    qDebug("This is a debug message");
    qWarning("This is a warning message, be careful!");
    qCritical("Don't panic");
    qFatal("Fatal.");

    return 0;
}
