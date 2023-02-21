#include<iostream>
#include<clocale>
#include<ctime>

using namespace std;

void swap(int& a, int& b);
void fillArray(int* a, int len);
void inputArray(int* a, int len);
void printArray(int* a, int len);
void mixArray(int* a, int len);
bool isSorted(int* a, int len, bool ascending = true);
int bubbleSort(int* a, int len, int k);
int insertionSort(int* a, int len, int k);
int selectionSort(int* a, int len, int k);

int main()
{
	int tr = 0;
	int cp = 0;
	int len = 5;
	
	
	setlocale(LC_ALL, "Russian");
	for (int i = 0; i < 4; ++i)
	{
		cout << "Для массива длинной" << len << ":" <<  endl;
		int* a = new int[len];
		fillArray(a, len);
		printArray(a, len);
		mixArray(a, len);
		printArray(a, len);
		for (int i = 0; i < 1000; ++i)
		{
			tr = tr + bubbleSort(a, len, 0);
			cp = cp + bubbleSort(a, len, 1);
		}
		cout << "Bubble sort:" << endl;
		cout << "Перестановок: " << tr / 1000 << endl;
		cout << "Сравнений: " << cp / 1000 << endl;
		
		for (int i = 0; i < 1000; ++i)
		{
			tr = tr + insertionSort(a, len, 0);
			cp = cp + insertionSort(a, len, 1);
		}
		cout << "Insertion sort:" << endl;
		cout << "Перестановок: " << tr / 1000 << endl;
		cout << "Сравнений: " << cp / 1000 << endl;

		for (int i = 0; i < 1000; ++i)
		{
			tr = tr + selectionSort(a, len, 0);
			cp = cp + selectionSort(a, len, 1);
		}
		cout << "Selection sort:" << endl;
		cout << "Перестановок: " << tr / 1000 << endl;
		cout << "Сравнений: " << cp / 1000 << endl;

		len = len + 5;
		
		delete[] a;
	}
	
	return 0;
}

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

void fillArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		a[i] = rand() % 90 + 10;
	}
}

void fillSequenceUpArray(int* a, int len, int k)
{
	for (int i = 0; i < len; ++i) {
		a[i] = k;
		++k;
	}
}
void fillSequenceDownArray(int* a, int len, int k)
{
	for (int i = 0; i < len; ++i) {
		a[i] = k;
		--k;
	}
}
void inputArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cin >> a[i];
	}
}

void printArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
	}
	cout << endl;
}

void mixArray(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		swap(a[i], a[rand() % len]);
	}
}

bool isSorted(int* a, int len, bool ascending)
{
	for (int i = 0; i < len - 1; ++i)
	{
		//1 2 3 4 5 3
		if (a[i] > a[i + 1] == ascending)
		{
			return false;
		}
	}
	return true;
}

int bubbleSort(int* a, int len, int k)
{
	int tr = 0;
	int cp = 0;
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = 0; j < len - i - 1; ++j)
		{
			++cp;
			if (a[j] > a[j + 1])
			{
				++tr;
				swap(a[j], a[j + 1]);
			}
		}
	}
	if (k == 0) return tr;
	else return cp;
}

int insertionSort(int* a, int len, int k)
{
	int tr = 0;
	int cp = 0;
	for (int i = 1; i < len; ++i)
	{
		int t = a[i];
		int j = i;
		while (j > 0 && a[j - 1] > t)
		{
			++cp;
			a[j] = a[j - 1];
			--j;
			++tr;
		}
		++cp;
		a[j] = t;
		++tr;
	}
	if (k == 0) return tr;
	else return cp;
 }

int selectionSort(int* a, int len, int k)
{
	int tr = 0;
	int cp = 0;
	for (int i = 0; i < len - 1; ++i)
	{
		int index = i;
		for (int j = i + 1; j < len; ++j)
		{
			++cp;
			if (a[j] < a[index])
			{
				index = j;
			}
		}
		swap(a[i], a[index]);
		++tr;
	}
	if (k == 0) return tr;
	else return cp;
}

