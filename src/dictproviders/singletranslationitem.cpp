#include "singletranslationitem.h"

SingleTranslationItem::SingleTranslationItem(QObject *parent) : QObject(parent)
{

}

SingleTranslationItem::SingleTranslationItem(SingleTranslationItem const & other) :
    QObject(other.parent()),
    _queryTerm(other._queryTerm),
    _definition(other._definition)
{

}

SingleTranslationItem::SingleTranslationItem(QString const & queryTerm, QString const & definition, QObject *parent) :
    QObject(parent),
    _queryTerm(queryTerm),
    _definition(definition)
{

}


void SingleTranslationItem::setQueryTerm(QString queryTerm)
{
    if(_queryTerm != queryTerm)
    {
        _queryTerm = queryTerm;
        emit queryTermChanged(_queryTerm);
    }
}

void SingleTranslationItem::setDefinition(QString definition)
{
    if(_definition != definition)
    {
        _definition = definition;
        emit definitionChanged(_definition);
    }
}

QString SingleTranslationItem::queryTerm() const
{
    return _queryTerm;
}

QString SingleTranslationItem::definition() const
{
    return _definition;
}

