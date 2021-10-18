#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>

class handler:public QObject
{
public:
    static handler* getInstance(){return hand;}
    void addScore();
private:
    handler();
private:
    static handler*hand;
signals:
    void beatMouse();
};

#endif // HANDLER_H
