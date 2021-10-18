#ifndef MYSCENE_H
#define MYSCENE_H
#include <QObject>
#include<QGraphicsScene>
#include"myitem.h"
#include<QTimer>
#include<QRandomGenerator>
#include<QGraphicsSceneMouseEvent>
#include<math.h>

class MyScene : public QGraphicsScene          //原先创建时选择基类是Qobject，然后再改成Qgra，cpp文件也要把obj改了
{
    Q_OBJECT
public:
    explicit MyScene(QObject *parent = nullptr);
    void setTimer(bool);

signals:

public slots:
    void showup();
    void startGame();
    void pauseGame();
    void stopGame();
private:
    myitem*item[16];
    QTimer*timer;
    int level;
};

#endif // MYSCENE_H
