#ifndef CURSORNAVIGATION_H
#define CURSORNAVIGATION_H

#include "cursornavigationattached.h"
#include "inputtypes.h"
#include "inputadapter.h"
#include "spatialnavigation360.h"
#include "spatialnavigation4dir.h"

#include <QObject>
#include <qqml.h>
#include <QStack>

//TODO remove useless debug prints and change over to categorized logging

class QQuickItem;

class CursorNavigation : public QObject
{
    Q_OBJECT

public:
    CursorNavigation(QQuickWindow *parent);

    //pass input events forward to the current item
    //void setMagnitude(qreal angle, qreal magnitude);
    //void setMagnitude(const QVector2D& vector);
    //move the cursor
    bool move(qreal angle, qreal tolerance, bool discrete);
    //find the next item without moving the cursor
    QQuickItem *find(qreal angle, qreal tolerance, bool discrete);
    bool action(Action action);

    static CursorNavigationAttached *qmlAttachedProperties(QObject *object);

    static CursorNavigation *cursorNavigationForWindow(QQuickWindow *window);

    static CursorNavigationAttached *cursorNavigationAttachment(QQuickItem *item);

private:
    void setCursorOnItem(CursorNavigationAttached *item);
    void onActiveFocusItemChanged();
    void registerItem(CursorNavigationAttached* item);
    void unregisterItem(CursorNavigationAttached* item);

    CursorNavigationAttached *defaultItem();

private:
    static const char windowPropertyName[];
    QQuickWindow *m_window;
    InputAdapter m_inputAdapter;
    CursorNavigationAttached *m_currentItem; //item that currently has the cursor
    SpatialNavigation360 m_navigation360;
    SpatialNavigation4Dir m_navigation4Dir;
    //a root item that is not tied to any actual QQuickItem
    CursorNavigationAttached *m_rootItem;

    friend class CursorNavigationAttached;
    friend class InputAdapter;
};

QML_DECLARE_TYPEINFO(CursorNavigation, QML_HAS_ATTACHED_PROPERTIES)

#endif // CURSORNAVIGATION_H
