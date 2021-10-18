#include "cll.h"

Cll::Cll()
{

}
int Cll::calcul()
{
    int result=0;
    switch (ope) {
    case '+':
        result=num1+num2;
        break;
    case'-':
        result=num1-num2;
        break;
    case'*':
        result=num1*num2;
        break;
    case'/':
        if(num2==0)
            result=0;
        else
            result=num1/num2;
        break;
    default:
        break;
    }
    return result;
}
