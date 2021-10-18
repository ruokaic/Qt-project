#include <QMouseEvent>
#include "title.h"
#include "ui_title.h"
#include "globalhelper.h"

#pragma execution_character_set("utf-8")

Title::Title(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Title)
{
    ui->setupUi(this);

    //setStyleSheet(GlobalHelper::GetQssStr("://title.css"));

    GlobalHelper::SetIcon(ui->CloseBtn, 9, QChar(0xf00d));

    ui->CloseBtn->setToolTip("关闭");

}

Title::~Title()
{
    delete ui;
}



void Title::on_CloseBtn_clicked()
{
    emit close();
}
