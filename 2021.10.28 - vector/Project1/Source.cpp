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
	vector<double> r(v.size() + v1.size());
	vector<double>::iterator i;
	copy(v.begin(), v.end(), r.begin());
	copy(v1.begin(), v1.end(), r.begin() + v.size());
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

vector<double>::iterator find_second(vector<double> v, int n)
{
	vector<double>::iterator i;
	i = find(find(v.begin(), v.end(), n) + 1, v.end(), n);
	return i;
}

vector<double>::iterator find_last(vector<double> v, int n)
{
	vector<double>::iterator i = v.begin();
	vector<double>::iterator k;
	if (*i == n) k = i;
	while (i != v.end())
	{
		i = find(i + 1, v.end(), n);
		if (i != v.end()) k = i;
	}
	return k;
}

bool subseq(vector<double> v, vector<double> v1)
{
	vector<double>::iterator i;
	vector<double>::iterator j = v.begin();
	int k = 0;
	if (v.begin() == v1.begin()) k = 1;
	for (i = v1.begin() + k; i != v1.end(); i++)
	{
		j = find(j + 1, v.end(), *i);
		if (j == v.end()) return false;
	}
	return true;
}

int find_index(vector<double> v, vector<double>::iterator i)
{
	int index = 0;
	vector<double>::iterator j;
	for (j = v.begin(); j != i; ++j)
	{
		index++;
	}
	return index;
}

void index(vector<double> v, double& x, double& i, double& j)
{
	vector<double>::iterator k;
	vector<double>::iterator n;
	int index = 0;
	k = lower_bound(v.begin(), v.end(), x);
	if (*k == x)
	{
		i = find_index(v, k);
		i = j;
	}
	else
	{
		while (*k == *(k - 1)) --k;
		i = find_index(v, k - 1);
		j = find_index(v, k);
	}
	cout << "до - " << i << "после - " << j << endl;
}

int main()
{
	vector<double> v;
	vector<double>::iterator i;
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
	vector<double> v1{ 1,2,3 };
	int ar[9];
	copy(v1.begin(), v1.end(), ar);
	for (int i = 0; i < 9; i++)
	{
		cout << ar[i] << ' ';
	}
	cout << endl;
	print(contact(v, v1));
	print(repeat(v1, 3));
	if (find_second(v, 1) != v.end())
	{
		cout << *find_second(v, 1) << endl;
	}

	if (find_last(v, 2) != v.end())
	{
		cout << *find_last(v, 2) << endl;
	}

	if (subseq(v, v1)) cout << "yes";
	else cout << "no";
	sort(v.begin(), v.end());
	double y = 3;
	double a = 5;
	double b = 5;
	index(v, y, a, b);
}