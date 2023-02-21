#include<iostream>
#include<ctime>
#include"ArrayList.h"

using namespace std;

void printMenu()
{
	cout << "МЕНЮ" << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Добавить элемент, введенный с клавиатуры" << endl;
	cout << "2 - Вывести массив" << endl;
	cout << "3 - Проверить, является ли массив симметричным" << endl;
	cout << "4 - Циклический сдвинуть массив на n элементов. n>0 - сдвиг вправо, n<0 - сдвиг влево" << endl;
	cout << "5 - Проверить, может ли массив стать симметричным, если из него удалить один элемент" << endl;
}

void processChoice(ArrayList& a, int choice)
{
	switch (choice)
	{
	case 1:
	{
		int element;
		cin >> element;
		a.add(element);
	}
	break;
	case 2:
	{
		cout << a.toString() << endl;
	}
	break;
	case 3:
	{
		int flag = 0;
		for (int i = 0; i < a.length() / 2; ++i)
		{
			if (a.get(i) != a.get(a.length() - i)) flag = 0;
		}
		if (flag == 0)
		{
			cout << "yes" << endl;
		}
		else
		{
			cout << "no" << endl;
		}
	}
	break;
	case 4:
	{
		ArrayList b(a);
		int n;
		cin >> n;
		n = n % a.length();
		if (n > 0)
		{
			for (int i = 0, j = a.length() - n; i < n; ++i, ++j)
			{
				a.set(i, b.get(j));
			}
			for (int i = n, j = 0; i < a.length(); ++i, ++j)
			{
				a.set(i, b.get(j));
			}
		}
		if (n < 0)
		{
			for (int i = a.length() - n, j = 0; i < n; ++i, ++j)
			{
				a.set(i, b.get(j));
			}
			for (int i = 0, j = n; i < a.length(); ++i, ++j)
			{
				a.set(i, b.get(j));
			}
		}
	}
	break;
	case 5:
	{
		for (int i = 0; i < a.length(); ++i)
		{
			ArrayList b(a);
			b.remove(i);
			int flag = 0;
			for (int i = 0; i < b.length() / 2; ++i)
			{
				if (b.get(i) != b.get(b.length() - i)) flag = 0;
			}
			if (flag == 0)
			{
				cout << "yes, number = " << i << endl;
			}
		}
	}
	break;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	ArrayList a;
	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(a, choice);
		system("pause");
	} while (choice != 0);

	return EXIT_SUCCESS;
}