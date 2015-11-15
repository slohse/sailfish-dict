#ifndef DICTCC_H
#define DICTCC_H

#include <QObject>
#include <QWebPage>
#include <QString>
#include <QList>

enum class RequestType {None, QueryLanguages, UpdateSuggestions, QueryTerm, ChangeLanguageTuple};

class DictCC : public QObject
{
    Q_OBJECT
public:
    explicit DictCC(QObject *parent = 0);

    void GetLanguages();

signals:
    void LanguagePoolUpdated(QList<QString> Languages);
    void SuggestionsUpdated(QList<QString> Suggestions);

public slots:
    void Query(QString const & Term);
    void SearchTermChanged(QString const & Term);
    void setLanguageTuple(QString const & Term);


private slots:
    void PageFinishedLoading();

private:

    QList<QString> ParseLanguages();
    void ExtractTranslations();
    void ExtractSuggestions();

    QUrl BuildUrl(QString const & LanguageTuple, QString const & SearchTerm);

    QString SelectedLanguageTuple;
    QWebPage RenderedPage;
    RequestType LastRequest;

};

#endif // DICTCC_H
