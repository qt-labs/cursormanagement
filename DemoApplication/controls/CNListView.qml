import QtQuick 2.11
import QtQuick.Controls 2.4
import CursorNavigation 1.0

ListView {
    id: listView

    //use CNItemDelegate as the delegate!

    /* when list view scopes the cursor, the cursor is passed further to its
     * currently focused child. this means, moving from outside to the list,
     * will return the cursor to the item that was previously selected
     * comment this out to make transition directly between individual list items and the rest of the ui
     */
    CursorNavigation.acceptsCursor: true

}
