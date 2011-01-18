TEMPLATE = lib
CLEAN_TARGET = BrisaCore
DEPENDPATH += .
INCLUDEPATH += .
DEFINES += BUILD_BRISA_CORE
CONFIG += QT
QT += network \
      core \
      xml
CONVENIENCE += $$CLEAN_TARGET
CONFIG += brisabuild

include(../../config.pri)
include(core.pri)
include(webserver.pri)
