#include<iostream>
#include<fstream>
#include<clocale>

using namespace std;

bool isRussianVowel(char symbol)
{
	return symbol == 'А' || symbol == 'а' ||
		symbol == 'Е' || symbol == 'е' ||
		symbol == 'Ё' || symbol == 'ё' ||
		symbol == 'И' || symbol == 'и' ||
		symbol == 'О' || symbol == 'о' ||
		symbol == 'У' || symbol == 'у' ||
		symbol == 'Ы' || symbol == 'ы' ||
		symbol == 'Э' || symbol == 'э' ||
		symbol == 'Ю' || symbol == 'ю' ||
		symbol == 'Я' || symbol == 'я';
}
bool isEnglishVowel(char symbol)
{
	return symbol == 'A' || symbol == 'a' ||
		symbol == 'E' || symbol == 'e' ||
		symbol == 'I' || symbol == 'i' ||
		symbol == 'O' || symbol == 'o' ||
		symbol == 'U' || symbol == 'u' ||
		symbol == 'Y' || symbol == 'y';
}

int main()
{
	setlocale(LC_ALL, "Russian");
	const int n = 32;
	char a[n] = { "впишите здесь нужный набор букв" };
	for (int i = 0; i < n; cout << a[i] << (i == n - 1 ? '\n' : ' '), ++i);

	fstream fbin;
	char b = 0;

	fbin.open("in.bin", ios::binary | ios::in | ios::out);
	while (!fbin.eof())
	{
		fbin.read((char*)&b, sizeof(char));
		cout << "read : " << b;
		if (isRussianVowel(b))
		{
			fbin.seekg(-(int)sizeof(char), ios::cur);
			b = '#';
			fbin.write((char*)&b, sizeof(char));
			cout << " changed to #";
			fbin.seekg(fbin.tellg(), ios::beg);
		}
		else if (isEnglishVowel(b))
		{
			fbin.seekg(-(int)sizeof(char), ios::cur);
			b = '#';
			fbin.write((char*)&b, sizeof(char));
			cout << " changed to #";
			fbin.seekg(fbin.tellg(), ios::beg);
		}
		cout << endl;
	}
	fbin.close();

	fbin.open("in.bin", ios::in);
	fbin.read((char*)&a, sizeof(a));
	for (int i = 0; i < n; cout << a[i] << (i == n - 1 ? '\n' : ' '), ++i);
	fbin.close();



	return 0;
}