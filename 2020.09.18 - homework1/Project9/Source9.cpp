#include<iostream>
using namespace std;
int main()
{
	int x, n;
	cin >> n;
	x = 1;
	x = -(x << n);
	x = ~x;
	cout << x << endl;
	return 0;
}