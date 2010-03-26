CONFIG += qt qxt 
TEMPLATE = app
BRISA += upnp core
QT += xml core network
QXT += upnp core web
include(brisadevice.pri)
include(../../../../deploy/qt/brisa.prf)
