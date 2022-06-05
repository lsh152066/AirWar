#ifndef SINGLE_SQL_H
#define SINGLE_SQL_H
#include<QSqlDatabase>
#include<qDebug>
#include<QCoreApplication>
#include <QSqlError>
class single_sql
{
public:

    static single_sql* GetDb(){
        if(s==NULL)
            s=new single_sql();
        return s;
    }
private:
    single_sql();
    static single_sql* s;
public:
    QSqlDatabase db;
    QString sid;
};

#endif // SINGLE_SQL_H
