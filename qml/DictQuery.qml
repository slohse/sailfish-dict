import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    id: rootWindow

    initialPage: Qt.resolvedUrl("pages/MainPage.qml")
//    cover: Qt.resolvedUrl("pages/Cover.qml")
    allowedOrientations: Orientation.All
    _defaultPageOrientations: Orientation.All

}


