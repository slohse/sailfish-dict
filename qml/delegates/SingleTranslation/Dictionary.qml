import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: singleTranslation

    property string lang1Term
    property string lang2Term

    //width: parent.width

    Text {
        text: "<i>" + lang1Term + "</i>" + " • " + lang2Term
        width: parent.width
        color: Theme.primaryColor
        wrapMode: Text.Wrap
    }
}

