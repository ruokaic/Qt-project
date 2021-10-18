#include "dialog.h"
#include "ui_dialog.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_BT_0_clicked()
{
    if(num!="")
    {
        num+=ui->BT_0->text();
        ui->LB_Screen->setText(num);
    }
}

void Dialog::on_BT_1_clicked()
{
    num+=ui->BT_1->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_2_clicked()
{
    num+=ui->BT_2->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_3_clicked()
{
    num+=ui->BT_3->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_4_clicked()
{
    num+=ui->BT_4->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_5_clicked()
{
    num+=ui->BT_5->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_6_clicked()
{
    num+=ui->BT_6->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_7_clicked()
{
    num+=ui->BT_7->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_8_clicked()
{
    num+=ui->BT_8->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_9_clicked()
{
    num+=ui->BT_9->text();
    ui->LB_Screen->setText(num);
}

void Dialog::on_BT_clear_clicked()
{
    num="";
    ui->LB_Screen->setText("0");
}

void Dialog::on_BT_add_clicked()
{
    cll.getnum1(num.toInt());
    num="";
    cll.getope('+');
}

void Dialog::on_BT_sub_clicked()
{
    cll.getnum1(num.toInt());
    num="";
    cll.getope('-');
}

void Dialog::on_BT_mul_clicked()
{
    cll.getnum1(num.toInt());
    num="";
    cll.getope('*');
}

void Dialog::on_BT_div_clicked()
{
    cll.getnum1(num.toInt());
    num="";
    cll.getope('/');
}


void Dialog::on_BT_eql_clicked()
{
    cll.getnum2(num.toInt());
    ui->LB_Screen->setText(num.setNum(cll.calcul()));
    num="";
}
