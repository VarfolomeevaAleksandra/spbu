#include<iostream>
#include<omp.h>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int n = 10'000'000;

double f(double x)
{
    return (x * x);
}
double integr(double (*f)(double), double A, double B)
{
    double h = (B - A) / 10;
    //cout << "h = " << h << endl;
    double I;
    double Xn [11] = {0};
    Xn[0] = f(A);
    //cout << "A = " << A << endl;
    //cout << "Xn[0] = " << Xn[0] << endl;
    Xn[10] = f(B);
    //cout << "B = " << B << endl;
    //cout << "Xn[10] = " << Xn[10] << endl;
    for (int i = 1; i < 10; ++i)
    {
        //cout << "f = " << f(A + (h * i)) << endl;
        Xn[i] = f(A + (h * i));
        //cout << Xn[i] << endl;
    }
    I = h * ((B - A) / 2);
    for (int i = 1; i < 10; ++i)
    {
        //cout << "Xn[i] * h = " << Xn[i] * h << endl;
        //cout << "I = " << I << endl;
        I = I + (Xn[i] * h);
        //cout << "I = " << I << endl;
    }
    return I;
}

double integral(double (*f)(double), double A, double B)
{
    double I;
    double I1;
    double I2;
    I = integr(f, A, B);
    //cout << "I = " << I << endl;
    I1 = integr(f, A, ((B - A)/2));
    //cout << "I1 = " << I1 << endl;
    I2 = integr(f, ((B - A)/2), B);
    //cout << "I2 = " << I2 << endl;
    //cout << "I - (I1 + I2) = " << (I - (I1 + I2)) << endl;
    if ((I - (I1 + I2)) < (1e-10)) return I;
#pragma omp task shared(I1)
    I1 = integral(f, A, ((B - A)/2));
#pragma omp task shared (I2)
    I2 = integral(f, ((B - A)/2), B);
#pragma omp taskwait
    return I1 + I2;
}

void qsortRecursive(int *mas, int size)
{
    int i = 0;
    int j = size - 1;

    int mid = mas[size / 2];

    do
        {
        while(mas[i] < mid)
        {
            i++;
        }
        while(mas[j] > mid)
        {
            j--;
        }
        if (i <= j)
        {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);
#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task
            if(j > 0)
            {
                qsortRecursive(mas, j + 1);
            }
#pragma omp task
            if (i < size)
            {
                qsortRecursive(&mas[i], size - i);
            }
        }
    }
}


int main()
{

    double I = 0;
    double A;
    double B;
    cin >> A;
    cin >> B;
#pragma omp parallel
    {
#pragma omp single
        {
            I = integral(f, A, B);
        }
    }
    cout << I << endl;

    /*int mas[20] = {0};
    for (int i = 0; i < 20; ++i)
    {
        mas[i] = rand() % 100;
        cout << mas[i] << " ";
    }
    cout << endl;
    qsortRecursive(mas, 20);

    for (int i = 0; i < 20; ++i)
    {
        cout << mas[i] << " ";
    }*/




    return EXIT_SUCCESS;
}
