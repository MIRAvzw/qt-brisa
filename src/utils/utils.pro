TEMPLATE        = lib
CLEAN_TARGET    = BrisaUtils
DEPENDPATH     += .
INCLUDEPATH    += . ../core
DEPENDPATH     += .
INCLUDEPATH    += . ../core
DEPENDPATH     += .
INCLUDEPATH    += . ../core
unix: CONFIG         += brisabuild
DEFINES        += BUILD_BRISA_UTILS
include(../../config.pri)
CONFIG         += QT
unix: CONFIG         += brisabuild
QT             += core network
include(../../config.pri)
CONVENIENCE    += $$CLEAN_TARGET
unix: CONFIG         += brisabuild

include(utils.pri)
include(../brisabase.pri)
include(../../config.pri)
