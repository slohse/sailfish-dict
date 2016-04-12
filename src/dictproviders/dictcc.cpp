#include "dictcc.h"
#include <QDebug>
#include <QWebElement>
#include <QWebFrame>
#include <QUrlQuery>

QString const DictCC::UrlScheme("http");
QString const DictCC::UrlHost("dict.cc");
QString const DictCC::UrlQueryKeywordSearchTerm("s");

// interesting javascript variables
QString const DictCC::JSArrayLang1("c1Arr");
QString const DictCC::JSArrayLang2("c2Arr");


DictCC::DictCC(QObject *parent) :
    QObject(parent),
    LastRequest(RequestType::None)
{
    connect(RenderedPage.mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(PageFinishedLoading()));

    RenderedPage.mainFrame()->setUrl(QUrl("http://www.dict.cc"));
}


//void DictCC::GetLanguages()
//{

//}


//---------------------------------------------------------------------------------------
// public slots
//---------------------------------------------------------------------------------------

void DictCC::Query(QString const & Term)
{
    qDebug() << "DictCC::Query()";

    LastRequest = RequestType::QueryTerm;

    RenderedPage.mainFrame()->setUrl(BuildUrl(SelectedLanguageTuple, Term));
}

void DictCC::SearchTermChanged(QString const & Term)
{
    LastRequest = RequestType::UpdateSuggestions;


}

void DictCC::setLanguageTuple(QString const & Tuple)
{
    SelectedLanguageTuple = Tuple;

    LastRequest = RequestType::ChangeLanguageTuple;

    RenderedPage.mainFrame()->setUrl(BuildUrl(Tuple, QString()));
}

void DictCC::PageFinishedLoading()
{
    qDebug() << "DictCC::PageFinishedLoading()";

    switch (LastRequest) {
    case RequestType::None:
        emit LanguagePoolUpdated(ParseLanguages());
        break;
    case RequestType::QueryLanguages:
        emit LanguagePoolUpdated(ParseLanguages());
        break;
    case RequestType::UpdateSuggestions:

        break;
    case RequestType::QueryTerm:
        ExtractTranslations();
        ParseLanguages();
        break;
    case RequestType::ChangeLanguageTuple:

        break;
    default:
        break;
    }
}


//---------------------------------------------------------------------------------------
// private methods
//---------------------------------------------------------------------------------------

QSet<LanguageTuple *> DictCC::ParseLanguages()
{
    QWebElement PageRoot = RenderedPage.mainFrame()->documentElement();

    QWebElement LanguageDropdown = PageRoot.findFirst(QString("#lpddbsf"));
    qDebug() << "DictCC::PageFinishedLoading> LanguageDropdown is of Tag Name '" << LanguageDropdown.tagName() << "'.";

    QWebElementCollection Languages = LanguageDropdown.findAll(QString("option"));

    QSet<LanguageTuple *> ParsedLanguages;

    foreach(QWebElement langTuple, Languages)
    {
        QString Label = langTuple.toPlainText();

        // for now only use bidirectional tuples
        if(Label.contains(QString("<>")))
        {
            QString CodeTuple = langTuple.attribute(QString("value"));
            qDebug() << "Tuple: " << CodeTuple << ", Label: " << Label;
            ParsedLanguages.insert(new LanguageTuple(CodeTuple));
        }
    }

    return ParsedLanguages;
}


void DictCC::ExtractTranslations()
{
    const QVariant Lang1Array = RenderedPage.mainFrame()->evaluateJavaScript(JSArrayLang1);
    const QVariant Lang2Array = RenderedPage.mainFrame()->evaluateJavaScript(JSArrayLang2);

    QStringList Lang1List = Lang1Array.toStringList();
    QStringList Lang2List = Lang2Array.toStringList();

    QList<SingleTranslationItem *> TranslationPairs;

    for(int i = 0; i < Lang1List.length() && i < Lang2List.length(); ++i)
    {
        if(Lang1List.at(i) != QString("") && Lang2List.at(i) != QString(""))
        {
            TranslationPairs.append(new SingleTranslationItem(Lang1List.at(i), Lang2List.at(i)));
        }
    }

    emit ResultReady(TranslationPairs);
}

void DictCC::ExtractSuggestions()
{
    // see js function "autosug_ku"
}

QUrl DictCC::BuildUrl(QString const & LanguageTuple, QString const & SearchTerm)
{
    QString UrlDomain("");

    if(LanguageTuple.length() > 0)
    {
        UrlDomain.append(LanguageTuple);
        UrlDomain.append(".");
    }

    qDebug() << UrlDomain;

    UrlDomain.append(UrlHost);

    qDebug() << UrlDomain;

    QUrl SearchUrl;

    SearchUrl.setScheme(UrlScheme);
    SearchUrl.setHost(UrlDomain);
    QUrlQuery Query;
    Query.addQueryItem(UrlQueryKeywordSearchTerm, SearchTerm);
    SearchUrl.setQuery(Query);

    qDebug() << SearchUrl.toDisplayString();

    return SearchUrl;
}
