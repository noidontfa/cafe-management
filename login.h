#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "QMessageBox"
#include "dulieu.h"
#include "quanly.h"
#include "nhanvien.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();
    void moveHome();

private:
    Ui::Login *ui;
    quanLy _quanly;
    nhanVien _nhanvien;
signals:
    void connListViewKV();

};

#endif // LOGIN_H
