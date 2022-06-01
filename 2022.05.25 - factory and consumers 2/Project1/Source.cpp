#include <iostream>
#include <vector>
#include<random>
#include<thread>
#include<chrono>
#include<mutex>
#include<queue>
#include <condition_variable>

using namespace std;

queue <int >object; // код товара
queue <bool> flag; // true -- склад заполнен, false -- склад пуст
bool work1 = true;
bool work2 = true;
vector<int> v1;
vector<int> v2;
// v1 -- производство, v2 – потребление

mt19937 mt;
uniform_int_distribution<int> r(0, 1000);
mutex m;
condition_variable cv;

//void factory();
//void consumer();
//void check_all();
//
//void factory_m();
//void consumer_m();
//void check_all_m();
//
//bool f();
//void factory_cv();
//void consumer_cv();
//void check_all_cv();






void factory()
{
	while (work1)
	{
		if (!object.empty())
		{
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			object.push(r(mt));
			v1.push_back(object.front());
			flag.push(true);
		}
	}
}

void consumer()
{
	while (work2)
	{
		if (object.empty())
		{
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			v2.push_back(object.front());
			object.pop();
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
		if (!object.empty())
		{
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			object.push(r(mt));
			v1.push_back(object.front());
			m.unlock();
		}
	}
}

void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (object.empty())
		{
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			v2.push_back(object.front());
			object.pop();
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

bool f()
{
	return !object.empty();
}

void factory_cv()
{
	while (work1)
	{
		m.lock();
		if (!object.empty())
		{
			m.unlock();
			this_thread::sleep_for(chrono::milliseconds(r(mt)));
		}
		else
		{
			object.push(r(mt));
			v1.push_back(object.front());
			cv.notify_one();
			m.unlock();
		}
	}
}

void consumer_cv()
{
	while (work2)
	{
		this_thread::sleep_for(chrono::milliseconds(r(mt)));

		unique_lock<mutex> l(m);
		cv.wait(l, f);
		if (!object.empty())
		{
			break;
		}
		v2.push_back(object.front());
		object.pop();
	}
}

void check_all_cv()
{
	thread t1(factory_cv);
	thread t2(factory_cv);
	thread t3(consumer_cv);
	thread t4(consumer_cv);
	thread t5(consumer_cv);
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
	flag.push(false);
	//check_all();
	//check_all_m();
	check_all_cv();

	return EXIT_SUCCESS;
}