import QtQuick 2.9
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Page {
    width: 600
    height: 400

    title: qsTr("Page 2")

    Label {
        text: qsTr("You are on Page 2.")
        anchors.centerIn: parent
    }

    FocusScope {
        CursorNavigation.acceptsCursor: true
        x: 385
        y: 19
        width: 198
        height: 359
        ListView {
            id: listView
            anchors.fill: parent
            spacing: 4
            focus: true

            Rectangle {
                border.width: 2
                border.color: "red"
                anchors.fill: parent
                visible: listView.activeFocus
                color: "transparent"
            }

            highlight: Rectangle {
                border.width: 2
                border.color: "red"
                color: "grey"
            }

            delegate: Item {
                x: 5
                width: listView.width
                height: 40

                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }

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
            }
        }
    }

    CNButton {
        id: button
        x: 95
        y: 54
        text: qsTr("Button")
    }

    CNButton {
        id: button1
        x: 95
        y: 158
        text: qsTr("Button")
    }

    CNButton {
        id: button2
        x: 95
        y: 266
        text: qsTr("Button")
    }

    CNButton {
        id: button3
        x: 400
        y: 400
        text: qsTr("Button")
    }

}
