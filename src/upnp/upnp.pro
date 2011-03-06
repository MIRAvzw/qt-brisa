TEMPLATE = lib
CLEAN_TARGET = BrisaUpnp
DEPENDPATH += . \
    ./ssdp \
    ./controlpoint \
    ./device \
    ../core \
    ../utils \
    ../../deploy/include/BrisaCore \
    ../../deploy/include/BrisaUtils
INCLUDEPATH += . \
    ./ssdp \
    ./controlpoint \
    ./device \
    ../core \
    ../utils
DEFINES += BUILD_BRISA_UPNP
CONFIG += BRISA QT 
QT += core network xml 
BRISA += core utils 
CONVENIENCE += $$CLEAN_TARGET
unix:CONFIG += brisabuild
include(upnp.pri)
include(controlpoint/controlpoint.pri)
include(ssdp/ssdp.pri)
include(device/device.pri)
include(../brisabase.pri)

# Deps
include(../../deps/qtsoap-2.7_1-opensource/src/qtsoap.pri)
