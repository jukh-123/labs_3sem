


#include </home/jukh/PycharmProjects/atasd/include.h>

class Dimension_Array
{
public:
    
    int n;
    float **arr;
    
    Dimension_Array(){}

    
    Dimension_Array(int n1)
    {
        n = n1;
        set_a();
    }

    void set_n(int n1)
    {
        n = n1;
        set_a();
    }

    void print_matrix()
    {
        cout << "\n\n************МАТРИЦЯ**************" << endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                cout << arr[i][j] << " | ";
                if(j == (n-1))
                {
                    cout << endl;
                }
               
            }
        }
        cout << "*******************************\n" << endl;
    }

private:
    void set_a()
    {
        arr = {new float *[n] {new float[n] {1,0.47,-0.11,0.55}, 
        new float[n]{0.42, 1, 0.35, 0.17},
        new float[n]{-0.25, 0.67, 1, 0.36},
        new float[n]{0.54, -0.32, -0.74, 1}
        }};
    }


    

};

class SLAR:public Dimension_Array
{
public:
    float e = 0.001;
    int n; 
    Dimension_Array A; //матриця коефіцієнтів
    float *B; //вільні члени
    float *X;

    

    SLAR(int n1, float *b);


    void iter_method();

    void check();

    void iter_form();

    void seidel(Dimension_Array A1, float *B1);

    void solution(Dimension_Array A1, float *B1);

    



    ~SLAR()
    {
        delete [] B;
        delete [] X;
    }
};

void SLAR::check()
{
    float summ = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(i != j) 
                {
                    summ += abs(A.arr[i][j]);
                }
            }
            if(abs(A.arr[i][i]) <= summ)
            {
                cout << "Масив не задовільняє умові сходимості." << endl;
                return;
            }

            summ = 0;
        }
        cout << "Масив задовільняє умові сходимості" << endl;
}

SLAR::SLAR(int n1, float *b)
{
    n = n1;
    B = new float [n];
    X = new float [n];
    A.set_n(n);
    for(int i=0; i<n; i++)
    {
        B[i] = b[i];
    }
}

void SLAR::iter_method()
{
    check();
    iter_form();
}

void SLAR::iter_form()
{
    Dimension_Array A1(n);
    float B1[n];
    for (int i = 0; i < n; i++)
    {
        for(int j=0 ;j<n; j++)
        {
            if(i == j)
            {
                A1.arr[i][j] = 0;
            }
            else
            {
                A1.arr[i][j] = -(A.arr[i][j] / A.arr[i][i]);
            }
            B1[i] = B[i]/A.arr[i][i];
        }
    }
    seidel(A1, B1);
    solution(A1, B1);
}

void SLAR::solution(Dimension_Array A1, float *B1)
{
    float X0[n];

    float E[n];
    int counter = 0;
    int ctr = 0;

    for(int i=0; i<n; i++)
    {
        X0[i] = B1[i];
    }

    do
    {
        counter ++;
        ctr = 0;
        for(int i=0; i<n; i++)
        {
            X[i] = 0;
            for(int j=0; j<n; j++)
            {
                X[i] += A1.arr[i][j] * X0[j] ;
            }
            X[i] += B1[i];
            E[i] = fabs(X[i] - X0[i]);
        }
        for(int i=0; i<n; i++)
        {
            if(e > E[i]) 
            {
                ctr++; 
            }
            X0[i] = X[i]; 
        }

    
        
        
        
    } while (ctr < n); // коли всі |x1 - x0| будуть менші за похибку
    cout << "\n\n\n Результат знайдено за " << counter << " ітерацій" << endl;
    cout << "*******************RESULT****************" << endl;
    for(int i=0; i<n; i++)
    {
        cout << round(1000*X[i])/1000 << endl;
    }
}

void SLAR::seidel(Dimension_Array A1, float *B1)
{
    float X0[n];
    float E[n];
    float X1[n];
    


    int counter = 0;
    int ctr = 0;

    for(int i=0; i<n; i++)
    {
        X0[i] = B1[i];
    }

    do
    {
        counter ++;
        ctr = 0;
        for(int i=0; i<n; i++)
        {
            X[i] = 0;
            for(int j=0; j<n; j++)
            {
                X[i] += A1.arr[i][j] * X0[j]; 
            }
            X[i] += B1[i];
            E[i] = fabs(X[i] - X0[i]);
            X0[i] = X[i];
        }

        for(int i=0; i<n; i++)
        {
            if(e > E[i]) 
            {
                ctr++; 
            }
            X0[i] = X[i]; 
        }

        
    } while (ctr < n); // коли всі |x1 - x0| будуть менші за похибку
    cout << "\n\n\n Результат знайдено за " << counter << " ітерацій" << endl;
    cout << "*******************RESULT SEIDEL METHOD****************" << endl;
    for(int i=0; i<n; i++)
    {
        cout << round(1000*X[i])/1000 << endl;
    }
}

int main(int argc, char const *argv[])
{
    float B_matrix[4] = {1.33, 1.29, 2.11, 0.1};
    SLAR S(4, B_matrix);
    
    S.iter_method();

    return 0;
}
