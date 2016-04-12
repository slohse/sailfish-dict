
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QApplication>
#include <QObject>
#include <QVariant>
#include "dictquerycore.h"


int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QApplication app(argc, argv);

    qmlRegisterType<LanguageTuple>("dictquery", 1, 0, "LanguageTuple");
    qmlRegisterType<SingleTranslationItem>("dictquery", 1, 0, "SingleTranslationItem");
    qmlRegisterType<DictQueryCore>("dictquery", 1, 0, "DictQueryCore");

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathTo("qml/DictQuery.qml"));

    view->show();

    return app.exec();
}

