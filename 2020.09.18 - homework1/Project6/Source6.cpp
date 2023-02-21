#include<iostream>
using namespace std;
int main()
{
	int x, i, k;
	k = 1;
	cin >> x;
	for (i = 2; i <= x; ++i)
		k = k * i;
	cout << k << endl;
	return 0;
}
