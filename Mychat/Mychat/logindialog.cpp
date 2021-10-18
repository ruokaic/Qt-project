#include "logindialog.h"
#include "ui_logindialog.h"
#include<QDate>
#include<QDebug>
#include<QMessageBox>
#include<QThread>
#include<QPainter>
#include<QGraphicsDropShadowEffect>
logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    QDate date =QDate::currentDate();
    ui->label_date->setText("MyChat\n" + date.toString("yyyy MM dd"));
    connect(ui->wtitle,&Title::close,this,[=](){
        this->close();
    });

    //去边框，父窗口透明
    setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    //阴影边框
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setColor(Qt::black);
    shadow->setOffset(0);
    ui->widget->setGraphicsEffect(shadow);

    ui->wtitle->setStyleSheet("QWidget#wtitle QPushButton#CloseBtn{background-color:transparent}"
                              "QWidget#wtitle QPushButton#CloseBtn:hover{background-color:#ff6022}");
    WinDrag = false;
}

logindialog::~logindialog()
{
    delete ui;
    delete mainw;
}

bool logindialog::ReadFile()
{
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,"Error",u8"无用户信息，请先注册!");
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if(line!="")
        {
            readfile.append(line);
        }

    }
    file.close();
    for(int i=0;i<readfile.length();i++)
        qDebug()<<readfile.at(i);
    return true;
}

void logindialog::paintEvent(QPaintEvent *event)
{
//    QPainter p(this);
//    p.drawPixmap(rect(),QPixmap("://a.png"));
}

void logindialog::on_btn_login_clicked()
{
    bool exist = false;
    if(ReadFile())
    {
        for(int i=0;i<readfile.length();i++)
        {
            QStringList account=readfile.at(i).split(" ");
            if(ui->lineEdit_account->text() == account.at(0))
            {
                exist = true;
                if(ui->lineEdit_password->text() == account.at(1))
                {
                    mainw = new mainwindow;
                    QThread::sleep(1);
                    mainw2 = new mainwindow;
                    mainw->show();
                    mainw2->show();
                    hide();
                }
                else
                {
                    QMessageBox::warning(0, QObject::tr("warning"), u8"密码错误！请重新输入。");
                    ui->lineEdit_password->clear();
                    ui->lineEdit_password->setFocus();
                    break;
                }
            }
        }
        if(!exist)
        {
            QMessageBox::warning(0, QObject::tr("warning"), u8"用户不存在！请重新输入。");
            ui->lineEdit_account->clear();
            ui->lineEdit_password->clear();
            ui->lineEdit_account->setFocus();
        }
    }
}

void logindialog::on_btn_register_clicked()
{
    regDialog reg;
    reg.exec();
}

void logindialog::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (ui->wtitle->geometry().contains(event->pos()))      //判断是不是在标题栏拖拽
        {
            WinDrag = true;
            QPoint MouseLocate = event->globalPos();            //鼠标相对于屏幕左上角的坐标，即鼠标全局位置
            QPoint WinLocate = this->geometry().topLeft();      //窗口左上角相对于屏幕左上角的坐标，即窗口全局位置
            x = MouseLocate - WinLocate;                        //记录鼠标拖拽窗口时，相对窗口左上角的位置
        }
    }
    QWidget::mousePressEvent(event);

}
void logindialog::mouseMoveEvent(QMouseEvent *event)
{
    if(WinDrag)
    {
        QPoint MouseLocate = event->globalPos();
        this->move(MouseLocate - x);                       //通过移动后的鼠标位置减去x得出窗口全局位置
    }
    QWidget::mouseMoveEvent(event);
}
void logindialog::mouseReleaseEvent(QMouseEvent *event)
{
    WinDrag = false;
    QWidget::mouseReleaseEvent(event);
}
