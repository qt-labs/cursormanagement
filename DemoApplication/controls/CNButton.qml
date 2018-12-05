import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Button {
    id: root
    implicitWidth: (textLabel.contentWidth + 40)
    implicitHeight: 40

    CursorNavigation.acceptsCursor: true
    //property bool hasCursor: CursorNavigation.hasCursor

    Rotation {
        id: rot
        origin.x: root.width/2
        origin.y: root.height/2
    }

    transform: rot

    CursorNavigation.onHasCursorChanged: {
        if (!hasCursor)
            rot.angle = 0
    }

    CursorNavigation.onMagnitudeChanged: {
        rot.angle = magnitude*45.0;
        var a = angle * Math.PI/180.0
        rot.axis.x = -Math.sin(a)
        rot.axis.y = Math.cos(a)
        rot.axis.z = 0
    }

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
            visible: root.CursorNavigation.hasCursor
            color: "transparent"
        }
    }
}
