TEMPLATE = app
CONFIG += QT BRISA

QMAKE_CLEAN += file.dat
BRISA += core
QT += network core
QXT += core web

# Input
SOURCES += brisa-conf.cpp

include(../../deploy/qt/brisa.prf)

