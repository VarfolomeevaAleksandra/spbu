#include<iostream>
#include<omp.h>
#include<algorithm>
#include<vector>

using namespace std;

double* sin1 = new double[100000000];
double* sin2 = new double[100000000];
void sin_1()
{
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 100000000; i != 50000000; --i)
			{
				sin1[i] = sin(3.14 / (2 * i));
			}
		}
#pragma omp section
		{
			for (int i = 50000000; i != 0; --i)
			{
				sin1[i] = sin(3.14 / (2 * i));
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
}

void sin_2()
{
	double t = omp_get_wtime();
	for (int i = 100000000; i != 0; --i)
	{
		sin2[i] = sin(3.14 / (2 * i));
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
}

double pi_1(int n)
{
	double pi = 0;
	double t = omp_get_wtime();
#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (double i = 1; i <= n; i+=2)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}
		}
#pragma omp section
		{
			for (double i = 2; i <= n; i+=2)
			{
				pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
			}
		}
	}
	pi = 4 * pi / n;
	cout << "Time 1: " << omp_get_wtime() - t << endl;
	return pi;
}

double pi_2(int n)
{
	double pi = 0;
	double t = omp_get_wtime();
	for (double i = 1; i <= n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = 4 * pi / n;
	cout << "Time 2: " << omp_get_wtime() - t << endl;
	return pi;
}


bool isPrime(int n)
{
	if (n == 1) return false;
	if (n % 2 == 0 && n != 2)
		return false;
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

void prime_numbers(int n)
{
	double t = omp_get_wtime();
	int sum = 0;
#pragma omp parallel sections reduction(+:sum)
	{
#pragma omp section
		{
			for (int i = 3; i < n; i += 4)
			{
				if (isPrime(i)) sum += 1;
			}
		}
#pragma omp section
		{
			for (int i = 5; i < n; i += 4)
			{
				if (isPrime(i)) sum += 1;
			}
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
	cout << "Sum: " << sum << endl;
	system("pause");
}

struct Point
{
	int x;
	int y;
	
	double dist(Point p1)
	{
		return ((x - p1.x) * (x - p1.x)) + ((y - p1.y) * (y - p1.y));
	}
};

Point p[10000];


double diam(int n)
{
	double maxd = 0;
	double d = 0;
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (maxd < d)
			{
				maxd = d;
			}
		}
	}
	return maxd;
}

double diam_2(int n)
{
	double maxd1 = 0;
	double maxd2 = 0;
	double d1 = 0;
	double d2 = 0;
	double x = n - sqrt(2) * n / 2;
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < x; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d1 = p[i].dist(p[j]);
					if (maxd1 < d1)
					{
						maxd1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = x; i < n - 1; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d2 = p[i].dist(p[j]);
					if (maxd2 < d2)
					{
						maxd2 = d2;
					}
				}
			}
		}
	}
	if (maxd1 > maxd2) return maxd1;
	else return maxd2;
}

double diam_3(int n)
{
	double maxd1 = 0;
	double maxd2 = 0;
	double maxd3 = 0;
	double d1 = 0;
	double d2 = 0;
	double d3 = 0;
	double y = n - n / sqrt(3);
	double x = y - sqrt(2) * y / 2;

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < x; ++i)
			{
				//cout << "i: " << i << ", ";
				for (int j = i + 1; j < n; ++j)
				{
					//cout << "i: " << i << ", j: " << j << endl;
					d1 = p[i].dist(p[j]);
					if (maxd1 < d1)
					{
						maxd1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = x + 1; i < y; ++i)
			{
				//cout << "i: " << i << ", ";
				for (int j = i + 1; j < n; ++j)
				{
					//cout << "i: " << i << ", j: " << j << endl;
					d2 = p[i].dist(p[j]);
					if (maxd2 < d2)
					{
						maxd2 = d2;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = y + 1; i < n - 1; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					//cout << "i: " << i << ", j: " << j << endl;
					d3 = p[i].dist(p[j]);
					if (maxd3 < d3)
					{
						maxd3 = d3;
					}
				}
			}
		}
	}
	if (maxd1 < maxd2) maxd1 = maxd2;
	if (maxd1 > maxd3) return maxd1;
	else return maxd3;
}

double diam_4(int n)
{
	double maxd1 = 0;
	double maxd2 = 0;
	double maxd3 = 0;
	double maxd4 = 0;
	double d1 = 0;
	double d2 = 0;
	double d3 = 0;
	double d4 = 0;
	double y = n - sqrt(2) * n / 2;
	double x = y - sqrt(2) * y / 2;
	double z = 2 * y - sqrt(2) * y / 2;
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < x; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d1 = p[i].dist(p[j]);
					if (maxd1 < d1)
					{
						maxd1 = d1;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = x + 1; i < y; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d2 = p[i].dist(p[j]);
					if (maxd2 < d2)
					{
						maxd2 = d2;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = y + 1; i < z; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d3 = p[i].dist(p[j]);
					if (maxd3 < d3)
					{
						maxd3 = d3;
					}
				}
			}
		}
#pragma omp section
		{
			for (int i = z + 1; i < n - 1; ++i)
			{
				for (int j = i + 1; j < n; ++j)
				{
					d4 = p[i].dist(p[j]);
					if (maxd4 < d4)
					{
						maxd4 = d4;
					}
				}
			}
		}
	}
	maxd1 = (maxd1 > maxd2) ? maxd1 : maxd2;
	maxd1 = (maxd1 > maxd3) ? maxd1 : maxd3;
	return (maxd1 > maxd4) ? maxd1 : maxd4;
}


int main()
{
	/*int n;
	cin >> n;
	double pi1 = pi_1(n);
	double pi2 = pi_2(n);
	
	cout << pi1 << ", " << pi2 << endl;*/

	/*int n;
	cin >> n;*/
	//prime_numbers(n);
	//cin >> n;
	for (int i = 0; i < 10000; ++i)
	{
		p[i].x = rand() % 100;
		p[i].y = rand() % 100;
	}
	double t = omp_get_wtime();
	cout << "d: " << diam(10000) << endl;
	cout << "Time: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
	cout << "d: " << diam_2(10000) << endl;
	cout << "Time 2: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
	cout << "d: " << diam_3(10000) << endl;
	cout << "Time 3: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
	cout << "d: " << diam_4(10000) << endl;
	cout << "Time 4: " << omp_get_wtime() - t << endl;

	return EXIT_SUCCESS;
}