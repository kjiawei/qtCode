#ifndef CREATEDB_H
#define CREATEDB_H

#include <QList>
#include <QStringList>

class CreateDb
{
public:
    CreateDb();

    void initDB();

    QList<QStringList> selectDataFromBase();

};

#endif // CREATEDB_H
