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
    ../utils
DEFINES += BUILD_BRISA_UPNP
CONFIG += BRISA QT 
QT += core network xml 
BRISA += core utils 
CONVENIENCE += $$CLEAN_TARGET
CONFIG += brisabuild
include(upnp.pri)
include(controlpoint/controlpoint.pri)
include(ssdp/ssdp.pri)
include(device/device.pri)
include(../brisabase.pri)

# Deps
include(../../deps/qtsoap-2.6-opensource/src/qtsoap.pri)
