import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

ToolButton {
    CursorNavigation.acceptsCursor: true
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 2
        border.color: "red"
        visible: parent.CursorNavigation.hasCursor
    }
}
