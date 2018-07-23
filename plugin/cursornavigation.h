#ifndef CURSORNAVIGATION_H
#define CURSORNAVIGATION_H

#include "cursornavigationattached.h"
#include "itemregister.h"
#include "inputtypes.h"
#include "inputadapter.h"

#include <QObject>
#include <qqml.h>

class QQuickItem;
class CursorNavigationAlgorithm;

class CursorNavigation : public QObject
{
    Q_OBJECT

public:
    CursorNavigation(QQuickWindow *parent);

    bool inputCommand(CursorNavigationCommand cmd);

    static CursorNavigationAttached *qmlAttachedProperties(QObject *object);

    static CursorNavigation *cursorNavigationForWindow(QQuickWindow *window);

private:
    void setCursorOnItem(QQuickItem *item);
    static CursorNavigationAttached *cursorNavigationAttachment(QQuickItem *item);

private:
    static const char windowPropertyName[];
    InputAdapter m_inputAdapter;
    QQuickItem *m_currentItem; //item that currently has the cursor
    QList<CursorNavigationAlgorithm*> m_algorithms;
    ItemRegister m_itemRegister;


    friend class CursorNavigationAttached;
};

QML_DECLARE_TYPEINFO(CursorNavigation, QML_HAS_ATTACHED_PROPERTIES)

#endif // CURSORNAVIGATION_H
