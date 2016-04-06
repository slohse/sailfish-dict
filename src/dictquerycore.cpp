#include "dictquerycore.h"

#include <QtAlgorithms>
#include <QQuickItem>
#include <QDebug>

DictQueryCore::DictQueryCore(QSharedPointer<QQuickView> view, QObject *parent) :
    QObject(parent),
    _dictCcProvider(parent),
    _translationsList(),
    _view(view)
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
    ClearLanguagesSet();
    ClearLanguagesList();
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
    qDebug() << _view->rootContext()->contextProperty("translationResultsModel");
    _view->rootContext()->setContextProperty("translationResultsModel",
                                             QVariant::fromValue(_translationsList));
    qDebug() << "after:";
    qDebug() << _view->rootContext()->contextProperty("translationResultsModel");
}

void DictQueryCore::ClearLanguagesList()
{
    QObject * deleteMe;
    while(!_availableLanguagesListModel.isEmpty())
    {
        deleteMe = _availableLanguagesListModel.takeFirst().value<LanguageTuple *>();
        if(deleteMe)
        {
            deleteMe->deleteLater();
        }
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
        _availableLanguagesListModel.append(QVariant::fromValue(tuple));
    }

    qSort(_availableLanguagesListModel.begin(), _availableLanguagesListModel.end(),
          [](QVariant const left, QVariant const right) -> bool
    {
        return *((left.value<LanguageTuple  * >()))
                < *((right.value<LanguageTuple  * >()));
    });

    qDebug() << "UpdateContext. number of languages after:" << _availableLanguagesListModel.size();

//    QObject * searchBar = _view->rootObject()->findChild<QObject *>("translationSearchBar");
//    if(searchBar)
//    {
//        // TODO: continue here
//        //QMetaObject::invokeMethod(searchBar, "updateLanguageSelection", Q_ARG(QOB))
//    }

    emit LanguageTuplesChanged(_availableLanguagesListModel);
}
