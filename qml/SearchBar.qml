import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    id: translationSearchBar
    signal searchRequested()
    //height: queryInput.height + langSelectSearchButtonRow.height
    anchors.left: parent.left
    anchors.right: parent.right


    TextField {
        id: queryInput
        width: 3 * (parent.width / 4)
        placeholderText: qsTr("search term")
    }

    Button {
        id: searchButton
        anchors.right: parent.right
        anchors.left: queryInput.right

        text: "→"
        onClicked: translationSearchBar.searchRequested()
    }

    ComboBox {
        id: languageSelector
        anchors.left: parent.left
        anchors.top: queryInput.bottom

        menu: ContextMenu {
            MenuItem { text: "DE ↔ EN" }
            MenuItem { text: "DE ↔ SV" }
        }
    }
}
