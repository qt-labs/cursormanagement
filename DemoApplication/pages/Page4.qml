import QtQuick 2.0
import CursorNavigation 1.0
import QtGamepad 1.0
import "../controls"

Item {
    //CursorNavigation.acceptsCursor: true

    Timer {
        id: cooldownTimer
        interval: 500
        repeat: false
    }

    Gamepad {
        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1

        function handleMove() {
            var v = Qt.vector2d(axisLeftX, axisLeftY)
            if (v.length() >= 0.99 && !cooldownTimer.running) {
                //console.log("handle joystick move, v=" + v)
                parent.CursorNavigation.move(Qt.vector2d(axisLeftX, axisLeftY), 10)
                cooldownTimer.start()
            }
        }

        onAxisLeftXChanged: handleMove()
        onAxisLeftYChanged: handleMove()
    }

    CNButton {
        id: cNButton
        x: 20
        y: 20
    }

    CNButton {
        id: cNButton1
        x: 20
        y: 120
    }

    CNButton {
        id: cNButton2
        x: 20
        y: 220
    }

    CNButton {
        id: cNButton3
        x: 150
        y: 20
    }

    CNButton {
        id: cNButton4
        x: 150
        y: 120
    }

    CNButton {
        id: cNButton5
        x: 150
        y: 220
        focus: true
    }

    CNButton {
        id: cNButton6
        x: 280
        y: 20
    }

    CNButton {
        id: cNButton7
        x: 280
        y: 120
    }

    CNButton {
        id: cNButton8
        x: 280
        y: 220
    }

}
