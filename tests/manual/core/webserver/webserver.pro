CONFIG += qt qxt brisa
TEMPLATE = app

BRISA += core
QT += network core
QXT += core web 

include(webserver.pri)
include(../../../../deploy/qt/brisa.prf)
