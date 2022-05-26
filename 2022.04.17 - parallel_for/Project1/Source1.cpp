#include<iostream>
#include<omp.h>
#include<algorithm>
#include<vector>

using namespace std;

double* sin1 = new double[100000000];
//double* sin2 = new double[100000000];

/*void sin_pf(int n)
{
	cout << "#1 sin" << endl;
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
		{
			sin1[i] = sin(3.14 * i / (2.0 * n));

		}
	cout << "Time line: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
#pragma omp parallel for schedule (static)
	for (int i = 0; i < n; ++i)
	{
		sin1[i] = sin(3.14 * i / (2.0 * n));

	}
	cout << "Time static: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();
#pragma omp parallel for schedule (dynamic, 1000)
	for (int i = 0; i < n; ++i)
	{
		sin1[i] = sin(3.14 * i / (2.0 * n));
	}
	cout << "Time dynamic: " << omp_get_wtime() - t << endl;

t = omp_get_wtime();
#pragma omp parallel for schedule (guided, 1000)
	for (int i = 0; i < n; ++i)
	{
		sin1[i] = sin(3.14 * i / (2.0 * n));
	}
	cout << "Time guided: " << omp_get_wtime() - t << endl;
	cout << endl;
}

void pi_pf(int n)
{
	cout << "#2 pi" << endl;
	double pi = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / n;
	cout << "Time line: " << omp_get_wtime() - t << endl;
	cout << "pi = " << pi << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / n;
	cout << "Time static: " << omp_get_wtime() - t << endl;
	cout << "pi = " << pi << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / n;
	cout << "Time dynamic: " << omp_get_wtime() - t << endl;
	cout << "pi = " << pi << endl;


	pi = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: pi)
	for (int i = 0; i < n; ++i)
	{
		pi += (1.0 / (1.0 + ((2.0 * i - 1) / (2.0 * n)) * ((2.0 * i - 1) / (2.0 * n))));
	}
	pi = pi * 4 / n;
	cout << "Time guided: " << omp_get_wtime() - t << endl;
	cout << "pi = " << pi << endl;
	cout << endl;
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

void prime_numbers_pf(int n)
{
	cout << "#3 prime numbers" << endl;
	int p = 0;
	double t = omp_get_wtime();
	for (int i = 3; i <= n; i += 2)
	{
		if (isPrime(i))
		{
			++p;
		}
	}
	cout << "Time line: " << omp_get_wtime() - t << endl;
	cout << "sum: " << p << endl;


	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (isPrime(i))
		{
			++p;
		}
	}
	cout << "Time static: " << omp_get_wtime() - t << endl;
	cout << "sum: " << p << endl;


	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (isPrime(i))
		{
			++p;
		}
	}
	cout << "Time dynamic: " << omp_get_wtime() - t << endl;
	cout << "sum: " << p << endl;


	p = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (+: p)
	for (int i = 3; i <= n; i += 2)
	{
		if (isPrime(i))
		{
			++p;
		}
	}
	cout << "Time guided: " << omp_get_wtime() - t << endl;
	cout << "sum: " << p << endl;
	cout << endl;
}*/

struct Point
{
	int x;
	int y;

	double dist(Point p1)
	{
		return ((x - p1.x) * (x - p1.x)) + ((y - p1.y) * (y - p1.y));
	}
};

Point p[1000000];

void filling_p(int n)
{
	for (int i = 0; i < n; ++i)
	{
		p[i].x = rand() % 100;
		p[i].y = rand() % 100;
	}
}

void diameter_pf(int n)
{
	cout << "#4 diameter" << endl;
	filling_p(10000);
	double max = 0;
	double d = 0;
	double t = omp_get_wtime();
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "diameter :" << sqrt(max) << endl;
	cout << "Time line: " << omp_get_wtime() - t << endl;


	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static,10) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "diameter :" << sqrt(max) << endl;
	cout << "Time static: " << omp_get_wtime() - t << endl;


	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(dynamic, 1000) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "diameter :" << sqrt(max) << endl;
	cout << "Time dynamic: " << omp_get_wtime() - t << endl;


	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(guided, 1000) reduction (max: max)
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i; j < n; ++j)
		{
			d = p[i].dist(p[j]);
			if (max < d)
			{
				max = d;
			}
		}
	}
	cout << "diameter :" << sqrt(max) << endl;
	cout << "Time guided: " << omp_get_wtime() - t << endl;
}

int main()
{
	int n = 0;
	cin >> n;
	//sin_pf(n);
	//pi_pf(n);
	//prime_numbers_pf(n);
	diameter_pf(n);

	return EXIT_SUCCESS;

}
