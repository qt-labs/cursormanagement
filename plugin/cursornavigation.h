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

class QQuickItem;

class CursorNavigation : public QObject
{
    Q_OBJECT

public:
    CursorNavigation(QQuickWindow *parent);

    //bool inputCommand(const CursorNavigationCommand &cmd);
    void move(qreal angle, qreal tolerance, bool discrete);
    void move(const QVector2D& vector, qreal tolerance, bool discrete);
    void action(Action action);

    static CursorNavigationAttached *qmlAttachedProperties(QObject *object);

    static CursorNavigation *cursorNavigationForWindow(QQuickWindow *window);

    static CursorNavigationAttached *cursorNavigationAttachment(QQuickItem *item);

private:
    void setCursorOnItem(CursorNavigationAttached *item);
    void onActiveFocusItemChanged();
    void registerItem(CursorNavigationAttached* item);
    void unregisterItem(CursorNavigationAttached* item);

    bool handleMove(const CursorNavigationCommand &cmd, bool discrete);

private:
    static const char windowPropertyName[];
    QQuickWindow *m_window;
    InputAdapter m_inputAdapter;
    CursorNavigationAttached *m_currentItem; //item that currently has the cursor
    //QList<CursorNavigationAlgorithm*> m_algorithms;
    SpatialNavigation360 m_navigation360;
    SpatialNavigation4Dir m_navigation4Dir;
    //a root item that is not tied to any actual QQuickItem
    CursorNavigationAttached *m_rootItem;
    //QStack<CursorNavigationAttached*> m_scopeStack;

    friend class CursorNavigationAttached;
};

QML_DECLARE_TYPEINFO(CursorNavigation, QML_HAS_ATTACHED_PROPERTIES)

#endif // CURSORNAVIGATION_H
