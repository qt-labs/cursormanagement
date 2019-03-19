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

#include "inputadapter.h"
#include "cursornavigation.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

InputAdapter::InputAdapter(QObject *target, CursorNavigation *cursorNavigation)
    : QObject(cursorNavigation)
    ,m_target(target)
    ,m_cursorNavigation(cursorNavigation)
{
    if (m_target)
        m_target->installEventFilter(this);
}

bool InputAdapter::eventFilter(QObject *object, QEvent *event)
{
    if (object != m_target)
        return false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        return handleKeyEvent(keyEvent);
    }
    return false;
}

bool InputAdapter::handleKeyEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        m_cursorNavigation->m_rootItem->moveLeft();
        break;
    case Qt::Key_Right:
        m_cursorNavigation->m_rootItem->moveRight();
        break;
    case Qt::Key_Up:
        m_cursorNavigation->m_rootItem->moveUp();
        break;
    case Qt::Key_Down:
        m_cursorNavigation->m_rootItem->moveDown();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        m_cursorNavigation->m_rootItem->activate();
        break;
    case Qt::BackButton:
    case Qt::Key_Escape:
        m_cursorNavigation->m_rootItem->escape();
        break;
    case Qt::Key_Tab:
        m_cursorNavigation->m_rootItem->moveForward();
        break;
    case Qt::Key_Backtab:
        m_cursorNavigation->m_rootItem->moveBack();
        break;
    default:
        return false;
    }

    return true;
}
