import QtQuick 2.9
import QtQuick.Controls 2.2
import CursorNavigation 1.0

CheckBox {
    id: root
    CursorNavigation.acceptsCursor: true
    CNCursorIndicator { cursorItem : parent }

    CursorNavigation.onActivated: {
        root.toggle();
    }
}
