#include<iostream>
#include<stdlib.h>
#include<clocale>

using namespace std;

void expand(int* arr, int& cap)
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
void add1(int* arr, int& count, int& cap)
{
	int x;
	cin >> x;
	if (count == cap)
	{
		expand(arr, cap);
	}
	arr[count] = x;
	++count;
}
void print(int* arr, int& count)
{
	for (int i = 0; i < count; ++i)
		cout << arr[i] << " ";
	cout << endl;
}
int max(int* arr, int& count)
{
	int i;
	int max;
	max = 0;
	for (i = 0; i < count; ++i)
	{
		if (arr[i] > arr[max]) max = i;
	}
	return i;
}
int min(int* arr, int& count)
{
	int i;
	int min = arr[0];
	for (i = 1; i < count; ++i)
	{
		if (arr[i] < min) min = arr[i];
	}
	return min;
}
int summa(int* arr, int& count)
{
	int i;
	int sum = 0;
	for (i = 0; i < count; ++i)
		sum = sum + arr[i];
	return sum;
}
void reverse(int* arr, int& count)
{
	int i;
	for (i = count; i >= 0; --i)
		cout << arr[i] << " ";
	cout << endl;
}

void choiсe(int*& arr, int& count, int& cap, int& in)
{
	switch (in)
	{
	case 0:
	{
		exit(0);
	}
	case 1:
	{
		add1(arr, count, cap);
		break;
	}
	case 2:
	{
		print(arr, count);
		break;
	}
	case 3:
	{
		cout << "Номер максимального элемента " << max(arr, count) << endl;
		break;
	}
	case 4:
	{
		cout << "Минимальный элемент " << min(arr, count) << endl;
		break;
	}
	case 5:
	{
		cout << "Сумма " << summa(arr, count) << endl;
		break;
	}
	case 6:
	{
		reverse(arr, count);
		break;
	}
	}
}
void menu()
{
		cout << "0 - Выход из программы" << endl
			<< "1 - Добавить число в массив" << endl
			<< "2 - Вывести массив на экран" << endl
			<< "3 - Найти номер максимального элемента массива"
			<< endl << "4 - Найти минимальный элемент массива"
			<< endl << "5 - Посчитать сумму элементов массива"
			<< endl << "6 - Вывести массив в обратном порядке"
			<< endl;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int cap = 10;
	int* arr = new int[cap];
	int count = 0;
	int in = 0;
	do
	{
		system("cls");
		menu();
		cin >> in;
		choiсe(arr, count, cap, in);
		system("pause");
	} 
	while (in != 0);
	delete[] arr;
	return 0;
}

