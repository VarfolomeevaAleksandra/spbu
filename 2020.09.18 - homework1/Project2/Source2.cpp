#include<iostream>;
using namespace std;
int main()
{
	int a, b, i;
	cin >> a >> b; //вначале делимое, потом делитель
	for (i = 1; i <= a; ++i)
	{
		if ((b * i) >= a)
		{
			break;
		}
	}
	if ((b * i) == a)
	{
		cout << i << endl;
	}
	else
	{
	cout << i - 1 << endl;
	}
	return 0;
}