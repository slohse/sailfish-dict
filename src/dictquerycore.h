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
    explicit DictQueryCore(QObject *parent = 0);

    DictQueryCore(DictQueryCore const & other);

    virtual ~DictQueryCore();

    QList<QObject *> & GetTranslationsList();

signals:
    Q_INVOKABLE void UpdateTranslations(QVariant translations);
    Q_INVOKABLE void UpdateLanguages(QVariant Languages);

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

    void ClearTranslationsList();
    void UpdateContext();
    void ClearLanguagesList();
    void ClearLanguagesSet();
    void UpdateLanguageContext();
};
Q_DECLARE_METATYPE(DictQueryCore)

#endif // DICTQUERYCORE_H
