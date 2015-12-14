import QtQuick 2.0
import Sailfish.Silica 1.0

import "../delegates/SingleTranslation"

Rectangle {
    color: "transparent"
    id: resultsList

    ListModel {
        id: dummyTranslationsModel

        ListElement {
            lang1Term: "great tits"
            lang2Term: "Kohlmeisen"
        }

        ListElement {
            lang1Term: "interesting"
            lang2Term: "Oh God, oh God, we're all going to die?"
        }
    }

    Component {
        id: dummyComponent
        Text {
            text: "<i>" + lang1Term + "</i>" + " • " + lang2Term
            width: parent.width
            color: Theme.primaryColor
            wrapMode: Text.Wrap
        }
    }

    ListView {
        anchors.fill: parent
        //model: translationResultsModel
        model: dummyTranslationsModel
        delegate: Dictionary {}
    }

}


