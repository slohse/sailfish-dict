import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    property string lang1Term
    property string lang2Term

    width: parent.width

    property int cellWidth: isPortrait ? parent.width / 2 : parent.width

    Rectangle {
        color: Theme.primaryColor
        width: cellWidth
        id: lang1Box

        Label {
            text: lang1Term
        }
    }

    Rectangle {
        color: Theme.secondaryColor
        width: cellWidth

        // place the translation left of the source language box (landscape mode)
        // or below it (portrait mode)
        anchors.left: isPortrait ? lang1Box.left : lang1Box.right
        anchors.top: isPortrait ? lang1Box.bottom : lang1Box.top

        Label {
            text: lang2Term
        }
    }

}

