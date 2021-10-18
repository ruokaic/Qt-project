#include "myscene.h"   //场景（图片-》图元-》场景-》mainwindow调用QGraphics容器）
#include<QDebug>
MyScene::MyScene(QObject *parent) : QGraphicsScene (parent)   //由Qobject（parent）改为QGraphicsScene (parent)
{
    for(int i=0;i<16;i++)       //第二步：设置好坐标，图元添加到场景，item的类型为QGraphicsPixmapItem，是QGraphicsItem的派生类
    {
        item[i]=new myitem;
        item[i]->setPos(i/4*item[i]->boundingRect().width(),i%4*item[i]->boundingRect().height());
        addItem(item[i]);
    }
    level=1;
    timer=new QTimer;            //第四步，设置每隔一段时间随机出现地鼠
    connect(timer,SIGNAL(timeout()),this,SLOT(showup()));
}
void MyScene::showup()
{
    static int count=1;
    for(int i=0;i<16;i++)
    {
        item[i]->setpic(":/bg/pic/chushi.png");//每次出现地鼠时，先还原初始状态
        item[i]->getmouse(false);
    }
    if(count%10==0&&level<3)
    {
        level++;
        timer->setInterval(1000*1.2);
    }
    for(int i=0;i<level;i++){
        int index=QRandomGenerator::global()->bounded(15);
        item[index]->setpic(":/bg/pic/chuxian.png");
        item[index]->getmouse(true);
        count++;
    }

}
void MyScene::startGame()
{
    timer->start(1000);
    for(int i=0;i<16;i++)
    {
        item[i]->getstart(true);
    }
}
void MyScene::pauseGame()
{
    timer->stop();
    for(int i=0;i<16;i++)
    {
        item[i]->getstart(false);
    }
}
void MyScene::stopGame()
{
    timer->stop();
    for(int i=0;i<16;i++)
    {
        item[i]=new myitem;
        item[i]->setPos(i/4*item[i]->boundingRect().width(),i%4*item[i]->boundingRect().height());
        addItem(item[i]);
        item[i]->getstart(false);
    }
    level=0;
}
void MyScene::setTimer(bool t)
{
    if(t==true)
        timer->start();
    else
        timer->stop();
}
