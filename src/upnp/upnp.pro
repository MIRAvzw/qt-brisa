TEMPLATE = lib
CLEAN_TARGET = BrisaUpnp
DEPENDPATH += . \
    ./ssdp \
    ./controlpoint \
    ./device \
    ../core \
    ../utils
INCLUDEPATH += . \
    ./ssdp \
    ./controlpoint \
    ./device \
    ../core \
    ../utils \
    ../../deploy/include/BrisaCore \
    ../../deploy/include/BrisaUtils
DEFINES += BUILD_BRISA_UPNP
CONFIG += BRISA \
    QT \
    QXT
QT += core \
    network \
    xml
QXT += core \
    web
BRISA += core \
    utils
CONVENIENCE += $$CLEAN_TARGET
CONFIG += brisabuild
include(upnp.pri)
include(controlpoint/controlpoint.pri)
include(ssdp/ssdp.pri)
include(device/device.pri)

# Deps
include(../../config.pri)
include(../../deps/qtsoap-2.6-opensource/src/qtsoap.pri)
include(../../deploy/qt/brisa.prf)
