#include<iostream>
#include <math.h>
#include <utility>
#include<vector>
#include <iomanip>
#include<stdlib.h>
#include<time.h>

using namespace std;

double function(double x)
{
	double f;
	f = x - (10 * (sin(x)));
	return f;
}

double first_diff(double x)
{
	double f;
	f = 1 - 10 * cos(x);
	return f;
}

double second_diff(double x)
{
	double f;
	f = 10 * sin(x);
	return f;
}

bool check_sign(double a, double b)
{
	if (function(a) * function(b) < 0) return true;
	else return false;
}

vector <pair <double, double>> odd(double a, double b, double n)
{
	double h;
	pair <double, double> interval;
	vector <pair <double, double>> intervals;
	h = (b - a) / n;
	double j = a;
	while (j <= b)
	{
		if (check_sign(j, j + h))
		{
			interval.first = j;
			interval.second = j + h;
			intervals.push_back(interval);
		}
		j = j + h;
	}
	return intervals;
}

pair <double, pair <double, int>> bisection(double a, double b, double e)
{
	pair <double, pair<double, int>> root;
	double a_i = a;
	double b_i = b;
	double c_i = 0;
	int k = 0;
	while (abs(b_i - a_i) > 2 * e)
	{
		c_i = (b_i + a_i) / 2;
		if (function(a_i) * function(c_i) < 0)
		{
			b_i = c_i;
		}
		else
		{
			a_i = c_i;
		}
		++k;
	}
	root.first = (a_i + b_i) / 2;
	root.second.first = abs(a_i - b_i);
	root.second.second = k;
	return root;
}

bool check_convergence(double x)
{
	if (function(x) * second_diff(x) < 0) return false;
	return true;
}

pair <double, pair <double, int>> Newton(double x_0, double x_1, double e, int k)
{
	pair <double, pair <double, int>> root;

	while (abs(x_1 - x_0) > 2 * e)
	{
		++k;
		x_0 = x_1;
		x_1 = x_0 - (function(x_0) / first_diff(x_0));
		Newton(x_0, x_1, e, k);
	}
	root.first = (x_0 + x_1) / 2;
	root.second.first = abs(x_1 - x_0);
	root.second.second = k;

	return root;
}

pair <double, pair <double, int>> mod_Newton(double x, double x_0, double x_1, double e, int k)
{
	pair <double, pair <double, int>> root;

	while (abs(x_1 - x_0) > 2 * e)
	{
		++k;
		x_0 = x_1;
		x_1 = x_0 - (function(x_0) / first_diff(x));
		Newton(x_0, x_1, e, k);
	}
	root.first = (x_0 + x_1) / 2;
	root.second.first = abs(x_1 - x_0);
	root.second.second = k;

	return root;
}

pair <double, pair <double, int>> secant(double x_0, double x_1, double e, int k)
{
	pair <double, pair <double, int>> root;
	double x_2 = x_1 - ((function(x_1) / (function(x_1) - function(x_0))) * (x_1 - x_0));
	while (abs(x_2 - x_1) > 2 * e)
	{
		++k;
		x_0 = x_1;
		x_1 = x_2;
		x_2 = x_1 - ((function(x_1) / (function(x_1) - function(x_0))) * (x_1 - x_0));
	}
	root.first = (x_2 + x_1) / 2;
	root.second.first = abs(x_2 - x_1);
	root.second.second = k;

	return root;
}

double RandomNumber(double min, double max, int precision)
{
	srand(time(0));

	double value;

	value = rand() % (int)pow(10, precision);

	value = min + (value / pow(10, precision)) * (max - min);

	return value;
}


void print(pair <double, pair <double, int>> root, vector <pair <double, double>> intervals, double e)
{
	cout << "Корень:" << setprecision(10) << root.first << endl;
	cout << "Итераций:" << root.second.second << endl;
	cout << "Длина последнего промежутка:" << root.second.first << endl;
	cout << "Невязка:" << abs(function(root.first) - 0) << endl;
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, n;
	long double e;
	cout << "Введите концы интервала" << endl;
	cin >> a;
	cin >> b;
	cout << "Введите шаг" << endl;
	cin >> n;
	cout << "Введите точность" << endl;
	cin >> e;

	vector <pair <double, double>> intervals;
	intervals = odd(a, b, n);
	cout << "Отрезки:" << endl;
	for (int i = 0; i != intervals.size(); ++i)
	{
		cout << "[" << intervals[i].first << ", " << intervals[i].second << "]" << endl;
	}
	cout << "Количество " << intervals.size() << endl;


	cout << "Метод бисекции:" << endl;
	pair <double, pair <double, int>> root;
	for (int i = 0; i != intervals.size(); ++i)
	{
		root = bisection(intervals[i].first, intervals[i].second, e);
		cout << "Начальное приближение к корню: " << (intervals[i].first + intervals[i].second) / 2 << endl;
		print(root, intervals, e);
	}
	

	cout << "Метод Ньютона" << endl;

	double x_0;
	double x_1;
	int p = 0;
	 
	for (int i = 0; i != intervals.size(); ++i)
	{
		while (p <= 1000000)
		{
			srand(time(0));
			x_0 = RandomNumber(intervals[i].first, intervals[i].second, 2);
			if (check_convergence(x_0)) break;
			else ++p;
		}
		p = 0;
		x_1 = x_0 - (function(x_0) / first_diff(x_0));
		int k = 0;
		root = Newton(x_0, x_1, e, k);
		cout << "Начальное приближение к корню: " << x_0 << endl;
		print(root, intervals, e);
	}

	p = 0;

	cout << "Метод секущих" << endl;


	for (int i = 0; i != intervals.size(); ++i)
	{
		double x_0 = intervals[i].first;
		double x_1 = intervals[i].second;
		int k = 0;
		root = secant(x_0, x_1, e, k);
		cout << "Начальное приближение к корню: " << x_0 << endl;
		print(root, intervals, e);
	}

	cout << "Модифицированный метод Ньютона" << endl;


	for (int i = 0; i != intervals.size(); ++i)
	{
		while (p <= 1000000)
		{
			srand(time(0));
			x_0 = RandomNumber(intervals[i].first, intervals[i].second, 2);
			if (check_convergence(x_0)) break;
			else ++p;
		}
		p = 0;
		double x = x_0;
		double x_1;
		x_1 = x_0 - (function(x_0) / first_diff(x_0));
		int k = 0;
		root = mod_Newton(x, x_0, x_1, e, k);
		cout << "Начальное приближение к корню: " << x_0 << endl;
		print(root, intervals, e);
	}


	
	
	return EXIT_SUCCESS;

}