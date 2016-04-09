#include "languagetuple.h"

#include <QHash>

LanguageTuple::LanguageTuple(QObject *parent) :
    QObject(parent)
{

}

LanguageTuple::LanguageTuple(LanguageTuple const & other) :
    QObject(other.parent())
{
    _lang1 = other._lang1;
    _lang2 = other._lang2;
}

LanguageTuple::LanguageTuple(QString tuple, QObject *parent) :
    QObject(parent)
{
    setTuple(tuple);
}

void LanguageTuple::setTuple(QString tuple)
{
    // language tuples consist of two ISO639-1 codes
    if(tuple.length() != 4)
    {
        return;
    }

    tuple = tuple.toLower();

    _lang1 = tuple.mid(0, 2);
    _lang2 = tuple.mid(2, 2);

    // order the languages to make comparisons between LanguageTuples easier
    if(_lang1 > _lang2)
    {
        _lang1.swap(_lang2);
    }

    emit tupleChanged(getTuple());
    emit prettyPrintChanged(getPrettyPrint());
}

QString LanguageTuple::getTuple() const
{
    return _lang1 + _lang2;
}

QString LanguageTuple::getPrettyPrint() const
{
    return _lang1.toUpper() + " ↔ " + _lang2.toUpper();
}


bool LanguageTuple::operator==(LanguageTuple const & other) const
{
    return ((other._lang1 == this->_lang1)
            && (other._lang2 == this->_lang2));
}

bool LanguageTuple::operator==(QString const & tuple) const
{
    return LanguageTuple(tuple).operator==(*this);
}

bool LanguageTuple::operator!=(LanguageTuple const & other) const
{
    return !(this->operator==(other));
}

bool LanguageTuple::operator!=(QString const & tuple) const
{
    return !(this->operator==(tuple));
}

bool LanguageTuple::operator<=(LanguageTuple const & other) const
{
    return (this->getTuple() <= other.getTuple());
}

bool LanguageTuple::operator<(LanguageTuple const & other) const
{
    return (this->operator<=(other) && this->operator!=(other));
}

bool LanguageTuple::operator>=(LanguageTuple const & other) const
{
    return (this->getTuple() >= other.getTuple());
}

bool LanguageTuple::operator>(LanguageTuple const & other) const
{
    return (this->operator>=(other) && this->operator!=(other));
}

bool operator==(QString const & lhs, LanguageTuple const & rhs)
{
    return rhs.operator==(lhs);
}

bool operator!=(QString const & lhs, LanguageTuple const & rhs)
{
    return rhs.operator!=(lhs);
}

uint qHash(LanguageTuple const * const key)
{
    return qHash(key->getTuple());
}

uint qHash(LanguageTuple const * const key, uint seed)
{
    return qHash(key->getTuple(), seed);
}
