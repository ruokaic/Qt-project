#ifndef MYITEM_H
#define MYITEM_H
#include<QGraphicsPixmapItem>
#include<QString>
class myitem : public QGraphicsPixmapItem
{
private:
    bool mouse;
    bool isstart;
public:
    myitem();
    void setpic(QString);  
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void getmouse(bool a){mouse=a;}
    void getstart(bool b){isstart=b;}

};

#endif // MYITEM_H
