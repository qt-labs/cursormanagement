import QtQuick 2.0
import CursorNavigation 1.0

//Cursor Navigable rectangle for reusing in tests
//has visual indication of cursor for running tests manually
Rectangle {
    color: CursorNavigation.hasCursor ? "red" : "green"
    width: 20
    height: 20

    CursorNavigation.acceptsCursor: true
}
