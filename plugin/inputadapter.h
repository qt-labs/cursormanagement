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

#ifndef INPUTADAPTER_H
#define INPUTADAPTER_H

#include <QObject>
#include "inputtypes.h"

class CursorNavigation;
class QQuickWindow;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

/* filter various input events and translate them for the cursor navigation.
 * it is possible to interpret mouse events as joystick/swipe events
 * Set instance of this class as an input filter to the window or component that
 * is being tracked.
 * Events are passed forward to the CursorNavigation class, which should accept
 * the event or reject it. When rejected, event is passed on.
 */

class InputAdapter : public QObject
{
    Q_OBJECT
public:
    InputAdapter(QObject *target, CursorNavigation *cursorNavigation);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    bool handleKeyEvent(QKeyEvent *ev);
    bool handleMouseEvent(QMouseEvent *ev);
    bool handleWheelEvent(QWheelEvent *ev);

    QObject *const m_target;
    CursorNavigation *m_cursorNavigation;

};

#endif // INPUTADAPTER_H
