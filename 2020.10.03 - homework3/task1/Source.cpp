#include<iostream>
#include<clocale>
#include<ctime>

using namespace std;

void printMenu()
{
	cout << "����" << endl;
	cout << "0 - ����� �� ���������" << endl;
	cout << "1 - ������ ��������� ��������� � ����������" << endl;
	cout << "2 - �������� � ������ n ��������� ����� � ���������� �� a �� b(n, a, b �������� � ����������)" << endl;
	cout << "3 - ������� ������ �� �����" << endl;
	cout << "4 - ����� ������� ��������" << endl;
	cout << "5 - ���������� ������ � �������" << endl;
	cout << "6 - ����������� ��������" << endl;
	cout << "7 - ������� �������� � ������" << endl;
	cout << "8 - �������� ���������� ������ ������ ��������� �������" << endl;
	cout << "9 - ����� ���������������������" << endl;
}

/// <summary>
/// ������������� �������
/// </summary>
/// <param name="capacity"> ��������������� ������� </param>
/// <returns> ��������� �� ������ �������</returns>
int* initArray(int capacity)
{
	int* result = new int[capacity + 2]{ 0 };
	*(result + 1) = capacity;
	result += 2;
	return result;
	//return (new int[capacity + 2]{ 0, capacity }) + 2;
}

/// <summary>
/// ������������ ������ ��-��� �������
/// </summary>
/// <param name="arr">���������</param>
void deleteArray(int* arr)
{
	/*
	arr -= 2;
	delete[] arr;
	*/
	delete[](arr - 2);
}

void expandArray(int*& arr)
{
	int* temp = initArray(2 * (*(arr - 1)));
	for (int i = 0; i < *(arr - 1); ++i)
	{
		*(temp + i) = *(arr + i);
	}
	*(temp - 2) = *(arr - 2);
	deleteArray(arr);
	arr = temp;
}

void addElement(int*& arr, int element)
{
	if (*(arr - 2) == *(arr - 1))
	{
		expandArray(arr);
	}
	*(arr + *(arr - 2)) = element;
	++(*(arr - 2));

}

void addRandomElements(int*& arr, int n, int min, int max)
{
	for (int i = 0; i < n; ++i)
	{
		addElement(arr, rand() % (max - min + 1) + min);
	}
}

void printArray(int* arr)
{
	cout << "[" << *(arr - 2) << "/" << *(arr - 1) << "] {";
	for (int i = 0; i < *(arr - 2); ++i)
	{
		cout << *(arr + i) << (i == *(arr - 2) - 1 ? "}\n" : ", ");
	}
}

/// <summary>
/// ������� ������ ������� ��������� �������� � �������.
/// </summary>
/// <param name="arr">������ � ����������</param>
/// <param name="element">������� �������</param>
/// <param name="start">����� ������ ������</param>
/// <returns>������ ������� ���������� �������� ��� -1, ���� ������� �� ������</returns>
int search(int* arr, int element, int start = 0)
{
	int result = -1;
	for (int i = 0; i < *(arr - 2); ++i)
		if (*(arr + i) == element)
		{
			result = i;
			break;
		}
	return result;
}

/// <summary>
/// ���������� ������� ���������.
/// </summary>
/// <param name="arr">������, � �������� ����������� ��������, ����������� ������ ���� �� ������� ����� ��� ��������� �� ������������ �������</param>
/// <param name="addedArr">������ � ������������ ����������</param>
void add(int*& arr, int* addedArr)
{
	int i;
	int j;
	for (i = *(arr - 2), j = 0; i < (*(arr - 2) + *(addedArr - 2)); ++i, ++j)
	{
		if (*(arr - 2) == *(arr - 1)) expandArray(arr);
		*(arr + i) = *(addedArr + j);
	}
	*(arr - 2) += *(addedArr - 2);
}

/// <summary>
/// ����������� ���� �������� � ����.
/// {a1, a2, a3, a4, a5} {b1, b2, b3, b4, b5, b6, b7, b8}
/// </summary>
/// <param name="a">������, �������� �������� ������ ������ �� ������ ������ � �������������� �������</param>
/// <param name="b">������, �������� �������� ������ ������ �� �������� ������ � �������������� �������</param>
/// <returns>
/// result[-1] = a[-2] + b[-2]
/// {a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, b6, b7, b8}
///</returns>
int* unify(int* a, int* b)
{
	int k;
	int i;
	int* result = initArray(*(a - 2) + *(b - 2));
	*(result - 2) = *(a - 2) + *(b - 2);
	for (i = 0, k = 0; i < *(a - 2); i += 2, ++k)
	{
		*(result + i) = *(a + k);
	}
	for (int i = 1, k = 0; i < *(b - 2); i += 2, ++k)
	{
		*(result + i) = *(b + k);
	}
	return result;
}

/// <summary>
/// ���������� �������� �� �������. ��� ��������, ������� ����� ����, ������ ���� �������� �� 1 �����.
/// </summary>
/// <param name="a">������ � �������</param>
/// <param name="index">������ ������������ ��������</param>
/// <returns>�������, �������� ��� �������� index, ���� index ��� ����������� - ������� -1</returns>
int extract(int* a, int index)
{
	int result;
	if ((index > * (a - 2)) or (index < 0))
	{
		result = -1;
	}
	else
	{
		result = *(a + index);
		--* (a - 2);
	}
	for (int i = index + 1; i < *(a - 2); ++i)
	{
		*(a + (i - 1)) = *(a + i);
	}
	return result;
}

/// <summary>
/// ������� �������� � ������. � ������������ �������� � ����� ������ ���� ������ index, ��� ����������� �������� ���������� �� 1 ������.
/// </summary>
/// <param name="a">�������������� ������</param>
/// <param name="index">������ ������������ ��������</param>
/// <param name="element">�������� ��������</param>
/// <returns>������������ 0, ���� ��� ������ � ������ ��� ���������, 1 - ���� ����� ��� �����������</returns>
int insert(int*& a, int index, int element)
{
	int result;
	if ((index > * (a - 2)) or (index < 0))
	{
		result = 1;
	}
	else
	{
		++* (a - 2);
		result = 0;
	}
	if (*(a - 2) == *(a - 1))
	{
		expandArray(a);
	}
	for (int i = *(a - 2); i > index; --i)
	{
		*(a + i) = *(a + (i - 1));
	}
	*(a + index) = element;
	return result;
}

/// <summary>
/// ������� ������������������ ��������� �� �������
/// </summary>
/// <param name="a">�������������� ������</param>
/// <param name="startIndex">������ ���������� �����</param>
/// <param name="count">���������� ��������� ���������</param>
/// <returns>0, ���� ��� ������ ������, 1, ���� ������� ������ ���� �������������</returns>
int deleteGroup(int* a, int startIndex, int count)
{
	int result;
	int i;
	int j;
	if ((startIndex > * (a - 2)) or (startIndex < 0) or (count > (*(a - 2) - startIndex)) or (count < 0))
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	for (i = startIndex + count, j = startIndex; i < (*(a - 2) - (startIndex + count)); ++i, ++j)
	{
		*(a + j) = *(a + i);
	}
	*(a - 2) = *(a - 2) - count;
	return result;
}

/// <summary>
/// ����� ��������������������� � �������
/// </summary>
/// <param name="a">������, � ������� ���� ���������������������</param>
/// <param name="b">������� ���������������������</param>
/// <returns>������ ������ ��������������������� ��� -1, ���� ������� ���</returns>
int subSequence(int* a, int* b)
{
	int f;
	int i;
	int j;
	int k;
	for (i = 0; i <= *(a - 2) - *(b - 2); ++i)
	{
		f = 0;
		for (j = i, k = 0; k < *(b - 2); ++j, ++k)
		{
			if (*(a + j) == *(b + k)) ++f;
		}
		if (f == *(b - 2))
		{
			return i;
			break;
		}
	}
	if (f < *(b - 2)) return -1;
}
int* arrayChoice(int* arr1, int* arr2)
{
	int array;
	cout << "�������� ������ (1 ��� 2)" << endl;
	cin >> array;
	if (array == 1) { return arr1; }
	else { return arr2; }
}


void processChoice(int*& arr1, int*& arr2, int choice)
{
	switch (choice)
	{
	case 0:
		exit(0);
	case 1:
		int* arr = arrayChoice(arr1, arr2);
		cout << "������� ��������, ��������� 0" << endl;
		int x = -1;
		while (x != 0)
		{
			cin >> x;
			addElement(arr, x);
		}
		break;
	case 2:
		int n;
		int min;
		int max;
		cout << "������� ���������� ���������, ������ � ������� �������" << endl;
		cin >> n >> min >> max;
		addRandomElements(arr1, n, min, max);
		break;
	case 3:
		printArray(arr1);
		break;
	case 4:
		int element2;
		cout << "������� �������" << endl;
		cin >> element2;
		cout << search(arr1, element2) << endl;;
		break;
	case 5:
		add(arr1, arr2);
		break;
	case 6:
		int*temp = unify(arr1, arr2);
		printArray(temp);
		deleteArray(temp);
		break;
	case 7:
		int index;
		cout << "������� ������" << endl;
		cin >> index;
		cout << extract(arr1, index) << endl;
		break;
	case 8:
		int startIndex;
		int num;
		cout << "������� ������ ������ ���������� ����� � ���������� ���������" << endl;
		cin >> startIndex >> num;
		cout << deleteGroup(arr1, startIndex, num) << endl;
		break;
	case 9:
		cout << subSequence(arr1, arr2) << endl;
		break;
	}
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int* a = initArray(10);
	int* b = initArray(10);

	int choice = 0;
	do
	{
		system("cls");
		printMenu();
		cin >> choice;
		processChoice(a, b, choice);
		system("pause");
	} while (choice != 0);

	deleteArray(a);
	deleteArray(b);
	return EXIT_SUCCESS;
}