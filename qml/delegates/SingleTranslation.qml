import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    property string lang1Term
    property string lang2Term

    width: parent.width

    property int cellWidth:  parent.width / 2
    Rectangle {
        color: Theme.primaryColor
        width: cellWidth
        height: childrenRect.height
        id: lang1Box

        Label {
            text: lang1Term
        }
    }

    Rectangle {
        color: Theme.secondaryColor
        width: cellWidth
        height: childrenRect.height

        // place the translation left of the source language box (landscape mode)
        // or below it (portrait mode)
        anchors.left: lang1Box.left
        anchors.top: lang1Box.bottom

        Label {
            text: lang2Term
        }
    }

}

