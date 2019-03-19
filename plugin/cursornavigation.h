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

#ifndef CURSORNAVIGATION_H
#define CURSORNAVIGATION_H

#include "cursornavigationattached.h"
#include "inputtypes.h"
#include "inputadapter.h"
#include "spatialnavigation360.h"
#include "spatialnavigation4dir.h"

#include <QObject>
#include <qqml.h>
#include <QStack>

//TODO remove useless debug prints and change over to categorized logging

class QQuickItem;

class CursorNavigation : public QObject
{
    Q_OBJECT

public:
    CursorNavigation(QQuickWindow *parent);

    //pass input events forward to the current item
    //void setMagnitude(qreal angle, qreal magnitude);
    //void setMagnitude(const QVector2D& vector);
    //move the cursor
    bool move(qreal angle, qreal tolerance, bool discrete);
    //find the next item without moving the cursor
    QQuickItem *find(qreal angle, qreal tolerance, bool discrete);
    bool action(Action action);

    static CursorNavigationAttached *qmlAttachedProperties(QObject *object);

    static CursorNavigation *cursorNavigationForWindow(QQuickWindow *window);

    static CursorNavigationAttached *cursorNavigationAttachment(QQuickItem *item);

private:
    void setCursorOnItem(CursorNavigationAttached *item);
    void onActiveFocusItemChanged();
    void registerItem(CursorNavigationAttached* item);
    void unregisterItem(CursorNavigationAttached* item);

    CursorNavigationAttached *defaultItem();

private:
    static const char windowPropertyName[];
    QQuickWindow *m_window;
    InputAdapter m_inputAdapter;
    CursorNavigationAttached *m_currentItem; //item that currently has the cursor
    SpatialNavigation360 m_navigation360;
    SpatialNavigation4Dir m_navigation4Dir;
    //a root item that is not tied to any actual QQuickItem
    CursorNavigationAttached *m_rootItem;

    friend class CursorNavigationAttached;
    friend class InputAdapter;
};

QML_DECLARE_TYPEINFO(CursorNavigation, QML_HAS_ATTACHED_PROPERTIES)

#endif // CURSORNAVIGATION_H
