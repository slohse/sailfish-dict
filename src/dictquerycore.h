#ifndef DICTQUERYCORE_H
#define DICTQUERYCORE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QQuickView>
#include <QSharedPointer>
#include <QQmlContext>
#include <QSet>

#include "dictproviders/dictcc.h"
#include "dictproviders/singletranslationitem.h"
#include "dictproviders/languagetuple.h"

class DictQueryCore : public QObject
{
    Q_OBJECT
public:
    explicit DictQueryCore(QSharedPointer<QQuickView> view, QObject *parent = 0);

    virtual ~DictQueryCore();

    QList<QObject *> & GetTranslationsList();

signals:
    void LanguageTuplesChanged(QVariant languageTuples);

public slots:
    void ChangeLanguage(QString languageTuple);
    void Search(QString searchTerm);
    void TypingEvent(QString searchTerm);
    void UpdateLanguageTuples(QSet<LanguageTuple *> languages);

private slots:
    void ReceiveTranslationResults(QList<SingleTranslationItem *> translations);

private:
    DictCC _dictCcProvider;
    QList<QObject *> _translationsList;
    QSet<LanguageTuple *> _availableLanguages;
    QVariantList _availableLanguagesListModel;
    QSharedPointer<QQuickView> _view;

    void ClearTranslationsList();
    void UpdateContext();
    void ClearLanguagesList();
    void ClearLanguagesSet();
    void UpdateLanguageContext();


};

#endif // DICTQUERYCORE_H
