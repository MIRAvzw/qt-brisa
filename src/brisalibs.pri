INCLUDEPATH += $${BRISA_SOURCE_TREE}/include
DEPENDPATH += $${BRISA_SOURCE_TREE}/include
unix:!macx:LIBS += -Wl,-rpath,$${BRISA_BUILD_TREE}/lib
macx:LIBS += -F$${BRISA_BUILD_TREE}/lib
LIBS += -L$${BRISA_BUILD_TREE}/lib

defineTest(brisaAddLibrary) {
    INCLUDEPATH += $${BRISA_SOURCE_TREE}/src/$$1
    INCLUDEPATH += $${BRISA_SOURCE_TREE}/include/$$2
    DEPENDPATH += $${BRISA_SOURCE_TREE}/src/$$1
    DEPENTPATH += $${BRISA_SOURCE_TREE}/include/$$2
    qtAddLibrary($$2)
}

contains(BRISA, core) {
    brisaAddLibrary(core, BrisaCore)
    BRISA += utils 
    QT  += core xml network
}

contains(BRISA, upnp) {
    brisaAddLibrary(upnp, BrisaUpnp)
    BRISA += core utils
    QT  += core xml network
}

contains(BRISA, utils) {
    brisaAddLibrary(utils, BrisaUtils)
    QT  += core network
}
