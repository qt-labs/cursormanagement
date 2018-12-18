import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    Component {
        id: delegate
        Text {
            id: nameText
            width: contentWidth
            text: index
            font.pixelSize: 24
            color: index%2 == 0 ? "green" : "black"
        }
    }

    FocusScope {
        id: leftMenu
        width: 199
        height: (parent.height - toolBar.height)
        property string bgColor: "#800080"
        Rectangle {
            id: rect
            anchors.fill: parent
            color: leftMenu.bgColor
            opacity: 0.6
        }
        Column {
            width: parent.width
            height: 300
            anchors.verticalCenter: parent.verticalCenter
            CNSwitch {
                width: 180
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Enable 2nd player"
            }
            CNRadioButton {
                width: 120
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Purple"
                checked: (leftMenu.bgColor === "#800080")
                onClicked: { leftMenu.bgColor = "#800080"; }
            }
            CNRadioButton {
                width: 120
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Orange"
                checked: (leftMenu.bgColor === "#ffa500")
                onClicked: { leftMenu.bgColor = "#ffa500"; }
            }
        }
    }
    FocusScope {
        width: 400
        height: parent.height
        anchors.centerIn: parent
        CursorNavigation.acceptsCursor: true
        //TODO should this work? it didn't either this way or
        //by setting just listView
        CursorNavigation.escapeTarget: listViewFocusScope
        //TODO it would be handy to have a way of implementing
        //the moveUp/Down/Right/Left functions of the cursor manager
        //as many times addtional view-specific actions need to
        //be done when those are triggered
        Keys.onDigit1Pressed: { pathView.decrementCurrentIndex(); }
        Keys.onDigit2Pressed: { pathView.incrementCurrentIndex(); }
        Rectangle {
            anchors.fill: parent
            border.width: 1
            border.color: pathView.CursorNavigation.hasCursor ? "red" : "transparent"
            color: "transparent"
        }
        PathView {
            id: pathView
            anchors.fill: parent
            model: 20
            delegate: delegate
            focus: true
            path: Path {
                startX: 50; startY: 200
                PathArc {
                    x: (pathView.width - 50); y: 200
                    radiusX: 100; radiusY: 90
                    useLargeArc: true
                }
                PathArc {
                    x: 50; y: 200
                    radiusX: 100; radiusY: 90
                    useLargeArc: true
                }
            }
        }
    }

    FocusScope {
        id: listViewFocusScope
        width: 200
        height: ((listView.count*40)+40)
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -toolBar.height

        CNListView {
            id: listView
            anchors.fill: parent
            spacing: 4

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
                ListElement { name: "Joe"; colorCode: "grey" }
                ListElement { name: "Hillary"; colorCode: "red" }
                ListElement { name: "Norton"; colorCode: "blue" }
                ListElement { name: "Hans"; colorCode: "green" }
                ListElement { name: "Ivan"; colorCode: "green" }
                ListElement { name: "Alex"; colorCode: "blue" }
                ListElement { name: "Erika"; colorCode: "red" }
            }
        }
    }
    FocusScope {
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        ToolBar {
            id: toolBar
            anchors.fill: parent
            RowLayout {
                anchors.fill: parent
                CNToolButton { text: "Menu" }
                CNToolButton { text: "Undo Table" }
                CNToolButton { text: "Rise Bet" }
                CNToolButton { text: "Start" }
                Item { Layout.fillWidth: true }
                CNCheckBox {
                    text: "Outside bet"
                    Layout.alignment: Qt.AlignRight
                }
            }
        }
    }
}
