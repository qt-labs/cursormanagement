#include "cursornavigationattached.h"
#include "cursornavigation.h"
#include <QQuickItem>
#include <QQuickWindow>

CursorNavigationAttached::CursorNavigationAttached(QQuickItem *parent)
:QObject(parent),
m_acceptsCursor(true),
m_cursorNavigation(nullptr),
m_hasCursor(false)
{
    connect(parent, &QQuickItem::windowChanged, this, &CursorNavigationAttached::onWindowChanged);

    if (item()->window())
    {
        qDebug() << "Item has a window already";
        onWindowChanged(item()->window());
    }
}

bool CursorNavigationAttached::acceptsCursor() const
{
    return m_acceptsCursor;
}

void CursorNavigationAttached::setAcceptsCursor(bool acceptsCursor)
{
    if (acceptsCursor != m_acceptsCursor) {
        m_acceptsCursor=acceptsCursor;
        emit acceptsCursorChanged(m_acceptsCursor);
    }
}

bool CursorNavigationAttached::hasCursor() const
{
    return m_hasCursor;
}

bool CursorNavigationAttached::trapsCursor() const
{
    return m_trapsCursor;
}

void CursorNavigationAttached::setTrapsCursor(bool trapsCursor)
{
    if (trapsCursor != m_trapsCursor) {
        m_trapsCursor=trapsCursor;
        emit trapsCursorChanged(m_trapsCursor);
    }
}

void CursorNavigationAttached::onWindowChanged(QQuickWindow *window)
{
    qDebug() << "window changed, window = " << window;
    if (m_cursorNavigation)
        m_cursorNavigation->m_itemRegister.unregisterItem(item());

    if (window) {
        m_cursorNavigation = CursorNavigation::cursorNavigationForWindow(window);
    } else {
        m_cursorNavigation = nullptr;
    }

    if (m_cursorNavigation)
        m_cursorNavigation->m_itemRegister.registerItem(item());

    //emit focusManagerChanged();
}

QQuickItem *CursorNavigationAttached::item() const
{
    Q_ASSERT(qobject_cast<QQuickItem *>(parent()));
    return static_cast<QQuickItem *>(parent());
}

void CursorNavigationAttached::setHasCursor(bool hasCursor)
{
    if (hasCursor != m_hasCursor) {
        m_hasCursor=hasCursor;
        emit hasCursorChanged(m_hasCursor);
    }
}
