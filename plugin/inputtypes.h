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

#ifndef INPUTTYPES_H
#define INPUTTYPES_H

#include <QtGlobal>

//TODO: make these into classes w accessors

enum Action
{
    NoAction,
    Forward,    //tab
    Back,       //ctrl-tab
    Activate,   //enter/click on item
    Escape      //leave scope
};

//generic of way of describing the input that cursor management can handle
struct CursorNavigationCommand
{
    CursorNavigationCommand();

    CursorNavigationCommand(qreal angle, qreal tolerance);

    CursorNavigationCommand(Action a);

    //bool angleIsBetween(qreal begin, qreal end);

    qreal angle;          //-pi to pi
    qreal angleTolerance;  //0 to pi
    Action action;

    //test if given angle is between given sector. sector defined clockwise from begin to end
    static bool angleIsBetween(qreal angle, qreal begin, qreal end);

    //fit the given angle to be between -pi and pi
    static qreal fitAngle(qreal angle);

};

/* TODO feedback
 * feedback datatype returned for commands, describing command results
 * this could be used for example to indicate that a end of a list has been reached,
 * that might produce force feedback on certain inut devices
 */
enum CommandResult
{
    Succesful = 0,
    AreaBoundsReached,
    ListEndReached
};

//describing which boundary was met
enum Boundary {
    Undefined = 0,
    Top = 1,
    Bottom = 2,
    Right = 4,
    Left = 8
};

class CursorNavigationFeedback
{
//    Q_GADGET
//    Q_PROPERTY(CommandResult READ commandResult NOTIFY commandResultChanged )
//    Q_PROPERTY(Boundary READ boundary NOTIFY boundaryChanged )

    //feedback cases;
    //-cmd succesfull
    //-end of list reached (or just the end of whatever selection area maybe)
    //-fell back to the previous scope
};


#endif // INPUTTYPES_H
