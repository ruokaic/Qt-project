#include "myitem.h"   //图元（图片-》图元-》场景-》QGraphics容器）
#include<QPixmap>
#include<QDebug>
#include<QCursor>
#include<handdd.h>
myitem::myitem()
{
    setPixmap(QPixmap(":/bg/pic/chushi.png")); //第一步设置图元（主要步骤，包含头文件等操作省略）：先把图片转换成图元：不同格式的图片都可使用Qpixmap构造函数转换成像素格式，然后用setpixmap插入图元
    isstart=false;
    mouse=false;
    setCursor(QCursor(QPixmap(":/b/pic/cuizi1.png")));
}
void myitem::setpic(QString pic)
{
    setPixmap(QPixmap(pic));
}
void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(QPixmap(":/b/pic/cuizi2.png")));
    if(isstart)
    {
        handdd*hand=handdd::getInstance();
        if(mouse){
            hand->addScore();
            setpic(":/b/pic/jizhong.png");
            getmouse(false);
        }
    }
}
void myitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(QCursor(QPixmap(":/b/pic/cuizi1.png")));
}
