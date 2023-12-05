#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
class Matr
{
private:
    double eps = 0.001;
    static const int n = 4;
    double masA[n][n] = {
        {0, 0.267442, 0.209302,  0.197674}, 
        {0.105263, 0, 0.0701754, 0.0789474},
        {0.16 , 0.24  ,  0    , -0.35},
        {0.306667  , -0.106667 ,  0.0666667,  0  }
        };

    double masB[n] = {-1.65116, -0.72807, 1.21, 0.866667};

public:

    void Itera()
    {
        double x[n];  
        double x0[n]; //ітерація i-1
        double E[n];     
        double max = 0;
        int counter = 0;

        for (int i = 0; i < n; i++)  // заповнюємо масив x0 значеннями B
            x0[i] = masB[i];          
        do
        {
            counter ++;
            for (int i = 0; i < n; i++)   
            {
                x[i] = 0;                
                for (int j = 0; j < n; j++)
                {
                    x[i] += masA[i][j] * x0[j];     
                }
                x[i] += masB[i];
                E[i] = fabs(x[i] - x0[i]);
            }
            max = 0;
            for (int i = 0; i < n; i++)
            {
                if (max < E[i]) max = E[i];
                x0[i] = x[i];
            }
        } while (max > eps);
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << "=" << x[i] << " " << endl;
    }
};

int main()
{
    Matr c;
    c.Itera();
}