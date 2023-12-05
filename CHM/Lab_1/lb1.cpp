

#include </home/jukh/PycharmProjects/atasd/include.h>

double function1(double a, double b, double c)
{
    return ((a*b)/pow(c, 1/3))*(a+b)*(sin(3*c));
}

double dfA1(double a, double b, double c)
{
    return a*b*((sin(3*c))/pow(c, 1/3)) + ((b*(a+b)*sin(3*c)) / (pow(c, 1/3)));
}

double dfB1(double a, double b, double c)
{
    return a*b*((sin(3*c))/pow(c, 1/3)) + ((a*(a+b)*sin(3*c)) / (pow(c, 1/3)));
}

double dfC1(double a, double b, double c)
{
    return ((3*a*b*(a+b)*cos(3*c)) / (pow(c, 1/3))) - ((a*b*(a+b)*sin(3*c)) / (3*pow(c, 4/3)));
}

void task1()
{
    double a, b, c, ae, be, ce;
    a = 2456;
    ae = 0.0005;

    b = 0.00078;
    be = 0.00003;

    c = 0.008;
    ce = 0.00013;

    double absolute_f = (fabs(dfA1(a, b, c)) * ae) + (fabs(dfB1(a, b, c)) * be) + (fabs(dfC1(a, b, c)) * ce);

    double relative_f = absolute_f / fabs(function1(a, b, c));


    cout << "******************Перша функція******************" << endl;
    cout << "|                                               |" << endl;
    cout << "|     Абсолютна похибка функції: " << absolute_f << "        |" << endl;
    cout << "|     Відносна похибка функції: " << relative_f << "       |" << endl;
    cout << "|                                               |" << endl;
    cout << "*************************************************" << endl;
}


double function2(double a, double b, double c)
{
    return ((a+b) / (a-b)) * asin(c);
}

double dfA2(double a, double b, double c)
{
    return ((asin(c)) / (a - b)) - (((a+b) * asin(c)) / pow((a - b), 2));

}

double dfB2(double a, double b, double c)
{
    return ((asin(c)) / (a - b)) + (((a+b) * asin(c)) / pow((a - b), 2));

}

double dfC2(double a, double b, double c)
{
    return (a+b) / (pow((1 - pow(c, 2)), 1/2) * (a - b));

}

void task2()
{
    double a, b, c, m;
    a=0.02456;
    b=0.007823;
    c=0.8348;
    m = 0.00004;
    double rA, rB, rC, t;

    rA = m/(dfA2(a, b, c) * 3);
    rB = m/(dfB2(a, b, c) * 3);
    rC = m/(dfC2(a, b, c) * 3);
    t = m/(dfA2(a, b, c) + dfB2(a, b, c) + dfC2(a, b, c));


    cout << endl <<"******************Друга функція******************" << endl;
    cout << "|                                                |" << endl;
    cout << "|               "<< "Похибка A: " << rA << "          |" << endl
         << "|               "<< "Похибка B: " << rB << "           |" << endl
         << "|               "<< "Похибка C: " << rC << "           |" << endl;
    cout << "|  "<< "Похибка завдання вихідних даних: " << t <<"  |"<< endl;
    cout << "*************************************************" << endl;
    
    
}



int main(int argc, char const *argv[])
{
    cout << "\n\n\n\n";
    task1();
    task2();
    cout << "\n\n\n\n";

    return 0;
}
