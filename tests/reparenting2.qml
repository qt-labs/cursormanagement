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
