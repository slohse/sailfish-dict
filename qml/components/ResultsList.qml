import QtQuick 2.0
import Sailfish.Silica 1.0

import "../delegates/SingleTranslation"

Rectangle {
    color: "transparent"
    id: resultsList

    ListModel {
        id: dummyTranslationsModel

        ListElement {
            originTerm: "great tits"
            translationTerm: "Kohlmeisen"
        }

        ListElement {
            originTerm: "interesting"
            translationTerm: "Oh God, oh God, we're all going to die?"
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
//        delegate: Dictionary
//        {
//            lang1Term: originTerm
//            lang2Term: translationTerm
//            width: parent.width
//        }
        delegate: Boxes
        {
            lang1Term: originTerm
            lang2Term: translationTerm
            width: parent.width
        }
    }

}


