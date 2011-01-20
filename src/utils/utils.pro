TEMPLATE        = lib
CLEAN_TARGET    = BrisaUtils
DEPENDPATH     += .
INCLUDEPATH    += . ../core
DEFINES        += BUILD_BRISA_UTILS
CONFIG         += QT
QT             += core network
CONVENIENCE    += $$CLEAN_TARGET
CONFIG         += brisabuild

include(../../config.pri)
include(utils.pri)
