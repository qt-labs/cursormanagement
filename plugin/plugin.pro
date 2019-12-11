TARGET = cursornavigationplugin
TEMPLATE = lib

QT -= gui
QT += qml quick core

CONFIG += plugin

DEFINES += PLUGIN_LIBRARY

SOURCES += \
        plugin.cpp \
    cursornavigation.cpp \
    cursornavigationattached.cpp \
    inputadapter.cpp \
    cursornavigationalgorithm.cpp \
    spatialnavigation4dir.cpp \
    inputtypes.cpp \
    spatialnavigation360.cpp \
    redirect.cpp

HEADERS += \
        plugin.h \
    cursornavigation.h \
    cursornavigationattached.h \
    inputadapter.h \
    inputtypes.h \
    cursornavigationalgorithm.h \
    spatialnavigation4dir.h \
    spatialnavigation360.h \
    redirect.h

pluginfiles.files += qmldir

target.path = $$[QT_INSTALL_QML]/CursorNavigation
pluginfiles.path = $$[QT_INSTALL_QML]/CursorNavigation

INSTALLS += target pluginfiles
