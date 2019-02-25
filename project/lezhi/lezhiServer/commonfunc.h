#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <QObject>

class CommonFunc : public QObject
{
    Q_OBJECT
public:
    explicit CommonFunc(QObject *parent = 0);

signals:

public slots:

private://data parse
    bool md5Encrypt();
    bool md5Decrypt();
};

#endif // COMMONFUNC_H
