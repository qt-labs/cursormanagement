TARGET = cursornavigationplugin
TEMPLATE = lib

QT -= gui
QT += qml quick

CONFIG += plugin

DEFINES += PLUGIN_LIBRARY

SOURCES += \
        plugin.cpp \
    cursornavigation.cpp \
    cursornavigationattached.cpp \
    itemregister.cpp \
    inputadapter.cpp \
    cursornavigationalgorithm.cpp \
    spatialnavigation4dir.cpp \
    inputtypes.cpp

HEADERS += \
        plugin.h \
    cursornavigation.h \
    cursornavigationattached.h \
    itemregister.h \
    inputadapter.h \
    inputtypes.h \
    cursornavigationalgorithm.h \
    spatialnavigation4dir.h

pluginfiles.files += qmldir

target.path = $$[QT_INSTALL_QML]/CursorNavigation
pluginfiles.path = $$[QT_INSTALL_QML]/CursorNavigation

INSTALLS += target pluginfiles
