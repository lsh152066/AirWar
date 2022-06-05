#include "single_sql.h"
single_sql* single_sql::s = nullptr;
single_sql::single_sql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");//主机服务器
    //auto str= QCoreApplication::applicationDirPath()+"/data.db";
    db.setDatabaseName("flightrank");//数据库名
    db.setPort(3307);//端口号
    db.setUserName("root");
    db.setPassword("xby123456");
    if(db.open()){
       qDebug()<<"log数据库连接成功";
    }
    else{
       qDebug()<<db.lastError();
       qDebug()<<"数据库连接失败";
    }
}
