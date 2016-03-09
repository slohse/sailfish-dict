import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: singleTranslation

    property string lang1Term
    property string lang2Term

    //width: parent.width
    height: childrenRect.height

    Text {
        id: innerText
        width: parent.width
        text: "<i>" + lang1Term + "</i>" + " • " + lang2Term
        color: Theme.primaryColor
        wrapMode: Text.Wrap
    }

}

