CLEAN_TARGET     = BrisaCore
DEFINES         += BUILD_BRISA_CORE
CONFIG		+= BRISA QT
QT               = core network xml
BRISA            =
CONVENIENCE     += $$CLEAN_TARGET

include(core.pri)
include(webserver.pri)
include(../brisabase.pri)