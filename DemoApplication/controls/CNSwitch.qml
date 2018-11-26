import QtQuick 2.9
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Switch {
    CursorNavigation.acceptsCursor: true
    Rectangle {
        border.width: 2
        border.color: "red"
        anchors.fill: parent
        visible: parent.CursorNavigation.hasCursor
        color: "transparent"
    }
}
