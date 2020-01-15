#include "login.h"
#include "ui_login.h"
#include <QPixmap>
Login::Login(QWidget *parent) :   QMainWindow(parent), ui(new Ui::Login)
{
    ui->setupUi(this);
     setWindowTitle("Welcome");

    ui->stackedWidget->insertWidget(1,&_quanly); //
    ui->stackedWidget->insertWidget(2,&_nhanvien);
    connect(&_quanly,SIGNAL(homeClicked()),this,SLOT(moveHome()));
    connect(&_nhanvien,SIGNAL(homeClicked()),this,SLOT(moveHome()));
    connect(this,SIGNAL(connListViewKV()),&_nhanvien,SLOT(getdatabaseListKV())); // NOI HAI TIN HIEU GIUA LOGIN VA HAM GETDATABASELISTKV BEN NHANVIEN
    QPixmap pix(":/resources/img/coffee-512.png");
    int w = ui->label_icon->width();
    int h = ui->label_icon->height();
    ui->label_icon->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString password, username;
    password = ui->edit_password->text();
    username = ui->edit_username->text();
    duLieu _dulieu;
    _dulieu.connectdb(); // database;
    QSqlQuery qry(_dulieu.mydb); // tao phien
    // MANAGE
    qry.prepare("SELECT * FROM MANAGE WHERE ID = '"+ username +"' AND DATE = '"+ password +"'");
    int count = 0;
    QString Info;
    if(qry.exec()) // dat dadabase
    {
        while(qry.next())
        {
            Info = " --- "+ qry.value(0).toString() + " --- " + qry.value(1).toString();
            count++;  
        }
        qry.clear();
    }
     // thoat khoi database;
    if(count == 1)
    {
        _dulieu.closedb();
        setWindowTitle(Info);
        ui->edit_password->setText("");
        ui->edit_username->setText("");
        ui->stackedWidget->setCurrentIndex(1); // CHUYEN SANG GIAO DIEN QUANLY
    }
    else
    {
        qry.prepare("SELECT * FROM EMPLOYEES WHERE ID = '" + username + "' AND DATE = '" + password + "'");
        if(qry.exec()) // dat dadabase
        {
            while(qry.next())
            {
                Info = " --- "+ qry.value(0).toString() + " --- " + qry.value(1).toString();
                count++;
            }
            qry.clear();
        }
        if(count == 1)
        {
            _dulieu.closedb();
            setWindowTitle(Info);
            emit connListViewKV();
            ui->edit_password->setText("");
            ui->edit_username->setText("");
            ui->stackedWidget->setCurrentIndex(2); // CHUYEN SANG GIAO DIEN NHANVIEN
        } else
            QMessageBox::critical(this,tr("THE TILE"),tr("Username or password is not correct"));
    }



}

void Login::moveHome()
{
    ui->stackedWidget->setCurrentIndex(0); // LOGIN
    setWindowTitle("Welcome");
}
