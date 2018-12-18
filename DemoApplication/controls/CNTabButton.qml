import QtQuick 2.9
import QtQuick.Controls 2.2
import CursorNavigation 1.0

TabButton {
    id: root
    CursorNavigation.acceptsCursor: true
    CNCursorIndicator { cursorItem : parent }
    CursorNavigation.onActivated: {
        root.checked = true;
    }
}
