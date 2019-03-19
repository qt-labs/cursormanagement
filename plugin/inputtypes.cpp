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

#include "inputtypes.h"
#include <QtMath>

CursorNavigationCommand::CursorNavigationCommand()
    :angle(-1), angleTolerance(-1), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(qreal a, qreal tolerance)
    :angle(CursorNavigationCommand::fitAngle(a)), angleTolerance(tolerance), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(Action a)
    :angle(-1), angleTolerance(-1), action(a)
{}

//test if this commands angle is between given angles. clockwise from begin to end
//bool CursorNavigationCommand::angleIsBetween(qreal begin, qreal end)
//{
//    return CursorNavigationCommand::angleIsBetween(this->angle, begin, end);
//}

bool CursorNavigationCommand::angleIsBetween(qreal angle, qreal begin, qreal end)
{
    if (begin > end)
        return angle >= begin || angle <= end;
    else
        return angle >= begin && angle <= end;
}

qreal CursorNavigationCommand::fitAngle(qreal angle)
{
    if (angle >= 2.0*M_PI)
        angle = std::fmod(angle, 2.0*M_PI);

    if (angle > M_PI)
        return -M_PI + std::fmod(angle, M_PI);
    else if (angle < -M_PI)
        return M_PI + std::fmod(angle, M_PI);
    return angle;
}
