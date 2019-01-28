import QtQuick 2.0
import CursorNavigation 1.0
import QtQuick.Layouts 1.3
import "../controls"

Item {

    Text {
        id: text
        text: "CursorNavigation allows passing the navigable items information about cursor's intended or actual movement. This example demonstrates a button that uses cursor's magnitude and movement information to implement a flipping motion that follows the cursor's direction."
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        wrapMode: Text.WordWrap
    }

    Item {
        anchors.top: text.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        GridLayout {
            columns: 4
            rows: 4
            rowSpacing: 10
            columnSpacing: 10

            anchors.centerIn: parent

            Repeater {
                CNFlipButton {
                    Layout.minimumWidth: 110
                    Layout.minimumHeight: 110
                    text: "Button " + index

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }

                model: 16
            }

        }
    }

}
