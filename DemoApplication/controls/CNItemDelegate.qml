import QtQuick 2.9
import QtQuick.Controls 2.4
import CursorNavigation 1.0

ItemDelegate {
    CursorNavigation.acceptsCursor: true
    CNCursorIndicator { cursorItem : parent }

    //here we make sure the list's current index follows the cursor!
    CursorNavigation.onHasCursorChanged: {
        if (CursorNavigation.hasCursor) {
            parent.currentIndex = index;
        }
    }
}
