#include<iostream>
#include<omp.h>
#include<algorithm>
#include<cstdlib>

using namespace std;

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
	cout << "diameter :" << max << endl;
	cout << "Time line: " << omp_get_wtime() - t << endl;


	max = 0;
	d = 0;
	t = omp_get_wtime();
#pragma omp parallel for schedule(static) reduction (max: max)
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
	cout << "diameter :" << max << endl;
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
	cout << "diameter :" << max << endl;
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
	cout << "diameter :" << max << endl;
	cout << "Time guided: " << omp_get_wtime() - t << endl;
}

int main()
{

    diameter_pf(10000);

    return EXIT_SUCCESS;
}
