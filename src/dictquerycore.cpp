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

QList<SingleTranslationItem *> & DictQueryCore::GetTranslationsList()
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
    TranslationsList += Translations;
    UpdateContext();

    qDebug() << "TranslationsList:";
    foreach (SingleTranslationItem * item, TranslationsList) {
        qDebug() << item->lang1Term() << " <-> " << item->lang2Term();
    }
}

void DictQueryCore::ClearTranslationsList()
{
    SingleTranslationItem * deleteMe;
    while(!TranslationsList.isEmpty())
    {
        deleteMe = TranslationsList.takeFirst();
        delete deleteMe;
    }
    UpdateContext();
}

void DictQueryCore::UpdateContext()
{
    qmlContext->setContextProperty("translationResultsModel", QVariant::fromValue(TranslationsList));
}

