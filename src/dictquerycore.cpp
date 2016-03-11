#include "dictquerycore.h"

#include <QtAlgorithms>
#include <QDebug>

DictQueryCore::DictQueryCore(QQmlContext* context, QObject *parent) :
    QObject(parent),
    _dictCcProvider(parent),
    _translationsList(),
    _qmlContext(context)
{
    QObject::connect(&_dictCcProvider, SIGNAL(ResultReady(QList<SingleTranslationItem *>)),
                     this, SLOT(ReceiveTranslationResults(QList<SingleTranslationItem *>)));
    QObject::connect(&_dictCcProvider, SIGNAL(LanguagePoolUpdated(QSet<LanguageTuple*>)),
                     this, SLOT(UpdateLanguageTuples(QSet<LanguageTuple*>)));
    UpdateContext();
}

DictQueryCore::~DictQueryCore()
{
    ClearTranslationsList();
}

QList<QObject *> & DictQueryCore::GetTranslationsList()
{
    return _translationsList;
}

void DictQueryCore::ChangeLanguage(QString languageTuple)
{

}

void DictQueryCore::Search(QString searchTerm)
{
    ClearTranslationsList();
    _dictCcProvider.Query(searchTerm);
}

void DictQueryCore::TypingEvent(QString searchTerm)
{

}

void DictQueryCore::UpdateLanguageTuples(QSet<LanguageTuple *> languages)
{
    int numOfTuples = _availableLanguages.size();
    _availableLanguages.unite(languages);

    if(numOfTuples < _availableLanguages.size())
    {
        UpdateLanguageContext();
    }
}

void DictQueryCore::ReceiveTranslationResults(QList<SingleTranslationItem *> translations)
{
//    TranslationsList += Translations;

    qDebug() << "TranslationsList:";
    for (SingleTranslationItem * item : translations)
    {
        _translationsList.append(dynamic_cast<QObject *>(item));
        qDebug() << item->queryTerm() << " <-> " << item->definition();
    }
    UpdateContext();
}

void DictQueryCore::ClearTranslationsList()
{
    QObject * deleteMe;
    while(!_translationsList.isEmpty())
    {
        deleteMe = _translationsList.takeFirst();
        deleteMe->deleteLater();
    }
    UpdateContext();
}

void DictQueryCore::UpdateContext()
{
    qDebug() << "UpdateContext. Before:";
    qDebug() << _qmlContext->contextProperty("translationResultsModel");
    _qmlContext->setContextProperty("translationResultsModel", QVariant::fromValue(_translationsList));
    qDebug() << "after:";
    qDebug() << _qmlContext->contextProperty("translationResultsModel");
}

void DictQueryCore::ClearLanguagesList()
{
    QObject * deleteMe;
    while(!_availableLanguagesListModel.isEmpty())
    {
        deleteMe = _availableLanguagesListModel.takeFirst();
        deleteMe->deleteLater();
    }
}

void DictQueryCore::UpdateLanguageContext()
{
    qDebug() << "UpdateContext. number of languages before:" << _availableLanguagesListModel.size();
    ClearLanguagesList();
    _availableLanguagesListModel = _availableLanguages.toList();

    qSort(_availableLanguagesListModel.begin(), _availableLanguagesListModel.end(),
          [](LanguageTuple const * const left, LanguageTuple const * const right) -> bool
    {
        return (*left) < (*right);
    });

    qDebug() << "UpdateContext. number of languages after:" << _availableLanguagesListModel.size();

    _qmlContext->setContextProperty("languageSelectorModel",
                                    QVariant::fromValue(_availableLanguagesListModel));
}
