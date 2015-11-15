#ifndef DICTQUERYCORE_H
#define DICTQUERYCORE_H

#include <QObject>
#include <QString>
#include "dictproviders/dictcc.h"

class DictQueryCore : public QObject
{
    Q_OBJECT
public:
    explicit DictQueryCore(QObject *parent = 0);

signals:

public slots:
    void ChangeLanguage(QString & LanguageTuple);
    void Search(QString & SearchTerm);
    void TypingEvent(QString & SearchTerm);

private:
    DictCC DictCCProvider;

};

#endif // DICTQUERYCORE_H
