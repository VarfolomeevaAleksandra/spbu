#include<iostream>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

void enlarge(vector<double>& v)
{
	vector<double> ::iterator k = v.begin() + 1;
	unsigned int i = 1;
	while (i < v.size())
	{
		k = v.insert(k, ((v[i - 1] + v[i]) * 0.5));
		i += 2;
		k += 2;
	}
}

void del(vector<double>& v)
{
	vector <double> f;
	for (int i = 1; i < v.size(); i += 2) 
	{
		f.push_back(v[i]);
	}
	v = f;
}

void print(vector<double> v)
{
	vector <double > ::iterator i;
	for (i = v.begin(); i != v.end(); i++)
		cout << *i << ' ';
	cout << endl;
}

vector<double> contact(vector<double> v, vector<double> v1)
{
	vector<double> r(v.size()+v1.size());
	vector<double>::iterator i;
	copy(v.begin(), v.end(), r.begin());
	copy(v1.begin(), v1.end(), r.begin()+v.size());
	return r;
}

vector<double> repeat(vector<double> v, int n)
{
	vector<double> r(n * v.size());
	vector<double>::iterator i;
	for (int i = 0; i < n; i++)
	{
		copy(v.begin(), v.end(), r.begin() + (i * v.size()));
	}
	return r;
}

int main()
{
	vector<double> v;
	double x;
	do
	{
		cout << "Enter data";
		cin >> x;
		v.push_back(x);
	} while (x != 0);
	enlarge(v);
	print(v);
	del(v);
	print(v);
	vector<double> v1{ 1,2,3,4,5,6,7,8,9 };
	int ar[9]; 
	copy(v1.begin(), v1.end(), ar);
	for (int i = 0; i < 9; i++)
	{
		cout << ar[i] << ' ';
	}
	cout << endl;
	print(contact(v, v1));
	print(repeat(v1, 3));

}