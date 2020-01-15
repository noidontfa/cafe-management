#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/img/btw-icon-cafe.png"));

    Login w;
    w.show();


    return a.exec();
}
