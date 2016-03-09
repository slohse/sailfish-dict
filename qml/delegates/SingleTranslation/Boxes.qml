import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    property string lang1Term
    property string lang2Term

    //width: parent.width
    height: childrenRect.height

    Rectangle {
//        color: Theme.primaryColor
        color: "transparent"
        width: parent.width
        height: childrenRect.height
        id: lang1Box

        Label {
            width: parent.width
            text: lang1Term
            wrapMode: Text.Wrap
        }
    }

    Rectangle {
        color: Theme.secondaryColor
        width: parent.width
        height: childrenRect.height

        // place the translation left of the source language box (landscape mode)
        // or below it (portrait mode)
        anchors.left: lang1Box.left
        anchors.top: lang1Box.bottom

        Label {
            width: parent.width
            text: lang2Term
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignRight
        }
    }

}

