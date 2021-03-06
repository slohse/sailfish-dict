#include "dictquerycore.h"

#include <QtAlgorithms>
#include <QDebug>

DictQueryCore::DictQueryCore(QObject *parent) :
    QObject(parent),
    _dictCcProvider(parent),
    _translationsList()
{
    QObject::connect(&_dictCcProvider, SIGNAL(ResultReady(QList<SingleTranslationItem *>)),
                     this, SLOT(ReceiveTranslationResults(QList<SingleTranslationItem *>)));
    QObject::connect(&_dictCcProvider, SIGNAL(LanguagePoolUpdated(QSet<LanguageTuple*>)),
                     this, SLOT(UpdateLanguageTuples(QSet<LanguageTuple*>)));

    emit updateTranslations(QVariant::fromValue(_translationsList));
}

DictQueryCore::~DictQueryCore()
{
    ClearTranslationsList();
    ClearLanguagesSet();
    ClearLanguagesList();
}

QList<QObject *> & DictQueryCore::GetTranslationsList()
{
    return _translationsList;
}

void DictQueryCore::changeLanguage(QString languageTuple)
{
    qDebug() << "changeLanguage " << languageTuple;
    _dictCcProvider.setLanguageTuple(languageTuple);
}

void DictQueryCore::search(QString searchTerm)
{
    ClearTranslationsList();
    _dictCcProvider.Query(searchTerm);
}

void DictQueryCore::typingEvent(QString searchTerm)
{

}

void DictQueryCore::UpdateLanguageTuples(QSet<LanguageTuple *> languages)
{
    QSet<LanguageTuple *> TuplesAlreadyPresent(languages);
    TuplesAlreadyPresent.intersect(_availableLanguages);

    if(TuplesAlreadyPresent.size() != languages.size())
    {
        _availableLanguages.unite(languages);
        UpdateLanguageContext();
    }

    // clean all languageTuples that did not make it into _availableLanguages
    for(LanguageTuple * deleteMe : TuplesAlreadyPresent)
    {
        deleteMe->deleteLater();
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

    emit updateTranslations(QVariant::fromValue(_translationsList));
}

void DictQueryCore::ClearTranslationsList()
{
    QObject * deleteMe;
    while(!_translationsList.isEmpty())
    {
        deleteMe = _translationsList.takeFirst();
        deleteMe->deleteLater();
    }

    emit updateTranslations(QVariant::fromValue(_translationsList));
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

void DictQueryCore::ClearLanguagesSet()
{
    for(LanguageTuple * deleteMe : _availableLanguages)
    {
        deleteMe->deleteLater();
    }

    _availableLanguages.clear();
}

void DictQueryCore::UpdateLanguageContext()
{
    qDebug() << "UpdateContext. number of languages before:" << _availableLanguagesListModel.size();
    ClearLanguagesList();
    for(LanguageTuple * tuple : _availableLanguages)
    {
        _availableLanguagesListModel.append(dynamic_cast<QObject *>(tuple));
    }

    qSort(_availableLanguagesListModel.begin(), _availableLanguagesListModel.end(),
          [](QObject const * const left, QObject const * const right) -> bool
    {
        return *(dynamic_cast<LanguageTuple const * const>(left))
                < *(dynamic_cast<LanguageTuple const * const>(right));
    });

    qDebug() << "UpdateContext. number of languages after:" << _availableLanguagesListModel.size();

    emit updateLanguages(QVariant::fromValue(_availableLanguagesListModel));
}
