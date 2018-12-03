#include "cursornavigationattached.h"
#include "cursornavigation.h"
#include <QQuickItem>
#include <QQuickWindow>

CursorNavigationAttached::CursorNavigationAttached(QQuickItem *parent)
:QObject(parent),
m_cursorNavigation(nullptr),
m_parentNavigable(nullptr),
m_acceptsCursor(true),
m_hasCursor(false),
m_escapeTarget(nullptr)
{
    if (parent)
        connect(parent, &QQuickItem::windowChanged, this, &CursorNavigationAttached::onWindowChanged);

    if (parent && item() && item()->window())
    {
        qDebug() << "Item has a window already";
        onWindowChanged(item()->window());
    }
}

CursorNavigationAttached::~CursorNavigationAttached()
{
    qWarning() << "~CursorNavigationAttached";
    if (m_cursorNavigation)
        m_cursorNavigation->unregisterItem(this);
}

bool CursorNavigationAttached::acceptsCursor() const
{
    return m_acceptsCursor;
}

void CursorNavigationAttached::setAcceptsCursor(bool acceptsCursor)
{
    if (acceptsCursor != m_acceptsCursor) {
        m_acceptsCursor=acceptsCursor;
        if (m_cursorNavigation) {
            if (m_acceptsCursor)
                m_cursorNavigation->registerItem(this);
            else
                m_cursorNavigation->unregisterItem(this);
        }

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

void CursorNavigationAttached::setEscapeTarget(QQuickItem *escapeTarget)
{
    if (m_escapeTarget == escapeTarget)
        return;

    m_escapeTarget = escapeTarget;
    emit escapeTargetChanged(m_escapeTarget);
}

void CursorNavigationAttached::move(qreal angle, qreal tolerance)
{
    qWarning() << "move";
    if (m_cursorNavigation)
        m_cursorNavigation->move(angle, tolerance, false);
}

void CursorNavigationAttached::move(QVector2D vector, qreal tolerance)
{
    qWarning() << "move";
    if (m_cursorNavigation)
        m_cursorNavigation->move(vector, tolerance, false);
}

QQuickItem *CursorNavigationAttached::find(qreal angle, qreal tolerance)
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->find(angle, tolerance, false);
        if (item)
            return item->item();
    }
    return nullptr;
}

QQuickItem *CursorNavigationAttached::find(QVector2D vector, qreal tolerance)
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->find(vector, tolerance, false);
        if (item)
            return item->item();
    }
    return nullptr;
}

void CursorNavigationAttached::moveUp()
{
    if (m_cursorNavigation)
        m_cursorNavigation->move(-90, 0, true);
}

void CursorNavigationAttached::moveDown()
{
    if (m_cursorNavigation)
        m_cursorNavigation->move(90, 0, true);
}

void CursorNavigationAttached::moveRight()
{
    if (m_cursorNavigation)
        m_cursorNavigation->move(0, 0, true);
}

void CursorNavigationAttached::moveLeft()
{
    if (m_cursorNavigation)
        m_cursorNavigation->move(180, 0, true);
}

void CursorNavigationAttached::activate()
{
    if (m_cursorNavigation)
        m_cursorNavigation->action(Activate);
}

void CursorNavigationAttached::forward()
{
    if (m_cursorNavigation)
        m_cursorNavigation->action(Forward);
}

void CursorNavigationAttached::back()
{
    if (m_cursorNavigation)
        m_cursorNavigation->action(Back);
}

void CursorNavigationAttached::escape()
{
    if (m_cursorNavigation)
        m_cursorNavigation->action(Escape);
}

void CursorNavigationAttached::onWindowChanged(QQuickWindow *window)
{
    qDebug() << "window changed, window = " << window;
    if (m_cursorNavigation && m_acceptsCursor)
        m_cursorNavigation->unregisterItem(this);

    if (window) {
        m_cursorNavigation = CursorNavigation::cursorNavigationForWindow(window);
    } else {
        m_cursorNavigation = nullptr;
    }

    if (m_cursorNavigation && m_acceptsCursor)
        m_cursorNavigation->registerItem(this);
}

QQuickItem *CursorNavigationAttached::item() const
{
    Q_ASSERT(qobject_cast<QQuickItem *>(parent()));
    return static_cast<QQuickItem *>(parent());
}

QQuickItem *CursorNavigationAttached::escapeTarget() const
{
    return m_escapeTarget;
}

void CursorNavigationAttached::setHasCursor(bool hasCursor)
{
    if (hasCursor != m_hasCursor) {
        m_hasCursor=hasCursor;
        emit hasCursorChanged(m_hasCursor);
    }
}

