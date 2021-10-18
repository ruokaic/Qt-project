#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer=new QTimer;
    ui->setupUi(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeflash()));
    ui->BT_pause->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::timeflash()
{
    int t=basetime.msecsTo(QTime::currentTime());
    QTime displaytime(0,0,0,0);
    displaytime=displaytime.addMSecs(t);
    showtime=displaytime.toString("hh:mm:ss:zzz");
    ui->lcdNumber->display(showtime);
    checktime=displaytime;
}
void MainWindow::on_BT_start_clicked()
{
    if(ui->BT_start->text()=="Start")
    {
        basetime=QTime::currentTime();
        timer->start(1);
        ui->BT_start->setText("Stop");
        ui->BT_stop->setEnabled(false);
        ui->BT_pause->setEnabled(true);
    }
    else {
        timer->stop();
        ui->BT_start->setText("Start");
        ui->BT_stop->setEnabled(true);
        ui->BT_pause->setEnabled(false);
    }
}

void MainWindow::on_BT_stop_clicked()      //对应按钮(reset)
{
    showtime="00:00:00:000";
    checktime.setHMS(0,0,0,0);
    ui->lcdNumber->display("00:00:00:000");
    ui->textBrowser->clear();
    ui->BT_start->setText("Start");
    ui->BT_pause->setText("Pause");
    ui->BT_pause->setEnabled(true);
    ui->BT_pause->setEnabled(false);
}

void MainWindow::on_BT_pause_clicked()
{
    if(ui->BT_pause->text()=="Resume")
    {
        QTime zero(0,0,0,0);
        int t=zero.msecsTo(checktime);
        basetime=QTime::currentTime().addMSecs(-t);
        timer->start();
        ui->BT_pause->setText("Pause");
        ui->BT_stop->setEnabled(false);
    }
    else {
        timer->stop();
        ui->BT_pause->setText("Resume");
        ui->BT_stop->setEnabled(true);
    }


}

void MainWindow::on_BT_log_clicked()
{
    ui->textBrowser->append(showtime);
}
