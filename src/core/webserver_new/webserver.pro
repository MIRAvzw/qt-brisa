QT += core \
    network
QT -= gui
TARGET = webserver
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
include(webserver.pri)
