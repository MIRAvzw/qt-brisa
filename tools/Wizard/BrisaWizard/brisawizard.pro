HEADERS += brisawizard.h \
    dialogargument.h \
    intropage.h \
    devicepage.h \
    servicepage.h \
    actionpage.h
SOURCES += brisawizard.cpp \
    main.cpp \
    dialogargument.cpp \
    intropage.cpp \
    devicepage.cpp \
    servicepage.cpp \
    actionpage.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/dialogs/classwizard
sources.files = $$SOURCES \
    $$HEADERS \
    $$FORMS \
    $$RESOURCES \
    *.pro \
    images
sources.path = $$[QT_INSTALL_EXAMPLES]/dialogs/classwizard
QT += network \
    xml
CONFIG += QT \
    BRISA
CONFIG += qt \
  #  qxt
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
RESOURCES += brisawizard.qrc
FORMS += dialogargument.ui \
    mainwindow.ui
