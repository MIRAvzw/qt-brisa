INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += ssdp/brisassdpclient.h 
HEADERS += ssdp/brisassdpserver.h

SOURCES += ssdp/brisassdpclient.cpp 
SOURCES +=ssdp/brisassdpserver.cpp
           
win32 {
    LIBS += -lwsock32 -lws2_32
}
