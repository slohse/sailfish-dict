#include "dictcc.h"
#include <QDebug>
#include <QWebElement>
#include <QWebFrame>

DictCC::DictCC(QObject *parent) : QObject(parent)
{
    connect(RenderedPage.mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(PageFinishedLoading()));
}



void DictCC::Query()
{
    qDebug() << "DictCC::Query()";

    RenderedPage.mainFrame()->setUrl(QUrl("http://www.dict.cc"));
}

void DictCC::PageFinishedLoading()
{
    qDebug() << "DictCC::PageFinishedLoading()";

    QWebElement PageRoot = RenderedPage.mainFrame()->documentElement();

    QWebElement LanguageDropdown = PageRoot.findFirst(QString("#lpddbsf"));
    qDebug() << "DictCC::PageFinishedLoading> LanguageDropdown is of Tag Name '" << LanguageDropdown.tagName() << "'.";

    QWebElementCollection Languages = LanguageDropdown.findAll(QString("option"));

    foreach(QWebElement languageTuple, Languages)
    {
        qDebug() << "Tuple: " << languageTuple.attribute(QString("value")) << ", Label: " << languageTuple.toPlainText();
    }
}


