#include<iostream>
#include<ctime>
#include"ArrayList.h"

using namespace std;

void printMenu()
{
	cout << "МЕНЮ" << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Вывести массив на экран" << endl;
	cout << "2 - Добавить элемент" << endl;
	cout << "3 - Добавить элемент в позицию" << endl;
	cout << "4 - Удалить элемент по индексу" << endl;
	cout << "5 - Найти элемент" << endl;
	cout << "6 - Добавить несколько элементов" << endl;
	cout << "7 - Добавить несколько элементов, начиная с некоторой позиции" << endl;
}

void processChoice(ArrayList& a, ArrayList& b, int choice)
{
	switch (choice)
	{
	case 1:
	{
		a.print();
	}
	break;
	case 2:
	{
		int element;
		cout << "Введите элемент" << endl;
		cin >> element;
		cout << a.add(element) << endl;
	}
	break;
	case 3:
	{
		int element;
		int index;
		cout << "Введите элемент и индекс" << endl;
		cin >> element >> index;
		cout << a.add(index, element) << endl;
	}
	break;
	case 4:
	{
		int index;
		cout << "Введите индекс" << endl;
		cin >> index;
		cout << a.remove(index) << endl;;
	}
	break;
	case 5:
	{
		int element;
		cout << "Введите элемент" << endl;
		cin >> element;
		cout << a.indexOf(element) << endl;
	}
	break;
	case 6:
	{
		int i;
		int element;
		cout << "Введите элементы, закончите нулем" << endl;
		while (element != 0)
		{
			if (b.count == b.capacity)
			{
				b.expand();
			}
			cin >> element;
			b.data[i] = element;
			++b.count;
			++i;
		}
		std::cout << a.addAll(a.count, b) << endl;
		b.clear();
		
	}
	break;
	case 7:
	{
		int element = -1;
		int index;
		int i = 0;
		cout << "Введите индекс" << endl;
		cin >> index;
		cout << "Ввдите элементы, закончите нулем" << endl;
		while ((element != 0) and (b.count < b.capacity))
		{
			if (b.count == b.capacity)
			{
				b.expand();
			}
			cin >> element;
			b.data[i] = element;
			++b.count;
			++i;
		}
		cout << a.addAll(index, b) << endl;
		b.clear();
	}
	break;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	ArrayList a;
	ArrayList b;
	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(a, b, choice);
		system("pause");
	} while (choice != 0);

	return EXIT_SUCCESS;
}