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

#include "redirect.h"
#include <QQuickItem>
#include <QtMath>
#include "inputtypes.h"

Redirect::Redirect(QObject *parent)
:QObject(parent)
,m_start(-1)
,m_end(-1)
,m_target(nullptr)
{
}

Redirect::~Redirect()
{
}

qreal Redirect::start() const
{
    return m_start;
}

qreal Redirect::end() const
{
    return m_end;
}

QQuickItem *Redirect::target() const
{
    return m_target;
}

void Redirect::setStart(qreal start)
{
    m_start = start;
    m_startR = CursorNavigationCommand::fitAngle(qDegreesToRadians(start));
}

void Redirect::setEnd(qreal end)
{
    m_end = end;
    m_endR = CursorNavigationCommand::fitAngle(qDegreesToRadians(end));
}

void Redirect::setTarget(QQuickItem *target)
{
    if (m_target) {
        disconnect(m_target, &QObject::destroyed, this, &Redirect::onTargetDestroyed);
    }
    m_target = target;
    if (m_target) {
        connect(m_target, &QObject::destroyed, this, &Redirect::onTargetDestroyed);
    }
}

bool Redirect::angleIsIncluded(qreal angle)
{
    if (m_startR > m_endR)
        return angle >= m_startR || angle <= m_endR;
    else
        return angle >= m_startR && angle <= m_endR;
}

void Redirect::onTargetDestroyed()
{
    m_target = nullptr;
}

