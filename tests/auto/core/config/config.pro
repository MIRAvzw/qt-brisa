CONFIG += qtestlib qt qxt
TEMPLATE = app

QMAKE_CLEAN += file.dat
BRISA += core
QT += network core
QXT += core web

include(config.pri)
include(../../../../deploy/qt/brisa.prf)
