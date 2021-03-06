/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the cursor management module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.11
import QtQuick.Controls 2.4
import CursorNavigation 1.0

CNButton {
    id: root

    implicitWidth: (textLabel.contentWidth + 40)
    implicitHeight: 40

    CursorNavigation.acceptsCursor: true

    background: Rectangle {
        anchors.fill: parent
        radius: 4
        opacity: root.pressed ? 0.6 : 0.4
        color: "grey"
    }

    contentItem: Item {
        anchors.fill: parent
        Label {
            id: textLabel
            anchors.centerIn: parent
            font.pixelSize: 14
            color: "blue"
            text: root.text
        }

        CNCursorIndicator { cursorItem : root; radius: 4}
    }

    Rotation {
        id: rot
        origin.x: root.width/2
        origin.y: root.height/2
    }

    NumberAnimation {
        id: returnAnimation
        target: rot
        property: "angle"
        duration: 400
        easing.type: Easing.InOutQuad
        from: 45
        to: 0
    }

    transform: rot

    CursorNavigation.onHasCursorChanged: {
        if (!hasCursor) {
            returnAnimation.start();
        }
    }

    function flip(angle, magnitude) {
        rot.angle = magnitude*45.0;
        var a = angle * Math.PI/180.0;
        rot.axis.x = -Math.sin(a);
        rot.axis.y = Math.cos(a);
        rot.axis.z = 0;
    }

    CursorNavigation.onMagnitudeChanged: {
        flip(angle, magnitude);
    }

    CursorNavigation.onMovedUp: {
        console.log("moved up ffs");
        flip(-90, 1);
        returnAnimation.start();
    }

    CursorNavigation.onMovedDown: {
        flip(90, 1);
        returnAnimation.start();
    }

    CursorNavigation.onMovedRight: {
        flip(0, 1);
        returnAnimation.start();
    }

    CursorNavigation.onMovedLeft: {
        flip(180, 1);
        returnAnimation.start();
    }
}
