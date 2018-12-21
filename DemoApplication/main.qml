import QtQuick 2.9
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
    }

    contentData: Item {
        id: contentItem
        anchors.fill: parent
        StackLayout {
            anchors.fill: parent
            currentIndex: tabBar.currentIndex
            Page1 { }
            Page2 { }
            Page4 { }
            Page6 { }
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
