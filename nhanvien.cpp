#include "nhanvien.h"
#include "ui_nhanvien.h"

nhanVien::nhanVien(QWidget *parent) : QDialog(parent),ui(new Ui::nhanVien)
{
     ui->setupUi(this);


}

nhanVien::~nhanVien()
{
    delete ui;
}

void nhanVien::setdefaut_radio(QRadioButton *Qrad)
{
    if(Qrad->isChecked())
    {
        Qrad->setAutoExclusive(false);
        Qrad->setChecked(false);
        Qrad->setAutoExclusive(true);
    }
}

void nhanVien::getdatabaseListKV()
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT NAME FROM KHUVUC");
    qry.exec();
    QSqlQueryModel *modal = new QSqlQueryModel(ui->_listViewKV);
    modal->setQuery(qry);
    ui->_listViewKV->setModel(modal);
    qry.clear();
    _dulieu.closedb();
}

void nhanVien::on_pushButton_2_clicked()
{
    emit homeClicked();
    ui->stackedWidget->setCurrentWidget(ui->pageIndex);

}



void nhanVien::on__listViewKV_clicked(const QModelIndex &index)
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QString val = ui->_listViewKV->model()->data(index).toString();
    QSqlQuery qry(_dulieu.mydb); // tao phien
    qry.prepare("SELECT SOLUONG FROM KHUVUC WHERE NAME = '" + val +"'");
    if(qry.exec())
         {
             while(qry.next())
             { // THEM BAN
                int k = qry.value(0).toInt();
                ui->_comboBoxBAN->clear();
                for(int i = 1; i <= k; i++)
                    ui->_comboBoxBAN->addItem(QString::number(i));
             }
         }
    qry.clear();
    _dulieu.closedb();
}

void nhanVien::on_pushButton_clicked() //ORDER
{
    ui->stackedWidget->setCurrentWidget(ui->pageOrder);
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT NAME,DONGIA FROM MENU");
    qry.exec();
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery(qry);
    ui->_treeViewOrder->setModel(modal);
    ui->_treeViewOrder->resizeColumnToContents(0);

    qry.clear();
    _dulieu.closedb();
    //ui->_comboBoxBAN->clear();
    ui->_lineOid->clear();
    ui->_lineOsl->clear();

    QModelIndex index = ui->_listViewKV->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    itemText += ui->_comboBoxBAN->currentText();
    ui->_lanameb->setText("Bàn: "+itemText);



}

void nhanVien::on__treeViewOrder_clicked(const QModelIndex &index)
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QString val = ui->_treeViewOrder->model()->data(index).toString();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT ID FROM MENU WHERE NAME = '" + val +"'");
    if(qry.exec())
         {
             while(qry.next())
             {
                ui->_lineOid->setText(qry.value(0).toString());
             }
    }
    qry.clear();
    _dulieu.closedb();

}

void nhanVien::on_pushButton_4_clicked() //ORDER
{
    if(ui->_comboBoxBAN->currentText() == "")
    {
        QMessageBox::critical(this,tr("Error:"),"Chưa chọn bàn");
    } else if(ui->_lineOsl->text() == "")
        QMessageBox::critical(this,tr("Error:"),"Chưa Có Số Lượng");
    else
    {// ORDER DO UONG
        // get string
        QModelIndex index = ui->_listViewKV->currentIndex();
        QString itemText = index.data(Qt::DisplayRole).toString();
        itemText += ui->_comboBoxBAN->currentText();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        if(qry.prepare("SELECT * FROM " + itemText) == false) // KIEM TRA DA TAO TABLE LUU TRU ORDER CHUA?
        {
            QString command = "CREATE TABLE "+itemText+" (aORDER TEXT NOT NULL,aSOLUONG TEXT NOT NULL);"; // TAO TABLE
            if(qry.prepare(command))
                 qry.exec();
            QString aOrder = ui->_lineOid->text();
            QString aSoluong = ui->_lineOsl->text();
            QString command2 =  "INSERT INTO " + itemText + " (aORDER,aSOLUONG) VALUES ('" + aOrder + "','"+ aSoluong +"');"; // THEM PHAN TU DAU TIEN
             qry.prepare(command2);
             if(qry.exec())
                     QMessageBox::information(this,tr("Order:"),"Ordered");
             else
                     qDebug() << qry.lastError().text();
        }
        else { // DA TAO TABLE
            if(qry.exec())
            {
                     while (qry.next())
                     {
                        QStringList list = qry.value(0).toString().split(' ');
                        int pos = list.indexOf(QRegExp("*" + ui->_lineOid->text() + "*",Qt::CaseInsensitive, QRegExp::Wildcard),0);
                        if (pos != -1) // TRUNG ORDER
                        {
                            QMessageBox::critical(this,tr("Order:"),"Duplipcated");
                            break;
                        }
                        QString aOrder = qry.value(0).toString() + " " +ui->_lineOid->text(); // CHEN PHAN TU TIEP THEO VAO CUOI CHUOI
                        QString aSoluong = qry.value(1).toString() + " " + ui->_lineOsl->text();
                        QString command = "UPDATE " + itemText + " SET aOrder = '" + aOrder + "', aSoluong = '" + aSoluong + "'"; // CAP NHAP LAI DU LIEU;
                        qry.prepare(command);
                        if(qry.exec())
                            QMessageBox::information(this,tr("Order:"),"Ordered");
                        else
                            qDebug() << qry.lastError().text();
                     }
             }
           }
        qry.clear();
        _dulieu.closedb();
    }

}

void nhanVien::on_pushButton_3_clicked() // INFORMATION
{
    ui->stackedWidget->setCurrentWidget(ui->pageInfo);
    // HIEN THI THONG TIN ORDER
    QModelIndex index = ui->_listViewKV->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    itemText += ui->_comboBoxBAN->currentText();
    ui->_lanameban->setText("Bàn : "+itemText);
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    ui->_treeWidgetInfo->clear();
    if(qry.prepare("SELECT * FROM " + itemText))
    {
        qry.exec();
        QString aOrder;
        QString aSoluong;
        while(qry.next())
        {
         aOrder = qry.value(0).toString();
         aSoluong = qry.value(1).toString();
        }
        QStringList lOrder = aOrder.split(' '); // LAY TOKENS ARRAY ORDER
        QStringList lSoluong = aSoluong.split(' '); // LAY TOKENS ARRAY SOLUONG
        ui->_treeWidgetInfo->setColumnCount(2);
        ui->_treeWidgetInfo->setHeaderLabels(QStringList() << " MÓN ĂN" << " SỐ LƯỢNG");
        int leng = lOrder.length() ;
        for (int i = 0 ; i < leng; i++)
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->_treeWidgetInfo);
             QString name = "";
             qry.exec("SELECT NAME FROM MENU WHERE ID = '" + lOrder[i] + "'");  // LAY TEN MON AN
             while(qry.next())
             {
                    name = qry.value(0).toString();
             }
             item->setText(0,name);
             item->setText(1,lSoluong[i]);
             ui->_treeWidgetInfo->resizeColumnToContents(0);

        }

    }
    qry.clear();
    _dulieu.closedb();

    ui->stackedWidget_2->setCurrentWidget(ui->pageIndex_2);
    setdefaut_radio(ui->_radtt);
    setdefaut_radio(ui->_radsua);
    setdefaut_radio(ui->_radxoa);

}

void nhanVien::on__radtt_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageThanhToan);
    ui->_lineTt->clear();
    QModelIndex index = ui->_listViewKV->currentIndex();
    QString itemText = index.data(Qt::DisplayRole).toString();
    itemText += ui->_comboBoxBAN->currentText();
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT * FROM " + itemText);
    qry.exec();
    QString aOrder;
    QString aSoluong;
    while(qry.next())
    {
        aOrder = qry.value(0).toString();
        aSoluong = qry.value(1).toString();
    }
    QStringList lOrder = aOrder.split(' ');
    QStringList lSoluong = aSoluong.split(' ');
    int leng = lOrder.length() ;
    long TONG = 0;
    for (int i = 0 ; i < leng; i++)
    {
        qry.exec("SELECT DONGIA FROM MENU WHERE ID = '" + lOrder[i] + "'");
        QString dongia;
        while(qry.next())
        {
             dongia= qry.value(0).toString();
        }
        TONG += dongia.toLong()*lSoluong[i].toLong();
     }
     ui->_lineTt->setText(QString::number(TONG));
     if(ui->_lineTt->text() == "0")
        QMessageBox::critical(this,tr("Error:"),"Không Có Thông Tin Thanh Toán");
     qry.clear();
     _dulieu.closedb();

}

void nhanVien::on__radsua_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageSuaMon);
    ui->_linesMa->clear();
    ui->_linesSl->clear();
}

void nhanVien::on__radxoa_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageXoaMon);
    ui->_linexMa->clear();
}

void nhanVien::on__treeWidgetInfo_clicked(const QModelIndex &index) // SET ACTIVE
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QString val = ui->_treeWidgetInfo->model()->data(index).toString();
    QSqlQuery qry(_dulieu.mydb);
     qry.prepare("SELECT ID FROM MENU WHERE NAME = '" + val +"'");
     if(qry.exec())
          {
              while(qry.next())
              {
                 if(ui->_radsua->isChecked())
                     ui->_linesMa->setText(qry.value(0).toString());
                 if(ui->_radxoa->isChecked())
                     ui->_linexMa->setText(qry.value(0).toString());
              }
     }
     qry.clear();
     _dulieu.closedb();
}

void nhanVien::on_pushButton_6_clicked() // SUA
{
    if(ui->_linesMa->text() == "")
         QMessageBox::critical(this,tr("Error:"),"Chưa Chọn Món");
    else if(ui->_linesSl->text() == "")
        QMessageBox::critical(this,tr("Error:"),"Chưa Có Số Lượng Món");
    else {
        QModelIndex index = ui->_listViewKV->currentIndex();
        QString itemText = index.data(Qt::DisplayRole).toString();
        itemText += ui->_comboBoxBAN->currentText();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("SELECT * FROM " + itemText);
        QString aOrder;
        QString aSoluong;
        if(qry.exec())
        {

            while(qry.next())
            {
                aOrder = qry.value(0).toString();
                aSoluong = qry.value(1).toString();
            }
            QStringList lOrder;
            QStringList lSoluong;
            lOrder = aOrder.split(' ');
            lSoluong = aSoluong.split(' ');
            QString sid = ui->_linesMa->text();
            QString ssl = ui->_linesSl->text();
            int pos = lOrder.indexOf(QRegExp("*" + sid + "*",Qt::CaseInsensitive, QRegExp::Wildcard),0); // RETUN -1 NEU K TIM RA;
                qDebug() << pos;
            lSoluong[pos] = ssl;
            aSoluong = "";
            int k = lOrder.length();
             qDebug() << k;
            for(int i = 0; i < k; i++)
                aSoluong +=lSoluong[i] + " ";
            qDebug() << aSoluong;
        }
        qry.prepare("UPDATE " + itemText + " SET  aSoluong = '" + aSoluong + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Edit:"),"Edited");
        qry.clear();
        _dulieu.closedb();
    }


}

void nhanVien::on_pushButton_7_clicked()
{
    if(ui->_linexMa->text() == "")
        QMessageBox::critical(this,tr("Error:"),"Chưa Chọn Món");
    else
    {
        QString xid = ui->_linexMa->text();
        QModelIndex index = ui->_listViewKV->currentIndex();
        QString itemText = index.data(Qt::DisplayRole).toString();
        itemText += ui->_comboBoxBAN->currentText();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("SELECT * FROM " + itemText);
        QString aOrder;
        QString aSoluong;
        if(qry.exec())
        {

            while(qry.next())
            {
                aOrder = qry.value(0).toString();
                aSoluong = qry.value(1).toString();
            }
            QStringList lOrder;
            QStringList lSoluong;
            lOrder = aOrder.split(' '); aOrder = "";
            lSoluong = aSoluong.split(' '); aSoluong = "";
            int pos = lOrder.indexOf(QRegExp("*" + xid + "*",Qt::CaseInsensitive, QRegExp::Wildcard),0); // RETUN -1 NEU KO TIM RA;
            int k = lOrder.length();
            for(int i = pos; i < k-1; i++)
            {
                lSoluong[i] = lSoluong[i+1];
                lOrder[i] = lOrder[i+1];
            }
            k--;
            for(int i = 0 ; i < k; i++)
            {
                aOrder += lOrder[i] + " ";
                aSoluong += lSoluong[i] + " ";
            }
        }
        qry.prepare("UPDATE " + itemText + " SET aOrder = '" + aOrder + "', aSoluong = '" + aSoluong + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Delete:"),"Deleted");
        qry.clear();
        _dulieu.closedb();
    }
}

void nhanVien::on_pushButton_5_clicked()
{
    if(ui->_lineTt->text() != "0")
    {

       duLieu _dulieu;
       _dulieu.connectdb();
       QSqlQuery qry(_dulieu.mydb);
       QModelIndex index = ui->_listViewKV->currentIndex();
       QString itemText = index.data(Qt::DisplayRole).toString();
       itemText += ui->_comboBoxBAN->currentText();
       // LUU DU LIEU TU BANG
       qry.prepare("SELECT * FROM " + itemText);
       QString aOrder;
       QString aSoluong;
       if(qry.exec())
       {

           while(qry.next())
           {
               aOrder = qry.value(0).toString();
               aSoluong = qry.value(1).toString();
           }
       }
       QStringList lOrder;
       QStringList lSoluong;

       lOrder = aOrder.split(' ');  // MA MON AN
       lSoluong = aSoluong.split(' '); // SO LUONG MON AN
       int leng = lOrder.length();
       // LUU VAO TABLE BAO CAO
       if(qry.prepare("SELECT * FROM BAOCAO") == false)
       { // TAO BAN BAO CAO
          qry.prepare("CREATE TABLE BAOCAO(ID TEXT PRIMARY KEY NOT NULL,NAME TEXT NOT NULL,DONGIA INTEGER NOT NULL,SOLUONG INTEGER NOT NULL,TONGTIEN INTEGER NOT NULL )");
          if(qry.exec())
          {
            for(int i = 0; i < leng; i++)
            {
                QString name,dongia;
                qry.prepare("SELECT NAME,DONGIA FROM MENU WHERE ID = '" + lOrder[i] + "'");
                if(qry.exec()) // LAY TEN MON VA DON GIA
                {
                    while(qry.next())
                    {
                        name = qry.value(0).toString();
                        dongia = qry.value(1).toString();
                    }
                }

                QString tongtien = QString::number(lSoluong[i].toLong()*dongia.toLong());
                qry.prepare("INSERT INTO BAOCAO(ID,NAME,DONGIA,SOLUONG,TONGTIEN) VALUES ('" + lOrder[i] + "','" + name + "'," + dongia + "," + lSoluong[i] + ","+ tongtien +")");
                qry.exec();
            }
          }
       } else
         {
            qry.exec();

            for(int i = 0; i < leng ; i++)
            {
                int flag = 0;
                qry.prepare("SELECT ID FROM BAOCAO");
                if(qry.exec())
                {
                    while(qry.next())
                        if(lOrder[i] == qry.value(0).toString())
                            flag = 1;
                }
                if(flag == 1)
                {
                    qry.prepare("SELECT DONGIA,SOLUONG,TONGTIEN FROM BAOCAO WHERE ID = '" + lOrder[i] + "'");
                    qry.exec();
                    QString soluong,tongtien,dongia;
                    while(qry.next())
                    {
                        dongia = qry.value(0).toString();
                        soluong = qry.value(1).toString();
                        tongtien = qry.value(2).toString();
                    }
                    soluong = QString::number(soluong.toInt() + lSoluong[i].toInt());
                    tongtien = QString::number(tongtien.toLong() + lSoluong[i].toLong()*dongia.toLong());
                    qry.prepare("UPDATE BAOCAO SET SOLUONG = " + soluong + " ,TONGTIEN = " +tongtien + " WHERE ID = '" + lOrder[i] + "'");
                    qry.exec();
                } else
                {
                        QString name,dongia;
                        qry.prepare("SELECT NAME,DONGIA FROM MENU WHERE ID = '" + lOrder[i] + "'");
                        if(qry.exec()) // LAY TEN MON VA DON GIA
                        {
                            while(qry.next())
                            {
                                name = qry.value(0).toString();
                                dongia = qry.value(1).toString();
                            }
                        }
                        QString tongtien = QString::number(lSoluong[i].toLong()*dongia.toLong());
                        qry.prepare("INSERT INTO BAOCAO(ID,NAME,DONGIA,SOLUONG,TONGTIEN) VALUES ('" + lOrder[i] + "','" + name + "'," + dongia + "," + lSoluong[i] + ","+ tongtien +")");
                        qry.exec();
                }
            }


         }
       // TONG CONG
       qry.prepare("SELECT ID FROM BAOCAO WHERE ID = 'TONGCONG'");
       if(qry.exec())
       {
           while(qry.next())
               if(qry.value(0).toString() == "TONGCONG")
                   qry.exec("DELETE FROM BAOCAO WHERE ID = 'TONGCONG'");
           qry.clear();
       }

       qry.prepare("SELECT SUM(TONGTIEN) FROM BAOCAO");
       QString tongcong;
       if(qry.exec())
       {
           while(qry.next())
               tongcong = qry.value(0).toString();
       }
       qry.exec("INSERT INTO BAOCAO(ID,NAME,DONGIA,SOLUONG,TONGTIEN) VALUES ('TONGCONG','','',''," + tongcong + ")"); // CHEM THEM VAO COT;



       qry.prepare("DROP TABLE " + itemText);
       if(qry.exec())
       {
            QMessageBox::information(this,tr("ThanhToan: "),"Tổng Số Tiền Cần Thanh Toán Là: "+ ui->_lineTt->text()+" VND");
       }
       else
           qDebug() << qry.lastError().text();
       qry.clear();
       _dulieu.closedb();



    }
}
