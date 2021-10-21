#include<iostream>
#include<cstdlib>

using namespace std;

struct DNode
{
	int data;
	DNode* next;
	DNode* prev;
	DNode(int d = 0, DNode* n = nullptr, DNode* p = nullptr) :
		data(d), next(n), prev(p) {}
};


DNode* copy(DNode* x);

struct DList
{
	DNode* head, * tail;
	DList() { head = nullptr; tail = nullptr; }

	~DList()
	{
		del();
	}

	DList(const DList& l)
	{
		head = copy(l.head);
		DNode* t = head;
		while (t->next != nullptr)
		{
			t = t->next;
		}
		tail = t;
	}

	DList& operator=(const DList& l)
	{
		if (&l != this)
		{
			del();
			head = copy(l.head);
			DNode* t = head;
			while (t->next != nullptr)
				{
					t = t->next;
				}
			tail = t;
		}
		return* this;
	}
	DNode* last()
	{
		return tail;
	}

	DNode* prelast()
	{
		return tail->prev;
	}

	void del()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			cout << endl;
		}
		else
		{
			DNode* t = head;
			while (t != nullptr)
			{
				t = t->next;
				del_first();
			}
			/*DNode* t = head;
			while (t != nullptr)
			{
				DNode* p = t;
				t = t->next;
				t->prev = nullptr;
				delete p;
				
			}*/
		}
	}

	void add_first(int d)
	{
		DNode* t;
		t = new DNode(d, head, nullptr);
		if (head == nullptr)
		{
			head = tail = t;
		}
		else
		{
			head->prev = t;
			head = t;
		}
	}

	void print_all()
	{
		DNode* p = head;
		while (p != nullptr)
		{
			cout << p->data << " (" << p << ")" << '\t';

			p = p->next;
		}
		cout << endl;
	}
	void print()
	{
		DNode* t;
		t = head;
		while (t != nullptr)
		{
			cout << t->data << "\t";
			t = t->next;
		}
		cout << endl;
	}
	void print_reverse()
	{
		DNode* t;
		t = tail;
		while (t != nullptr)
		{
			cout << t->data << "\t";
			t = t->prev;
		}
		cout << endl;
	}
	void Print()
	{
		print();
		print_reverse();
		cout << endl;
	}

	void add_last(int d)
	{
		if (head == nullptr)
		{
			add_first(d);
		}
		DNode* t;
		t = tail;
		t->next = new DNode(d, nullptr, t);
		tail = t->next;
	}
	void add_after_first(int d)
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			cout << endl;
			return;
		}
		if (head->next == nullptr)
		{
			add_last(d);
			return;
		}
		else
		{
			DNode* t = head->next;
			t = new DNode(d, t, head);
			t->next->prev = t;
			head->next = t;
			return;
		}
	}

	void del_first()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			cout << endl;
			return;
		}
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			return;
		}
		else
		{
			DNode* t;
			t = head;
			head = head->next;
			head->prev = nullptr;
			delete t;
			return;
		}
	}

	void del_last()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			cout << endl;
			return;
		}
		if (head->next == nullptr)
		{
			delete head;
			head = tail = nullptr;
			return;
		}
		else
		{
			DNode* t;
			t = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete t;
			return;
		}
	}
	void del_second()
	{
		if (head == nullptr)
		{
			cout << "List is empty";
			cout << endl;
			return;
		}
		if (head->next == nullptr)
		{
			cout << "Only one element in the List";
			cout << endl;
			return;
		}
		if (head->next->next == nullptr)
		{
			del_last();
			return;
		}
		else
		{
			DNode* t;
			t = head->next;
			head->next = t->next;
			t->next->prev = head;
			delete t;
			return;
		}
	}

	void insertp(int n, int d)
	{
		if (n == 0)
		{
			add_first(d);
		}
		else
		{
			DNode* t = head;
			for (int i = 0; i < n; ++i)
			{
				t = t->next;
			}
			t = new DNode(d, t, t->prev);
			t->next->prev = t;
			t->prev->next = t;
		}
	}
	void delp(int n)
	{
		if (n == 0)
		{
			del_first();
		}
		else
		{
			DNode* t = head;
			for (int i = 0; i < n; ++i)
			{
				t = t->next;
			}
			DNode* p = t;
			t->prev->next = t->next;
			t->next->prev = t->prev;
			delete p;
		}
	}
	int length()
	{
		DNode* t = head;
		int n = 0;
		while (t != nullptr)
		{
			t = t->next;
			++n;
		}
		return n;
	}

	
	/*bool IF(DNode* p)
	{
		if (((p->data) % 2) == 0) return true;
	}
	void remove_if()
	{
		DNode* p = head;
		for (int i = 0; i < length(); ++i)
		{
			if (IF(p)) delp(i-1);
			p = p->next;
		}
	}*/
};

DNode* copy(DNode* x)
{
	if (x == nullptr)
		return nullptr;
	DNode* y = new DNode(x->data, copy(x->next));
	DNode* t = y;
	if (t->next != nullptr)
	{
		t->next->prev = t;
		t = t->next;
	}
	return y;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	DList l;
	l.add_first(7);
	l.add_first(6);
	l.add_first(5);
	l.add_first(4);
	l.add_first(3);
	l.add_first(2);
	l.add_first(1);
	cout << "Список" << endl;
	l.Print();
	cout << "Последний элемент - " << l.last()->data << endl;
	cout << "Предпоследний элемент - " << l.prelast()->data << endl;
	l.add_last(8);
	cout << "Добавить последний элемент 8" << endl;
	l.Print();
	l.add_after_first(10);
	cout << "Добавить второй элемент 10" << endl; 
	l.Print();
	l.del_last();
	cout << "Удалить последний элемент" << endl; 
	l.Print();
	l.del_second();
	cout << "Удалить второй элемент" << endl; 
	l.Print();
	l.insertp(3, 10);
	cout << "Вставить на четвертое место 10" << endl; 
	l.Print();
	l.delp(3);
	cout << "Удалить четвертый элемент" << endl; 
	l.Print();
	cout << "Длина списка - " << l.length() << endl;
	DList m(l);
	cout << "Конструктор копирования" << endl;
	m.Print();
	DList l2;
	l2.add_first(50);
	l2.add_first(40);
	l2.add_first(30);
	l2.add_first(20);
	cout << "Новый список" << endl;
	l2.Print();
	l2 = l;
	cout << "Оператор присваивания" << endl;
	l2.Print();

	return EXIT_SUCCESS;
}
