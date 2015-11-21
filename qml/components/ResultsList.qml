import QtQuick 2.0
import Sailfish.Silica 1.0

import "../delegates"


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
        Row {
            spacing: 5
            Text {
                text: lang1Term
                color: Theme.primaryColor
            }
            Text {
                text: lang2Term
                color: Theme.secondaryColor
            }
        }
    }

    ListView {
        anchors.fill: parent
        //model: translationResultsModel
        model: dummyTranslationsModel
        delegate: dummyComponent
    }

}


