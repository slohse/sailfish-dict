import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components"
import "../delegates"

import dictquery 1.0

Page {
    id: mainPage

    Column {
        anchors.fill: parent

        spacing: Theme.paddingSmall

        SearchBar {
            id: mainSearchBar
            onSearchRequested: {
                console.log("SearchBar StartSearch clicked")
                dictQueryCore.search(term)
            }
            onSearchTextChanged: dictQueryCore.typingEvent(term)
        }

        ResultsList {
            id: results
            height: rootWindow.height - mainSearchBar.height
            width: parent.width
        }
    }

    DictQueryCore
    {
        id: dictQueryCore
        onUpdateLanguages: mainSearchBar.updateLanguages(languages)
        onUpdateTranslations: results.updateResults(translations)
    }
}


