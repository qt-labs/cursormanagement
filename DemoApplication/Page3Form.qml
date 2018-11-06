import QtQuick 2.0
import CursorNavigation 1.0

Item {
    FocusScope {
        id: rootScope
        Row {
            spacing: 10

            CNButton {
                width: 100
                height: 100
                text: "alone!"
            }

            Rectangle {

                width: 250
                height: 200

                Grid {
                    spacing: 5
                    columns: 2
                    rows: 2

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

            }

            Rectangle {

                width: 250
                height: 200

                border.width: 2
                border.color: "gray"

                FocusScope {
                    CursorNavigation.acceptsCursor: true
                    anchors.fill: parent
                    CursorNavigation.escapeTarget: defaultButton

                    Grid {
                        spacing: 5
                        columns: 2
                        rows: 2

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

                    }
                }

            }
        }
    }
}
