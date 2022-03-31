#include<iostream>
#include<map>
#include<set>

using namespace std;

void function_1()
{
	int x;
	map <int, int> m;
	while (cin >> x)
	{
		if (m.count(x)) ++m[x];
		else (m[x] = 1);
	}
	for (auto x : m)
		cout << x.first << " -> " << x.second << endl;
}

map <int, int> function_2()
{
	map <int, int> m;
	int n;
	cin >> n;
	int f;
	int s;
	for (int i = 0; i < n; ++i)
	{
		cin >> f;
		cin >> s;
		m[f] = s;
	}
	return m;
}

void function_3()
{
	map<int, int> m;
	m = function_2();
	int x;
	while (cin >> x)
	{
		if (m.count(x))
		{
			//map <int, int>::iterator i;
			cout << m[x] << endl;
		}
		else cout << x << endl;
	}
}

template <class T1, class T2>
map <T1, T2> function_4(map<T1, T2> m1, map<T1, T2> m2)
{
	map <T1, T2> result;
	for (auto i = m1.begin(); i != m1.end(); i++)
	{
		result[i->first] = m1[i->first] + m2[i->first];
	}
	return result;
}

template <class T1, class T2, class T3>
map <T1, T3> function_5(map <T1, T2> m1, map <T2, T3> m2)
{
	map <T1, T3> result;
	for (auto i = m1.begin(); i != m1.end(); i++)
	{
		result[i->first] = m2[m1[i->first]];
	}
	return result;
}
int main()
{
	map <int, int> m1;
	map <int, int> m2;
	map <int, int> m;
	m = function_4(m1, m2);
	m = function_5(m1, m2);
	return EXIT_SUCCESS;
}