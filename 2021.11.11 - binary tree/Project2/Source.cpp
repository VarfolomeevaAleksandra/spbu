#include <iostream>
#include <Stack>

using namespace std;
struct BNode
{
	int data;
	BNode* left, * right;
	BNode(int d, BNode* l = nullptr, BNode* r = nullptr) :
		data(d), left(l), right(r) {}
};

void f_print(BNode* r, int d = 0)
{
	if (r == nullptr) return;
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
		cout << ' ';
	cout << r->data << endl;
	f_print(r->left, d + 3);
}

struct BTree
{
	BNode* root;
	BTree(BNode* p) : root(p) {}
	void print()
	{
		cout << "_____________________________________________" << endl;
		f_print(root);
		cout << "_____________________________________________" << endl;
	}
};

//Домашняя работа 1 - Двоичные деревья

BNode* leftNode(BNode* p)
{
	BNode* k1 = p;
	while (k1->left != nullptr) 
	{
		k1 = k1->left;
	}
	return k1;
}

void delLeftNode(BNode* p)
{
	BNode* k1 = p;
	while (k1->left->left != nullptr) 
	{
		k1 = k1->left;
	}
	if (k1->left->right == nullptr) 
	{
		delete k1->left;
		k1->left = nullptr;
		return;
	}
	else 
	{
		BNode* temp = k1->left->right;
		delete k1->left;
		k1->left = temp;
		return;
	}
}
void addLeft(BNode* p, int data) 
{
	BNode* k1 = p;
	while (k1->left != nullptr) 
	{
		k1 = k1->left;
	}
	BNode* temp = new BNode(data);
	k1->left = temp;
	return;
}
BNode* leftLeave(BNode* p) 
{
	BNode* k = p;
	while (k->left != nullptr && k->right != nullptr) 
	{
		while (k->left != nullptr) 
		{
			k = k->left;
		}
		if (k->right != nullptr) 
		{
			k = k->right;
		}
	}
	return k;
}
void delLeftLeave(BNode* p) 
{
	BNode* k = p;
	BNode* k1 = p;
	while (k->left != nullptr && k->right != nullptr)  
	{
		while (k->left != nullptr) 
		{
			k1 = k;
			k = k->left;
		}
		if (k->right != nullptr) 
		{
			k1 = k;
			k = k->right;
		}
	}
	if (k1->left == k) 
	{
		delete k;
		k1->left = nullptr;
		return;
	}
	else 
	{
		delete k;
		k1->right = nullptr;
	}
}
BNode* secondLeftLeave(BNode* p) 
{
	BNode* k = p;
	BNode* start = p;
	while (k->left != nullptr && k->right != nullptr) 
	{
		while (k->left != nullptr) 
		{
			if (k->right != nullptr) 
			{
				start = k->right;
			}
			k = k->left;
		}
		if (k->right != nullptr) 
		{
			k = k->right;
		}
	}
	return leftLeave(start);
}


//Домашнее задание 2 - Обход дерева

void scale(BNode* p) 
{
	if (p != nullptr) 
	{
		(p->data) *= 3;
		scale(p->left);
		scale(p->right);
	}
}
int sum(BNode* p) 
{
	if (p == nullptr) 
	{
		return 0;
	}
	return p->data + sum(p->left) + sum(p->right);
}
int count_neg(BNode* p) 
{
	if (p == nullptr) 
	{
		return 0;
	}
	return (p->data < 0) ? 1 : 0 + count_neg(p->left) + count_neg(p->right);
}
int height(BNode* p) 
{
	if (p == nullptr) 
	{
		return 0;
	}
	return 1 + max(height(p->left), height(p->right));
}
void reflect(BNode* p) 
{
	if (p != nullptr) 
	{
		swap(p->left, p->right);
		reflect(p->left);
		reflect(p->right);
	}
}
int mult(BNode* p) 
{
	if (p == nullptr) 
	{
		return 1;
	}
	return ((p->left != nullptr && p->right != nullptr) ? p->data : 1) * mult(p->left) * mult(p->right);
}

int eval(BNode* p) 
{
	if (p->left == nullptr && p->right == nullptr) 
	{
		return p->data;
	}
	if (p->data == 1) 
	{
		return eval(p->left) + eval(p->right);
	}
	if (p->data == 2) 
	{
		return eval(p->left) - eval(p->right);
	}
	if (p->data == 3) 
	{
		return eval(p->left) * eval(p->right);
	}
	if (p->data == 4) 
	{
		return eval(p->left) / eval(p->right);
	}
}

template <class T>
BNode* find(T d, BNode* p) 
{
	if (p != nullptr) 
	{
		if (d == p->data) 
		{
			return p;
		}
		find(d, p->left);
		find(d, p->right);
		return nullptr;
	}
}

int min(int minimum, BNode* p) 
{
	if (p != nullptr) 
	{
		if (p->data < minimum) 
		{
			return min(min(p->data, p->left), min(p->data, p->right));
		}
		else {
			return min(min(minimum, p->left), min(minimum, p->right));
		}
	}
	return minimum;
}

// Домашняя работа 3 - Удаление узлов

void f_del(BNode*& p)
{
	if (p == nullptr) return;
	f_del(p->left);
	f_del(p->right);
	p = nullptr;
	delete p;
}

void del0(BNode*& p)
{
	if (p != nullptr)
	{
		if (p->data == 0)
		{
			f_del(p);
			return;
		}
		else {
			if (p->right != nullptr)
			{
				del0(p->right);
			}
			if (p->left != nullptr)
			{
				del0(p->left);
			}
		}
	}
}
void delLeaves(BNode*& p)
{
	if (p != nullptr)
	{
		if (p->left == nullptr && p->right == nullptr)
		{
			p = nullptr;
			delete p;
		}
		else
		{
			delLeaves(p->left);
			delLeaves(p->right);
		}
	}
}
void enlarge(BNode*& p, int d)
{
	if (p == nullptr)
	{
		BNode* k = new BNode(d);
		p = k;
	}
	else
	{
		enlarge(p->left, d);
		enlarge(p->right, d);
	}
}

int sum_alt(BNode* p, int result = 0)
{
	if (p != nullptr)
	{
		if (p->right != nullptr) result += p->right->data + sum_alt(p->right);
		if (p->left != nullptr) result -= p->left->data + sum_alt(p->left);
	}
	return result;
}

//Домашняя работа 4 - деревья двоичного поиска

BNode* searchRecursion(BNode* p, int data)
{
	if (p != nullptr)
	{
		if (p->data == data)
		{
			return p;
		}
		else
		{
			if (searchRecursion(p->left, data) != nullptr) return searchRecursion(p->left, data);
			if (searchRecursion(p->right, data) != nullptr) return searchRecursion(p->right, data);
		}
	}
	else
	{
		return nullptr;
	}
}
BNode* searchCycle(BNode* p, int data)
{
	stack <BNode*> stack;

	BNode* check = p;
	if (p != nullptr)
	{
		stack.push(p);
	}
	while (!stack.empty())
	{
		check = stack.top();
		if (check->data == data) return check;
		stack.pop();
		if (check->left != nullptr) stack.push(check->left);
		if (check->right != nullptr) stack.push(check->right);
	}
	return nullptr;
}
bool addRecursion(BNode*& p, int data)
{
	if (p != nullptr)
	{
		if (p->data < data)
		{
			addRecursion(p->right, data);
		}
		else if (p->data == data)
		{
			return false;
		}
		else
		{
			addRecursion(p->left, data);
		}
	}
	else
	{
		p = new BNode(data);
	}

}
bool addCycle(BNode*& p, int data)
{
	stack<BNode*> stack;
	BNode* check = p;
	if (check != nullptr)
	{
		stack.push(check);
	}
	while (!stack.empty())
	{
		check = stack.top();
		stack.pop();
		if (check->data == data)
		{
			return false;
		}
		else if (check->data < data)
		{
			if (check->right != nullptr)
				stack.push(check->right);
			else
			{
				check->right = new BNode(data);
				return true;
			}
		}
		else
		{
			if (check->left != nullptr)
				stack.push(check->left);
			else
			{
				check->left = new BNode(data);
				return true;
			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	BNode* p1 = new BNode(1),
		* p4 = new BNode(4),
		* p7 = new BNode(7),
		* p13 = new BNode(13),
		* p6 = new BNode(6, p4, p7),
		* p14 = new BNode(14, p13),
		* p10 = new BNode(10, nullptr, p14),
		* p3 = new BNode(3, p1, p6),
		* p8 = new BNode(8, p3, p10);

	BTree t(p8);
	t.print();
	cout << endl << endl;

	cout << "Левый узел - ";
	cout << leftNode(p8)->data << endl << endl;

	cout << "Удалить левый узел" << endl;
	delLeftNode(p8);
	t.print();
	cout << endl << endl;

	cout << "Добавить к левому узлу" << endl;
	addLeft(p8, 66);
	t.print();
	cout << endl << endl;

	cout << "Левый лист - " << leftLeave(p8)->data << endl << endl;

	cout << "Удалить левый лист" << endl;
	delLeftLeave(p8);
	t.print();
	cout << endl << endl;

	cout << "Второй лист слева - " << secondLeftLeave(p8)->data << endl << endl;

	cout << "Умножить все узлы на 3" << endl;
	scale(p8);
	t.print();
	cout << endl << endl;

	cout << "sum: " << sum(p8) << endl;

	cout << "num neg: " << count_neg(p8) << endl;

	cout << "height: " << height(p8) << endl;

	cout << "Отразить зеркально" << endl;
	reflect(p8);
	t.print();
	cout << endl << endl;

	cout << "mult: " << mult(p8) << endl;



	BNode* q1 = new BNode(43),
		* q2 = new BNode(13),
		* q4 = new BNode(-13),
		* q3 = new BNode(0, q1, q2),
		* q5 = new BNode(2, q3, q4);
	BTree q(q5);
	q.print();
	cout << endl << endl;

	cout << "eval: " << eval(q5) << endl;

	cout << "min: " << min(INT_MAX, q5) << endl;

	cout << "Удалить листы" << endl;
	delLeaves(q.root);
	q.print();
	cout << endl << endl;

	cout << "Удалить все листы с 0" << endl;
	del0(q.root);
	q.print();
	cout << endl << endl;

	cout << "Заменить все нулевые указатели на 123" << endl;
	enlarge(q.root, 123);
	q.print();
	cout << endl << endl;

	cout << "sum alt = " << sum_alt(t.root) << endl;
	t.print();
	cout << endl << endl;

	cout << "sum alt = " << sum_alt(q.root) << endl;
	q.print();
	cout << endl << endl;

	BNode* r7 = new BNode(50);
	BNode* r3 = new BNode(10);
	BNode* r2 = new BNode(25, r3, r7);
	BNode* r5 = new BNode(130);
	BNode* r6 = new BNode(120);
	BNode* r4 = new BNode(125, r6, r5);
	BNode* r1 = new BNode(100, r2, r4);

	BTree r(r1);

	r.print();
	cout << endl << endl;

	addCycle(r1, 27);
	r.print();
	cout << endl << endl;

	addRecursion(r1, 999);
	r.print();
	cout << endl << endl;

	cout << searchRecursion(r1, 10) << endl;
	cout << searchCycle(r1, 10) << endl;
	
	return EXIT_SUCCESS;
} 