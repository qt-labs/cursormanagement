import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

RadioButton {
    CursorNavigation.acceptsCursor: true
    CNCursorIndicator { cursorItem : parent }
}
