#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

long long factorial(int k)
{
	long long fact = 1;
	for (int i = 1; i <= k; ++i)
	{
		if (k == 0) break;
		fact = fact * i;
	}
	return fact;
}

int first(int k)
{
	int c = -1;
	for (int i = 0; i <= k; ++i)
	{
		c = c * (-1);
	}
	return c;
}

double second(double x, int k)
{
	double c = x;
	for (int i = 1; i < 2 * k + 1; ++i)
	{
		if (k == 0) break;
		c = c * x;
	}
	return c;
}

double accuracy(int n)
{
	double c = 1;
	for (int i = 0; i <= n; ++i)
	{
		c = c * 0.1;
	}
	return c;
}

double mySin(double x, int n)
{
	double sin = 0;
	int j = 1;
	if (x < 0) j = -1;
	for (int i = 0; (j * second(x, i)) / factorial(2 * i + 1) >= accuracy(n); ++i)
	{
		sin = sin + ((first(i) * second(x, i)) / factorial(2 * i + 1));
	}
	return sin;
}

int main()
{
	int n = 0;
	double x = 0;
	cin >> x >> n;
	cout << sin(x) << endl;
	cout << setprecision(n) << mySin(x, n) << endl;
}