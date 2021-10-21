#include<iostream>
#include<cstdlib>


using namespace std;

struct Node
{
	int data;
	Node* next;
	Node (int d = 0, Node * n = nullptr): data(d), next(n) {}
};

Node* copy(Node* x);

struct List
{
	Node* head;
	List() { head = nullptr; }

	~List()
	{
		Node* t = head;
		while (t != nullptr)
		{
			Node* n = t;
			t = t->next;
			delete n;
		}
	}

	List(const List& l)
	{
		/*head = nullptr;

		Node* temp = l.head;
		while (temp != nullptr)
		{
			add_last(temp->data);
			temp = temp->next;
		}*/
		head = copy(l.head);
	}

	void del()
	{
		Node* t = head;
		while (t != nullptr)
		{
			Node* n = t;
			t = t->next;
			delete n;
		}
	}
	Node* prelast()
	{
		Node* p = head;
		Node* t = p->next->next;
		while (t != nullptr)
		{
			t = t->next;
			p = p->next;
		}
		return p;
	}

	Node* last()
	{
		Node* p = head;
		if (p != nullptr)
		{
			Node* t = p->next;
			while (t != nullptr)
			{
				t = t->next;
				p = p->next;
			}
		}
		return p;
	}

	Node* get_ptr(int n)
	{
		Node* p = head;
		for (int i = 0; i < n - 1; ++i)
		{
			p = p->next;
		}
		return p;
	}

	void add_after_first(int d)
	{
		Node* p = head->next;
		head->next = new Node(d, p);
	}

	void add_last(int d)
	{
		Node* p = last();
		if (p != nullptr)
		{
			p->next = new Node(d);
		}
		else 
		{
			head = new Node(d);
		}
		
	}

	void del_last()
	{
		Node* p = head;
		while (p->next->next != nullptr)
		{
			p = p->next;
		}
		delete p->next;
		p->next = nullptr;
	}

	void add_first(int d)
	{
		Node* t;
		t = new Node(d, head);
		head = t;
	}

	void print()
	{
		Node* p = head;
		while (p != nullptr)
		{
			cout << p->data << "\t";
			p = p->next;
		}
		cout << endl;
	}

	void insept(int index, int element)
	{
		if (index == 0)
		{
			add_first(element);
		}
		Node* temp = head;
		for (int i = 0; i < index - 1; ++i)
		{
			temp = temp->next;
		}
		temp->next = new Node(element, temp->next);
	}

	void delp(int index)
	{
		if (index == 0)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
		else
		{ 
			Node* p = head;
			for (int i = 0; i < index - 1; ++i)
			{
				p = p->next;
			}
			Node* t = p->next;
			p->next = p->next->next;
			delete t;
		}
		
	}
List &operator=(const List& l)
{
	if (&l != this)
	{
		Node* temp = head;
		while (temp != nullptr)
		{
			Node* node = temp;
			temp = temp->next;
			delete node;

		}
		temp = l.head;
		while (temp != nullptr)
		{
			add_last(temp->data);
			temp = temp->next;
		}
	}
	return *this;
}
};

Node* copy(Node* x)
{
	if (x == nullptr)
		return nullptr;
	Node* y = new Node(x->data, copy(x->next));
	return y;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	List l;
	l.add_first(6);
	l.add_first(5);
	l.add_first(4);
	l.add_first(3);
	l.add_first(2);
	l.add_first(1);
	l.print();
	cout << "последний элемент - " << l.last()->data << endl;
	cout << "предпоследний элемент - " << l.prelast()->data << endl;
	cout << "третий элемент - " << l.get_ptr(2)->data << endl;
	l.add_after_first(10);
	l.print();
	l.add_last(10);
	l.print();
	l.del_last();
	l.print();
	l.insept(2, 20);
	l.print();
	l.delp(2);
	l.print();
	List l2(l);
	l2.print();
	List m;
	m = l;
	m.print();
}