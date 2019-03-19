/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the cursor management module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6
import CursorNavigation 1.0
import QtGamepad 1.0
import QtQuick.Shapes 1.11

Item {
    width: parent.width
    height: parent.height

    Text {
        id: text
        text: "CursorNavigation allows navigation in a simple 4-way, or a completely free 360 degree manner. The 4 way navigation is useful for traditional, rectangular and structured UIs, however, the example here works best when using a controller that allows moving to any direction (eg. analog stick)."
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        wrapMode: Text.WordWrap
    }

    Timer {
        id: cooldownTimer
        interval: 500
        repeat: false
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
            var currentPosition = positionSource.position.coordinate;
            map.center = currentPosition;
            var distance = currentPosition.distanceTo(lastSearchPosition);
            if (distance > 500) {
                // 500m from last performed pizza search
                lastSearchPosition = currentPosition;
                searchModel.searchArea = QtPositioning.circle(currentPosition);
                searchModel.update();
            }
        }
    }

    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)

    PlaceSearchModel {
        id: searchModel

        plugin: mapPlugin

        searchTerm: "Pizza"
        searchArea: QtPositioning.circle(locationOslo)

        Component.onCompleted: { update(); }
    }

    Map {
        id: map
        anchors.top: text.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
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
            if (searchModel.status == PlaceSearchModel.Error) {
                console.log("Search error!");
                console.log(searchModel.errorString());
            }
        }
    }
}
