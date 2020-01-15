#ifndef DULIEU_H
#define DULIEU_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
class duLieu
{
public:
    QSqlDatabase mydb;
    bool connectdb();
    void closedb();
    ~duLieu();
    duLieu();

};

#endif // DULIEU_H
