
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

    qmlRegisterType<LanguageTuple>("LanguageTuple", 1, 0, "LanguageTuple");

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext* context = view->rootContext();

    QScopedPointer<DictQueryCore> QueryCore(new DictQueryCore(context));

    view->setSource(SailfishApp::pathTo("qml/DictQuery.qml"));

    QObject * qmlRoot = view->rootObject();
    QObject * mainPage = qmlRoot->findChild<QObject *>("mainPage");

    QObject::connect(mainPage, SIGNAL(startSearch(QString)), QueryCore.data(), SLOT(Search(QString)));
    QObject::connect(mainPage, SIGNAL(searchTermChanged(QString)), QueryCore.data(), SLOT(TypingEvent(QString)));

    view->show();

    return app.exec();
}

