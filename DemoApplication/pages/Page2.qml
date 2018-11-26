import QtQuick 2.9
import QtQuick.Controls 2.4

import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    Item {
        width: 580
        height: 450
        anchors.centerIn: parent
        FocusScope {
            id: focusScope
            width: 198
            height: 359
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: 20

            CursorNavigation.acceptsCursor: true
            ListView {
                id: listView
                anchors.fill: parent
                spacing: 4
                focus: true

                Rectangle {
                    anchors.fill: parent
                    visible: listView.activeFocus
                    border.width: 2
                    border.color: "red"
                    color: "transparent"
                }

                highlight: Rectangle {
                    width: listView.width
                    height: 40
                    color: "lightgrey"
                    opacity: 0.3
                }

                delegate: ItemDelegate {
                    width: listView.width
                    height: 40

                    contentItem: Row {
                        width: (parent.width - x)
                        height: 35
                        x: 5
                        anchors.verticalCenter: parent.verticalCenter
                        spacing: 10
                        Rectangle {
                            width: parent.height
                            height: parent.height
                            radius: width/2
                            color: colorCode
                        }
                        Text {
                            height: parent.height
                            font.bold: true
                            verticalAlignment: Text.AlignVCenter
                            text: name
                        }
                    }
                    onClicked: {
                        listView.currentIndex = index;
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
            id: button3
            anchors.top: focusScope.bottom
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 60
            text: qsTr("Button")
        }
        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 50
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
