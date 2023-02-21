#include<iostream>
using namespace std;
int main()
{
	int x, i, k;
	cin >> x;
	k = 0;
	for (i = 1; i <= sqrt(x); ++i)
	{
		if (x % i == 0)
		{
			if (i * i != x)
				k = k + 2;
			else
			{
				++k;
			}
		}
	}
	cout << k << endl;
	return 0;
}