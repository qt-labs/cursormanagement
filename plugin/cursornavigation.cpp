#include "cursornavigation.h"
#include "cursornavigationalgorithm.h"
#include "spatialnavigation4dir.h"
#include <QQuickWindow>
#include <QQuickItem>

const char CursorNavigation::windowPropertyName[] = "cursor_navigation";

CursorNavigation::CursorNavigation(QQuickWindow *parent)
:QObject(parent)
,m_inputAdapter(parent, this)
,m_currentItem(nullptr)
{
    m_algorithms.push_back(new SpatialNavigation4Dir(&m_itemRegister));
}

bool CursorNavigation::inputCommand(CursorNavigationCommand cmd)
{
    QQuickItem *nextItem;

    for (auto alg : m_algorithms) {
        nextItem = alg->getNextCandidate(m_itemRegister.items(), m_currentItem, cmd);
        if (nextItem)
            break;
    }

    if (nextItem) {
        if (m_currentItem) {
            CursorNavigationAttached *current=cursorNavigationAttachment(m_currentItem);
            Q_ASSERT(current);
            current->setHasCursor(false);
        }
        CursorNavigationAttached *next=cursorNavigationAttachment(nextItem);
        Q_ASSERT(next);
        next->setHasCursor(true);
        m_currentItem = nextItem;
    }
}

CursorNavigationAttached *CursorNavigation::qmlAttachedProperties(QObject *object)
{
    // if the object is a window, use its contentItem instead
    if (auto win = qobject_cast<QQuickWindow *>(object)) {
        object = win->contentItem();
    }

    if (!qobject_cast<QQuickItem *>(object)) {
        qWarning("Cannot manage focus for a non-Item!");
        return nullptr;
    }

    QQuickItem *item = static_cast<QQuickItem *>(object);

    // TODO: what if an object, with an already attached object, gets reparented (say, in another window?)
    // with or without a focus system.

    return new CursorNavigationAttached(item);
}

CursorNavigation *CursorNavigation::cursorNavigationForWindow(QQuickWindow *window)
{
    if (!window)
        return nullptr;

    const QVariant &oldCursorNavigation = window->property(windowPropertyName);
    if (!oldCursorNavigation.isNull())
        return oldCursorNavigation.value<CursorNavigation *>();

    CursorNavigation *cursorNavigation = new CursorNavigation(window);
    window->setProperty(windowPropertyName, QVariant::fromValue(cursorNavigation));

    //why would the context property be needed?
    /*if (QQmlEngine *engine = cn->qmlEngine(window)) {
        engine->rootContext()->setContextProperty("_cursorNavigation", cn);
    } else {
        qDebug() << "Couldn't find QQmlEngine";
    }*/

    return cursorNavigation;
}

CursorNavigationAttached *CursorNavigation::cursorNavigationAttachment(QQuickItem *item)
{
    Q_ASSERT(item);
    return static_cast<CursorNavigationAttached *>(qmlAttachedPropertiesObject<CursorNavigation>(item, false));
}

