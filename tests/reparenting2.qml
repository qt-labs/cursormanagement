/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the cursor management module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import CursorNavigation 1.0
import QtQuick.Controls 2.5

Item {
    width: 130
    height: 170

    CNRect {
        x: 10
        y: 20
    }

    CNRect {
        x: 10
        y: 80
    }


    Rectangle {
        id: rect0
        x: 50
        y: 10
        width: 70
        height: 40

        color: "blue"

        FocusScope {
            CursorNavigation.acceptsCursor: true
            anchors.fill: parent

            CNRect {
                x: 10
                y: 10
                focus: true
            }

            CNRect {
                objectName: "movableItem"
                id: movableItem
                x: 40
                y: 10
            }
        }
    }

    Rectangle {
        id: rect1
        x: 50
        y: 70
        width: 70
        height: 40

        color: "lightblue"

        CNRect {
            x: 10
            y: 10
        }
    }

    Button {
        x: 10
        y: 120

        onClicked: {
            movableItem.parent = rect1
        }
    }
}
