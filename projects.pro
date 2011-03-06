#################################################
# Main projectfile
#################################################

unix:!macx:include(features/unix/brisabuild.prf)
win32:include(features/win32/brisa.prf)

TEMPLATE = subdirs
DESTDIR = deploy/libs

features.path = $$[QT_INSTALL_DATA]/mkspecs/features
features.files = deploy/qt/brisa.prf

INSTALLS += features

exists(modules.prf) {
   unix:system(rm -f modules.prf)
   win32:system(del modules.prf)
}

contains(BRISA_BUILD, core) {
   message(building core module)
   sub_core.subdir = src/core
   SUBDIRS += sub_core
   system(echo BRISA_MODULES+=core >> modules.prf)
}

contains(BRISA_BUILD, utils) {
   message(building utils module)
   sub_utils.subdir = src/utils
   SUBDIRS += sub_utils
   system(echo BRISA_MODULES+=utils >> modules.prf)
}

contains(BRISA_BUILD, upnp) {
   message(building upnp module)
   sub_upnp.subdir = src/upnp
   SUBDIRS += sub_upnp
   system(echo BRISA_MODULES+=upnp >> modules.prf)
}

QMAKE_CLEAN += modules.prf deps/qtsoap-2.7_1-opensource/qtsoap_build.log deps/libqxt/config.log deploy/qt/brisa.prf

unix:system((echo BRISAbase=$${BRISAINSTALLDIR}; echo BRISAinclude=$${include.path}; echo BRISAbin=$${bin.path}; echo BRISAlib=$${target.path}; cat modules.prf; cat deploy/qt/brisa.prf.m) > deploy/qt/brisa.prf)

win32:system((echo BRISAbase=$${BRISAINSTALLDIR}& echo BRISAinclude=$${include.path} & echo BRISAbin=$${bin.path} & echo BRISAlib=$${target.path} & type modules.prf & type deploy\qt\brisa.prf.m) > deploy\qt\brisa.prf)
