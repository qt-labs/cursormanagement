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

#ifndef CURSORNAVIGATIONATTACHED_H
#define CURSORNAVIGATIONATTACHED_H

//#include <qqml.h>
#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "redirect.h"

class CursorNavigation;
class QQuickItem;
class QQuickWindow;

class CursorNavigationAttached : public QObject
{
    Q_OBJECT
    //is included for cursor navigation
    Q_PROPERTY(bool acceptsCursor READ acceptsCursor WRITE setAcceptsCursor NOTIFY acceptsCursorChanged)
    //indicates if item is currently selected, indicated also by activeFocus property
    Q_PROPERTY(bool hasCursor READ hasCursor NOTIFY hasCursorChanged)
    //traps cursor. a trapped cursor can not be traversed outside of the item that traps it until the escape input is given
    Q_PROPERTY(bool trapsCursor READ trapsCursor WRITE setTrapsCursor NOTIFY trapsCursorChanged)
    //item to select when escaping
    Q_PROPERTY(QQuickItem *escapeTarget READ escapeTarget WRITE setEscapeTarget NOTIFY escapeTargetChanged)
    Q_PROPERTY(QQmlListProperty<Redirect> redirects READ redirects)

public:
    CursorNavigationAttached(QQuickItem *parent);
    ~CursorNavigationAttached();

    bool acceptsCursor() const;
    bool hasCursor() const;
    bool trapsCursor() const;
    QQuickItem *escapeTarget() const;
    QQmlListProperty<Redirect> redirects();

    /* indicates if the item is currently available for the navigation.
     * item might not be availble if it is disabled, invisible, outside of its
     * parent's geometry or simply not accepting cursor
     */
    bool available() const;

    QQuickItem *item() const;

public slots:
    void setAcceptsCursor(bool acceptsCursor);
    void setTrapsCursor(bool trapsCursor);
    void setEscapeTarget(QQuickItem * escapeTarget);

    /* just for passing movement changes forward. does not move the cursor.
     * events are received by the item that currently has the cursor
     */
    void setMagnitude(qreal angle, qreal magnitude);
    void setMagnitude(QVector2D vector);

    void move(qreal angle, qreal tolerance = 0);
    void move(QVector2D vector, qreal tolerance = 0);

    //find the next item with this move, without moving
    QQuickItem *find(qreal angle, qreal tolerance = 0);
    QQuickItem *find(QVector2D vector, qreal tolerance = 0);

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void activate();
    void moveForward();
    void moveBack();
    void escape();


signals:
    void acceptsCursorChanged(bool acceptsCursor);
    void hasCursorChanged(bool hasCursor);
    void trapsCursorChanged(bool trapsCursor);

    void escapeTargetChanged(QQuickItem * escapeTarget);

    void magnitudeChanged(qreal angle, qreal magnitude);
    void moved(qreal angle, qreal tolerance);
    void movedUp();
    void movedDown();
    void movedRight();
    void movedLeft();
    void activated();
    void movedForward();
    void movedBack();
    void escaped();

private slots:
    void onWindowChanged(QQuickWindow *window);

private:
    void setHasCursor(bool hasCursor);

    static void appendRedirect(QQmlListProperty<Redirect> *property, Redirect *redirect);
    static int redirectCount(QQmlListProperty<Redirect> *property);
    static Redirect *redirect(QQmlListProperty<Redirect> *property, int index);
    static void clearRedirects(QQmlListProperty<Redirect> *property);

    CursorNavigation *m_cursorNavigation;
    CursorNavigationAttached *m_parentNavigable;
    QList<CursorNavigationAttached*> m_children;

    bool m_acceptsCursor;
    bool m_hasCursor;
    bool m_trapsCursor;

    friend class CursorNavigation;
    //TODO detect if the escape target is deleted
    QQuickItem * m_escapeTarget;
    QVector<Redirect*> m_redirects;
};

#endif // CURSORNAVIGATIONATTACHED_H
