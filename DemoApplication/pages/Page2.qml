import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    RowLayout {
        anchors.fill: parent
        spacing: 10

        Column {
            CNListView {
                id: listView
                width: 198
                height: 359
                //anchors.right: parent.right
                //anchors.top: parent.top
                //anchors.topMargin: 20
                spacing: 4
                clip: true

                model: ListModel {
                    ListElement {
                        name: "Grey"
                        colorCode: "grey"
                    }
                    ListElement {
                        name: "Red"
                        colorCode: "red"
                    }
                    ListElement {
                        name: "Blue"
                        colorCode: "blue"
                    }
                    ListElement {
                        name: "Green"
                        colorCode: "green"
                    }
                    ListElement {
                        name: "Cyan"
                        colorCode: "cyan"
                    }
                    ListElement {
                        name: "Magenta"
                        colorCode: "magenta"
                    }
                    ListElement {
                        name: "Yellow"
                        colorCode: "yellow"
                    }
                    ListElement {
                        name: "Black"
                        colorCode: "black"
                    }
                    ListElement {
                        name: "Aliceblue"
                        colorCode: "aliceblue"
                    }
                    ListElement {
                        name: "Blueviolet"
                        colorCode: "blueviolet"
                    }
                    ListElement {
                        name: "Coral"
                        colorCode: "coral"
                    }
                }
            }
            CNButton {
                anchors.horizontalCenter: parent.horizontalCenter
                id: button3
                //anchors.top: listView.bottom
                //anchors.topMargin: 20
                //anchors.right: parent.right
                //anchors.rightMargin: 60
                text: qsTr("Button")
            }
        }
        Column {
            //anchors.verticalCenter: parent.verticalCenter
            //anchors.left: parent.left
            //anchors.leftMargin: 50
            spacing: 30
            CNButton {
                text: qsTr("Button")
            }

            CNButton {
                text: qsTr("Button")
            }

            CNButton {
                text: qsTr("Button")
            }
        }

    }
}
