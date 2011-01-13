TEMPLATE        = lib
CLEAN_TARGET    = BrisaUtils
DEFINES        += BUILD_BRISA_UTILS
CONFIG         += QT
QT             += core network
CONVENIENCE    += $$CLEAN_TARGET

include(utils.pri)
include(../brisabase.pri)
