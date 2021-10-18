#include "logindialog.h"
#include <QApplication>
#include"mainwindow.h"
#include "globalhelper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logindialog *w = new logindialog;
    w->show();
    return a.exec();
}
