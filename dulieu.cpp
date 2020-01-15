#include "dulieu.h"



bool duLieu::connectdb()
{
    // THEM DATABASE

    // PHẢI THAY ĐỔI DƯỜNG DẪN ĐỂ TRUY CẬP DATABASE.
    mydb.setDatabaseName("C:/Users/Thinh/Downloads/DO AN HDL-20190615T073345Z-001/DO AN HDL/all_database.db");
    if(!mydb.open())
    {
        qDebug() << mydb.lastError().text();
        return false;
    }// END

    return true;

}

void duLieu::closedb()
{
    mydb.close();


}

duLieu::~duLieu()
{

    mydb.removeDatabase(mydb.defaultConnection);

}

duLieu::duLieu()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
}

