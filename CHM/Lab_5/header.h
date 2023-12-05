
#include </home/jukh/PycharmProjects/atasd/include.h>
class IntegralA
{
    public:
        double a = 0.8;
        double b = 1.6;
        unsigned k = 10;
        int n = k;
        double ans;
        
        void left_rect();
        void right_rect();
        void centr_rect();
        void trapeze();
        void sympson();
        void print_res(string method);
        
};

double F(double x)
{
    return ( 1 / sqrt(2 * pow( x, 2 ) + 1) );
}

void IntegralA::print_res(string method)
{
    cout << "При розділенні на " << n << " відрізків" << endl << "Методом " << method << " , результат = " << ans << endl; 
}

void IntegralA::left_rect()
{
    // f(x) = h*f(x0) + h*f(x1) + ... + h*f(xn-1) сума площин кожного прямокутника
    double distance = (b-a)/n;
    ans = 0;
    for(unsigned int i=0; i<=n-1; i++)
    {
        ans += distance * F(a + i * distance); // площина прямокутника ширина = distance, висота = F(x)
    }
}

void IntegralA::right_rect()
{
    double distance = (b-a)/n;
    ans = 0;
    for(int i=1; i<=n ; i++)
    {
        ans += distance * F(a + i * distance);
    }
}

void IntegralA::centr_rect()
{
    // f(x) = h*f(x0) + h*f(x1) + ... + h*f(xn-1) сума площин кожного прямокутника
    double distance = (b-a)/n;
    ans = 0;
    for(unsigned int i=0; i<=n-1; i++)
    {
        ans += distance * F(a + i * distance + distance/2); // площина прямокутника ширина = distance, висота = F(x)
    }
}


void IntegralA::trapeze()
{
    double distance = (b-a)/n;
    ans = F(a) + F(b);
    for(unsigned i = 1; i<=n-1; i++)
    {
        ans += 2 * F(a + i * distance);
    }
    ans *= distance/2;
}

void IntegralA::sympson()
{
    double distance = (b-a)/n;
    ans = F(a) + F(b);
    int k;
    for(unsigned i = 1; i<=n-1; i++)
    {
        k = 2 + 2 * (i % 2 ); // Якщо i парне => k = 2, якщо непарне, то 4
        ans += k * F(a + i * distance);
    }
    ans *= distance / 3;
}
