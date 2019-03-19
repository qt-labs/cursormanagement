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

import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGamepad 1.0

import CursorNavigation 1.0
import controls 1.0
import "pages"

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: qsTr("Cursor Navigation Demo Application")

    MessageDialog {
        id: dialog
        visible: false
        x: window.x+window.width/2-dialog.width/2
        y: window.y+window.height/2-dialog.height/2
    }

    Shortcut {
        id: dialogSC
        sequence: "p"
        onActivated: {
            dialog.visible = true;
        }
    }

    /* there are alternative ways to implement a tabbar. the traditional tabbar has
     * problems with CursorNavigation: when trying to navigate the cursor on it
     * right after launching the application, the cursor will not be passed onto
     * the children. However, if clicked first, the navigation works. Another
     * workaround is to force the active focus on one of the tabs.
     * The listview approach works right out of the box
     */

    header:/* ListView {
        id: tabBar
        orientation: ListView.Horizontal
        width: window.width
        height: 40
        CursorNavigation.acceptsCursor: true

        delegate: Rectangle {
            CursorNavigation.acceptsCursor: true
            CursorNavigation.onHasCursorChanged: {
                if (CursorNavigation.hasCursor)
                    tabBar.currentIndex = index
            }
            width: tabBar.width/tabBar.count
            height: 40
            border.width: 2
            border.color: CursorNavigation.hasCursor ? "red" : "transparent"

            Text { anchors.centerIn: parent; text: pageName}
        }

        model: ListModel {
            ListElement {
                pageName: "Page 1"
            }
            ListElement {
                pageName: "Page 2"
            }
            ListElement {
                pageName: "Page 3"
            }
            ListElement {
                pageName: "Page 4"
            }
            ListElement {
                pageName: "Page 5"
            }
            ListElement {
                pageName: "Map"
            }
        }

    }*/

    TabBar {
        id: tabBar
        width: window.width
        CursorNavigation.acceptsCursor: true

        CNTabButton {
            id: defaultButton
            text: qsTr("Basics and scopes")
            focus: true
        }
        CNTabButton {
            text: qsTr("Lists etc")
        }
        CNTabButton {
            text: qsTr("Flip buttons")
        }
        CNTabButton {
            text: qsTr("Map")
        }
        CNTabButton {
            text: qsTr("Redirects")
        }
    }

    contentData: Item {
        id: contentItem
        anchors.fill: parent
        StackLayout {
            anchors.fill: parent
            currentIndex: tabBar.currentIndex
            Basics { }
            Lists { }
            FlipButtons { }
            MapView { }
            Redirects { }
        }

        CursorNavigation.acceptsCursor: false

        Timer {
            id: cooldownTimer
            interval: 500
            repeat: false
        }

        Rectangle {
            id: pointerRect
            border.color: "orange"
            border.width: 1
            visible: false
            color: "transparent"
        }

        //use gamepad as another source of input. use analog stick input for magnitude information
        Gamepad {
            deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1

            function handleMove() {
                var v = Qt.vector2d(axisLeftX, axisLeftY);
                if (v.length() >= 0.99 && !cooldownTimer.running) {
                    //console.log("handle joystick move, v=" + v)
                    contentItem.CursorNavigation.move(Qt.vector2d(axisLeftX, axisLeftY), 10);
                    cooldownTimer.start();
                } else if (v.length() >= 0.1) {
                    contentItem.CursorNavigation.setMagnitude(v);
                    /*var item = parent.CursorNavigation.find(v, 10)
                    //cooldownTimer.start()
                    if (item != undefined) {
                        pointerRect.x = item.x
                        pointerRect.y = item.y
                        pointerRect.width = item.width
                        pointerRect.height = item.height
                        pointerRect.visible = true
                    }*/
                } else {
                    contentItem.CursorNavigation.setMagnitude(0,0);
                    pointerRect.visible = false;
                }
            }

            onAxisLeftXChanged: { handleMove(); }
            onAxisLeftYChanged: { handleMove(); }
            onButtonAChanged: { if (buttonA) { contentItem.CursorNavigation.activate(); } }
            onButtonBChanged: { if (buttonB) { contentItem.CursorNavigation.activate(); } }
        }
    }

    //a trick that ensures the cursor can be moved on the tabbar without needing to click teh tabbar first
    Component.onCompleted: {
        defaultButton.forceActiveFocus();
    }
}
