
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QApplication>
#include <QObject>
#include "dictcc.h"


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

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext* context = view->rootContext();

    view->setSource(SailfishApp::pathTo("qml/DictQuery.qml"));

    QObject * qmlRoot = view->rootObject();

    QScopedPointer<DictCC> DictCCProvider(new DictCC());

    //DictCCProvider.data()->Query();

    QObject::connect(qmlRoot, SIGNAL(startSearch()), DictCCProvider.data(), SLOT(Query()));

    view->show();

    return app.exec();
}

