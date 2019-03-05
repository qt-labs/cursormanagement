import QtQuick 2.0
import CursorNavigation 1.0

Item {
    width: 200
    height: 200


    CNRect {
        objectName: "left"
        x: 20
        y: 60
        CursorNavigation.objectName: "leftAttached"
    }

    CNRect {
        objectName: "center"
        x: 60
        y: 60
    }

    CNRect {
        objectName: "top"
        x: 60
        y: 20
    }

    CNRect {
        objectName: "bottom"
        x: 60
        y: 100
    }

    CNRect {
        objectName: "right"
        x: 100
        y: 60
    }

    CNRect {
        objectName: "right1"
        x: 140
        y: 44
    }

    CNRect {
        objectName: "right2"
        x: 141
        y: 76
    }
}
