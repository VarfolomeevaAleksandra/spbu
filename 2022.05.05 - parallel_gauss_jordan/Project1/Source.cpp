#include<iostream>
#include<iomanip>
#include<omp.h>
#include<algorithm>

using namespace std;

void divide(double** matrix, int x, double a, int m, int n)
{
	for (int i = 0; i < n; ++i)
	{
		matrix[x][i] = matrix[x][i] / a;
	}
}

void subtract(double** matrix, int x1, int x2, double a, int m, int n)
{
	for (int i = 0; i < n; ++i)
	{
		matrix[x2][i] = matrix[x2][i] - (a * matrix[x1][i]);
	}
}

void swap(double** matrix, int x1, int x2, int n)
{
	double a = 0;
	for (int i = 0; i < n; ++i)
	{
		a = matrix[x1][i];
		matrix[x1][i] = matrix[x2][i];
		matrix[x2][i] = a;
	}
}

void transform_parl(double **matrix, int m, int n)
{
	int a = 0;
	double x = 0;
	for (int j = 0; j < m; ++j)
	{
		x = matrix[j][j];
		for (int i = j; i < m; ++i)
		{
			if (x < matrix[i][j])
			{
				x = matrix[i][j];
				a = i;
			}
		}
		if (x != matrix[j][j]) swap(matrix, j, a, n);
		divide(matrix, j, x, m, n);
#pragma omp parallel for schedule(static, 5)
		for (int k = 0; k < m; ++k)
		{
			//cout << "number of thread = " << omp_get_thread_num() << endl;
			if (k != j) subtract(matrix, j, k, matrix[k][j], m, n);
		}
	}
	
}

void transform_posl(double** matrix, int m, int n)
{
	int a = 0;
	double x = 0;
	for (int j = 0; j < m; ++j)
	{
		x = matrix[j][j];
		for (int i = j; i < m; ++i)
		{
			if (x < matrix[i][j])
			{
				x = matrix[i][j];
				a = i;
			}
		}
		if (x != matrix[j][j]) swap(matrix, j, a, n);
		divide(matrix, j, x, m, n);
		for (int k = 0; k < m; ++k)
		{
			//cout << "number of thread = " << omp_get_thread_num() << endl;
			if (k != j) subtract(matrix, j, k, matrix[k][j], m, n);
		}
	}

}

void system_solution_parl(double **matrix, int n, int m)
{
	transform_parl(matrix, m, n);
	for (int i = 0; i < m; ++i)
	{
		cout << matrix[i][n - 1] << " " << endl;
	}
}

void system_solution_posl(double** matrix, int n, int m)
{
	transform_posl(matrix, m, n);
	for (int i = 0; i < m; ++i)
	{
		cout << matrix[i][n - 1] << " " << endl;
	}
}

int main()
{
	int m = 0;
	cin >> m;
	int n = 0;
	cin >> n;
	int c = 0;
	double** matrix1 = new double* [m];
	double** matrix2 = new double* [m];
	for (int i = 0; i < m; ++i)
	{
		matrix1[i] = new double[n];
		matrix2[i] = new double[n];
	}
	
	//int x1 = 0;
	//cin >> x1;
	//int x2 = 0;
	//cin >> x2;
	//int a = 0;
	//cin >> a;
	//divide(matrix, x, a, m, n);
	//subtract(matrix, x1, x2, a, m, n);
	//transform(matrix, m, n);
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			//cin >> c;
			matrix1[i][j] = rand() % 10;
			cout << matrix1[i][j] << " ";
			matrix2[i][j] = matrix1[i][j];
		}
		cout << endl;
	}
	cout << endl;
	double t = omp_get_wtime();

	//חהוסü ןמקולף-עמ ןנט גûחמגו system_solution_parl גסו נאבמעאוע
	//א ןנט גûחמגו transform_parl ןנמדנאללא מעגוע םו גûהאוע

	/*system_solution_parl(matrix1, n, m);
	cout << "Time parl: " << omp_get_wtime() - t << endl;*/

	t = omp_get_wtime();
	transform_parl(matrix1, n, m);
	cout << "Time parl: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
	system_solution_posl(matrix2, n, m);
	cout << "Time posl: " << omp_get_wtime() - t << endl;
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << matrix1[i][j] << " ";
		}
		cout << endl;
	}
}