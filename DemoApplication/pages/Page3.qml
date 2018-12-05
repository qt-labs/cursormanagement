import QtQuick 2.0

import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    FocusScope {
        id: rootScope
        anchors.fill: parent
        Row {
            anchors.centerIn: parent
            spacing: 10
            CNButton {
                width: 100
                height: 100
                text: "alone!"

                CursorNavigation.onMovedUp: text = "moved up"
                CursorNavigation.onMovedDown: text = "moved down"
                CursorNavigation.onMovedRight: text = "moved right"
                CursorNavigation.onMovedLeft: text = "moved left"
            }

            Grid {
                columns: 2
                rows: 2
                spacing: 5

                CNButton {
                    text: "b1"
                }

                CNButton {
                    text: "b2 (default focus)"
                    focus: true
                }

                CNButton {
                    id: defaultButton
                    text: "b3 (escape target)"
                }

                CNButton {
                    text: "b4"
                }
            }

            Rectangle {
                width: 250
                height: 200

                border.width: 2
                border.color: "grey"

                FocusScope {
                    anchors.fill: parent
                    CursorNavigation.acceptsCursor: true
                    CursorNavigation.escapeTarget: defaultButton
                    CursorNavigation.trapsCursor: trapCheckBox.checked

                    //redefine the controls for this scope
                    //(default arrow keys will still work as well, unless reassigned here)
                    Keys.onDigit5Pressed: CursorNavigation.moveUp()
                    Keys.onDigit2Pressed: CursorNavigation.moveDown()
                    Keys.onDigit3Pressed: CursorNavigation.moveRight()
                    Keys.onDigit1Pressed: CursorNavigation.moveLeft()

                    Grid {
                        spacing: 5
                        columns: 2
                        rows: 3

                        CNButton {
                            text: "sb1"
                        }

                        CNButton {
                            text: "sb2"
                        }

                        CNButton {
                            text: "sb3"
                        }

                        CNButton {
                            text: "sb4 (default focus)"
                            focus: true
                        }

                        CNCheckBox {
                            id: trapCheckBox
                            text: "trap cursor"
                        }
                    }
                }
            }
        }
        //this seems to be the way to force focus on a newly opened dialog?
        Component.onCompleted: { forceActiveFocus(); }
    }
}
