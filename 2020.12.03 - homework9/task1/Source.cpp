#include<iostream>
#include<string>
#include <stdlib.h>
#include<clocale>
#include<ctime>

using namespace std;


int extraCharacters(string str)
{
	int errorCode = 0;
	int j = 0;
	if (str[0] == '-') j = 1;
	for (int i = j; str[i] != '\0'; ++i)
	{
		if (str[0] == '.')
		{
			errorCode = 1;
			break;
		}
		if (str[i] == ' ')
		{
			errorCode = 1;
			break;
		}

		if ((str[i] < '0' or str[i] > '9') && str[i] != '.')
		{
			errorCode = 1;
			break;
		}
	}
	return errorCode;
}
int stringToInt(string& str)
{
	int result = 0;
	int j = 0;
	if (str[0] == '-') j = 1;
	for (int i = j; str[i] != '\0' && extraCharacters(str) == 0; ++i)
	{
		result = 10 * result + str[i] - '0';
	}
	if (j == 1) result = -result;
	return result;
}

double stringToDouble(string& str)
{
	int i;
	int j = 0;
	int k = 0;
	double result = 0;
	if (str[0] == '-') j = 1;
	for (i = j; str[i] != '.' && extraCharacters(str) == 0; ++i)
	{
		result = 10 * result + str[i] - '0';
		k = i;
	}
	for (i = k + 2; str[i] != '\0' && extraCharacters(str) == 0; ++i)
	{
		result = 10 * result + str[i] - '0';
	}
	while (i != k + 2)
	{
		result = result / 10;
		--i;
	}
	if (j == 1) result = -result;
	return result;
}


void trim(string& str) // ������� �����
{
	int startIndex = 0;
	while (str[startIndex] == ' ')
	{
		startIndex++;
	}
	str = str.substr(startIndex);
}

int sizeInt(string str)
{
	int errorCode = 0;
	string size;
	size = "9223372036854775807";
	int j = 0;
	if (str[0] == '-') j = 1;
	if (size.length() == str.length())
	{
		for (int i = j; size[i] != '\0'; ++i)
		{
			if (size[i] - str[i] < 0) errorCode = 2;
		}
	}
	else if (size.length() < str.length()) errorCode = 2;
	/*
	if ((stringToInt(str) > 9223372036854775807) or (stringToInt(str) < -9223372036854775807)) errorCode = 2;
	*/
	return errorCode;
}

int sizeDouble(string str)
{
	int errorCode = 0;
	string size;
	size = "179769";
	for (int i = 0; i < 309; ++i)
	{
		size = size + '0';
	}
	int j = 0;
	if (str[0] == '-') j = 1;
	if (size.length() == str.length())
	{
		for (int i = j; i < 6; ++i)
		{
			if (size[i] - str[i] < 0)
			{
				errorCode = 3;
			}
			if (str[i] == '.')
			{
				errorCode = 0;
				break;
				j = -1;
			}
		}
		for (int i = 7; i < 309; ++i)
		{
			if (j == -1) break;
			if (str[i] != '0')
			{
				errorCode = 3;
			}
			if (str[i] == '.')
			{
				errorCode = 0;
				break;
			}
		}
	}
	else if (size.length() < str.length()) errorCode = 3;
	return errorCode;
}

long long readInt(string& str)
{
	long long number_int = 0;
	if (extraCharacters(str) != 0) return number_int;
	else if (sizeInt(str) != 0) return number_int;
	else
	{
		number_int = stringToInt(str);
		return number_int;
	}
}

double readDouble(string& str)
{
	double number_double = 0;
	if (extraCharacters(str) != 0) return number_double;
	else if (sizeDouble(str) != 0) return number_double;
	else
	{
		number_double = stringToDouble(str);
		return number_double;
	}
}

int intInsteadOfDouble(string& str)
{
	int errorCode = 0;
	int c = 0;
	int i;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == '.') c = 1;
	}
	if (str[i - 1] == '.') errorCode = 4;
	if (c == 0) errorCode = 4;
	return errorCode;
}

int doubleInsteadOfInt(string& str)
{
	int errorCode = 0;
	int c = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		if (str[i] == '.') c = 1;
	}
	if (c == 1) errorCode = 4;
	return errorCode;
}

string text(int i)
{
	string* str_text = new string[16];

	str_text[0] = "������� ������������!";
	str_text[1] = "������� ��������� ��������� �� ������������ ���������� ���������";
	str_text[2] = "��������� �� ���������, ��������";
	str_text[3] = "�� ��� ��������� ���� ������� �������� �������, ���������, ����������";
	str_text[4] = "��������, �� ������������ �� ������, ��� ��� �� ��������� ����� ������������ ����������� �������";
	str_text[5] = "�� ����� ������� ������� ��� ������� ��������� �����, ��������� ��������";
	str_text[6] = "��������� �� ����������� � ������ �������, �������� ��������� ������";
	str_text[7] = "���������, ��� ����� ����� ������ �������� ��� ��� \"1234\", � ������� ��� \"123.45\". �� ���������, ��� �������������� ���� - �����";
	str_text[8] = "������� ����� �����";
	str_text[9] = "������� ������� �����";
	str_text[10] = "���� ������ �����, ������� 0, ���� ��� - ����� ������ �����";
	str_text[11] = "��� ������� ����������!";
	str_text[12] = "�� ����� ������ �������� ����� �����. ����������, ���� ������ ������ ����� �����, �� ������� � ������� \"5.0\" ";
	str_text[13] = "����������, ��������� ���� �������� �����. ���� �� ������ ������ ����� ����� ����� ��������, �� ������� � ������� \"5.0\" ";
	str_text[14] = "�� ����� ������� ����� ������ ������, ���������� ��������� ����";
	str_text[15] = "����������, ��������� ���� ������ �����, �� ����� ������ ���� �������";

	return str_text[i];
}
bool resolveError(string str1, string str2)
{
	if (extraCharacters(str1) + extraCharacters(str2) + sizeInt(str1) + sizeDouble(str2) + intInsteadOfDouble(str2) + doubleInsteadOfInt(str1) != 0)
	{
		cout << text(0) << endl;
		cout << text(rand() % 2 + 1) << endl;
		if (extraCharacters(str1) == 1 or extraCharacters(str2) == 1)
		{
			cout << text(rand() % 2 + 3) << endl;
		}
		if (sizeInt(str1) == 2 or sizeDouble(str2) == 3)
		{
			cout << text(rand() % 2 + 5) << endl;
		}
		if (extraCharacters(str2) == 0 && sizeDouble(str2) == 0 && intInsteadOfDouble(str2) != 0)
		{
			cout << text(rand() % 2 + 12) << endl;;
		}
		if (extraCharacters(str1) == 0 && sizeInt(str1) == 0 && doubleInsteadOfInt(str1) != 0)
		{
			cout << text(rand() % 2 + 14) << endl;
		}
		cout << text(7) << endl;
		return false;
	}
	else
	{
		cout << text(11) << endl;
		return true;
	}
		/*
	if (errorCode != 0)
	{

		cout << text(0) << endl;
		if (errorCode == 1)
		{
			cout << text(rand() % 2 + 1) << endl;
			cout << text(rand() % 2 + 3) << endl;
		}
		if (errorCode == 2)
		{
			cout << text(rand() % 2 + 1) << endl;
			cout << text(rand() % 2 + 5) << endl;
		}
		if (errorCode == 3)
		{
			cout << text(rand() % 2 + 1) << endl;
			cout << text(rand() % 2 + 5) << endl;
		}
		cout << text(7) << endl;

	}
	*/
}
void summ(string& str1, string& str2)
{
	if (resolveError(str1, str2))
	{
		long long number_int = readInt(str1);
		double number_double = readDouble(str2);
		cout << number_int << endl;
		cout << number_double << endl;
		double result = number_int * 1.0 + number_double;
		cout << result << endl;
		cout << endl;
	}
}

int main()
{
	string str1;
	string str2;
	setlocale(LC_ALL, "Russian");
	int choice = 0;
	do
		{	
			cout << text(8) << endl;
			getline(cin, str1);
			trim(str1);
			cout << text(9) << endl;
			getline(cin, str2);
			trim(str2);
			summ(str1, str2);
			cout << text(10) << endl;
			cin >> choice;
			getline(cin, str1);
			system("cls");
		} while (choice != 0);
}