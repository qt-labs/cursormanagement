import QtQuick 2.0
import CursorNavigation 1.0

Item {
    width: 300
    height: 300

    CNRect {
        objectName: "center"
        CursorNavigation.objectName: "centerAttached"
        x: 140
        y: 140
    }

    CNRect {
        objectName: "d0"
        x: 270
        y: 140
    }

    CNRect {
        objectName: "d45"
        x: 270
        y: 270
    }

    CNRect {
        objectName: "d90"
        x: 140
        y: 270
    }

    CNRect {
        objectName: "d135"
        x: 10
        y: 270
    }

    CNRect {
        objectName: "d180"
        x: 10
        y: 140
    }

    CNRect {
        objectName: "d225"
        x: 10
        y: 10
    }

    CNRect {
        objectName: "d270"
        x: 140
        y: 10
    }

    CNRect {
        objectName: "d315"
        x: 270
        y: 10
    }
}
