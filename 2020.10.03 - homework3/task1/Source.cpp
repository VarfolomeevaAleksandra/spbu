#include<iostream>
#include<clocale>
#include<ctime>

using namespace std;

void printMenu()
{
	cout << "МЕНЮ" << endl;
	cout << "0 - Выход из программы" << endl;
	cout << "1 - Ввести несколько элемнетов с клавиатуры" << endl;
	cout << "2 - Добавить в массив n случайных чисел в промежутке от a до b(n, a, b вводится с клавиатуры)" << endl;
	cout << "3 - Вывести массив на экран" << endl;
	cout << "4 - Поиск индекса элемента" << endl;
	cout << "5 - Добавление массив к массиву" << endl;
	cout << "6 - Объединение массивов" << endl;
	cout << "7 - Вставка элемента в массив" << endl;
	cout << "8 - Удаление нескольких подряд идущих элементов массива" << endl;
	cout << "9 - Поиск подпоследовательности" << endl;
}

/// <summary>
/// Инициализация массива
/// </summary>
/// <param name="capacity"> вместительность массива </param>
/// <returns> указатель на начало массива</returns>
int* initArray(int capacity)
{
	int* result = new int[capacity + 2]{ 0 };
	*(result + 1) = capacity;
	result += 2;
	return result;
	//return (new int[capacity + 2]{ 0, capacity }) + 2;
}

/// <summary>
/// Освобождение памяти из-под массива
/// </summary>
/// <param name="arr">Указатель</param>
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
/// Функция поиска первого вхождения элемента в массиве.
/// </summary>
/// <param name="arr">Массив с элементами</param>
/// <param name="element">Искомый элемент</param>
/// <param name="start">Место начала поиска</param>
/// <returns>индекс первого найденного элемента или -1, если элемент не найден</returns>
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
/// Добавление массива элементов.
/// </summary>
/// <param name="arr">Массив, к которому добавляются элементы, расширяется только если не хватило места для элементов из добавляемого массива</param>
/// <param name="addedArr">Массив с добавляемыми элементами</param>
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
/// Объединение двух массивов в один.
/// {a1, a2, a3, a4, a5} {b1, b2, b3, b4, b5, b6, b7, b8}
/// </summary>
/// <param name="a">Массив, элементы которого должны стоять на четных местах в результирующем массиве</param>
/// <param name="b">Массив, элементы которого должны стоять на нечетных местах в результирующем массиве</param>
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
/// Извлечение элемента из массива. Все элементы, стоящие после него, должны быть сдвинуты на 1 влево.
/// </summary>
/// <param name="a">Массив с данными</param>
/// <param name="index">Индекс извлекаемого элемента</param>
/// <returns>элемент, стоявший под индексом index, если index был некорректен - вернуть -1</returns>
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
/// Вставка элемента в массив. У вставляемого элемента в итоге должен быть индекс index, все последующие элементы сдвигаются на 1 вправо.
/// </summary>
/// <param name="a">Модифицируемый массив</param>
/// <param name="index">Индекс вставленного элемента</param>
/// <param name="element">Значение элемента</param>
/// <returns>Возвращается 0, если все хорошо и индекс был корректен, 1 - если индес был некорректен</returns>
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
/// Удалить последовательность элементов из массива
/// </summary>
/// <param name="a">Модифицируемый массив</param>
/// <param name="startIndex">Начало удаляемого куска</param>
/// <param name="count">Количество удаялемых элементов</param>
/// <returns>0, если все прошло хорошо, 1, если входные данные были некорректными</returns>
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
/// Поиск подпоследовательности в массиве
/// </summary>
/// <param name="a">Массив, в котором ищем подпоследовательность</param>
/// <param name="b">Искомая подпоследовательность</param>
/// <returns>Индекс начала подпоследовательности или -1, если таковой нет</returns>
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
	cout << "Выберете массив (1 или 2)" << endl;
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
		cout << "Введите элементы, последний 0" << endl;
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
		cout << "Введите количество элементов, нижнюю и верхнюю границы" << endl;
		cin >> n >> min >> max;
		addRandomElements(arr1, n, min, max);
		break;
	case 3:
		printArray(arr1);
		break;
	case 4:
		int element2;
		cout << "Введите элемент" << endl;
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
		cout << "Введите индекс" << endl;
		cin >> index;
		cout << extract(arr1, index) << endl;
		break;
	case 8:
		int startIndex;
		int num;
		cout << "Введите индекс начала удаляемого куска и количество элементов" << endl;
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