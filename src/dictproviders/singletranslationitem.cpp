#include "singletranslationitem.h"

SingleTranslationItem::SingleTranslationItem(QObject *parent) : QObject(parent)
{

}

SingleTranslationItem::SingleTranslationItem(QString const & queryTerm, QString const & definition, QObject *parent) :
    QObject(parent),
    m_queryTerm(queryTerm),
    m_definition(definition)
{

}


void SingleTranslationItem::setQueryTerm(QString queryTerm)
{
    m_queryTerm = queryTerm;
    emit queryTermChanged(m_queryTerm);
}

void SingleTranslationItem::setDefinition(QString definition)
{
    m_definition = definition;
    emit definitionChanged(m_definition);
}

QString SingleTranslationItem::queryTerm() const
{
    return m_queryTerm;
}

QString SingleTranslationItem::definition() const
{
    return m_definition;
}

