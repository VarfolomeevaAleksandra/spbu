#include <iostream>
#include <future>
#include <chrono>
#include <vector>
#include <cmath>
using namespace std;
using namespace std::chrono;


int block_size(int threads, int n)
{
	return n / threads + (n % threads ? 1 : 0);
}

double f(double x)
{
	return 1 / (1 + x * x);
}

double pi(int n, int a, int b)
{
	double sum = 0;
	for (int i = a; i <= b; ++i)
	{
		sum += f((2.0 * i - 1) / (2.0 * n));
	}
	return sum;
}

void MultiThread_pi(int threads, int n)
{
	double p = 0;
	vector<future <double>> pi_result(threads);
	int bl_size = block_size(threads, n);
	int first_index = 0;
	int i = 0;
	while (first_index < n)
	{
		pi_result[i] = async(pi, n, first_index, first_index + bl_size);
		first_index += bl_size;
		i++;
	}

	for (int j = 0; j < i; ++j)
	{
		p += pi_result[j].get();
	}

	p = p * 4 / n;
	cout << "pi = " << p << endl;
}


int Find(string what, string s, int a, int b)
{
	int n = 0;
	//string s1 = "";
	//s1 = s.substr(a, b - a);
	//n = s1.find(what);
	for (int i = a; i < b; ++i)
	{

		if (what[0] == s[i])
		{
			++n;

			for (int j = 1; j < what.size() && i + j < b; ++j)
			{
				if (what[j] != s[j + i])
				{
					--n;
					break;
				}
			}
		}
	}
	return n;
}

int Find_thread(string what, string s, int threads, int a)
{
	int b = a + block_size(threads, s.size());
	/*if (s.find_first_of(what[0], b - what.size() + 1) != -1 && b + what.size() < s.size())
	{
		b += what.size();
	}*/
	cout << a << " " << b << endl;
	int n = 0;
	n = Find(what, s, a, b);
	return n;
}

int MultiThreadFind(string what, string s, int threads)
{
	int n = 0;
	vector<future <int>> count(threads);
	int bl_size = block_size(threads, s.size());
	int first_index = 0;
	int i = 1;
	count[0] = async(Find_thread, what, s, threads, first_index);
	first_index += bl_size;
	while (first_index < s.size())
	{
		count[i] = async(Find_thread, what, s, threads, first_index);
		first_index += bl_size;
		++i;
	}

	for (int j = 0; j < i; ++j)
	{
		n += count[j].get();
	}
	return n;
}

int main()
{
	//auto t1 = steady_clock::now();
	//MultiThread_pi(4, 1000000);
	//auto t2 = steady_clock::now();
	//cout << duration_cast <seconds> (t2-t1).count();
	string s = "11123658991112365891114456332111445611236914562111478962khghjnbc111bvghb11563288nnnn1nnn111";
	string what = "111";
	int n = MultiThreadFind(what, s, 4);
	cout << n;
}