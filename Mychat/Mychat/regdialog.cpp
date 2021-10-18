#include "regdialog.h"
#include "ui_regdialog.h"
#include<QPainter>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QDebug>
regDialog::regDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(u8"用户注册");
}

regDialog::~regDialog()
{
    delete ui;
}

void regDialog::paintEvent(QPaintEvent *event)
{
//    QPainter p(this);
//    p.drawPixmap(rect(),QPixmap("://a.png"));
}

void regDialog::on_btn_ok_clicked()
{
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    QString check = ui->lineEdit_check->text();
    QMessageBox mes;
    if(ReadFile())
    {
        for(int i=0;i<readfile.length();i++)
        {
            QStringList account_file = readfile.at(i).split(" ");
            if(account == account_file.at(0))
            {
                mes.critical(this,"Error",u8"用户已存在！",u8"返回");
                return;
            }
        }
        if(account.length()==0||password.length()<6||check.length()==0)
        {
            QMessageBox mes;
            if(password.length()<6)
                mes.critical(this,"Error",u8"密码长度少于六位！",u8"返回");
            else
                mes.critical(this,"Error",u8"信息不完整！",u8"返回");
        }
        else if(password!=check)
        {
            mes.critical(this,"Error",u8"两次密码输入不一致！",u8"返回");
        }
        else
        {
            QString str = account + " " + password;
            WriteFile(str);
            mes.information(this,"Tip",u8"注册成功！",u8"返回");
            ClearUserInterface();
        }

    }


}
void regDialog::ClearUserInterface()
{
    ui->lineEdit_account->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_check->clear();
    ui->lineEdit_account->setFocus();
}

bool regDialog::ReadFile()
{
    QFile file("data.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,"Error","can not open the file!");
        return false;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();    //每行包含用户名和密码，用户名和密码间用空格隔开
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

void regDialog::WriteFile(QString &str)
{
    QFile file("data.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox mes;
        mes.critical(this,"Error",u8"无法打开或创建文件",u8"确定");
    }
    QTextStream out(&file);
    out << str << endl;
    file.close();
}

void regDialog::on_btn_no_clicked()
{
    this->close();
}

