#include<iostream>
#include<math.h>

using namespace std;

void printBits(short s)
{
	int k = 0;
	int bitlength = sizeof(s) * 8;
	for (int i = 0; i < bitlength; ++i)
	{
		++k;
		unsigned short bit = s;
		bit = bit << i;
		bit = bit >> (bitlength - 1);
		cout << bit;
		if (k % 8 == 0) 
		{
			cout << " ";
		}
	}
	cout << endl;
}

void printBits(long l)
{
	int k = 0;
	int bitlength = sizeof(l) * 8;
	for (int i = 0; i < bitlength; ++i)
	{
		++k;
		unsigned long bit = l;
		bit = bit << i;
		bit = bit >> (bitlength - 1);
		cout << bit;
		if (k % 8 == 0) 
		{
			cout << " ";
		}
	}
	cout << endl;
}

void printBits(long long ll)
{
	int k = 0;
	int bitlength = sizeof(ll) * 8;
	for (int i = 0; i < bitlength; ++i)
	{
		++k;
		unsigned long long bit = ll;
		bit = bit << i;
		bit = bit >> (bitlength - 1);
		cout << bit;
		if (k % 8 == 0) 
		{
			cout << " ";
		}
	}
	cout << endl;
}
int number(int s) 
{
	int k = 0;
	while (s >= 2) 
	{
		k++;
		s = s / 2;
	}
	return k;
}
void binaryI(int s, int n, int j) 
{
	int k = 0;
	int* bit = new int[n] { 0 };
	while (s >= 2) 
	{
		k++;
		bit[k - 1] = s % 2;
		s = s / 2;
	}
	bit[k] = s % 2;
	for (int i = k - j; i >= 0; --i) 
	{
		cout << bit[i];
	}
}
void binaryF(double d, int k, int n) 
{
	double d1 = d - (int)d;
	for (int i = k + 1; i <= n; ++i) 
	{
		if (d1 > 0)
		{
			d1 *= 2;
			cout << (int)(d1);
			d1 = d1 - (int)d1;
		}
		else cout << 0;
	}
}

void printBits(double d)
{
	if (d > 0)
	{
		cout << "0 ";
	}
	else
	{
		cout << "1 ";
		d *= (-1);
	}
	int k = number(int(d));
	binaryI(k + 1023, 11, 0);
	cout << " ";
	binaryI(int(d), 52, 1);
	binaryF(d, k, 52);
}

void printBits(float f)
{
	if (f > 0)
	{
		cout << "0 ";
	}
	else
	{
		cout << "1 ";
		f *= (-1);
	}
	int k = number(int(f));
	binaryI(k + 127, 8, 0);
	cout << " ";
	binaryI(int(f), 23, 1);
	binaryF(f, k, 52);
}

void printBits(long double f) 
{
	printBits((double)f);
}

int main()
{
	short s;
	long l;
	long long ll;
	double d;
	float f;
	long double ld;
	
	cin >> s;
	printBits(s);
	cin >> l;
	printBits(l);
	cin >> ll;
	printBits(ll);
	cin >> d;
	printBits(d);
	cin >> f;
	printBits(f);
	cin >> ld;
	printBits(ld);
	/*
	cout << "int " << sizeof(int) << endl;
	cout << "long " << sizeof(long) << endl;
	cout << "long long " << sizeof(long long) << endl;
	cout << "short " << sizeof(short) << endl;
	cout << "double " << sizeof(double) << endl;
	cout << "long double " << sizeof(long double) << endl;
	cout << "float " << sizeof(float) << endl;
	*/

	return 0;
}