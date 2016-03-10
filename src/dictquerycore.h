#ifndef DICTQUERYCORE_H
#define DICTQUERYCORE_H

#include <QObject>
#include <QString>
#include <QList>
#include <QQmlContext>
#include "dictproviders/dictcc.h"
#include "dictproviders/singletranslationitem.h"

class DictQueryCore : public QObject
{
    Q_OBJECT
public:
    explicit DictQueryCore(QQmlContext* context, QObject *parent = 0);

    virtual ~DictQueryCore();

    QList<QObject *> & GetTranslationsList();

signals:

public slots:
    void ChangeLanguage(QString LanguageTuple);
    void Search(QString SearchTerm);
    void TypingEvent(QString SearchTerm);

private slots:
    void ReceiveTranslationResults(QList<SingleTranslationItem *> Translations);

private:
    DictCC DictCCProvider;
    QList<QObject *> TranslationsList;
    QQmlContext* qmlContext;

    void ClearTranslationsList();
    void UpdateContext();

};

#endif // DICTQUERYCORE_H
