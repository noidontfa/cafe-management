#ifndef NHANVIEN_H
#define NHANVIEN_H

#include <QDialog>
#include "dulieu.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QRadioButton>
namespace Ui {
class nhanVien;
}

class nhanVien : public QDialog
{
    Q_OBJECT

public:
    explicit nhanVien(QWidget *parent = nullptr);
    ~nhanVien();
    void setdefaut_radio(QRadioButton *Qrad);


private:
    Ui::nhanVien *ui;


private slots:
    void getdatabaseListKV();
    void on_pushButton_2_clicked();


    void on__listViewKV_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on__treeViewOrder_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on__radtt_clicked();

    void on__radsua_clicked();

    void on__radxoa_clicked();

    void on__treeWidgetInfo_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

signals:
    void homeClicked(); // LOGIN

};

#endif // NHANVIEN_H
