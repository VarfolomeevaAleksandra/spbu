#include<iostream>
using namespace std;
int main()
{
	int x, y, i, r;
	r = 1;
	cin >> x >> y; // ������� ����� ����� �������
	for (i = 1; i <= y; ++i)
		r = r * x;
	cout << r << endl;
	return 0;

}