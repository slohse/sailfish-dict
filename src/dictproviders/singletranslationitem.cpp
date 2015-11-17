#include "singletranslationitem.h"

SingleTranslationItem::SingleTranslationItem(QObject *parent) : QObject(parent)
{

}

SingleTranslationItem::SingleTranslationItem(QString const & lang1Term, QString const & lang2Term, QObject *parent) :
    QObject(parent),
    m_lang1Term(lang1Term),
    m_lang2Term(lang2Term)
{

}


void SingleTranslationItem::setLang1Term(QString lang1Term)
{
    m_lang1Term = lang1Term;
    emit lang1TermChanged(m_lang1Term);
}

void SingleTranslationItem::setLang2Term(QString lang2Term)
{
    m_lang2Term = lang2Term;
    emit lang2TermChanged(m_lang2Term);
}

QString SingleTranslationItem::lang1Term() const
{
    return m_lang1Term;
}

QString SingleTranslationItem::lang2Term() const
{
    return m_lang2Term;
}

