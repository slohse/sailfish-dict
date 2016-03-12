import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    id: translationSearchBar
    signal searchRequested(string term)
    signal searchTextChanged(string term)
    //signal languageTupleChanged(string tuple)
    anchors.left: parent.left
    anchors.right: parent.right

    height: childrenRect.height

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
                model: ListModel { id: languageSelectorModel }
                delegate: MenuItem { text: model.getPrettyPrint }
            }

//            MenuItem { text: "DE ↔ EN" }
//            MenuItem { text: "DE ↔ SV" }
        }

        //onValueChanged: translationSearchBar.languageTupeChanged(menu.data)
    }

    function updateLanguageSelection(languages)
    {
        if(languages.length != languageSelectorModel.count)
        {
            var selectedTuple = ""
            if(languageSelector.currentIndex != -1)
            {
                selectedTuple = languageSelectorModel.get(languageSelector.currentIndex).getTuple
            }

            languageSelectorModel.clear()
            for(var i = 0; i < languages.length; i++)
            {
                languageSelectorModel.append(languages[i])
            }
        }
    }
}
