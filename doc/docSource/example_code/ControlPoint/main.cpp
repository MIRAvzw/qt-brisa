#include <QCoreApplication>
#include "controlpoint.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.processEvents();
    ControlPoint cp;
   
    return a.exec();
}
