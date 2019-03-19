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

import QtQuick 2.12
import CursorNavigation 1.0

Rectangle {
    id: root

    width: 150
    height: 100

    Row {

    Rectangle {
        objectName: "cnItem0"

        width: 50
        height: 50

        //only set the object name to create a default constructed attachment
        CursorNavigation.objectName: "cnItem0Attached"

    }

    Rectangle {
        objectName: "cnItem1"

        width: 50
        height: 50

        CursorNavigation.objectName: "cnItem1Attached"
        CursorNavigation.acceptsCursor: true

        Rectangle {
            width: 20
            height: 20
            objectName: "cnItem1Child"
        }

    }

    Rectangle {
        objectName: "cnItem2"

        width: 50
        height: 50

        CursorNavigation.objectName: "cnItem2Attached"
        CursorNavigation.acceptsCursor: true

        Rectangle {
            width: 20
            height: 20

            Rectangle {
                width: 10
                height: 10
                objectName: "cnItem2IndirectChild"
            }
        }

    }

    }

}
