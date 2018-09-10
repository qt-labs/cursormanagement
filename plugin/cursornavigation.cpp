#include "cursornavigation.h"
#include "cursornavigationalgorithm.h"
#include "spatialnavigation4dir.h"
#include <QQuickWindow>
#include <QQuickItem>

const char CursorNavigation::windowPropertyName[] = "cursor_navigation";

CursorNavigation::CursorNavigation(QQuickWindow *parent)
:QObject(parent)
,m_window(parent)
,m_inputAdapter(parent, this)
,m_currentItem(nullptr)
{
    m_algorithms.push_back(new SpatialNavigation4Dir(&m_itemRegister));

    connect(m_window, &QQuickWindow::activeFocusItemChanged, this, &CursorNavigation::onActiveFocusItemChanged);
    onActiveFocusItemChanged();
}

bool CursorNavigation::inputCommand(CursorNavigationCommand cmd)
{
    QQuickItem *nextItem = nullptr;

    for (auto alg : m_algorithms) {
        nextItem = alg->getNextCandidate(m_itemRegister.items(), m_currentItem, cmd);
        if (nextItem) {
            setCursorOnItem(nextItem);
            break;
        }
    }

    return true;
}

CursorNavigationAttached *CursorNavigation::qmlAttachedProperties(QObject *object)
{
    // if the object is a window, use its contentItem instead
    if (auto win = qobject_cast<QQuickWindow *>(object)) {
        object = win->contentItem();
    }

    if (!qobject_cast<QQuickItem *>(object)) {
        qWarning("Cannot manage cursor for a non-Item!");
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

void CursorNavigation::setCursorOnItem(QQuickItem *item)
{
    if (item != m_currentItem) {
        if (m_currentItem) {
            CursorNavigationAttached *current=cursorNavigationAttachment(m_currentItem);
            Q_ASSERT(current);
            m_currentItem->setFocus(false);
            current->setHasCursor(false);
        }
        CursorNavigationAttached *next=cursorNavigationAttachment(item);
        if (next) {
            next->setHasCursor(true);
            m_currentItem = item;
            m_currentItem->setFocus(true);
            qWarning() << "Set cursor to " << item;
        } else {
            qWarning() << "Set cursor to NULL";
            m_currentItem = nullptr;
        }
    }
}

void CursorNavigation::onActiveFocusItemChanged()
{
    qWarning() << "onActiveFocusItemChanged, item:" << m_window->activeFocusItem();
    setCursorOnItem(m_window->activeFocusItem());
}

CursorNavigationAttached *CursorNavigation::cursorNavigationAttachment(QQuickItem *item)
{
    return static_cast<CursorNavigationAttached *>(qmlAttachedPropertiesObject<CursorNavigation>(item, false));
}

