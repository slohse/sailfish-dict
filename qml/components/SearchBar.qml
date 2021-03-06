import QtQuick 2.0
import Sailfish.Silica 1.0

import dictquery 1.0

Item {

    id: translationSearchBar
    signal searchRequested(string term)
    signal searchTextChanged(string term)
    signal languageTupleChanged(string tuple)
    anchors.left: parent.left
    anchors.right: parent.right

    height: childrenRect.height

    property var languageSelectorModel : []

    TextField {
        id: queryInput
        width: 3 * (parent.width / 4)
        placeholderText: qsTr("search term")
        onTextChanged: translationSearchBar.searchTextChanged(text)
    }

    Button {
        id: searchButton
        anchors.right: parent.right
        anchors.left: queryInput.right

        text: "→"
        onClicked: translationSearchBar.searchRequested(queryInput.text)
    }

    ComboBox {
        id: languageSelector
        label: "Languages"
        anchors.left: parent.left
        anchors.top: queryInput.bottom

        menu: ContextMenu {
            Repeater {
                width: parent.width
                model: languageSelectorModel
                MenuItem { text: modelData.prettyPrint }
            }
        }

        onValueChanged: translationSearchBar.languageTupleChanged(languageSelectorModel[currentIndex].tuple)

        //onValueChanged: translationSearchBar.languageTupeChanged(menu.data)
    }

    function updateLanguages(languages)
    {
        languageSelectorModel = languages
    }
}
