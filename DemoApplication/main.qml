import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import CursorNavigation 1.0
import "pages"
import "controls"

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
    }

    contentData: StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Page1 { }
        Page2 { }
        Page3 { }
    }
}
