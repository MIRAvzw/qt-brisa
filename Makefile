#############################################################################
# Makefile for building: projects
# Generated by qmake (2.01a) (Qt 4.6.2) on: Mon May 3 19:17:41 2010
# Project:  projects.pro
# Template: subdirs
# Command: /usr/bin/qmake -unix -o Makefile projects.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-src-core \
		sub-src-utils \
		sub-src-upnp

src/core/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src/core/ || $(MKDIR) src/core/ 
	cd src/core/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/core/core.pro -unix -o $(MAKEFILE)
sub-src-core-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src/core/ || $(MKDIR) src/core/ 
	cd src/core/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/core/core.pro -unix -o $(MAKEFILE)
sub-src-core: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE)
sub-src-core-make_default: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) 
sub-src-core-make_first: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) first
sub-src-core-all: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) all
sub-src-core-clean: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-core-distclean: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-core-install_subtargets: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) install
sub-src-core-uninstall_subtargets: src/core/$(MAKEFILE) FORCE
	cd src/core/ && $(MAKE) -f $(MAKEFILE) uninstall
src/utils/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src/utils/ || $(MKDIR) src/utils/ 
	cd src/utils/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/utils/utils.pro -unix -o $(MAKEFILE)
sub-src-utils-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src/utils/ || $(MKDIR) src/utils/ 
	cd src/utils/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/utils/utils.pro -unix -o $(MAKEFILE)
sub-src-utils: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE)
sub-src-utils-make_default: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) 
sub-src-utils-make_first: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) first
sub-src-utils-all: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) all
sub-src-utils-clean: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-utils-distclean: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-utils-install_subtargets: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) install
sub-src-utils-uninstall_subtargets: src/utils/$(MAKEFILE) FORCE
	cd src/utils/ && $(MAKE) -f $(MAKEFILE) uninstall
src/upnp/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src/upnp/ || $(MKDIR) src/upnp/ 
	cd src/upnp/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/upnp/upnp.pro -unix -o $(MAKEFILE)
sub-src-upnp-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src/upnp/ || $(MKDIR) src/upnp/ 
	cd src/upnp/ && $(QMAKE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/src/upnp/upnp.pro -unix -o $(MAKEFILE)
sub-src-upnp: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE)
sub-src-upnp-make_default: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) 
sub-src-upnp-make_first: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) first
sub-src-upnp-all: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) all
sub-src-upnp-clean: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-upnp-distclean: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-upnp-install_subtargets: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) install
sub-src-upnp-uninstall_subtargets: src/upnp/$(MAKEFILE) FORCE
	cd src/upnp/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: projects.pro .qmake.cache /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		.qmake.cache \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		config.pri \
		deploy/qt/brisa.prf \
		features/brisabuild.prf \
		features/unix/brisabuild.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/silent.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -unix -o Makefile projects.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
.qmake.cache:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
config.pri:
deploy/qt/brisa.prf:
features/brisabuild.prf:
features/unix/brisabuild.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/silent.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -unix -o Makefile projects.pro

qmake_all: sub-src-core-qmake_all sub-src-utils-qmake_all sub-src-upnp-qmake_all FORCE

make_default: sub-src-core-make_default sub-src-utils-make_default sub-src-upnp-make_default FORCE
make_first: sub-src-core-make_first sub-src-utils-make_first sub-src-upnp-make_first FORCE
all: sub-src-core-all sub-src-utils-all sub-src-upnp-all FORCE
clean: sub-src-core-clean sub-src-utils-clean sub-src-upnp-clean FORCE
	-$(DEL_FILE) *.gcda
	-$(DEL_FILE) *.gcno
	-$(DEL_FILE) modules.prf
	-$(DEL_FILE) deps/qtsoap-2.6-opensource/qtsoap_build.log
	-$(DEL_FILE) deps/libqxt/config.log
	-$(DEL_FILE) deploy/qt/brisa.prf
distclean: sub-src-core-distclean sub-src-utils-distclean sub-src-upnp-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-src-core-install_subtargets sub-src-utils-install_subtargets sub-src-upnp-install_subtargets FORCE
uninstall_subtargets: sub-src-core-uninstall_subtargets sub-src-utils-uninstall_subtargets sub-src-upnp-uninstall_subtargets FORCE

astyle:
	astyle --pad=oper --unpad=paren --convert-tabs --brackets=break --indent-namespaces

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install_features: FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/usr/share/qt4/mkspecs/features/ || $(MKDIR) $(INSTALL_ROOT)/usr/share/qt4/mkspecs/features/ 
	-$(INSTALL_FILE) /my/projects/brisa/svn/brisa/qt/trunk/qt-brisa/deploy/qt/brisa.prf $(INSTALL_ROOT)/usr/share/qt4/mkspecs/features/


uninstall_features:  FORCE
	-$(DEL_FILE) -r $(INSTALL_ROOT)/usr/share/qt4/mkspecs/features/brisa.prf
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/share/qt4/mkspecs/features/ 


install: install_subtargets install_features  FORCE

uninstall: uninstall_features  uninstall_subtargets FORCE

FORCE:

