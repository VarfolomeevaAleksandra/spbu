#include<iostream>
using namespace std;
int main()
{
	int x, i, j, k;
	cin >> x;
	k = 0;
	for (i = 1; i <= x; ++i)
	{
		for (j = 1; j <= i; ++j)
		{
			if ((i % j) == 0)
				k = ++k;
		}
		if (k == 2)
			cout << i << endl;
		k = 0;

	}
	return 0;
}
