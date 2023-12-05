


#include </home/jukh/PycharmProjects/atasd/include.h>
/*0.96489651
    0.02108845
    1.96323957
    1.03851088*/    

double determinant(float **x, int m)
{
    if(m == 2)
    {
        return (x[0][0] * x[1][1] - x[0][1] * x[1][0]);
    }
    else if (m == 1)
    {
        return x[0][0];
    }
    else if (m >= 3)
    {
        //створюємо і заповнюємо масив
        float **tmp = new float *[m-1];
        for(int i=0; i<m-1; i++)
        {
            tmp[i] = new float[m-1];
        }
        double det = 0;
        int a,b;

        for(int j=0; j<m; j++)
        {
            a=0;
            for(int k=1;k<m;k++)
            {
                b=0;
                for(int s=0; s<m; s++)
                {
                    if(s!=j)
                    {
                        tmp[a][b] = x[k][s];
                        b++;
                    }

                }
                a++;
            }
            det += pow(-1, j+1+1)*x[0][j]*determinant(tmp, m-1);
            
        }
        return det;

    }
    else
    {
        return 0;
    }
}


void matrix_method(float inv_matrix[][4], float B_mat[][1])
{
    
 

    float **X_matrix;
    X_matrix = new float* [4];
    
    for (int i = 0; i < 4; i++)
    {
        X_matrix[i] = new float[1];
        for (int j = 0; j < 1; j++)
        {
        X_matrix[i][j] = 0;
        for (int k = 0; k < 4; k++)
            X_matrix[i][j] += inv_matrix[i][k] * B_mat[k][j];
        }
    }

    cout << "\n\n\n**************** Матричний метод ****************" << endl;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<1; j++)
        {
            cout << "X" << i+1 << " = " << round(1000*X_matrix[i][j])/1000 << endl;
        }
    }
}

void gauss_method()
{
    float A[4][5] = {
        {  1   , 0.47  , -0.11 , 0.55, 1.33},
        {0.42  ,  1    , 0.35  , 0.17, 1.29},
        {-0.25 , 0.67  ,  1    , 0.36, 2.11},
        {0.54  , -0.32 , -0.74 ,  1  , 0.1}
    };
   

    int n = 4; 




    for(int k = 0 ; k < n-1 ; k++) // прямий хід
    {
        if(A[k][k] != 0)
        {
            for(int j = k+1 ; j< n+1 ; j++)
            {
                A[k][j] = A[k][j] / A[k][k]; // формула 1
            }

            for(int i = k+1; i<n; i++) //i - рядок
            {
                for(int j = k+1; j<n+1; j++) // j - стовбчик
                {
                    A[i][j] = A[i][j] - A[i][k]*A[k][j]; // формула 2
                }
            }
        }
        else 
        {
            cout << "A" << "[" << k << "]" << "[" << k << "]" << "== 0" << endl;
            return;
        }
    }
    
    A[3][4] = A[3][4] / A[3][3]; // обернений хід

    
    for(int k=2; k>=0; k--) // обернений хід
    {
        for(int j = k+1 ; j < n+1 ; j++)
        {
            A[k][4] = A[k][4] - A[k][j]*A[j][4];
        }
    }


    cout << "***************** Метод Гаусса *****************" << endl;
    for(int i=0; i<4; i++)
    {
        cout << "X" << i+1 << " = " << round(1000*A[i][4])/1000 << endl;
    }
}

void kramer_method(float **A, float B_mat[][1], int m)
{
    float det = determinant(A, m);
    if(det != 0)
    {
        float **coeff_matrix = new float *[4];
        for(int i=0; i<4; i++)
        {
            coeff_matrix[i] = new float[4];
            memcpy(coeff_matrix[i], A[i], m*sizeof(float));
        }

        float X[4];
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<m; j++)
            {
                coeff_matrix[j][i] = B_mat[j][0];
            }

            X[i] = determinant(coeff_matrix, 4)/det;

            for(int k=0; k<m; k++)
            {
                coeff_matrix[k][i] = A[k][i];
            }
            
        }


        cout << "************** Метод Крамера ************" << endl;
        for(int i=0; i<4; i++)
        {
             cout << "X" << i+1 << " = " << round(1000*X[i])/1000 << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    float **coeff_matrix {new float *[4] {new float[4] {1, 0.47, -0.11, 0.55}, 
    new float[4]{0.42, 1, 0.35, 0.17},
    new float[4]{-0.25 , 0.67  ,  1    , 0.36},
    new float[4]{0.54  , -0.32 , -0.74 ,  1  }
    }};

    float B_matrix[4] = {1.33, 1.29, 2.11, 0.1};

    float inverse_matrix[4][4] = {
        { 1.976017,   -1.20178828, -0.01189686, -0.87822247},
        {-1.28847304,  2.10047582, -0.48699455,  0.52689732},
        { 1.49230179, -1.7240748,   1.08741406, -0.91914233},
        {-0.37505723,  0.04530258,  0.65527245,  0.96268196}
    };

    
    matrix_method(inverse_matrix, B_matrix);

    gauss_method();

    kramer_method(coeff_matrix, B_matrix, 4);

    return 0;
}
