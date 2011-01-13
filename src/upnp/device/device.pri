INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += device/brisaactionxmlparser.h 
HEADERS += device/brisadevice.h 
HEADERS += device/brisadevicexmlhandler.h 
HEADERS += device/brisaeventcontroller.h 
HEADERS += device/brisaeventmessage.h 
HEADERS += device/brisaservice.h 
HEADERS += device/brisaeventsubscription.h 
HEADERS += device/brisaabstracteventmessage.h 
HEADERS += device/brisamulticasteventmessage.h 
HEADERS += device/brisacontrolwebservice.h

SOURCES += device/brisadevice.cpp 
SOURCES += device/brisadevicexmlhandler.cpp 
SOURCES += device/brisaservice.cpp 
SOURCES += device/brisaeventcontroller.cpp 
SOURCES += device/brisaeventmessage.cpp 
SOURCES += device/brisaeventsubscription.cpp 
SOURCES += device/brisaactionxmlparser.cpp 
SOURCES += device/brisaabstracteventmessage.cpp 
SOURCES += device/brisamulticasteventmessage.cpp 
SOURCES += device/brisacontrolwebservice.cpp
