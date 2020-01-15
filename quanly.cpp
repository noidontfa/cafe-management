#include "quanly.h"
#include "ui_quanly.h"

quanLy::quanLy(QWidget *parent) : QDialog(parent),ui(new Ui::quanLy)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}

quanLy::~quanLy()
{
    delete ui;
}

void quanLy::setdefaut_radio(QRadioButton *Qrad)
{
    if(Qrad->isChecked())
    {
        Qrad->setAutoExclusive(false);
        Qrad->setChecked(false);
        Qrad->setAutoExclusive(true);
    }
}


void quanLy::on_pushBack_clicked()
{
    emit homeClicked();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentWidget(ui->index_2);
    ui->stackedWidget_3->hide();


}

void quanLy::on_pushNV_clicked()
{
    duLieu _dulieu;
     _dulieu.connectdb();
    ui->stackedWidget->setCurrentWidget(ui->pageNhanVien);
    ui->stackedWidget_3->hide();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT * FROM EMPLOYEES");
    qry.exec();
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery(qry);
    ui->_tableViewNV->setModel(modal);
    qry.clear();
    _dulieu.closedb();

    setdefaut_radio(ui->_nvradthem);
    setdefaut_radio(ui->_nvradsua);
    setdefaut_radio(ui->_nvradxoa);
    setdefaut_radio(ui->_nvradcc);
    setdefaut_radio(ui->_mradthem);
    setdefaut_radio(ui->_mradsua);
    setdefaut_radio(ui->_mradxoa);
    setdefaut_radio(ui->_kvradsua);
    setdefaut_radio(ui->_kvradthem);
    setdefaut_radio(ui->_kvradxoa);

    ui->stackedWidget_2->setCurrentWidget(ui->index_2);
}

void quanLy::on_pushMENU_clicked()
{
    duLieu _dulieu;
     _dulieu.connectdb();
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
    ui->stackedWidget_3->hide();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT * FROM MENU");
    qry.exec();
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery(qry);
    ui->_tableViewM->setModel(modal);
    qry.clear();
    _dulieu.closedb();

    setdefaut_radio(ui->_mradthem);
    setdefaut_radio(ui->_mradsua);
    setdefaut_radio(ui->_mradxoa);
    setdefaut_radio(ui->_nvradthem);
    setdefaut_radio(ui->_nvradsua);
    setdefaut_radio(ui->_nvradxoa);
    setdefaut_radio(ui->_nvradcc);
    setdefaut_radio(ui->_kvradsua);
    setdefaut_radio(ui->_kvradthem);
    setdefaut_radio(ui->_kvradxoa);

    ui->stackedWidget_2->setCurrentWidget(ui->index_2);

}

void quanLy::on__nvradthem_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageThem);
    ui->_ilaid->setText("MaNV: ");
    ui->_ilaname->setText("TenNV: ");
    ui->_ila3->setText("NamSinh: ");
    ui->_ila4->setText("HeSoLuong: ");
    ui->_ila5->hide();
    ui->_linei5->hide();
    if(ui->_ila4->isHidden()) ui->_ila4->show();
    if(ui->_linei4->isHidden()) ui->_linei4->show();
    ui->_lineiid->setText("");
    ui->_lineiname->setText("");
    ui->_linei3->setText("");
    ui->_linei4->setText("");


}

void quanLy::on_pushButton_clicked() //INSERT
{
    if(ui->_nvradthem->isChecked())
    {   // THEM NHAN VIEN
       QString id = ui->_lineiid->text();
       QString name = ui->_lineiname->text();
       QString date = ui->_linei3->text();
       QString salary = ui->_linei4->text();
       duLieu _dulieu;
       _dulieu.connectdb();
       QSqlQuery qry(_dulieu.mydb);
       qry.prepare("INSERT INTO EMPLOYEES (ID,NAME,DATE,SALARY) VALUES ('" + id + "','" + name + "','" + date + "','" + salary + "')");
       if(qry.exec())
           QMessageBox::information(this,tr("Save:"),tr("Saved"));
       else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
       qry.clear();
       _dulieu.closedb();
    }
    if(ui->_mradthem->isChecked())
    { // THEM MENU
        QString id = ui->_lineiid->text();
        QString name = ui->_lineiname->text();
        QString pride = ui->_linei3->text();
        QString unit = ui->_linei4->text();
        QString type = ui->_linei5->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("INSERT INTO MENU (ID,NAME,DONGIA,DONVI,LOAIMON) VALUES ('" + id + "','" + name + "'," + pride + ",'" + unit + "','" + type + "')");
        if(qry.exec())
            QMessageBox::information(this,tr("Save:"),tr("Saved"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
         _dulieu.closedb();
    }
    if(ui->_kvradthem->isChecked())
    { // THEM KHUVUC
        QString id = ui->_lineiid->text();
        QString name = ui->_lineiname->text();
        QString soluong = ui->_linei3->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("INSERT INTO KHUVUC (ID,NAME,SOLUONG) VALUES ('" + id + "','" + name + "'," +soluong + ")");
        if(qry.exec())
            QMessageBox::information(this,tr("Save:"),tr("Saved"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
         _dulieu.closedb();

    }
}

void quanLy::on__nvradsua_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageSua);
    ui->_lineuid->setText("");
    ui->_lineuname->setText("");
    ui->_lineu3->setText("");
    ui->_lineu4->setText("");
    ui->_lineu5->hide();
    ui->_ula5->hide();
    ui->_ulaid->setText("MaNV: ");
    ui->_ulaname->setText("TenNV: ");
    ui->_ula3->setText("NamSinh: ");
    ui->_ula4->setText("HeSoLuong: ");
    if(ui->_ula4->isHidden()) ui->_ula4->show();
    if(ui->_lineu4->isHidden()) ui->_lineu4->show();



}

void quanLy::on__nvradxoa_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageXoa);
    ui->_dlaid ->setText("MaNV: ");
    ui->_linedxoa->setText("");
}

void quanLy::on__tableViewNV_activated(const QModelIndex &index) // active table employees view database
{
    duLieu _dulieu;
    _dulieu.connectdb();

        QString val = ui->_tableViewNV->model()->data(index).toString();
        QSqlQuery qry(_dulieu.mydb); // tao phien
        qry.prepare("SELECT * FROM EMPLOYEES WHERE ID = '" + val+"'");
        if(qry.exec())
        {
            while(qry.next())
            {
                if(ui->_nvradsua->isChecked())
                {
                    ui->_lineuid->setText(qry.value(0).toString());
                    ui->_lineuname->setText(qry.value(1).toString());
                    ui->_lineu3->setText(qry.value(2).toString());
                    ui->_lineu4->setText(qry.value(3).toString());
                }
                if(ui->_nvradxoa->isChecked())
                {
                    ui->_linedxoa->setText(qry.value(0).toString());
                }
                if(ui->_nvradcc->isChecked())
                {
                    ui->_lineSmanv->setText(qry.value(0).toString());
                }
            }
        } else QMessageBox::critical(this,tr("error::"),qry.lastError().text());

       qry.clear();
    _dulieu.closedb();

}

void quanLy::on_pushButton_3_clicked() // DELETE
{

    if(ui->_nvradxoa->isChecked())
    {   // XOA NHAN VIEN
        QString id = ui->_linedxoa->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("DELETE FROM EMPLOYEES WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Delete:"),tr("Deleted"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
    }
    if(ui->_mradxoa->isChecked())
    { // XOA MENU
        QString id = ui->_linedxoa->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("DELETE FROM MENU WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Delete:"),tr("Deleted"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
    }
    if(ui->_kvradxoa->isChecked())
    {// XOA KHUVUC
        QString id = ui->_linedxoa->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("DELETE FROM KHUVUC WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Delete:"),tr("Deleted"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
    }

}

void quanLy::on_pushButton_2_clicked() // UPDATE/EDIT
{
    if(ui->_nvradsua->isChecked())
    { // SUA NHAN VIEN
        QString id = ui->_lineuid->text();
        QString name = ui->_lineuname->text();
        QString date = ui->_lineu3->text();
        QString salary = ui->_lineu4->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("UPDATE EMPLOYEES SET NAME = '" + name + "', DATE = '" + date + "', SALARY = '" + salary + "' WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Update:"),tr("Updated"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();

    }
    if (ui->_mradsua->isChecked())
    { // SUA MENU
        QString id = ui->_lineuid->text();
        QString name = ui->_lineuname->text();
        QString pride = ui->_lineu3->text();
        QString unit = ui->_lineu4->text();
        QString type = ui->_lineu5->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("UPDATE MENU SET NAME = '" + name + "', DONGIA = " + pride + ", DONVI = '" + unit + "', LOAIMON = '" + type + "' WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Update:"),tr("Updated"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
    }
    if(ui->_kvradsua->isChecked())
    { // SUA KHUVUC
        QString id = ui->_lineuid->text();
        QString name = ui->_lineuname->text();
        QString soluong = ui->_lineu3->text();
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("UPDATE KHUVUC SET NAME = '" + name + "', SOLUONG = " + soluong + " WHERE ID = '" + id + "'");
        if(qry.exec())
            QMessageBox::information(this,tr("Update:"),tr("Updated"));
        else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
    }
}

void quanLy::on__nvradcc_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageChamCong);
    ui->_lineSmanv->setText("");
    ui->_lineSgl->setText("");
}

void quanLy::on_pushButton_4_clicked() // CHAM CONG
{
    QString id = ui->_lineSmanv->text();
    long _rsalary = ui->_lineSgl->text().toLong();
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb); // tao phien
    qry.exec("SELECT SALARY FROM EMPLOYEES WHERE ID = '" + id +"'");
    qry.next();
    QString rsalary = qry.record().value(0).toString();
    _rsalary *= rsalary.toLong();
    qry.clear();
    QString qsalary ;
    qsalary.setNum(_rsalary);   
    qry.prepare("UPDATE EMPLOYEES SET R_SALARY = " + qsalary + " WHERE ID ='" +id+ "'");
    if(qry.exec())
        QMessageBox::information(this,tr("Update:"),tr("Updated"));
    else QMessageBox::critical(this,tr("Error:"),qry.lastError().text());
    qry.clear();
    _dulieu.closedb();

}

void quanLy::on__mradthem_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageThem);

    ui->_ilaid->setText("MaMenu: ");
    ui->_ilaname->setText("TenMenu: ");
    ui->_ila3->setText("DonGia: ");
    ui->_ila4->setText("DonVi: ");
    ui->_ila5->setText("LoaiMon: ");
    if(ui->_ila5->isHidden()) ui->_ila5->show();
    if(ui->_linei5->isHidden()) ui->_linei5->show();
    if(ui->_ila4->isHidden()) ui->_ila4->show();
    if(ui->_linei4->isHidden()) ui->_linei4->show();
    ui->_lineiid->setText("");
    ui->_lineiname->setText("");
    ui->_linei3->setText("");
    ui->_linei4->setText("");
    ui->_linei5->setText("");
}

void quanLy::on__mradsua_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageSua);
    ui->_ulaid->setText("MaMenu: ");
    ui->_ulaname->setText("TenMenu: ");
    ui->_ula3->setText("DonGia: ");
    ui->_ula4->setText("DonVi: ");
    ui->_ula5->setText("LoaiMon: ");
    if(ui->_ula5->isHidden()) ui->_ula5->show();
    if(ui->_lineu5->isHidden()) ui->_lineu5->show();
    if(ui->_ula4->isHidden()) ui->_ula4->show();
    if(ui->_lineu4->isHidden()) ui->_lineu4->show();

    ui->_lineuid->setText("");
    ui->_lineuname->setText("");
    ui->_lineu3->setText("");
    ui->_lineu4->setText("");
    ui->_lineu5->setText("");
}

void quanLy::on__mradxoa_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageXoa);
    ui->_dlaid ->setText("MaMenu: ");
    ui->_linedxoa->setText("");

}

void quanLy::on__tableViewM_activated(const QModelIndex &index) // SET ACTIVE TABLE MENU VIEW DATABASE
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QString val = ui->_tableViewM->model()->data(index).toString();
    QSqlQuery qry(_dulieu.mydb); // tao phien
    qry.prepare("SELECT * FROM MENU WHERE ID = '" + val+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            if(ui->_mradsua->isChecked())
            {
                ui->_lineuid->setText(qry.value(0).toString());
                ui->_lineuname->setText(qry.value(1).toString());
                ui->_lineu3->setText(qry.value(2).toString());
                ui->_lineu4->setText(qry.value(3).toString());
                ui->_lineu5->setText(qry.value(4).toString());
            }
            if(ui->_mradxoa->isChecked())
            {
                ui->_linedxoa->setText(qry.value(0).toString());
            }
        }
    } else QMessageBox::critical(this,tr("error::"),qry.lastError().text());

    qry.clear();
    _dulieu.closedb();
}

void quanLy::on_pushKV_clicked()
{
    duLieu _dulieu;
     _dulieu.connectdb();
    ui->stackedWidget->setCurrentWidget(ui->pageKhuVuc);
    ui->stackedWidget_3->hide();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("SELECT * FROM KHUVUC");
    qry.exec();
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery(qry);
    ui->_tableViewKV->setModel(modal);
    qry.clear();
    _dulieu.closedb();

    setdefaut_radio(ui->_mradthem);
    setdefaut_radio(ui->_mradsua);
    setdefaut_radio(ui->_mradxoa);
    setdefaut_radio(ui->_nvradthem);
    setdefaut_radio(ui->_nvradsua);
    setdefaut_radio(ui->_nvradxoa);
    setdefaut_radio(ui->_nvradcc);
    setdefaut_radio(ui->_kvradsua);
    setdefaut_radio(ui->_kvradthem);
    setdefaut_radio(ui->_kvradxoa);
    ui->stackedWidget_2->setCurrentWidget(ui->index_2);

}

void quanLy::on__kvradthem_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageThem);

    ui->_ilaid->setText("MaKV: ");
    ui->_ilaname->setText("TenKV: ");
    ui->_ila3->setText("SoLuong: ");
    ui->_ila4->hide();
    ui->_ila5->hide();
    ui->_linei5->hide();
    ui->_linei4->hide();
    ui->_lineiid->setText("");
    ui->_lineiname->setText("");
    ui->_linei3->setText("");


}

void quanLy::on__kvradsua_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageSua);
    ui->_lineuid->setText("");
    ui->_lineuname->setText("");
    ui->_lineu3->setText("");
    ui->_lineu4->hide();
    ui->_ula4->hide();
    ui->_lineu5->hide();
    ui->_ula5->hide();
    ui->_ulaid->setText("MaKV: ");
    ui->_ulaname->setText("TenKV: ");
    ui->_ula3->setText("SoLuong: ");

}

void quanLy::on__kvradxoa_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->pageXoa);
    ui->_dlaid ->setText("MaKV: ");
    ui->_linedxoa->setText("");

}

void quanLy::on__tableViewKV_activated(const QModelIndex &index)
{
    duLieu _dulieu;
    _dulieu.connectdb();

        QString val = ui->_tableViewKV->model()->data(index).toString();
        QSqlQuery qry(_dulieu.mydb); // tao phien
        qry.prepare("SELECT * FROM KHUVUC WHERE ID = '" + val+"'");
        if(qry.exec())
        {
            while(qry.next())
            {
                if(ui->_kvradsua->isChecked())
                {
                    ui->_lineuid->setText(qry.value(0).toString());
                    ui->_lineuname->setText(qry.value(1).toString());
                    ui->_lineu3->setText(qry.value(2).toString());
                }
                if(ui->_kvradxoa->isChecked())
                {
                    ui->_linedxoa->setText(qry.value(0).toString());
                }

            }
        } else QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();

}

void quanLy::on_pushBC_clicked()
{
    ui->stackedWidget_3->show();
    ui->stackedWidget->setCurrentWidget(ui->Index);
    ui->stackedWidget_2->setCurrentWidget(ui->index_2);
    ui->stackedWidget_3->setCurrentWidget(ui->pageBC);

    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    QSqlQueryModel *modal = new QSqlQueryModel(ui->_tableViewBC);
    qry.prepare("SELECT * FROM BAOCAO");
    if(qry.exec()){
    modal->setQuery(qry);
    }
    ui->_tableViewBC->setModel(modal);
    qry.clear();
    _dulieu.closedb();


}
void quanLy::on_pushButton_6_clicked()
{
    duLieu _dulieu;
    _dulieu.connectdb();
    QSqlQuery qry(_dulieu.mydb);
    qry.prepare("DROP TABLE BAOCAO");
    if(qry.exec())
        QMessageBox::information(this,tr("Delete:"),tr("Deleted"));
    else  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    qry.clear();
    _dulieu.closedb();


}



// LUU RA FILE EXCEL....
#include <fstream>
#include <iostream>
void quanLy::on_pushButton_5_clicked() // XUAT BAOCAO FILE EXCEL
{

    QDateTime date;
     //qDebug() << date.currentDateTime().toString("MMMM,dd,yyyy");
    QString name = date.currentDateTime().toString("MMMM,dd,yyyy");
    std::ofstream myfile;
    myfile.open("/excelfile/"+ name.toStdString() +".csv",std::ios::out );
    if(myfile.fail()) qDebug() << "cant not open file";
    else {
        myfile << "ID,NAME,DONGIA,SOLUONG,TONGTIEN" << std::endl; // dau , la cot moi. dau ; la dong moi
        duLieu _dulieu;
        _dulieu.connectdb();
        QSqlQuery qry(_dulieu.mydb);
        qry.prepare("SELECT * FROM BAOCAO");
        if(qry.exec())
        {
            while(qry.next())
            {
                std::string strList;
                myfile << qry.value(0).toString().toStdString() << "," << qry.value(1).toString().toStdString();
                if(qry.value(2).toString() == "" && qry.value(3).toString() == "")
                {
                    myfile << "," << qry.value(2).toString().toStdString()
                           << "," <<qry.value(3).toString().toStdString()<< "," << qry.value(4).toString().toLong() << std::endl;
                } else
                    {
                    myfile << "," << qry.value(2).toString().toLong()
                           << "," <<qry.value(3).toString().toInt()<< "," << qry.value(4).toString().toLong() << std::endl;
                    }
            }
            QMessageBox::information(this,tr("Information:"),"Đã Lưu vào Filename: " + name);
        }
            else QMessageBox::critical(this,tr("error::"),qry.lastError().text());
        qry.clear();
        _dulieu.closedb();
        myfile.close();

    }



}


