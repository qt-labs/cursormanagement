import QtQuick 2.12
import CursorNavigation 1.0

Rectangle {
    id: root

    width: 150
    height: 100

    Row {

    Rectangle {
        objectName: "cnItem0"

        width: 50
        height: 50

        //only set the object name to create a default constructed attachment
        CursorNavigation.objectName: "cnItem0Attached"

    }

    Rectangle {
        objectName: "cnItem1"

        width: 50
        height: 50

        CursorNavigation.objectName: "cnItem1Attached"
        CursorNavigation.acceptsCursor: true

        Rectangle {
            width: 20
            height: 20
            objectName: "cnItem1Child"
        }

    }

    Rectangle {
        objectName: "cnItem2"

        width: 50
        height: 50

        CursorNavigation.objectName: "cnItem2Attached"
        CursorNavigation.acceptsCursor: true

        Rectangle {
            width: 20
            height: 20

            Rectangle {
                width: 10
                height: 10
                objectName: "cnItem2IndirectChild"
            }
        }

    }

    }

}
