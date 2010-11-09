PROVIDER        = BRisa
TEMPLATE        = lib
TARGET          = CustomProjectWizard

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


QTC_SOURCE_DIR = /home/wvs/Downloads/qt-creator-2.0.1-src
IDE_SOURCE_TREE = $$QTC_SOURCE_DIR
QTC_BUILD_DIR = /home/wvs/Downloads/qt-creator-2.0.1-src

#DESTDIR =/home/camilo/qtcreator-build-desktop/lib/qtcreator/plugins
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

HEADERS         = CustomProjectWizard.h \
                  DoNothingPlugin.h \
                  brisawizard.h \
                  dialogargument.h \
                  intropage.h \
                  devicepage.h \
                  servicepage.h \
                  actionpage.h


SOURCES         = CustomProjectWizard.cpp \
                    DoNothingPlugin.cpp \
                    dialogargument.cpp \
                    intropage.cpp \
                    devicepage.cpp \
                    servicepage.cpp \
                    brisawizard.cpp \
                    actionpage.cpp


OTHER_FILES     = CustomProjectWizard.pluginspec

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
