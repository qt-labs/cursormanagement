#include "cursornavigation.h"
#include "cursornavigationalgorithm.h"
#include "spatialnavigation4dir.h"
#include <QQuickWindow>
#include <QQuickItem>

const char CursorNavigation::windowPropertyName[] = "cursor_navigation";

CursorNavigation::CursorNavigation(QQuickWindow *parent)
:QObject(parent)
,m_window(parent)
,m_inputAdapter(m_window->contentItem(), this)
,m_currentItem(nullptr)
,m_rootItem(new CursorNavigationAttached(nullptr))
{
    m_rootItem->setParent(m_window->contentItem());
    m_rootItem->m_cursorNavigation = this;

    connect(m_window, &QQuickWindow::activeFocusItemChanged, this, &CursorNavigation::onActiveFocusItemChanged);
    onActiveFocusItemChanged();
}

bool CursorNavigation::move(qreal angle, qreal tolerance, bool discrete)
{
    CursorNavigationAttached *nextItem = find(angle, tolerance, discrete);

    if (nextItem) {
        setCursorOnItem(nextItem);
        return true;
    }
    return false;
}

CursorNavigationAttached *CursorNavigation::find(qreal angle, qreal tolerance, bool discrete)
{
    CursorNavigationAttached *nextItem = nullptr;
    CursorNavigationAttached *parent = m_currentItem ?
                m_currentItem->m_parentNavigable :
                m_rootItem;

    if (!m_currentItem)
        return defaultItem();

    qWarning() << "find next item, angle = " << angle << " tolerance = " << tolerance << " discrete = " << discrete;

    QList<CursorNavigationAttached*> candidates;

    do {
        candidates.append(parent->m_children);

        if (parent->trapsCursor())
            break;
        parent = parent->m_parentNavigable;
    } while (parent);

    if (candidates.isEmpty())
        return nullptr;

    CursorNavigationCommand cmd(angle, tolerance);

    if (discrete) {
        nextItem = m_navigation4Dir.getNextCandidate(candidates, m_currentItem, cmd);
    } else {
        nextItem = m_navigation360.getNextCandidate(candidates, m_currentItem, cmd);
    }

    return nextItem;
}

bool CursorNavigation::action(Action action)
{
    qWarning() << "handleActionCommand, action= " << action;
    switch (action) {
        case Forward:
        break;
        case Back:
        break;
        case Activate:
        break;
        case Escape: {
            /* if item has escapeTarget defined, set focus to that. otherwise leave
             * scope, ie. go back to parent's parent in the hierarchy and set focus
             * (back) to it (setting the focus further to one of its children
             * depends on the focus mechanism).
             * if we are already at the root item's children, nothing happens
             */
            if (!m_currentItem)
                return false;

            QQuickItem *escapeTarget = m_currentItem->m_parentNavigable->escapeTarget();
            if (!escapeTarget) {
                if (m_currentItem->m_parentNavigable == m_rootItem) {
                    return false;
                }
                escapeTarget = m_currentItem->m_parentNavigable->m_parentNavigable->item();
            }
            qWarning() << "escaping, target = " << escapeTarget;
            setCursorOnItem(nullptr);
            escapeTarget->forceActiveFocus();
            onActiveFocusItemChanged();
            //escapeTarget->setFocus(true);
            return true;
        }

        default:
        break;
    }
    return false;
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

CursorNavigationAttached *CursorNavigation::cursorNavigationAttachment(QQuickItem *item)
{
    return dynamic_cast<CursorNavigationAttached *>(qmlAttachedPropertiesObject<CursorNavigation>(item, false));
}

void CursorNavigation::setCursorOnItem(CursorNavigationAttached *item)
{
    qWarning() << "set cursor on item " << item << " , currentItem " << m_currentItem;
    if (item != m_currentItem) {
        if (m_currentItem) {
            m_currentItem->setHasCursor(false);
            //m_currentItem->item()->setFocus(false);
        }
        if (item && item->acceptsCursor()) {
            item->setHasCursor(true);
            m_currentItem = item;
            m_currentItem->item()->forceActiveFocus();
            //m_currentItem->item()->setFocus(true);
            qWarning() << "Set cursor to " << item->item();
        } else {
            qWarning() << "Set cursor to NULL";
            m_currentItem = nullptr;
        }
    }
}

void CursorNavigation::onActiveFocusItemChanged()
{
    qWarning() << "onActiveFocusItemChanged, item:" << m_window->activeFocusItem();
    setCursorOnItem(cursorNavigationAttachment(m_window->activeFocusItem()));
}

void CursorNavigation::registerItem(CursorNavigationAttached* item)
{
    qWarning() << "register item " << item;
    if (!item)
        return;

    //find first cursor navigable parent
    QQuickItem *parentItem = item->item()->parentItem();
    CursorNavigationAttached *parentCNA=nullptr;
    while (parentItem) {
        if ((parentCNA=CursorNavigation::cursorNavigationAttachment(parentItem)) && parentCNA->acceptsCursor())
            break;
        parentItem = parentItem->parentItem();
    }

    if (parentCNA) {
        item->m_parentNavigable=parentCNA;
        parentCNA->m_children.append(item);
    } else {
        m_rootItem->m_children.append(item);
        item->m_parentNavigable=m_rootItem;
    }
}

void CursorNavigation::unregisterItem(CursorNavigationAttached* item)
{
    qWarning() << "unregister item " << item;
    if (item == m_currentItem)
        setCursorOnItem(nullptr);

    if (item->m_parentNavigable)
        item->m_parentNavigable->m_children.removeOne(item);

    //TODO if the item that is being unregistered has children, they should be reassigned to the item's parent
}

CursorNavigationAttached *CursorNavigation::defaultItem()
{
    if (m_rootItem->m_children.size())
        return m_rootItem->m_children.first();
    return nullptr;
}
