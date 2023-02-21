#include<iostream>

using namespace std;


void print(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%3d ", data[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}
void one(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			data[i][j] = i + j;
		}
	}
	cout << "1." << endl;
	print(data, n);
}

void two(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			data[i][j] = 2*n - 1 - i - j;
		}
	}
	cout << "2." << endl;
	print(data, n);
}

void three(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			data[i][j] = j + 1;
		}
	}
	cout << "3." << endl;
	print(data, n);
}

void four(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == 0) data[i][j] = i + 1;
			else if (i > j) data[i][j] = data[i - 1][j];
			else data[i][j] = i + 1;
		}
	}
	cout << "4." << endl;
	print(data, n);
}
void five(int** data, int n)
{
	int i = 1;
	int j = 1;
	for (int k = 0; k < n; ++k)
	{
		data[k][0] = k + 1;
	}
	for (int k = 1; k < n; ++k)
	{
		data[n - 1][k] = k + n;
	}
	for (int k = n - 2; k >= 0; --k)
	{
		data[k][n - 1] = data[k + 1][n - 1] + 1;
	}
	for (int k = n - 2; k > 0; --k)
	{
		data[0][k] = data[0][k + 1] + 1;
	}
	int c = data[0][1];
	while (c < n * n - 1)
	{
		if ((data[i][j - 1] > 0) & (i < n - 1) & (data[i + 1][j] == 0))
		{
			data[i][j] = c + 1;
			++c;
			++i;
		}
		else if ((data[i + 1][j] > 0) & (j < n - 1) & (data[i][j + 1] == 0))
		{
			data[i][j] = c + 1;
			++c;
			++j;
		}
		else if ((data[i][j + 1] > 0) & (i > 1) & (data[i - 1][j] == 0))
		{
			data[i][j] = c + 1;
			++c;
			--i;
		}
		else if ((data[i - 1][j] > 0) & (j > 1) & (data[i][j - 1] == 0))
		{
			data[i][j] = c + 1;
			++c;
			--j;
		}
	}
	if (n % 2 == 1)
	{
		data[n / 2][n / 2] = n * n;
	}
	else
	{
		data[n / 2 - 1][n / 2] = n * n;
	}
	cout << "5." << endl;
	print(data, n);
}

void free(int** data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		delete[] data[i];
	}
	delete[] data;
}

int main()
{
	int n;
	cin >> n;
	int** data = new int* [n] { 0 };
	for (int i = 0; i < n; ++i)
	{
		data[i] = new int[n] { 0 };
	}
	
	one(data, n);
	two(data, n);
	three(data, n);
	four(data, n);
	five(data, n);
	free(data, n);
}