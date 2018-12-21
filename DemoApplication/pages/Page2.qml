import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    Text {
        id: text
        text: "Lists and list items may also be defined cursor navigable. Try moving the cursor between the lists and the other controls. List on the left is defined as a navigable item and so are its items. A list like this will relay the cursor to its currently selected child. However, list on the right has only its children defined as navigables and this will mean cursor will move to the item based on cursor's and item's locations."
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

        RowLayout {
            anchors.centerIn: parent
            spacing: 10

            Column {
                CNListView {
                    id: listView
                    width: 198
                    height: 359

                    spacing: 4
                    clip: true

                    delegate: CNItemDelegate {
                        width: listView.width
                        height: 40

                        contentItem: Item {
                            width: listView.width
                            height: 40

                            Row {
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
                    text: qsTr("Button")
                }
            }

            Column {
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

            CNListView {
                id: listView2
                width: 198
                height: 359

                spacing: 4
                clip: true

                /* when we set acceptsCursor false for the ListView itself,
                 * navigation between the list items and items outside of the list,
                 * is based on the item geometry and not just the whole ListView's geometry
                 */
                CursorNavigation.acceptsCursor: false

                delegate: CNItemDelegate {
                    width: listView.width
                    height: 40

                    CursorNavigation.onActivated: checkBox.toggle()

                    contentItem: Item {
                        width: listView.width
                        height: 40

                        CheckBox{
                            id: checkBox
                            text: "Item " + index
                            anchors.centerIn: parent
                        }
                    }
                }

                model: 10
            }
        }
    }
}
