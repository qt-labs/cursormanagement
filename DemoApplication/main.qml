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

    header: TabBar {
        id: tabBar
        width: parent.width
        CNTabButton {
            text: qsTr("Page 1")
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
}
