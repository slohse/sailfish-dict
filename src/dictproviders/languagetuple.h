#ifndef LANGUAGETUPLE_H
#define LANGUAGETUPLE_H

#include <QObject>
#include <QString>

class LanguageTuple : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString tuple READ getTuple WRITE setTuple NOTIFY tupleChanged)
    Q_PROPERTY(QString prettyPrint READ getPrettyPrint NOTIFY prettyPrintChanged)

public:
    explicit LanguageTuple(QObject *parent = 0);
    LanguageTuple(LanguageTuple const & other);
    LanguageTuple(QString tuple, QObject *parent = 0);

    void setTuple(QString tuple);

    QString getTuple() const;
    QString getPrettyPrint() const;

    bool operator==(LanguageTuple const & other) const;
    bool operator==(QString const & tuple) const;
    bool operator!=(LanguageTuple const & other) const;
    bool operator!=(QString const & tuple) const;
    bool operator<=(LanguageTuple const & other) const;
    bool operator<(LanguageTuple const & other) const;
    bool operator>=(LanguageTuple const & other) const;
    bool operator>(LanguageTuple const & other) const;


signals:
    void tupleChanged(QString);
    void prettyPrintChanged(QString);

public slots:

private:
    QString _lang1;
    QString _lang2;
};

Q_DECLARE_METATYPE(LanguageTuple)

bool operator==(QString lhs, LanguageTuple rhs);
bool operator!=(QString lhs, LanguageTuple rhs);

uint qHash(LanguageTuple const * const key);
uint qHash(LanguageTuple const * const key, uint seed);

#endif // LANGUAGETUPLE_H
