//暂时不用QSS载入
#include "globalhelper.h"
#include <QFile>

GlobalHelper::GlobalHelper()
{

}
QString GlobalHelper::GetQssStr(QString strQssPath)
{
    QString strQss;
    QFile FileQss(strQssPath);
    if (FileQss.open(QIODevice::ReadOnly))
    {
        strQss = FileQss.readAll();
        FileQss.close();
    }
    else
    {
        qDebug() << "读取样式表失败" << strQssPath;
    }
    return strQss;
}

void GlobalHelper::SetIcon(QPushButton* btn, int iconSize, QChar icon)
{
    QFont font;
    font.setFamily("FontAwesome");
    font.setPointSize(iconSize);

    btn->setFont(font);
    btn->setText(icon);
}
