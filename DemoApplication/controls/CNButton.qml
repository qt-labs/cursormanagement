import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Button {
    id: root
    implicitWidth: (textLabel.contentWidth + 40)
    implicitHeight: 40

    CursorNavigation.acceptsCursor: true
    property bool hasCursor: CursorNavigation.hasCursor

    background: Rectangle {
        anchors.fill: parent
        radius: 40
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

        Rectangle {
            border.width: 2
            border.color: "red"
            anchors.fill: parent
            visible: root.hasCursor
            color: "transparent"
        }
    }
}
