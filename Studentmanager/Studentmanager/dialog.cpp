#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QString>
#include<QDebug>
#include <QList>
#include <QAbstractButton>
#include<iterator>
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

void Dialog::on_BT_yes_clicked()                         //点击确认后触发
{
    QString name=ui->LE_name->text();     //获取姓名               //将输入的信息文本保存为字符串
    QString num=ui->LE_num->text();          //获取学号
    QString sex=ui->sexgroup->checkedButton()->text();    //通过按钮组（互斥）获取性别
    QList<QAbstractButton*>list_ins=ui->insgroup->buttons();  //通过按钮组获取兴趣一栏的按钮信息
    QString ins;
    QList<QAbstractButton*>::iterator pr;

    for(pr=list_ins.begin();pr!=list_ins.end();pr++) {         //将兴趣一栏被选中的合成一个string
        if((*pr)->isChecked())
        {
            ins+=(*pr)->text()+",";
        }
    }
    ins.resize(ins.size()-1);                             //减去末尾的“，”

    QString age=ui->CB_old->currentText();        //获取下拉框选中的年龄
    QString fac=ui->CB_fac->currentText();        //获取下拉框选中的学院
    QString str2="name: "+name+"\n"+"num: "+num+"\n"+"sex: "+sex+"\n"+"age: "+age+"\n"     //用于messagebox显示信息，真正保存的是str
            +"faculty: "+fac+"\n"+"interesting: "+ins;
    QString str=name+"\n"+num+"\n"+sex+"\n"+age+"\n"+fac+"\n"+ins;
    QMessageBox mesbox;                                                              //设置弹窗。输出信息
    if(name.length()==0||num.length()<10||ins.length()==0)
        mesbox.critical(this,"Error","Unfinished information!","try again");       //不能用中文？？
    else {
        int red=mesbox.information(this,"Information Check",str2,"Yes","No");
        if(red==0){
            ClearUserInterface();                  //按确定后，保存信息并还原界面
            WriteFile(str);
        }
    }

}
void Dialog::ClearUserInterface()                         //按确认后，还原初始默认界面
{
    ui->LE_name->clear();
    ui->LE_num->clear();
    ui->CB_old->setCurrentIndex(0);
    ui->CB_fac->setCurrentIndex(0);
    ui->RB_male->setChecked(true);
    QList<QAbstractButton*>list_ins=ui->insgroup->buttons();
    QList<QAbstractButton*>::iterator pr;
    for(pr=list_ins.begin();pr!=list_ins.end();pr++) {
        if((*pr)->isChecked())
        {
            (*pr)->setChecked(false);
        }
    }
    ui->LE_name->setFocus();
}
void Dialog::WriteFile(QString str)
{
    QFile file("out.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox mes;
        mes.critical(this,"Error","Can't create output file!","ok");
        return;
    }

    QTextStream out(&file);
    out<<str<<endl;
    out<<endl;
}
void Dialog::on_BT_no_clicked()
{
    close();
}
