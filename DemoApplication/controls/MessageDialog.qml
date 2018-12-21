import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import controls 1.0

Window {
    id: root
    width: 300
    height: 150

    ColumnLayout {
        anchors.fill: parent

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: "This is a dialog!"
        }

        Row {
            Layout.alignment: Qt.AlignHCenter
            CNButton {
                text: "Yes"
                focus: true
                onClicked: { root.close(); }
            }
            CNButton {
                text: "Whatever"
                onClicked: { root.close(); }
            }
            CNButton {
                text: "No"
                onClicked: { root.close(); }
            }
        }
    }


}
