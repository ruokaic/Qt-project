#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<handdd.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sc=new MyScene;
    ui->GV_scene->setScene(sc);   //第三步：调用graphicsview容器，设置场景
    connect(ui->BT_Start,SIGNAL(clicked(bool)),sc,SLOT(startGame()));   //开始游戏按钮不能用“转到槽”，信号接收必须是myscene类型，因为游戏状态与timer绑定，而timer又和myscene绑定以便场景随机切换图片，最后，槽函数须为public
    connect(ui->BT_Stop,SIGNAL(clicked(bool)),sc,SLOT(stopGame()));
    connect(ui->BT_Pause,SIGNAL(clicked(bool)),sc,SLOT(pauseGame()));
    score=0;
    handdd*hand=handdd::getInstance();
    connect(hand,SIGNAL(beatMouse()),this,SLOT(UpdateScore()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    sc->setTimer(false);
    int red=QMessageBox::question(this,"Quit","quit the game?","Yes","Cancel");
    if(red==1)
    {
        event->ignore();
        sc->setTimer(true);
    }
}
void MainWindow::UpdateScore()
{
    score+=10;
    ui->lcdnumber->display(score);
}
