import QtQuick 2.9
import QtQuick.Controls 2.2
import CursorNavigation 1.0

CheckBox {
    CursorNavigation.acceptsCursor: true
    Rectangle {
        anchors.fill: parent
        color: "transparent"
        border.width: 2
        border.color: "red"
        visible: parent.CursorNavigation.hasCursor
    }
}
