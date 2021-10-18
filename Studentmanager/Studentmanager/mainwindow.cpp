#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dialog.h"
#include"dialog2.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionaddstu_triggered()
{
    Dialog a;
    //a.show();    //使用show（）需要把a添加为私有成员而不是在该函数内声明Dialog a，这样函数结束不会销毁a，不然界面只会一闪而过（执行完show离开函数自动销毁）
    a.exec();
    //也可以直接使用a.exec（）
    //使用exec将强制锁定当前界面（置顶）
}

void MainWindow::on_actionquerystu_triggered()
{
    Dialog2 a;
    if(a.ReadFile()==0)
        a.close();
    a.exec();
}
