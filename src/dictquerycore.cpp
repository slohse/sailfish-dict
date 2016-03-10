#include "dictquerycore.h"
#include <QDebug>

DictQueryCore::DictQueryCore(QQmlContext* context, QObject *parent) :
    QObject(parent),
    DictCCProvider(parent),
    TranslationsList(),
    qmlContext(context)
{
    QObject::connect(&DictCCProvider, SIGNAL(ResultReady(QList<SingleTranslationItem *>)),
                     this, SLOT(ReceiveTranslationResults(QList<SingleTranslationItem *>)));
    UpdateContext();
}

DictQueryCore::~DictQueryCore()
{
    ClearTranslationsList();
}

QList<QObject *> & DictQueryCore::GetTranslationsList()
{
    return TranslationsList;
}

void DictQueryCore::ChangeLanguage(QString LanguageTuple)
{

}

void DictQueryCore::Search(QString SearchTerm)
{
    ClearTranslationsList();
    DictCCProvider.Query(SearchTerm);
}

void DictQueryCore::TypingEvent(QString SearchTerm)
{

}

void DictQueryCore::ReceiveTranslationResults(QList<SingleTranslationItem *> Translations)
{
//    TranslationsList += Translations;

    qDebug() << "TranslationsList:";
    for (SingleTranslationItem * item : Translations)
    {
        TranslationsList.append(dynamic_cast<QObject *>(item));
        qDebug() << item->queryTerm() << " <-> " << item->definition();
    }
    UpdateContext();
}

void DictQueryCore::ClearTranslationsList()
{
    QObject * deleteMe;
    while(!TranslationsList.isEmpty())
    {
        deleteMe = TranslationsList.takeFirst();
        deleteMe->deleteLater();
    }
    UpdateContext();
}

void DictQueryCore::UpdateContext()
{
    qDebug() << "UpdateContext. Before:";
    qDebug() << qmlContext->contextProperty("translationResultsModel");
    qmlContext->setContextProperty("translationResultsModel", QVariant::fromValue(TranslationsList));
    qDebug() << "after:";
    qDebug() << qmlContext->contextProperty("translationResultsModel");
}

