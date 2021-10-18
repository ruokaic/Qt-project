//暂时不用QSS载入
#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H
#pragma execution_character_set("utf-8")
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <QStringList>

class GlobalHelper
{
public:
    GlobalHelper();
    static QString GetQssStr(QString strQssPath);
    static void SetIcon(QPushButton* btn, int iconSize, QChar icon);    //按钮设置显示图标
};

#endif // GLOBALHELPER_H


