CONFIG += qt \
    qxt
TEMPLATE = app
BRISA += upnp
QT += xml \
    core
QXT += upnp
include(brisaservice.pri)
include(../../../../deploy/qt/brisa.prf)
