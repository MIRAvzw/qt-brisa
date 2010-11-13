PROVIDER        = BRisa
TEMPLATE        = lib
TARGET          = brisaprojectwizard

QT += network \
    xml
CONFIG += QT \
    BRISA
CONFIG += qt \
    qxt
QT += core \
    network \
    xml
BRISA += upnp \
    core \
    utils
QXT += core \
    web
INSTALLS += target \
    sources


QTC_SOURCE_DIR = /home/camilo/qt-creator-2.0.1-src #change this field to your Qt Creator Source code dir
IDE_SOURCE_TREE = $$QTC_SOURCE_DIR
QTC_BUILD_DIR = /home/camilo/qtcreator-build-desktop #change this field to your Qt Creator Builded code dir

DESTDIR = $$QTC_BUILD_DIR/lib/qtcreator/plugins/BRisa
IDE_BUILD_TREE = $$QTC_BUILD_DIR

LIBS += -L$$IDE_BUILD_TREE/lib/qtcreator/ \
        -L$$IDE_BUILD_TREE/lib/qtcreator/plugins/Nokia

include( $$IDE_SOURCE_TREE/src/qtcreatorplugin.pri )
include( $$IDE_SOURCE_TREE/src/plugins/coreplugin/coreplugin.pri )
include( $$IDE_SOURCE_TREE/src/plugins/projectexplorer/projectexplorer.pri )
include( $$IDE_SOURCE_TREE/src/plugins/texteditor/texteditor.pri )

INCLUDEPATH += $$IDE_SOURCE_TREE/src \
               $$IDE_SOURCE_TREE/src/plugins \
               $$IDE_SOURCE_TREE/src/libs \
               $$IDE_SOURCE_TREE/src/libs/extensionsystem \

HEADERS         = brisaprojectwizard.h \
                  brisaplugin.h \
                  brisawizard.h \
                  dialogargument.h \
                  intropage.h \
                  devicepage.h \
                  servicepage.h \
                  actionpage.h


SOURCES         = brisaprojectwizard.cpp \
                    brisaplugin.cpp \
                    dialogargument.cpp \
                    intropage.cpp \
                    devicepage.cpp \
                    servicepage.cpp \
                    brisawizard.cpp \
                    actionpage.cpp


OTHER_FILES     = brisaprojectwizard.pluginspec

# install
target.path = $$[QT_INSTALL_EXAMPLES]/dialogs/classwizard
sources.files = $$SOURCES \
    $$HEADERS \
    $$FORMS \
    $$RESOURCES \
    *.pro \
    images
sources.path = $$[QT_INSTALL_EXAMPLES]/dialogs/classwizard
RESOURCES += brisawizard.qrc
FORMS += dialogargument.ui \
    mainwindow.ui
