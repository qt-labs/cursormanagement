
## What is it for?

Cursor is an indicator for the target of user interactions in a GUI. In this case, it's more specifically a selector for individual UI elements, such as buttons, and not completely freely moving, like a mouse pointer. The purpose of the CursorNavigation plugin is to provide a generic way of enabling cursor navigation in QML UIs with minimal configuration and ease of use in mind. Minimal configuration, in this case, would be in comparison to eg. qt's existing key navigation, where the navigation path has to be defined explicitly on a per element basis. CursorNavigation ships as a plugin for Qt and is loaded by simply importing it in QML, usable right from the beginning of the ui development.


## How does it work?

CursorNavigation works by allowing the developer to define individual QML elements as navigable. The framework's backend keeps track of the navigable items and their parent-child relations and position and geometry on the UI. Moving the cursor is handled by algorithms, and is based just on the location and geometry of the items. There are 2 algorithm for spatial navigation: 4-way and free-directional. The simpler 4-way navigation is well suited for traditional, rectangular and structured UIs, while the 360-algorithm allows moving freely to any direction.

There may be one instance of the CursorNavigation backend per window and one item per window having the cursor. Moving the cursor is also moving the active focus between the items. This means that inputs are directed on the item that has the cursor and that the cursor movement can be refined using Qt's FocusScopes.

By default, CursorNavigation uses they keyboard as input, but it also provides an API for using any kind of input source for control.


## Installing

CursorNavigation is distributed as a Qt QML plugin. Build the plugin and the demo application by building the project CursorNavigation.pro. Run make install in the build directory to install the plugin to Qt's plugins directory. After installing the plugin is available to any project using that version of Qt.


## Interface

### Properties

Set this to true to include the item for cursor navigation.
```
bool acceptsCursor
```

Indicates if the item itself, or one of its non-navigable children has the active focus.
```
bool hasCursor
```

Set this to true to limit the cursor's movement to this item and its children. In order to move the cursor out of the item's scope, force active focus somewhere outside or define an escape target.
```
bool trapsCursor
```

Set a target for moving to cursor to in case of the escape-input.
```
QQuickItem* escapeTarget
```

### Methods

Just for passing forward information of intended movement, eg. analog joystick movement. Does not affect the cursor in any way. Changes are received by the item that currently has the cursor.
```
void setMagnitude(qreal angle, qreal magnitude);
void setMagnitude(QVector2D vector);
```

Move the cursor to the given direction using the angle +- the given tolerance. Units are in degrees. Angle is clockwise from the center of the current item with x-axis pointing to 0 degrees. Items that are exactly in the direction are preferred over items that just fall within the tolerance. The item that had the cursor will have its moved-signal emitted. If there is no item to be found, nothing happens.
```
void move(qreal angle, qreal tolerance = 0);
void move(QVector2D vector, qreal tolerance = 0);
```

Finds the next item, without moving the cursor. Units are in degrees. Angle is clockwise from the center of the current item with x-axis pointing to 0 degrees. If there is no item to be found, returns a null.
```
QQuickItem *find(qreal angle, qreal tolerance = 0);
QQuickItem *find(QVector2D vector, qreal tolerance = 0);
```

Moves the cursor up, down, right or left using the 4-way algorithm. The item that had the cursor will have its corresponding signal emitted. If there is no item to move to, does nothing.
```
void moveUp();
void moveDown();
void moveRight();
void moveLeft();
```

The item that currently has the cursor, will have its activated signal emitted. Does not affect the cursor position.
```
void activate();
```

Not yet implemented. Would do the tab- back-tab style of navigation.
```
void moveForward();
void moveBack();
```

Move the cursor to the escape target defined to this item. If no escape target is defined, cursor is passed to item's parent. The item that had the cursor will have its escaped-signal emitted.
```
void escape();
```

### Signals

```
void magnitudeChanged(qreal angle, qreal magnitude);
void moved(qreal angle, qreal tolerance);
void movedUp();
void movedDown();
void movedRight();
void movedLeft();
void activated();
void movedForward();
void movedBack();
void escaped();
```

## Using CursorNavigation

### Basics

The way to define items as cursor navigable, is done via CursorNavigation's attached property 'acceptsCursor'. Use the read-only property 'hasCursor' to test if the item is selected. The example below shows how to define a button that is navigable:

```
// CNButton.qml
// This is a button that supports cursor navigation

import QtQuick 2.0
import QtQuick.Controls 2.2
import CursorNavigation 1.0

Button {
    id: button
    CursorNavigation.acceptsCursor: true

    //visualize selection with a bright border
    Rectangle {
        border.width: 2
        border.color: "red"
        anchors.fill: parent
        visible: parent.CursorNavigation.hasCursor
    }
}
```

### Scoping

As CursorNavigation is about moving the active focus, it is possible to use FocusScopes with it. FocusScopes are useful when focus needs to be proxied to Item's children. The example below show how to have a "cursor scope", an item that accepts the cursor, but passes it on to the child items. It is also possible to limit the cursor's movement to the children using the CursorNavigation.trapsCursor property. To leave a scope that traps the cursor, define a escape target with the CursorNavigation.escapeTarget property.

```
//combine existing focus mechanisms and cursor management to have cursor scopes

CNButton {
    id: homeButton
    text: "home button (escape target)"
}

//define a container with cursor manageable contents
Rectangle {
    FocusScope {
        anchors.fill: parent
        //enable cursor navigation for the container
        CursorNavigation.acceptsCursor: true
        // (optionally) once the cursor enters the scope, limit the movement to this item's children
        CursorNavigation.trapsCursor: true
        //escape command would by default return the focus to the parent of this scope
        //OR alternatively, we may define an escape target item, that receives the focus when leaving this scope
        CursorNavigation.escapeTarget: homeButton

        CNButton {
            id : button1
            //to forward selection from container, set this button to have the focus/cursor by default
            focus: true
        }

        CNButton {
            id : button2
        }
    }
}
```
### Input binding

The CursorNavigation attached object implements the functions needed for controlling the cursor. Bind different input  sources to these functions. In this example, the keyboard and a gamepad are used for moving the cursor.


```
Item {
    FocusScope {
        id: cnScope
        anchors.fill: parent
        CursorNavigation.acceptsCursor: true

        ...
    }
}

//navigation with keys...
Keys {
    //4 way moves
    onRightPressed: cnScope.CursorNavigation.moveRight()
    onLeftPressed: cnScope.CursorNavigation.moveLeft()
    onUpPressed: cnScope.CursorNavigation.moveUp()
    onDownPressed: cnScope.CursorNavigation.moveDown()
}

// ..or with gamepad
Gamepad {
    onAxisLeftXChanged: handleAxisChanged()
    onAxisLeftYChanged: handleAxisChanged()


    function handleAxisChanged: {
        //move cursor providing just an angle and a tolerance around the angle
        cnScope.CursorNavigation.move(calculateAngle(axisLeftX, axisLeftY), 10)
    }

    onButtonAChanged: {
        if (buttonA)
            cnScope.CursorNavigation.activate();
    }

}

```


