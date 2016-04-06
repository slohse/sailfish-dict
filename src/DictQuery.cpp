
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

    QSharedPointer<QQuickView> view(SailfishApp::createView());

    QScopedPointer<DictQueryCore> QueryCore(new DictQueryCore(view));

    view->setSource(SailfishApp::pathTo("qml/DictQuery.qml"));

    QObject * qmlRoot = view->rootObject();

    QObject::connect(qmlRoot, SIGNAL(startSearch(QString)), QueryCore.data(), SLOT(Search(QString)));
    QObject::connect(qmlRoot, SIGNAL(searchTermChanged(QString)), QueryCore.data(), SLOT(TypingEvent(QString)));
    QObject::connect(QueryCore.data(), SIGNAL(LanguageTuplesChanged(QVariant)),
                     qmlRoot, SLOT(updateAvailableLanguages(QVariant)));


    view->show();

    return app.exec();
}

