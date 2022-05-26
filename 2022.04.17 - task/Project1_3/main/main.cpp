#include<iostream>
#include<omp.h>
#include<algorithm>
#include<cstdlib>
#include<math.h>

using namespace std;
const int n = 10'000'000;

double f(double x)
{
    return (x * x);
}
double integr(double (*f)(double), double A, double B)
{
    double I = 0;
	double h = (B - A) / 10;
	for (int i = 0; i < 10; ++i)
	{
		I += h * (f(A + i * h) + f(A + (i + 1) * h)) / 2;
	}
    return I;
}

double integral(double (*f)(double), double A, double B)
{
    double I;
    double I1;
    double I2;
    I = integr(f, A, B);
    I1 = integr(f, A, (A + B)/2);
    I2 = integr(f, ((A + B)/2), B);
    if (fabs(I - (I1 + I2)) < (1e-10)) return I;
#pragma omp task shared(I1)
    I1 = integral(f, A, ((A + B)/2));
#pragma omp task shared (I2)
    I2 = integral(f, ((A + B)/2), B);
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

    int mas[20] = {0};
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
    }

    return EXIT_SUCCESS;
}
