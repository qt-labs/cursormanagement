QT += testlib quick
#QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    tst_cursornavigation.cpp
INCLUDEPATH += ../plugin

DISTFILES += \
    basics.qml \
    CNRect.qml \
    4WayTest.qml \
    reparenting.qml \
    reparenting2.qml \
    360Test.qml
