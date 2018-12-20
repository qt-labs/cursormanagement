import QtQuick 2.0
import CursorNavigation 1.0
import QtQuick.Layouts 1.3
import "../controls"

Item {

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
