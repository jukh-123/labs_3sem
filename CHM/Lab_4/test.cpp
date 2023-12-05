#include <iostream>
#include<cstdlib>
#include <cmath>
using namespace std;

double F(double x)
{
    return (3*pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2) - 5);
}
double DF(double x)
{
    return (12*pow(x, 3) + 12*pow(x, 2) - 24*x);
}
double D2F(double x)
{
    return(36*pow(x, 2) + 24*x - 24);
}



int main()
{
    float x0[2];
    x0[0] = -2.8;
    x0[1] = 1.5;
    float eps = 0.0001;

    cout << DF(x0[0]) * (D2F(x0[0])) << endl;
    x0[0] = -3;
    
    cout << DF(x0[1]) * (D2F(x0[1])) << endl;
    x0[1] = 2;

    float x = x0[1];
    while(abs(F(x)) > eps)
    {
        x -= F(x)/DF(x);
    }

    cout << x << endl;
    
    return 0;
}