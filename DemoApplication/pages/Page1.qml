import QtQuick 2.9
import QtQuick.Layouts 1.3
import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    Text {
        id: text
        text: "Welcome to the CursorNavigation demo!\nUse the arrow keys, keys a,w,s,d or a game controller to move the cursor between the UI elements."
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
            spacing: 10

            anchors.centerIn: parent

            GridLayout {
                rows: 3
                columns: 2
                rowSpacing: 10
                columnSpacing: 10
                anchors.margins: 10

                CNButton {
                    id: button
                    text: qsTr("Button")
                }

                CNButton {
                    id: button1
                    text: qsTr("Button")
                }

                CNButton {
                    id: button2
                    text: qsTr("Button \n(cursor off)")
                    CursorNavigation.acceptsCursor: false
                }

                CNButton {
                    id: button3
                    text: qsTr("Button \n(esc. target)")
                }

                Rectangle {
                    border.width: 1
                    CNCursorIndicator { cursorItem: textEdit }
                    Layout.columnSpan: 2
                    Layout.fillWidth: true
                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 200
                    Layout.maximumWidth: 300
                    Layout.minimumHeight: 30
                    TextEdit {
                        id: textEdit
                        anchors.fill: parent
                        CursorNavigation.acceptsCursor: true
                        text: "some text..."
                    }
                }

            }

            Rectangle {
                Layout.fillWidth: true
                //Layout.minimumWidth: 300
                //Layout.preferredWidth: 250
                //Layout.maximumWidth: 300
                //Layout.minimumHeight: 350
                Layout.minimumHeight: grid.height
                Layout.minimumWidth: grid.width
                border.width: 1

                FocusScope {
                    anchors.fill: parent
                    CursorNavigation.acceptsCursor: true
                    CursorNavigation.escapeTarget: button3
                    CursorNavigation.trapsCursor: trapCheckBox.checked

                    GridLayout {
                        id: grid
                        anchors.centerIn: parent
                        rows: 4
                        columns: 2
                        rowSpacing: 10
                        columnSpacing: 10

                        CNButton {
                            id: button4
                            //make the focusscope forward the focus and the cursor to it's children
                            focus: true
                            text: qsTr("Button")
                        }

                        CNButton {
                            id: button5
                            text: qsTr("Button")
                        }

                        CNButton {
                            id: button6
                            text: qsTr("Button")
                        }

                        CNButton {
                            id: button7
                            text: qsTr("Button")
                        }

                        CNCheckBox {
                            id: trapCheckBox
                            text: "Trap cursor to this scope"
                            Layout.columnSpan: 2
                        }

                        Text {
                            text: "Press 'esc' to exit the scope."
                            Layout.columnSpan: 2
                        }
                    }
                }
            }
        }
    }
}
