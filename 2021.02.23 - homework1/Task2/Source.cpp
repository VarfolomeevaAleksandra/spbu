#include<iostream>

using namespace std;

double average(int n, ...)
{
	int sum = 0;
	for (int i = 0; i < n; ++i)
	{
		int* ptr = &n + 1 + i;
		sum += *ptr;
	}
	int result = sum/n;
	return result;
}

int main()
{
	cout << average(6, 5, 7, 3, 10, 9, 2) << endl;
	return 0;
}