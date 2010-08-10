QT += core \
    network
QT -= gui
TARGET = webserver
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    httprequest.cpp \
    httpserver.cpp \
    httpsession.cpp \
    tcpserver.cpp \
    httpresponse.cpp \
    webserversession.cpp \
    httpversion.cpp \
    webserver.cpp
HEADERS += httprequest.h \
    httpserver.h \
    httpsession.h \
    tcpserver.h \
    httpresponse.h \
    webserversession.h \
    httpversion.h \
    webserver.h \
    webresource.h
