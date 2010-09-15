QT += core \
    network
QT -= gui
TARGET = webserver
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    webserver.cpp \
    webserversession.cpp
include(webserver.pri)
HEADERS += webserver.h \
    webserversession.h
