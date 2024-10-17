
#include <QApplication>
#include "UI/Login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*    Main main;
    main.show();*/
    Login login;
    login.show();
    //qDebug() << "准备录卡";
    return a.exec();
}
