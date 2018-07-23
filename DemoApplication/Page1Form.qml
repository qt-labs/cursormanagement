import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    width: 600
    height: 400

    title: qsTr("Page 1")

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }

    CNButton {
        id: button
        x: 52
        y: 50
        text: qsTr("Button")
    }

    CNButton {
        id: button1
        x: 110
        y: 138
        text: qsTr("Button")
    }

    CNButton {
        id: button2
        x: 202
        y: 241
        text: qsTr("Button")
    }

    CNButton {
        id: button3
        x: 383
        y: 241
        text: qsTr("Button")
    }

    CNButton {
        id: button4
        x: 383
        y: 322
        text: qsTr("Button")
    }

    CNButton {
        id: button5
        x: 383
        y: 138
        text: qsTr("Button")
    }

    CNButton {
        id: button6
        x: 383
        y: 50
        text: qsTr("Button")
    }

    CNButton {
        id: button7
        x: 62
        y: 241
        text: qsTr("Button")
    }



}
