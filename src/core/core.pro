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
HEADERS = brisacore.h \
    brisawebfile.h \
    brisawebservice.h \
    brisawebserviceprovider.h \
    brisawebstaticcontent.h
SOURCES = brisawebfile.cpp \
    brisawebservice.cpp \
    brisawebserviceprovider.cpp \
    brisawebstaticcontent.cpp
