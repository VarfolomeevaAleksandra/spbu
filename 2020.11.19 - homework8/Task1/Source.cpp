#include<iostream>
#include"LinkedList.h"

using namespace std;

int main()
{
	LinkedList list1;
	LinkedList list2;
	LinkedList list3;

	list2 += 1; list3 += 1; list3 += 2; list3 += 3; list3 += 4;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	
	list1.addToHead(100); list1.addToTail(110);
	list2.addToHead(100); list2.addToTail(110);
	list3.addToHead(100); list3.addToTail(110);
	cout << "addToHead(100), addToTail(110)" << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	
	// возвращение к изначальному виду 
	list1.extractHead(); list1.extractTail();
	list2.extractHead(); list2.extractTail();
	list3.extractHead(); list3.extractTail();


	list1.extractHead();
	list2.extractHead();
	list3.extractHead();
	cout << "extractHead()" << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду 
	list2.addToHead(1); 
	list3.addToHead(1); 
	
	list1.extractTail();
	list2.extractTail();
	list3.extractTail();
	cout << "extractTail()" << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду - тут перестает работать addToTail
	list2.addToTail(1);
	list3.addToTail(4);

	
	list1.extract(0);
	list2.extract(0);
	list3.extract(2);
	cout << " list1.extract(0); list2.extract(0); list3.extract(2)" << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду
	list2.add(0, 1);
	list3.add(2, 3);

	list1.add(0, 1);
	list2.add(0, 2);
	list3.add(2, 6);

	cout << "list1.add(0, 1); list2.add(0, 2); list3.add(2, 6) " << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду
	list1.extractHead();
	list2.extractHead();
	list3.extract(2);


	cout << " list2.get(0), list3.get(2)" << endl;
	cout << list2.get(0) << endl;
	cout << list3.get(2) << endl;
	cout << endl;
	
	list2.set(0, 2);
	list3.set(2, 6);
	cout << " list2.set(0, 2); list3.set(2, 6) " << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду
	list2.set(0, 1);
	list3.set(2, 3);

	cout << "list1[0],list2[0], list3[1]" << endl;
	cout << list1[0] << endl;
	cout << list2[0] << endl;
	cout << list3[1] << endl;
	cout << endl;

	// возвращение к изначальному виду
	list1.extract(0);

	list2 -= 0;
	list3 -= 1;
	cout << " list2 -= 0; list3 -= 1; " << endl;
	cout << list1 << endl;
	cout << list2 << endl;
	cout << list3 << endl;
	cout << endl;

	// возвращение к изначальному виду
	list2.add(0, 1);
	list3.add(1, 2);

	
	cout << " list2.indexOf(1); list3.indexOf(2); " << endl;
	cout << list2.indexOf(1) << endl;
	cout << list3.indexOf(2) << endl;
	cout << endl;

	cout << "list1.contains(9), list2.contains(1), list2.contains(9), list3.contains(2), list3.contains(9)," << endl;
	cout << (list1.contains(9) == true ? "yes" : "no") << endl;
	cout << (list2.contains(1) == true ? "yes" : "no") << endl;
	cout << (list2.contains(9) == true ? "yes" : "no") << endl;
	cout << (list3.contains(2) == true ? "yes" : "no") << endl;
	cout << (list3.contains(9) == true ? "yes" : "no") << endl;

	list3.swap(0, 1);
	cout << "list3.swap(0, 1)" << endl;
	cout << list3 << endl;



}

