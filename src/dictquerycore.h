#ifndef DICTQUERYCORE_H
#define DICTQUERYCORE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QQmlContext>
#include <QSet>

#include "dictproviders/dictcc.h"
#include "dictproviders/singletranslationitem.h"
#include "dictproviders/languagetuple.h"

class DictQueryCore : public QObject
{
    Q_OBJECT
public:
    explicit DictQueryCore(QQmlContext* context, QObject *parent = 0);

    virtual ~DictQueryCore();

    QList<QObject *> & GetTranslationsList();

signals:
    void LanguageTuplesChanged(QList<QObject*> languageTuples);

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
    QList<QObject *> _availableLanguagesListModel;
    QQmlContext* _qmlContext;

    void ClearTranslationsList();
    void UpdateContext();
    void ClearLanguagesList();
    void UpdateLanguageContext();


};

#endif // DICTQUERYCORE_H
