import QtQuick 2.0
import Sailfish.Silica 1.0

import "../delegates"

ListView {
    width: parent.width

    model: translationResultsModel
    delegate: SingleTranslation {
        lang1Term: model.modelData.lang1Term
        lang2Term: model.modelData.lang2Term
    }
}

