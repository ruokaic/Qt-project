#include "dialog2.h"
#include "ui_dialog2.h"
#include<QDebug>

#include<QMessageBox>
Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    model=new QStandardItemModel;
    setitemform();
}

Dialog2::~Dialog2()
{
    delete model;
    delete ui;
}
bool Dialog2::ReadFile()      //将单个学生信息压缩成一行（1个string），以方便后续搜索时循环拆分查找
{
    QFile file("out.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Error","can not open the file!");
        return false;
    }
    QTextStream in(&file);
    QString sum ="";
    while (!in.atEnd()) {
        QString line = in.readLine();
        sum =sum+line+" ";
        if(line=="")
        {
            sum.resize(sum.size()-2);     //-2，拼接最后一行加的空格还有拼接空行时加的空格，共2个空格
            stu.append(sum);              //将每个学生拼接成一个string，并逐个存入Qlist中（Qlist元素可以用at访问也可以用迭代器）
            sum="";                       //重置
        }

    }
    file.close();
    for(int i=0;i<stu.length();i++)
        qDebug()<<stu.at(i);
    return true;
}

void Dialog2::on_BT_search_clicked()
{
    int method=ui->CB_method->currentIndex();  //获取搜索条件
    QString content=ui->LE_content->text();    //获取关键词
    search(content,method);
}
void Dialog2::search(QString cnt,int met)
{
    int row=0;                                //多个结果时，需要设置搜索结果的行数
    for(int i=0;i<stu.length();i++)
    {
        QList<QString> stu_sp=stu.at(i).split(" ");   //将Qlist单个元素拆分，即将每个学生的信息拆分成一个Qlist(at(0)代表姓名，at(1)代表学号，at(4)代表院系...)
        switch (met) {
        case 1:
            if(stu_sp.at(0)==cnt)
                displayitem(row++,stu_sp);   //发送结果，显示在第几行
            break;
        case 2:
            if(stu_sp.at(1)==cnt)
                displayitem(row++,stu_sp);
            break;
        case 3:
            if(stu_sp.at(4)==cnt)
                displayitem(row++,stu_sp);
            break;
        }
    }
}
void Dialog2::setitemform()
{
    model->setHorizontalHeaderItem(0,new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1,new QStandardItem("Num"));
    model->setHorizontalHeaderItem(2,new QStandardItem("Sex"));
    model->setHorizontalHeaderItem(3,new QStandardItem("Age"));
    model->setHorizontalHeaderItem(4,new QStandardItem("Faculty"));
    model->setHorizontalHeaderItem(5,new QStandardItem("Interesting"));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,150);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,50);
    ui->tableView->setColumnWidth(4,100);
    ui->tableView->setColumnWidth(5,150);
}
void Dialog2::displayitem(int row,QStringList stu)
{
    for(int i=0;i<stu.length();i++)
    {
        model->setItem(row,i,new QStandardItem(stu.at(i)));
    }
}
