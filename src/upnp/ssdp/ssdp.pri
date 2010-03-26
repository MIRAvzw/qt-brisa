HEADERS += ssdp/brisassdpclient.h \
           ssdp/brisassdpserver.h

SOURCES += ssdp/brisassdpclient.cpp \
           ssdp/brisassdpserver.cpp
           
win32 {
    LIBS += -lwsock32 -lws2_32
}
