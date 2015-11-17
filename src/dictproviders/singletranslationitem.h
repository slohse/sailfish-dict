#ifndef SINGLETRANSLATIONITEM_H
#define SINGLETRANSLATIONITEM_H

#include <QObject>

class SingleTranslationItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString lang1Term READ lang1Term WRITE setLang1Term NOTIFY lang1TermChanged)
    Q_PROPERTY(QString lang2Term READ lang2Term WRITE setLang2Term NOTIFY lang2TermChanged)

public:
    explicit SingleTranslationItem(QObject *parent = 0);

    SingleTranslationItem(QString const & lang1Term, QString const & lang2Term, QObject *parent = 0);

    void setLang1Term(QString lang1Term);
    void setLang2Term(QString lang2Term);
    QString lang1Term() const;
    QString lang2Term() const;

signals:
    void lang1TermChanged(QString);
    void lang2TermChanged(QString);

private:
    QString m_lang1Term;
    QString m_lang2Term;
};

#endif // SINGLETRANSLATIONITEM_H
