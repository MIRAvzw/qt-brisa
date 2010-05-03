isEmpty(BRISAbase){
    unix:!macx: BRISAbase = /usr/local/
    win32:      BRISAbase = C:/qt-brisa
    macx :
}

isEmpty(BRISAinclude): BRISAinclude = $${BRISAbase}/include/Brisa
isEmpty(BRISAbin):     BRISAbin     = $${BRISAbase}/bin

macx {
    isEmpty(BRISAlib):     BRISAlib = /Library/Frameworks
}

!macx {
    isEmpty(BRISAlib):     BRISAlib = $${BRISAbase}/lib
}

INCLUDEPATH     += $${BRISAinclude}
unix:!macx:LIBS += -Wl,-rpath,$${BRISAlib}
macx:LIBS       += -F$${BRISAlib}
LIBS            += -L$${BRISAlib}

contains(BRISA, core) {
    INCLUDEPATH       += $${BRISAinclude}/BrisaCore
    macx: INCLUDEPATH += $${BRISAlib}/BrisaCore.framework/HEADERS/
    qtAddLibrary(BrisaCore)
    contains(BRISA_MODULES, core):DEFINES += BRISA_CORE_LIB
}

contains(BRISA, utils) {
    INCLUDEPATH       += $${BRISAinclude}/BrisaUtils
    macx: INCLUDEPATH += $${BRISAlib}/BrisaUtils.framework/HEADERS/
    qtAddLibrary(BrisaUtils)
    contains(BRISA_MODULES, utils):DEFINES += BRISA_UTILS_LIB
}

contains(BRISA, upnp) {
    INCLUDEPATH       += $${BRISAinclude}/BrisaUpnp
    macx: INCLUDEPATH += $${BRISAlib}/BrisaUpnp.framework/HEADERS/
    qtAddLibrary(BrisaUpnp)
    contains(BRISA_MODULES, upnp):DEFINES += BRISA_UPNP_LIB
}
