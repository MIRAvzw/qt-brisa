TEMPLATE = lib
CLEAN_TARGET = BrisaCore
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_BRISA_CORE
CONFIG += QT \
    QXT
QT += network \
    core \
    xml
QXT += core \
    web
CONVENIENCE += $$CLEAN_TARGET
CONFIG += brisabuild
include(../../config.pri)
include(core.pri)

