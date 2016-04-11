import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../delegates"

import dictquery 1.0

Page {
    id: mainPage

    property DictQueryCore dictQueryCore

    Column {
        anchors.fill: parent

        spacing: Theme.paddingSmall

        SearchBar {
            id: mainSearchBar
            onSearchRequested: console.log("SearchBar StartSearch clicked")
        }

        ResultsList {
            id: results
            height: rootWindow.height - mainSearchBar.height
            width: parent.width
        }

        Component.onCompleted: {
            mainSearchBar.searchRequested.connect(dictQueryCore.Search)
            mainSearchBar.searchTextChanged.connect(dictQueryCore.TypingEvent)
            dictQueryCore.UpdateTranslations.connect(results.updateResults)
            dictQueryCore.UpdateLanguages.connect(mainSearchBar.updateLanguages)
        }
    }
}


