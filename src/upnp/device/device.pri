INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += device/brisaactionxmlparser.h \
    device/brisadevice.h \
    device/brisadevicexmlhandler.h \
    device/brisaeventcontroller.h \
    device/brisaeventmessage.h \
    device/brisaservice.h \
    device/brisaeventsubscription.h \
    brisaabstracteventmessage.h \
    brisamulticasteventmessage.h \
    brisacontrolwebservice.h
SOURCES += device/brisadevice.cpp \
    device/brisadevicexmlhandler.cpp \
    device/brisaservice.cpp \
    device/brisaeventcontroller.cpp \
    device/brisaeventmessage.cpp \
    device/brisaeventsubscription.cpp \
    device/brisaactionxmlparser.cpp \
    brisaabstracteventmessage.cpp \
    brisamulticasteventmessage.cpp \
    brisacontrolwebservice.cpp
