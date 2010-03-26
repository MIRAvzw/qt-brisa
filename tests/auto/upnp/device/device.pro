CONFIG += qtestlib qt qxt
CONFIG += QT BRISA
TEMPLATE = app

QMAKE_CLEAN += file.dat
BRISA += upnp core utils
QT += network core xml
QXT += core web

include(device.pri)
include(../../../../deploy/qt/brisa.prf)
