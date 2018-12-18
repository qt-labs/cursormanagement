import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import CursorNavigation 1.0
import controls 1.0
import "pages"

ApplicationWindow {
    id: window
    width: 800
    height: 600
    visible: true
    title: qsTr("Cursor Navigation Demo Application")

    /* there are alternative ways to implement a tabbar. the traditional tabbar has
     * problems with CursorNavigation: when trying to navigate the cursor on it
     * right after launching the application, the cursor will not be passed onto
     * the children. However, if clicked first, the navigation works. Another
     * workaround is to force the active focus on one of the tabs.
     * The listview approach works right out of the box
     */

    header:/* ListView {
        id: tabBar
        orientation: ListView.Horizontal
        width: window.width
        height: 40
        CursorNavigation.acceptsCursor: true

        delegate: Rectangle {
            CursorNavigation.acceptsCursor: true
            CursorNavigation.onHasCursorChanged: {
                if (CursorNavigation.hasCursor)
                    tabBar.currentIndex = index
            }
            width: tabBar.width/tabBar.count
            height: 40
            border.width: 2
            border.color: CursorNavigation.hasCursor ? "red" : "transparent"

            Text { anchors.centerIn: parent; text: pageName}
        }

        model: ListModel {
            ListElement {
                pageName: "Page 1"
            }
            ListElement {
                pageName: "Page 2"
            }
            ListElement {
                pageName: "Page 3"
            }
            ListElement {
                pageName: "Page 4"
            }
            ListElement {
                pageName: "Page 5"
            }
            ListElement {
                pageName: "Map"
            }
        }

    }*/

    TabBar {
        id: tabBar
        width: window.width
        CursorNavigation.acceptsCursor: true

        CNTabButton {
            id: defaultButton
            text: qsTr("Page 1")
            focus: true
        }
        CNTabButton {
            text: qsTr("Page 2")
        }
        CNTabButton {
            text: qsTr("Page 3")
        }
        CNTabButton {
            text: qsTr("Page 4")
        }
        CNTabButton {
            text: qsTr("Page 5")
        }
        CNTabButton {
            text: qsTr("Map")
        }
    }

    contentData: StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page1 { }
        Page2 { }
        Page3 { }
        Page4 { }
        Page5 { }
        Page6 { }
    }

    //a trick that ensure the cursor can be moved on the tabbar without needing to click teh tabbar first
    Component.onCompleted: {
        defaultButton.forceActiveFocus()
    }

}
