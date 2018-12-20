import QtQuick 2.9
import CursorNavigation 1.0

Rectangle {
    property Item cursorItem
    border.width: 2
    border.color: "deeppink"
    anchors.fill: parent
    visible: cursorItem.CursorNavigation.hasCursor
    color: "transparent"
}
