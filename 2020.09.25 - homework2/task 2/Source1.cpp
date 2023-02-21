#include<iostream>
#include<math.h>

using namespace std;

void print(int*& arr, int& count)
{
	for (int i = 0; i < count; ++i)
	{
		cout << arr[i] << " ";

	}
	cout << endl;
}
void expand(int*& arr, int& cap)
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
void add(int*& arr, int& count, int& cap)
{
	int x;
	cin >> x;
	if (count == cap)
	{
		expand(arr, cap);
	}
	arr[count] = x;
	++count;
	print(arr, count);
}
void add_random(int*& arr, int& count, int& cap)
{
	int a;
	int b;
	int n;
	int i;
	cin >> a >> b >> n;
	for (i = 0; i < n; ++i)
	{
		if (count == cap) expand(arr, cap);
		arr[count] = rand() % (b - a + 1) + a;
		count++;
	}
	print(arr, count);
}
void reverse(int*& arr, int& count)
{
	int c = 0;
	for (int i = 0; i <= (count / 2); ++i)
	{
		c = arr[i];
		arr[i] = arr[count - i];
		arr[count - i] = c;
	}
	print(arr, count);
}
int* pair_reverse(int*& arr, int& count)
{
	int i;
	int c;
	for (i = 0; i < count; i = i + 2)
	{
		if ((i + 1) > count) break;
		c = arr[i];
		arr[i] = arr[i + 1];
		arr[i + 1] = c;
	}
	return arr;
}
int* cyclic_shift(int*& arr, int& count)
{
	int t;
	t = arr[count - 1];
	for (int j = count - 2; j >= 0; j--)
	{
		arr[j + 1] = arr[j];
	}
	arr[0] = t;
	return arr;
}
int* middle_reverse(int*& arr, int& count)
{
	int n;
	int c;
	cin >> n;
	int n_l = n - 1;
	int n_r = n;
	int i = 0;
	while (i < n_l)
	{
		c = arr[i];
		arr[i] = arr[n_l];
		arr[n_l] = c;
		i++;
		n_l--;
	}
	int new_count = count;
	while (n_r < new_count)
	{
		c = arr[n_r];
		arr[n_r] = arr[new_count - 1];
		arr[new_count - 1] = c;
		n_r++;
		new_count--;
	}
	return arr;
}
void choice(int*& arr, int& count, int& cap, int in)
{
	switch (in)
	{
	case 0:
	{
		exit(0);
	}
	case 1:
	{
		add_random(arr, count, cap);
		break;
	}
	case 2:
	{
		reverse(arr, count);
		break;
	}
	case 3:
	{
		cout << pair_reverse(arr, count) << endl;
		break;
	}
	case 4:
	{
		cout << cyclic_shift(arr, count) << endl;
		break;
	}
	case 5:
	{
		cout << middle_reverse(arr, count) << endl;
		break;
	}
	case 6:
	{
		add(arr, count, cap);
	}
	}
}
void menu()
{
	cout << "0 - Выход из программы" <<
		endl << "1 - Добавить в массив n случайных чисел в промежутке от a до b(n, a, b вводится с клавиатуры)" <<
		endl << "2 - Развернуть массив" <<
		endl << "3 - Поменять элементы массива местами в парах.Если число элементов нечетно, последний элемент остается на своем месте" <<
		endl << "4 - Циклический сдвиг вправо на 1" <<
		endl << "5 - Развернуть две половинки массива.n - индекс элемента, разделяющего половинки" <<
		endl << "6 - Добавить элемент в массив" <<
		endl;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int cap;
	cap = 10;
	int* arr = new int[cap];
	int count = 0;
	int in = 0;
	do
	{
		system("cls");
		menu();
		cin >> in;
		choice(arr, count, cap, in);
		system("pause");
	} while (in != 0);
	delete[] arr;
	return 0;
}
