#include "handler.h"

handler::handler()
{

}
handler* handler::hand=new handler;
void handler::addScore()
{
    emit beatMouse();
}
