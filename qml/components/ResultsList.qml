import QtQuick 2.0
import Sailfish.Silica 1.0

import dictquery 1.0

import "../delegates/SingleTranslation"

Rectangle {
    color: "transparent"
    id: resultsList

    property var translationResultsModel : []

    ListView {
        anchors.fill: parent
        model: translationResultsModel
        delegate: Dictionary
        {
            lang1Term: queryTerm
            lang2Term: definition
            width: parent.width
        }
//        delegate: Boxes
//        {
//            lang1Term: model.modelData.queryTerm
//            lang2Term: model.modelData.definition
//            width: parent.width
//        }
    }

    function updateResults(results)
    {
        console.log("updateResults, length: ", results.length)
        translationResultsModel = results
    }

}


