#include "dictcc.h"
#include <QDebug>
#include <QWebElement>
#include <QWebFrame>

DictCC::DictCC(QObject *parent) :
    QObject(parent),
    LastRequest(RequestType::None)
{
    connect(RenderedPage.mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(PageFinishedLoading()));

    RenderedPage.mainFrame()->setUrl(QUrl("http://www.dict.cc"));
}



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

        break;
    case RequestType::QueryLanguages:
        emit LanguagePoolUpdated(ParseLanguages());
        break;
    case RequestType::UpdateSuggestions:

        break;
    case RequestType::QueryTerm:

        break;
    case RequestType::ChangeLanguageTuple:

        break;
    default:
        break;
    }
}


QList<QString> DictCC::ParseLanguages()
{
    QWebElement PageRoot = RenderedPage.mainFrame()->documentElement();

    QWebElement LanguageDropdown = PageRoot.findFirst(QString("#lpddbsf"));
    qDebug() << "DictCC::PageFinishedLoading> LanguageDropdown is of Tag Name '" << LanguageDropdown.tagName() << "'.";

    QWebElementCollection Languages = LanguageDropdown.findAll(QString("option"));

    QList<QString> ParsedLanguages;

    foreach(QWebElement languageTuple, Languages)
    {
        qDebug() << "Tuple: " << languageTuple.attribute(QString("value")) << ", Label: " << languageTuple.toPlainText();
        ParsedLanguages.append(languageTuple.attribute(QString("value")));
    }

    return ParsedLanguages;
}


void DictCC::ExtractTranslations()
{

}

void DictCC::ExtractSuggestions()
{

}

QUrl DictCC::BuildUrl(QString const & LanguageTuple, QString const & SearchTerm)
{
    QString Url("http://");

    Url.append(LanguageTuple);

    Url.append("dict.cc/?s=");

    Url.append(SearchTerm);

    return QUrl(Url);
}
