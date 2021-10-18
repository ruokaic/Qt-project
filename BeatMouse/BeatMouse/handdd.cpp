#include "handdd.h"


handdd*handdd::hand=new handdd;
handdd::handdd(QObject *parent) : QObject(parent)
{

}
void handdd::addScore()
{
    emit beatMouse();
}
