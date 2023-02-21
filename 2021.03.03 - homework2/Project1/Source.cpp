#include<iostream>

using namespace std;

template <typename T1, typename T2>
T1 sum(T1 a, T2 b)
{
	return a + b;
}
template <typename T1, typename T2>
T1 mult(T1 a, T2 b)
{
	return a * b;
}
template <typename T1, typename T2>
T1 diff(T1 a, T2 b)
{
	return a - b;
}
template <typename T1, typename T2>
T1 div(T1 a, T2 b)
{
	return a / b;
}


int number(char p)
{
	if (p == '+') return 1;
	else if (p == '-') return 2;
	else if (p == '/') return 3;
	else if (p == '*') return 4;
	else return 5;
}

template <class T1, class T2>
T1 prosesChoice(T1 a, T2 b, char opc)
{
	T1(*op[5])(T1, T2) = { sum, diff, div, mult};
	int choice = number(opc);
	T1 result = 0;
	switch (choice)
	{
	case 1:
		result = op[1](a,b);
	case 2:
		result = op[2](a, b);
	case 3:
		result = op[3](a, b);
	case 4:
		result = op[4](a, b);
	case 5:
		cout << "Ошибка ввода";
		exit(0);
	}
	return result;
}

int typeCheck(char* opc)
{
	if (atof(opc) == 0)
		return 0;
	else return 1;
}
int main(int argv, char* argc[])
{
	double a;
	double b;
	char opc;
	int k = 0;
	for (int i = 0; i < argv; ++i)
	{
		if (argc[i] == "--operand1")
		{
			if (typeCheck(argc[i + 1]) == 0)
			{
				a = atoi(argc[i + 1]);
			}
			else a = atof(argc[i + 1]);
			++k;
		}
		if (argc[i] == "--operand2")
		{
			if (typeCheck(argc[i + 1]) == 0)
			{
				b = atoi(argc[i + 1]);
			}
			else b = atof(argc[i + 1]);
			++k;
		}
		if (argc[i + 1] == "--operator")
		{
			opc = *(argc[i]);
			++k;
		}
	}
	if (k < 3)
	{
		cout << "Ошибка ввода";
	}
	else
	{
		cout << a << ' ' << opc << ' ' << b << " = " << prosesChoice(a, b, opc);
	}
	
	return 0;
}