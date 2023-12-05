




#include </home/jukh/PycharmProjects/atasd/include.h>
#include "header.h"
// Відповідь 0.412975

int main(int argc, char const *argv[])
{
    IntegralA l;
    double eps = 0.01; // eps = 0.000000001
    double s1; // для попередніх значень 

    do{
        l.n = l.n*2;
        s1 = l.ans;
        l.left_rect();
    }while(fabs(s1 - l.ans) > eps);
    l.print_res("лівих прямокутників");


    l.n = l.k;
    l.ans = 100;
    do{
        l.n = l.n*2;
        s1 = l.ans;
        l.right_rect();
    }while(fabs(s1 - l.ans) > eps);
    l.print_res("правих прямокутників");

    l.n = l.k;
    l.ans = 100;
    do{
        l.n = l.n*2;
        s1 = l.ans;
        l.centr_rect();
    }while(fabs(s1 - l.ans) > eps);
    l.print_res("центральних прямокутників");


    l.n = l.k;
    l.ans = 100;
    do{
        l.n = l.n*2;
        s1 = l.ans;
        l.trapeze();
    }while(fabs(s1 - l.ans) > eps);
    l.print_res("трапецій");

    l.n = l.k;
    l.ans = 100;
    do{
        l.n = l.n*2;
        s1 = l.ans;
        l.sympson();
    }while(fabs(s1 - l.ans) > eps);
    l.print_res("Сімпсона");



    return 0;
}
