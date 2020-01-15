#ifndef QUANLY_H
#define QUANLY_H

#include <QDialog>
#include "dulieu.h"
#include <QMessageBox>
#include <QRadioButton>
namespace Ui {
class quanLy;
}

class quanLy : public QDialog
{
    Q_OBJECT

public:
    explicit quanLy(QWidget *parent = nullptr);
    ~quanLy();
    void setdefaut_radio(QRadioButton *Qrad);

private slots:


    void on_pushBack_clicked();

    void on_pushNV_clicked();

    void on_pushMENU_clicked();

    void on__nvradthem_clicked();

    void on_pushButton_clicked();

    void on__nvradsua_clicked();

    void on__nvradxoa_clicked();

    void on__tableViewNV_activated(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on__nvradcc_clicked();

    void on_pushButton_4_clicked();

    void on__mradthem_clicked();

    void on__mradsua_clicked();

    void on__mradxoa_clicked();

    void on__tableViewM_activated(const QModelIndex &index);

    void on_pushKV_clicked();

    void on__kvradthem_clicked();

    void on__kvradsua_clicked();

    void on__kvradxoa_clicked();

    void on__tableViewKV_activated(const QModelIndex &index);

    void on_pushBC_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::quanLy *ui;

signals:
    void homeClicked(); // LOGIN
};

#endif // QUANLY_H
