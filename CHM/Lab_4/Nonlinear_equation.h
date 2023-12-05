
#include </home/jukh/PycharmProjects/atasd/include.h>
double F(double x)
{
    return (3*pow(x, 4) + 4 * pow(x, 3) - 12 * pow(x, 2) - 5);
}
double DF(double x)
{
    return (12*pow(x, 3) + 12*pow(x, 2) - 24*x);
}
double DF2(double x)
{
    return(36*pow(x, 2) + 24*x - 24);
}

class Nonlinear_equation
{
public:
    
    float X; // відповіді
    unsigned short int counter = 0; //Для красивого відображення відповідей
    double a, b;

    float eps = pow(10, -4); // похибка

    void half_cut(float *interval);
    void hord_method(float *interval);
    void print_answer(string method);
    void newton_method(float *interval);

};

void Nonlinear_equation::newton_method(float *interval)
{
    double X0 = interval[0];

    if(DF(X0) * (DF2(X0)) > 0)
    {
        X0 = interval[1];
    }

    while(abs(F(X0)) > eps)
    {
        X0 -= F(X0)/DF(X0);
    }
    X = X0;
    print_answer("Ньютона");
    counter ++;
}

void Nonlinear_equation::print_answer(string method)
{
    if(counter >= 2) counter = 0;
    if (counter == 0)
        cout << "\n\n********************* Метод " << method << " ************************" << endl ;
    cout << "X" << counter+1 << " = " << X << endl;
}

void Nonlinear_equation::half_cut(float *interval)
{
    a = interval[0];
    b = interval[1];

    while(fabs(b - a) > eps)
    {
        float x = (a + b) / 2;
        if(F(a) * F(x) < 0)
        {
            b = x;
        }
        else
        {
            a = x;
        }
    }
    
    X = (a + b) / 2;
    
    print_answer("половинного поділу");
    counter ++;
    
}

void Nonlinear_equation::hord_method(float *interval) //!!!!!!!!!!!!!!НЕ ПРАЦЮЄ З ФЛОАТ, ТІЛЬКИ ДАБЛ
{
    double a = interval[0];
    double b = interval[1];
    double c = a + abs(F(a) / (F(b) - F(a))) * (b - a);
    while(abs(F(c)) > eps)
    {
        c = a + abs(F(a) / (F(b) - F(a))) * (b - a);
        if(F(a) * F(c) < 0) b = c;
        else a = c;
    }
    X = c;
    print_answer("хорд");
    counter ++;
}
