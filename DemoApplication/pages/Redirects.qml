import QtQuick 2.9
import QtQuick.Layouts 1.3
import CursorNavigation 1.0
import controls 1.0

Item {
    width: parent.width
    height: parent.height

    Text {
        id: text
        text: "CursorNavigation allows overriding the navigation algorithm with the redirects -property. You may define angle sectors that bypass the algorithm, and instead move the cursor or focus to a predefined target object. This is useful for example implementing wrapping. Moving the cursor past the end of the button rows will wrap the cursor to the other end. The row in the bottom is done using a repeater and redirects have been set dynamically. Movement between the button rows has been redirected to go via the button in the center."

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
            id: upperRow
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            CNButton {
                id: firstButton
                text: "Button 1"

                CursorNavigation.redirects: [
                    Redirect { start: 45; end: 135; target: centerButton },
                    Redirect { start: 135; end: 225; target: lastButton }
                ]
            }

            CNButton {
                text: "Button 2"

                CursorNavigation.redirects: [
                    Redirect { start: 45; end: 135; target: centerButton }
                ]
            }

            CNButton {
                text: "Button 3"

                CursorNavigation.redirects: [
                    Redirect { start: 45; end: 135; target: centerButton }
                ]
            }

            CNButton {
                id: lastButton
                text: "Button 4"

                CursorNavigation.redirects: [
                    Redirect { start: 45; end: 135; target: centerButton },
                    Redirect { start: 315; end: 45; target: firstButton }
                ]
            }

        }

        CNButton {
            id: centerButton
            text: "Center button"
            anchors.centerIn: parent
        }

        RowLayout {
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom

            Repeater {
                id: buttonRepeater
                model: 6

                CNButton {
                    Layout.minimumWidth: 110
                    Layout.minimumHeight: 110
                    text: "Button " + index

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    CursorNavigation.redirects: [
                        Redirect { start: 225; end: 315; target: centerButton }
                    ]

                    Component.onCompleted: {
                        if (index == buttonRepeater.count-1) {
                            console.info("creating redirects for repeater buttons, count =" + buttonRepeater.count)
                            buttonRepeater.itemAt(0).CursorNavigation.redirects.push(
                                Qt.createQmlObject(
                                   "import CursorNavigation 1.0;
                                    Redirect { start: 135; end: 225;
                                    target: buttonRepeater.itemAt(buttonRepeater.count-1) }",
                                    buttonRepeater.itemAt(0)
                                    ));
                            buttonRepeater.itemAt(buttonRepeater.count-1).CursorNavigation.redirects.push(
                                Qt.createQmlObject(
                                   "import CursorNavigation 1.0;
                                    Redirect { start: 315; end: 45;
                                    target: buttonRepeater.itemAt(0) }",
                                    buttonRepeater.itemAt(buttonRepeater.count-1)
                                    ));
                        }
                    }
                }



            }
        }

    }
}
