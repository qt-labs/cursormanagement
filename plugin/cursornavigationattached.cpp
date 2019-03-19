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

#include "cursornavigationattached.h"
#include "cursornavigation.h"
#include <QQuickItem>
#include <QQuickWindow>
#include <QtMath>

CursorNavigationAttached::CursorNavigationAttached(QQuickItem *parent)
:QObject(parent),
m_cursorNavigation(nullptr),
m_parentNavigable(nullptr),
m_acceptsCursor(false),
m_hasCursor(false),
m_trapsCursor(false),
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

void CursorNavigationAttached::setMagnitude(qreal angle, qreal magnitude)
{
    if (m_cursorNavigation && m_cursorNavigation->m_currentItem)
        m_cursorNavigation->m_currentItem->magnitudeChanged(angle, magnitude);
}

void CursorNavigationAttached::setMagnitude(QVector2D vector)
{
    if (m_cursorNavigation && m_cursorNavigation->m_currentItem)
        m_cursorNavigation->m_currentItem->magnitudeChanged(
            qRadiansToDegrees(qAtan2(vector.y(), vector.x())), vector.length());
}

void CursorNavigationAttached::move(qreal angle, qreal tolerance)
{
    if (m_cursorNavigation) {
        qWarning() << "move";
        qreal a = qDegreesToRadians(angle);
        qreal t = qDegreesToRadians(qFabs(std::fmod(tolerance, 180)));
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(a, t, false) && item)
            item->moved(a,t);
    }
}

void CursorNavigationAttached::move(QVector2D vector, qreal tolerance)
{
    if (m_cursorNavigation) {
        qWarning() << "move (vector)";
        qreal a = qAtan2(vector.y(), vector.x());
        qreal t = qDegreesToRadians(qFabs(std::fmod(tolerance, 180)));
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(a, t, false) && item)
            item->moved(a,t);
    }
}

QQuickItem *CursorNavigationAttached::find(qreal angle, qreal tolerance)
{
    if (m_cursorNavigation) {
        qreal a = qDegreesToRadians(angle);
        qreal t = qDegreesToRadians(qFabs(std::fmod(tolerance, 180)));
        return m_cursorNavigation->find(a, t, false);
    }
    return nullptr;
}

QQuickItem *CursorNavigationAttached::find(QVector2D vector, qreal tolerance)
{
    if (m_cursorNavigation) {
        qreal a = qAtan2(vector.y(), vector.x());
        qreal t = qDegreesToRadians(qFabs(std::fmod(tolerance, 180)));
        return m_cursorNavigation->find(a, t, false);
    }
    return nullptr;
}

void CursorNavigationAttached::moveUp()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(qDegreesToRadians(-90.0f), 0, true) && item)
            item->movedUp();
    }
}

void CursorNavigationAttached::moveDown()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(qDegreesToRadians(90.0f), 0, true) && item)
            item->movedDown();
    }
}

void CursorNavigationAttached::moveRight()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(qDegreesToRadians(0.0f), 0, true) && item)
            item->movedRight();
    }
}

void CursorNavigationAttached::moveLeft()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->move(qDegreesToRadians(180.0f), 0, true) && item)
            item->movedLeft();
    }
}

void CursorNavigationAttached::activate()
{
    if (m_cursorNavigation && m_cursorNavigation->m_currentItem)
        m_cursorNavigation->m_currentItem->activated();
}

void CursorNavigationAttached::moveForward()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->action(Forward) && item)
            item->movedForward();
    }
}

void CursorNavigationAttached::moveBack()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->action(Back) && item)
            item->movedBack();
    }
}

void CursorNavigationAttached::escape()
{
    if (m_cursorNavigation) {
        CursorNavigationAttached *item = m_cursorNavigation->m_currentItem;
        if (m_cursorNavigation->action(Escape) && item)
            item->escaped();
    }
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

QQmlListProperty<Redirect> CursorNavigationAttached::redirects()
{
    return QQmlListProperty<Redirect>(this, this,
                                      &CursorNavigationAttached::appendRedirect,
                                      &CursorNavigationAttached::redirectCount,
                                      &CursorNavigationAttached::redirect,
                                      &CursorNavigationAttached::clearRedirects);
}

bool CursorNavigationAttached::available() const
{
    /* TODO think again if this is necessary or even limiting for the user
     * reasons: all the conditions tested here can be done in the qml by the user if
     * they see it necessary, eg; CursorNavigation.acceptsCursor : visible it could be useful to allow cursor also on
     * disabled items (testing the intersection in qml is not that
     * straightforward but enabling clipping sets clipped items invisible)
     */

    if (m_acceptsCursor && item()->isVisible() && item()->isEnabled()) {
        QRectF parentRect(0,0,m_parentNavigable->item()->width(), m_parentNavigable->item()->height());
        QRectF thisRect = item()->mapRectToItem(m_parentNavigable->item(), QRectF(0,0,item()->width(), item()->height()));
        return parentRect.intersects(thisRect);
    }
    return false;
}

void CursorNavigationAttached::setHasCursor(bool hasCursor)
{
    if (hasCursor != m_hasCursor) {
        m_hasCursor=hasCursor;
        emit hasCursorChanged(m_hasCursor);
    }
}

void CursorNavigationAttached::appendRedirect(QQmlListProperty<Redirect> *property, Redirect *redirect)
{
    CursorNavigationAttached *cna = static_cast<CursorNavigationAttached*>(property->object);
    cna->m_redirects.append(redirect);
}

int CursorNavigationAttached::redirectCount(QQmlListProperty<Redirect> *property)
{
    CursorNavigationAttached *cna = static_cast<CursorNavigationAttached*>(property->object);
    return cna->m_redirects.count();
}

Redirect *CursorNavigationAttached::redirect(QQmlListProperty<Redirect> *property, int index)
{
    CursorNavigationAttached *cna = static_cast<CursorNavigationAttached*>(property->object);
    return cna->m_redirects.at(index);
}

void CursorNavigationAttached::clearRedirects(QQmlListProperty<Redirect> *property)
{
    CursorNavigationAttached *cna = static_cast<CursorNavigationAttached*>(property->object);
    cna->m_redirects.clear();
}

