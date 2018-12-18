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
        if (!hasCursor)
            returnAnimation.start()
    }

    function flip(angle, magnitude) {
        rot.angle = magnitude*45.0;
        var a = angle * Math.PI/180.0
        rot.axis.x = -Math.sin(a)
        rot.axis.y = Math.cos(a)
        rot.axis.z = 0
    }

    CursorNavigation.onMagnitudeChanged: {
        flip(angle, magnitude)
    }


    CursorNavigation.onMovedUp: {
        console.log("moved up ffs")
        flip(-90, 1);
        returnAnimation.start()
    }

    CursorNavigation.onMovedDown: {
        flip(90, 1);
        returnAnimation.start()
    }

    CursorNavigation.onMovedRight: {
        flip(0, 1);
        returnAnimation.start()
    }

    CursorNavigation.onMovedLeft: {
        flip(180, 1);
        returnAnimation.start()
    }
}
