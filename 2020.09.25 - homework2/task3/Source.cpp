#include<iostream>

using namespace std;
void expand(int*& arr, int& count, int& cap)
{
	int newcap = cap * 2;
	int* temp = new int[newcap];
	for (int i = 0; i < cap; ++i)
	{
		temp[i] = arr[i];
	}
	cap = newcap;
	delete[] arr;
	arr = temp;
}
int* factorial(int*& arr, int*& f, int& count)
{
	int i;
	for (i = 0; i < count; ++i)
	{
		for (int j = 1; j <= arr[i]; ++j)
		{
			if (arr[i] == 0)
			{
				f[i] = 1;
				break;
			}
			else
			{
				f[i] = f[i] * j;
			}
		}
	}
	return f;
}
int average(int*& f, int& count)
{
	int result = 0;
	for (int i = 0; i < count; ++i)
	{
		result = result + f[i];
	}
	result = result / count;
	return result;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int cap;
	cap = 10;
	int* arr = new int[cap];
	cout << "¬ведите последовательность чисел, последн€€ цифра 0" << endl;
	int count = 0;
	while (true)
	{
		int x = 0;
		cin >> x;
		if (x == 0)
		{
			break;
		}
		arr[count] = x;
		count++;
		if (count == cap)
		{
			expand(arr, count, cap);
		}
	}
	cout << endl;
	int* f = new int[count];
	for (int i = 0; i < count; ++i)
	{
		f[i] = 1;
	}
	factorial(arr, f, count);
	cout << average(f, count) << endl;
	
	return EXIT_SUCCESS;
}