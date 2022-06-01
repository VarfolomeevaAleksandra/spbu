#include<iostream>
#include<vector>
#include<random>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;

int object; // код товара
bool flag = false; // true -- склад заполнен, false -- склад пуст
bool work1 = true;
bool work2 = true;
vector<int> v1;
vector<int> v2;
// v1 -- производство, v2 – потребление

mt19937 mt;
uniform_int_distribution<int> r(0, 1000);
mutex m;



void factory()
{
	while (work1)
	{
		if (flag)
		{
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
		}
	}
}

void consumer()
{
	while (work2)
	{
		if (!flag)
		{
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{

			v2.push_back(object);
			flag = false;
		}
	}
}

void check_all()
{
	thread t1(factory);
	thread t2(factory);
	thread t3(consumer);
	thread t4(consumer);
	thread t5(consumer);
	this_thread::sleep_for(1s);
	work1 = false;
	t1.join();
	t2.join();
	work2 = false;
	t3.join();
	t4.join();
	t5.join();

	cout << "v1 = ";
	for (int i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl << "v2 = ";
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << " ";
	}

}

void factory_m()
{
	while (work1)
	{
		m.lock();
		if (flag)
		{
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
			m.unlock();
		}
	}
}

void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (!flag)
		{
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			v2.push_back(object);
			flag = false;
			m.unlock();
		}
	}
}

void check_all_m()
{
	thread t1(factory_m);
	thread t2(factory_m);
	thread t3(consumer_m);
	thread t4(consumer_m);
	thread t5(consumer_m);
	this_thread::sleep_for(1s);
	work1 = false;
	t1.join();
	t2.join();
	work2 = false;
	t3.join();
	t4.join();
	t5.join();

	cout << "v1 = ";
	for (int i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << " ";
	}
	cout << endl << "v2 = ";
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << " ";
	}
}

int main()
{
	//check_all();
	check_all_m();

	return EXIT_SUCCESS;
}