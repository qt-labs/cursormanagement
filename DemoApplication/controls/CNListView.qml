import QtQuick 2.11
import QtQuick.Controls 2.4
import CursorNavigation 1.0

ListView {
    id: listView
    anchors.fill: parent
    spacing: 4
    focus: true
    /* when list view scopes the cursor, the cursor is passed further to its
     * currently focused child. this means, moving from outside to the list,
     * will return the cursor to the item that was previously selected
     * comment this out to make transition directly between individual list items and the rest of the ui
     */
    CursorNavigation.acceptsCursor: true

    Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: listView.activeFocus ? "red" : "black"
        color: "transparent"
    }

    highlight: Rectangle {
        width: listView.width
        height: 40
        color: "lightgrey"
        opacity: 0.3
    }

    delegate: ItemDelegate {
        id: deleg
        width: listView.width
        height: 40
        CursorNavigation.acceptsCursor: true

        //make sure the list's current index follows the cursor!
        CursorNavigation.onHasCursorChanged: {
            if (CursorNavigation.hasCursor)
                listView.currentIndex = index
        }

        contentItem: Rectangle {
            width: listView.width
            height: 40
            border.color: deleg.CursorNavigation.hasCursor ? "red" : "transparent"

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
        onClicked: {
            listView.currentIndex = index;
        }
    }

}
