#ifndef SINGLETRANSLATIONITEM_H
#define SINGLETRANSLATIONITEM_H

#include <QObject>

class SingleTranslationItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString queryTerm READ queryTerm WRITE setQueryTerm NOTIFY queryTermChanged)
    Q_PROPERTY(QString definition READ definition WRITE setDefinition NOTIFY definitionChanged)

public:
    explicit SingleTranslationItem(QObject *parent = 0);
    SingleTranslationItem(SingleTranslationItem const & other);

    SingleTranslationItem(QString const & queryTerm, QString const & definition, QObject *parent = 0);

    void setQueryTerm(QString queryTerm);
    void setDefinition(QString definition);
    QString queryTerm() const;
    QString definition() const;

signals:
    void queryTermChanged(QString);
    void definitionChanged(QString);

private:
    QString _queryTerm;
    QString _definition;
};
Q_DECLARE_METATYPE(SingleTranslationItem)

#endif // SINGLETRANSLATIONITEM_H
