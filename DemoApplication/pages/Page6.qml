
import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6
import CursorNavigation 1.0
import QtGamepad 1.0
import QtQuick.Shapes 1.11

Item {
    width: parent.width
    height: parent.height

    Timer {
        id: cooldownTimer
        interval: 500
        repeat: false
    }

    Gamepad {
        deviceId: GamepadManager.connectedGamepads.length > 0 ? GamepadManager.connectedGamepads[0] : -1

        function handleMove() {
            var v = Qt.vector2d(axisLeftX, axisLeftY)
            if (v.length() >= 0.99 && !cooldownTimer.running) {
                //console.log("handle joystick move, v=" + v)
                parent.CursorNavigation.moveCursor(Qt.vector2d(axisLeftX, axisLeftY), 10)
                cooldownTimer.start()
            } else if (v.length() >= 0.1) {
                var item = parent.CursorNavigation.find(v, 10)
                //cooldownTimer.start()
                if (item != undefined) {
                    pointerRect.x = item.x
                    pointerRect.y = item.y
                    pointerRect.width = item.width+10
                    pointerRect.height = item.height+10
                    pointerRect.radius = item.width/2+5
                    pointerRect.visible = true
                }
            } else {
                pointerRect.visible = false
            }
        }

        onAxisLeftXChanged: handleMove()
        onAxisLeftYChanged: handleMove()
    }


    Plugin {
        id: mapPlugin
        name: "esri" //"osm", "mapboxgl", "esri", ...
    }

    PositionSource {
        id: positionSource
        property variant lastSearchPosition: locationOslo
        active: true
        updateInterval: 120000 // 2 mins
        onPositionChanged:  {
            var currentPosition = positionSource.position.coordinate
            map.center = currentPosition
            var distance = currentPosition.distanceTo(lastSearchPosition)
            if (distance > 500) {
                // 500m from last performed pizza search
                lastSearchPosition = currentPosition
                searchModel.searchArea = QtPositioning.circle(currentPosition)
                searchModel.update()
            }
        }
    }

    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)

    PlaceSearchModel {
        id: searchModel

        plugin: mapPlugin

        searchTerm: "Pizza"
        searchArea: QtPositioning.circle(locationOslo)

        Component.onCompleted: update()
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin;
        center: locationOslo
        zoomLevel: 13

        Rectangle {
            id: pointerRect
            border.color: "#00ff00"
            border.width: 2
            visible: false
            color: "transparent"
        }

        MapItemView {
            model: searchModel
            delegate: MapQuickItem {
                id: itemDelegate
                CursorNavigation.acceptsCursor: true
                coordinate: place.location.coordinate

                property bool highlight: false

                anchorPoint.x: image.width * 0.5
                anchorPoint.y: image.height

                sourceItem: Column {
                    Image { id: image; source: "../graphics/marker.png";
                        transform: Scale {
                            xScale: itemDelegate.CursorNavigation.hasCursor ? 1.8 : 1
                            yScale: itemDelegate.CursorNavigation.hasCursor ? 1.8 : 1
                            origin.x: width/2
                            origin.y: height
                        }
                    }
                    Text { text: title; font.bold: itemDelegate.CursorNavigation.hasCursor }
                }
            }
        }
    }

    Connections {
        target: searchModel
        onStatusChanged: {
            if (searchModel.status == PlaceSearchModel.Error)
                console.log("Search error!")
                console.log(searchModel.errorString());
        }
    }
}
