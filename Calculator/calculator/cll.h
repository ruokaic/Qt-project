#ifndef CLL_H
#define CLL_H


class Cll
{
private:
    int num1;
    int num2;
    char ope;
public:
    Cll();
    void getnum1(int a){num1=a;}
    void getnum2(int a){num2=a;}
    void getope(char a){ope=a;}
    char sentope(){return ope;}
    int calcul();
    };

#endif // CLL_H
