#ifndef DICTCC_H
#define DICTCC_H

#include <QObject>
#include <QWebPage>

class DictCC : public QObject
{
    Q_OBJECT
public:
    explicit DictCC(QObject *parent = 0);

    void GetLanguages();

signals:

public slots:
    void Query();

private slots:
    void PageFinishedLoading();

private:
    QWebPage RenderedPage;

};

#endif // DICTCC_H
