#include<iostream>
#include<set>

using namespace std;

void function_1()
{
	int x;
	set <int> s;
	while (cin >> x)
	{
		s.insert(x);
	}
	set <int>::iterator i;
	for (i = s.begin(); i != s.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void function_2()
{
	set<int> s;
	set<int> s1;
	int x;
	while (cin >> x)
	{
		if (s.count(x)) s1.insert(x);
		s.insert(x);
	}
	set <int>::iterator i;
	for (i = s1.begin(); i != s1.end(); ++i)
		cout << *i << " ";
	cout << endl;
}

void function_3()
{
	int x;
	set<int> s2;
	set<int> s;
	set<int> s1;
	while (cin >> x)
	{
		if (s1.count(x)) s2.insert(x);
		if (s.count(x)) s1.insert(x);
		s.insert(x);
	}
	set <int>::iterator i;
	for (i = s1.begin(); i != s1.end(); ++i)
	{
		if (s1.count(*i) && !s2.count(*i))
		{
			cout << *i << " ";
		}
	}
		
	cout << endl;
}

template <typename T>
set <T> function_4(set <T> v, set <T> w) {
	set <T> result;
	for (int x : v)
	{
		result.insert(x);
	}
	for (int x : w)
	{
		result.insert(x);
	}
	return result;
}


int main()
{
	set <int> s;
	//function_1();
	//function_2();
	//function_3();
	set<int> s1;
	set<int> s2;
	int x;
	int k = 0;

	while (cin >> x)
	{
		if (k % 2 == 1)
		{
			s1.insert(x);
		}
		else
		{
			s2.insert(x);
		}
		++k;
	}

	s = function_4(s1, s2);
	set <int>::iterator i;
	for (i = s.begin(); i != s.end(); ++i)
		cout << *i << " ";
	cout << endl;
	
	return EXIT_SUCCESS;

}