import QtQuick 2.9

import CursorNavigation 1.0
import "../controls"

Item {
    width: parent.width
    height: parent.height

    FocusScope {
        anchors.fill: parent

        Item {
            width: 500
            height: 400
            anchors.centerIn: parent

            CNButton {
                id: button
                x: 52
                y: 50
                text: qsTr("Button")
            }

            CNButton {
                id: button1
                x: 110
                y: 138
                text: qsTr("Button")
            }

            CNButton {
                id: button2
                x: 160
                y: 241
                text: qsTr("Button with default focus")
                focus: true
            }

            CNButton {
                id: button3
                x: 383
                y: 241
                text: qsTr("Button")
            }

            CNButton {
                id: button4
                x: 383
                y: 322
                text: qsTr("Button")
            }

            CNButton {
                id: button5
                x: 383
                y: 138
                text: qsTr("Button")
            }

            CNButton {
                id: button6
                x: 383
                y: 50
                text: qsTr("Button")
            }

            CNButton {
                id: button7
                x: 62
                y: 241
                text: qsTr("Button")
            }
        }
        //this seems to be the way to force focus on a newly opened dialog?
        Component.onCompleted: { forceActiveFocus(); }
    }
}
