import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import CursorNavigation 1.0

Window {
    id: window0
    objectName: "window0"
    width: 100
    height: 100

    CNRect {
        id: cn0
        objectName: "win0Item0"
        CursorNavigation.objectName: "win0Item0Attached"
        x: 10
        y: 10
    }

    CNRect {
        id: cn1
        objectName: "movedItem0"
        CursorNavigation.objectName: "movedItem0Attached"
        x: 40
        y: 10
    }

    CNRect {
        id: cn2
        objectName: "movedItem1"
        x: 70
        y: 10
    }

    function reparent() {
        cn1.parent = window1.contentItem;
        cn2.parent = window1.contentItem;
    }

    Button {
        x: 30
        y: 30
        onClicked: {
            window0.reparent();
        }
    }

    //window that already has CursorNavigation initialized
    Window {
        id: window1
        objectName: "window1"
        width: 100
        height: 100
        visible: true

        CNRect {
            id: cn1_0
            objectName: "win1Item0"
            CursorNavigation.objectName: "win1Item0Attached"
            x: 10
            y: 10
        }

        function reparent() {
            cn1.parent = window2.contentItem;
            cn2.parent = window2.contentItem;
        }

        Button {
            x: 30
            y: 30
            onClicked: {
                window1.reparent();
            }
        }

    }

    //window that does not have CursorNavigation initialized
    Window {
        id: window2
        objectName: "window2"
        width: 100
        height: 100
        visible: true

        function reparent() {
            cn1.parent = window0.contentItem;
            cn2.parent = window0.contentItem;
        }

        Button {
            x: 30
            y: 30
            onClicked: {
                window2.reparent();
            }
        }

    }

}


