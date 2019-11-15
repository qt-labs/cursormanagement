/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the cursor management module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "cursornavigation.h"
#include "cursornavigationalgorithm.h"
#include "spatialnavigation4dir.h"
#include <QQuickWindow>
#include <QQuickItem>
#include <QtMath>

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

bool CursorNavigation::move(qreal angle, qreal offset, qreal tolerance, bool discrete)
{
    QQuickItem *foundItem = find(angle + offset, tolerance, discrete);
    CursorNavigationAttached *nextItem = cursorNavigationAttachment(foundItem);

    if (nextItem) {
        setCursorOnItem(nextItem);
        return true;
    } else if (foundItem) {
        foundItem->forceActiveFocus();
        return true;
    }
    return false;
}

QQuickItem *CursorNavigation::find(qreal angle, qreal tolerance, bool discrete)
{
    if (!m_currentItem) {
        auto defaultItemRef = defaultItem();
        return defaultItemRef ? defaultItemRef->item() : nullptr;
    }

    if (m_currentItem->m_redirects.size()) {
        for (auto redirect : m_currentItem->m_redirects) {
            if (redirect->angleIsIncluded(angle)) {
                if (!redirect->target())
                    qWarning() << "Redirect target is null";
                return redirect->target();
            }
        }
    }

    CursorNavigationAttached *nextItem = nullptr;
    CursorNavigationAttached *parent = m_currentItem ?
                m_currentItem->m_parentNavigable :
                m_rootItem;
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

    return nextItem ? nextItem->item() : nullptr;
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

    return new CursorNavigationAttached(item);
}

CursorNavigation *CursorNavigation::cursorNavigationForWindow(QQuickWindow *window)
{
    if (!window)
        return nullptr;

    const QVariant &oldCursorNavigation = window->property(windowPropertyName);
    if (!oldCursorNavigation.isNull())
        return oldCursorNavigation.value<CursorNavigation *>();

    qWarning() << "Created a new CN engine";
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
    if (item != m_currentItem) {
        if (m_currentItem) {
            m_currentItem->setHasCursor(false);
            //m_currentItem->item()->setFocus(false);
        }
        if (item && item->acceptsCursor()) {
            item->setHasCursor(true);
            m_currentItem = item;
            m_currentItem->item()->forceActiveFocus();
        } else {
            m_currentItem = nullptr;
        }
    }
}

void CursorNavigation::onActiveFocusItemChanged()
{
    qWarning() << "onActiveFocusItemChanged, item:" << m_window->activeFocusItem();

    QQuickItem *item = m_window->activeFocusItem();
    while (item) {
        CursorNavigationAttached *cursorNavigable = cursorNavigationAttachment(item);
        if (cursorNavigable && cursorNavigable->available()) {
            setCursorOnItem(cursorNavigable);
            return;
        }
        item = item->parentItem();
    }
    setCursorOnItem(nullptr);
}

void CursorNavigation::registerItem(CursorNavigationAttached* item)
{
    //qWarning() << "register item " << item;
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

    /* TODO fix unregistering and reregistering navigable items with navigable children
     *
     * currently, for est results, items should define if they accpet cursor already
     * at the construction time. this will ensure that the tree is properly constructed
     * currently, unregisterin a container, is going to unregister all of its
     * navigable children too. reregisterin gthe container will reregister the children
     * regitering a container after its navigable children have been registered,
     * will not list the children under the container but as its siblings
     */

    /* TODO reparenting from window to another kind of works, but reparenting
    * within a window not so well. problems arise when reaprenting items
    * contained in an item that is also navigable. for this to work, we would
    * need to detect all parent changes, including items non navigable parents
    * and grandparents, and reorganize the internal tree when needed.
    * For now, consider reparenting as not recommended
    */
}

void CursorNavigation::unregisterItem(CursorNavigationAttached* item)
{
    //qWarning() << "unregister item " << item;
    if (item == m_currentItem)
        setCursorOnItem(nullptr);

    if (item->m_parentNavigable)
        item->m_parentNavigable->m_children.removeOne(item);

}

CursorNavigationAttached *CursorNavigation::defaultItem()
{
    if (m_rootItem->m_children.size())
        return m_rootItem->m_children.first();
    return nullptr;
}
