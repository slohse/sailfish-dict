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

    SingleTranslationItem(QString const & queryTerm, QString const & definition, QObject *parent = 0);

    void setQueryTerm(QString queryTerm);
    void setDefinition(QString definition);
    QString queryTerm() const;
    QString definition() const;

signals:
    void queryTermChanged(QString);
    void definitionChanged(QString);

private:
    QString m_queryTerm;
    QString m_definition;
};

#endif // SINGLETRANSLATIONITEM_H
