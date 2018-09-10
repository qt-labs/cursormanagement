import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Button {
    id: button
    CursorNavigation.acceptsCursor: true
    property bool hasCursor: CursorNavigation.hasCursor

    Rectangle {
        border.width: 2
        border.color: "red"
        anchors.fill: parent
        visible: button.hasCursor
        color: "transparent"
    }

}
