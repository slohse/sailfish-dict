#ifndef DICTCC_H
#define DICTCC_H

#include <QObject>
#include <QWebPage>
#include <QString>
#include <QList>
#include "singletranslationitem.h"
#include "languagetuple.h"

enum class RequestType {None, QueryLanguages, UpdateSuggestions, QueryTerm, ChangeLanguageTuple};

class DictCC : public QObject
{
    Q_OBJECT
public:
    explicit DictCC(QObject *parent = 0);

    void GetLanguages();

signals:
    void LanguagePoolUpdated(QSet<LanguageTuple*> Languages);
    void SuggestionsUpdated(QList<QString> Suggestions);
    void ResultReady(QList<SingleTranslationItem *> Results);

public slots:
    void Query(QString const & Term);
    void SearchTermChanged(QString const & Term);
    void setLanguageTuple(QString const & Term);


private slots:
    void PageFinishedLoading();

private:

    QSet<LanguageTuple *> ParseLanguages();
    void ExtractTranslations();
    void ExtractSuggestions();

    QUrl BuildUrl(QString const & LanguageTuple, QString const & SearchTerm);

    QString SelectedLanguageTuple;
    QWebPage RenderedPage;
    RequestType LastRequest;

    QString static const UrlScheme;
    QString static const UrlHost;
    QString static const UrlQueryKeywordSearchTerm;
    QString static const JSArrayLang1;
    QString static const JSArrayLang2;


};

#endif // DICTCC_H
