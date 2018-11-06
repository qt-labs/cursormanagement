#ifndef CURSORNAVIGATION_H
#define CURSORNAVIGATION_H

#include "cursornavigationattached.h"
#include "inputtypes.h"
#include "inputadapter.h"

#include <QObject>
#include <qqml.h>
#include <QStack>

class QQuickItem;
class CursorNavigationAlgorithm;

class CursorNavigation : public QObject
{
    Q_OBJECT

public:
    CursorNavigation(QQuickWindow *parent);

    bool inputCommand(const CursorNavigationCommand &cmd);
    void move(QVector2D moveVector);
    void action();

    static CursorNavigationAttached *qmlAttachedProperties(QObject *object);

    static CursorNavigation *cursorNavigationForWindow(QQuickWindow *window);

    static CursorNavigationAttached *cursorNavigationAttachment(QQuickItem *item);

private:
    void setCursorOnItem(CursorNavigationAttached *item);
    void onActiveFocusItemChanged();
    void registerItem(CursorNavigationAttached* item);
    void unregisterItem(CursorNavigationAttached* item);

    bool handleDirectionCommand(const CursorNavigationCommand &cmd);
    bool handleActionCommand(const CursorNavigationCommand &cmd);

private:
    static const char windowPropertyName[];
    QQuickWindow *m_window;
    InputAdapter m_inputAdapter;
    CursorNavigationAttached *m_currentItem; //item that currently has the cursor
    QList<CursorNavigationAlgorithm*> m_algorithms;
    //a root item that is not tied to any actual QQuickItem
    CursorNavigationAttached *m_rootItem;
    QStack<CursorNavigationAttached*> m_scopeStack;

    friend class CursorNavigationAttached;
};

QML_DECLARE_TYPEINFO(CursorNavigation, QML_HAS_ATTACHED_PROPERTIES)

#endif // CURSORNAVIGATION_H
