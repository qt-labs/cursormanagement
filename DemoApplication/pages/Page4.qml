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

    Rectangle {
        id: pointerRect
        border.color: "orange"
        border.width: 1
        visible: false
        color: "transparent"
    }

    Gamepad {
        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1

        function handleMove() {
            var v = Qt.vector2d(axisLeftX, axisLeftY)
            if (v.length() >= 0.99 && !cooldownTimer.running) {
                //console.log("handle joystick move, v=" + v)
                parent.CursorNavigation.move(Qt.vector2d(axisLeftX, axisLeftY), 10)
                cooldownTimer.start()
            } else if (v.length() >= 0.1) {
                parent.CursorNavigation.setMagnitude(v)
                var item = parent.CursorNavigation.find(v, 10)
                //cooldownTimer.start()
                if (item != undefined) {
                    pointerRect.x = item.x
                    pointerRect.y = item.y
                    pointerRect.width = item.width
                    pointerRect.height = item.height
                    pointerRect.visible = true
                }
            } else {
                parent.CursorNavigation.setMagnitude(0,0)
                pointerRect.visible = false
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
