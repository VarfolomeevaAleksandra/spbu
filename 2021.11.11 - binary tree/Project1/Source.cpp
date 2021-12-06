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

void f_del(BNode*& p);
void f_print(BNode* r, int d = 0) // ôóíêöèÿ îòîáðàæàþùàÿ äåðåâî  
{
	if (r == nullptr)
	{
		return;
	}
	f_print(r->right, d + 3);
	for (int i = 0; i < d; i++)
	{
		cout << " ";
	}
	cout << r->data << endl;
	f_print(r->left, d + 3);
}
void c_print(BNode* r)
{
	if (r == nullptr)
	{
		cout << "BThree is empty" << endl;
		return;
	}
	else
	{
		f_print(r);
	}
}

void cprint(BNode* r)
{
	cout << "---------------------------------------------" << endl;
	                                                                                   
	c_print(r);
	cout << "---------------------------------------------" << endl;
} // ôóíêöèÿ îòîáðàæåíèÿ ñ ïîëîñêàìè(äëÿ óäîáñòâà) 
struct BThree
{
	~BThree()
	{
		f_del(root);
	}
	BNode* root;
	BThree(BNode* p) : root(p) {}


	void del0(BNode*& p)
	{
		if (p != nullptr)
		{
			if (p->data == 0)
			{
				f_del(p);
			}
			else if (p->right != nullptr)
				del0(p->right);
			else  if (p->left != nullptr)
			{
				del0(p->left);
			}
		}
		else
		{

		}
	}
	void print()
	{
		cprint(root);
	}

};

//Задание Двоичные деревья

BThree* quest1() // номер 1
{
	BNode* p13 = new BNode(13);
	BNode* p14 = new BNode(14, p13);
	BNode* p10 = new BNode(10, nullptr, p14);
	BNode* p7 = new BNode(7);
	BNode* p4 = new BNode(4);
	BNode* p6 = new BNode(6, p4, p7);
	BNode* p1 = new BNode(1);
	BNode* p3 = new BNode(3, p1, p6);
	BNode* p8 = new BNode(8, p3, p10);
	BThree* result = new BThree(p8);
	return result;
}
BThree* quest2() // ñîçäàíèå äåðåâà èç çàäàíèÿ 
{
	BNode* p13 = new BNode(13);
	BNode* p7 = new BNode(7);
	BNode* p4 = new BNode(4);
	BNode* p14 = new BNode(0, p13);
	BNode* p10 = new BNode(10, nullptr, p14);
	BNode* p6 = new BNode(0, p4, p7);
	BNode* p1 = new BNode(1);
	BNode* p3 = new BNode(0, p1, p6);
	BNode* p8 = new BNode(8, p3, p10);
	BThree* result = new BThree(p8);
	return result;
}
BNode* left_node(BNode* p) // номер 2 - самый левый узел 
{
	BNode* result = p;
	if (p->left != nullptr)
	{
		result = left_node(p->left);
	}
	else
	{
		return result;
	}
} 
bool branchesNot(BNode* p) //есть ли ветки у узла
{
	BNode* k = p;
	while (k != nullptr)
	{
		if (k->left != nullptr && k->right != nullptr)
		{
			return false;
		}
		else
		{
			/*if (k->left != nullptr)
			{
				branchesNot(k->left);
			}
			if (k->right != nullptr)
			{
				branchesNot(k->right);
			}*/
			return true;
		}
		
	}
} 
BNode* left_sheet(BNode* p) // номер 5 - самый левый лист(не узел)
{
	BNode* left = p;
	if (left->left != nullptr)
	{
		left = left_sheet(left->left);
	}
	else if (left->right != nullptr)
	{
		left = left_sheet(left->right);
	}
	return left;

} 

bool delete_left_node(BNode* d) //номер 3 - удалить самый левый узел
{
	BNode* del = left_node(d);
	BNode* prev = d;
	if (del == prev)
	{

		delete del;
		return true;

	}
	while (prev->left != del)
	{
		prev = prev->left;
	}
	if (del->right == nullptr)
	{
		delete del;
	}
	else
	{
		prev->left = del->right;
		delete del;
	}
	return true;
}
bool delete_left_sheet(BThree* d) //номер 6 - удалить самый левый узел
{
	BNode* del = left_sheet(d->root);
	BNode* prev = d->root;
	while (prev->left != del && prev->right != del)
	{
		if (prev->left != nullptr)
		{
			prev = prev->left;
		}
		else if (prev->right != nullptr)
		{
			prev = prev->right;
		}
	}
	if (prev->left == del)
	{
		delete del;
		prev->left = nullptr;
	}
	else
	{
		delete del;
		prev->right = nullptr;
	}

	return true;
}
bool add_left(int data, BNode* r) //номер 4 - добавить лист к самому левому узлу
{
	BNode* NEW = new BNode(data);
	BNode* prev = left_node(r);
	prev->left = NEW;
	return true;
}

// задание Обход дерева

bool scale(BNode* d) //номер 1 - умножить значение каждого узла на 3
{
	d->data = 3 * d->data;
	if (d->left != nullptr)
	{
		scale(d->left);
	}
	if (d->right != nullptr)
	{
		scale(d->right);
	}
	return true;
}
int sum(BNode* d, int result = 0) //номер 2 - вычислить сумму всех данных в узлах
{
	result += d->data;
	if (d->left != nullptr)
	{
		sum(d->left);
	}
	if (d->right != nullptr)
	{
		sum(d->right);
	}
	return result;
}
int count_neg(BNode* d, int result = 0) // номер 3 - число узлов с отричательными данными
{
	BNode* r = d;
	if (r->data < 0)
		{
			result += 1;
		}
	if (d->left != nullptr)
	{
		count_neg(d->left);
	}
	if (d->right != nullptr)
	{
		count_neg(d->right);
	}
	return result;
}
int height(BNode* d, int result = 0)
{
	BNode* r = d;
	if (r != nullptr)
	{
		result += 1;
		result = result += (height(r->left) > height(r->right) ? height(r->left) : (height(r->right)));
		return result;
	}
	else
	{
		return 0;
	}
}
bool reflect(BNode* d)
{
	BNode* r = d;
	if (r == nullptr)
	{
		return true;
	}
	if (r->right != nullptr || r->left != nullptr)
	{
		BNode* l = d->left;
		d->left = d->right;
		d->right = l;
		reflect(r->right);
		reflect(r->left);
	}

}
int mult(BNode* d, int result = 1)
{
	BNode* r = d;
	if (r != nullptr)
	{
		result = result * r->data;
		result = result * mult(d->right) * (mult(d->left));
		return result;
	}
	else
	{
		return result;
	}
}

BNode* find(BNode* d, int T)
{
	BNode* r = d;
	if (r == nullptr)
	{
		return nullptr;
	}
	if (r->data == T)
	{
		return r;
	}
	else
	{
		if (find(r->left, T) != nullptr)
		{
			return find(r->left, T);
		}
		else if (find(r->right, T) != nullptr)
		{
			return find(r->right, T);
		}
	}
	return nullptr;
}
int min(BNode* d, int result = INT_MAX)
{
	if (d != nullptr)
	{
		if (result > d->data)
		{
			result = d->data;
		}
		if (result > min(d->left, result))
		{
			result = min(d->left, result);
		}
		if (result > min(d->right), result)
		{
			result = min(d->right, result);
		}
	}
	return result;

}

// homework 3 
void f_del(BNode*& p)
{
	if (p == nullptr)
		return;
	f_del(p->left);
	f_del(p->right);
	p = nullptr;
	delete p;
}
void del0(BNode*& p)
{
	if (p == nullptr)
	{


	}
	else
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
	if (p == nullptr)
	{

	}
	else
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
//homework 4 
BNode* searchRe(BNode* p, int data)
{
	if (p != nullptr)
	{
		if (p->data == data)
		{
			return p;
		}
		else
		{
			if (searchRe(p->left, data) != nullptr)
				return searchRe(p->left, data);
			if (searchRe(p->right, data) != nullptr)
				return searchRe(p->right, data);

		}
	}
	else
	{
		return nullptr;
	}
}
BNode* searchCy(BNode* p, int data)
{
	stack <BNode*> stack;

	BNode* check = p;
	if (p != nullptr)
	{
		stack.push(p);
	}
	else
	{

	}
	while (!stack.empty())
	{
		check = stack.top();
		if (check->data == data)
		{
			return check;
		}
		stack.pop();
		if (check->left != nullptr)
			stack.push(check->left);

		if (check->right != nullptr)
			stack.push(check->right);

	}
	return nullptr;
}
bool addRe(BNode* p, int data)
{
	if (p != nullptr)
	{
		if (p->data < data)
		{
			addRe(p->right, data);
		}
		else if (p->data == data)
		{
			return false;
		}
		else
		{
			addRe(p->left, data);
		}
	}
	else
	{
		p->data = data;
	}

}
bool addCy(BNode* p, int data)
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
//homework 5 
BNode* prefind(BNode* p, int data) // return element prev data
{
	BNode* r = p;
	if (r == nullptr)
	{
		return nullptr;
	}
	if (r->left != nullptr || r->left->data == data)
	{
		return r;
	}
	if (r->right != nullptr || r->right->data == data)
	{
		return r;
	}
	else
	{
		if (prefind(r->left, data) != nullptr)
		{
			return prefind(r->left, data);
		}
		else if (prefind(r->right, data) != nullptr)
		{
			return prefind(r->right, data);
		}
	}
	return nullptr;
}
bool del(BNode* p, int data)
{
	BNode* element = find(p, data);
	BNode* preElement = prefind(p, data);
	if (element == nullptr)
	{
		return false;
	}
	else
	{
		if (element->left == nullptr && element->right != nullptr)
		{
			element->data = element->right->data;
			BNode* p = element->right;
			element->right = p->right;
			delete p;
		}
		if (element->left != nullptr && element->right == nullptr)
		{
			element->data = element->left->data;
			BNode* left = element->left;
			element->left = left->left;
			element->right = left->right;
			delete left;
		}
		if (element->left == nullptr && element->right == nullptr)
		{
			if (preElement->right == element)
			{
				preElement->right = nullptr;
				delete element;
			}
			else
			{
				preElement->left = nullptr;
				delete element;
			}
		}
		if (element->right != nullptr && element->left != nullptr)
		{
			element->data = left_node(element->right)->data;
			delete_left_node(element->right);
		}
		return true;
	}


}

int main()
{
	BNode* p6 = new BNode(6);
	BNode* p5 = new BNode(5);
	BNode* p4 = new BNode(4);
	BNode* p0 = new BNode(1);
	BNode* p3 = new BNode(3, p6, p0);
	BNode* p2 = new BNode(1, p4, p5);
	BNode* p1 = new BNode(3, p2, p3);
	BThree t(p1);
	t.print();
	BThree* p = quest1();
	cout << left_node(p1)->data << endl;
	p->print();
	cout << left_node(p->root)->data << endl;
	delete_left_node(p->root);
	p->print();
	cout << " test leftmost_sheet " << left_sheet(p->root)->data << endl;
	add_left(123, p->root);
	cout << "test add_leftmost" << endl;
	p->print();
	cout << " test leftmost_sheet = " << left_sheet(p->root)->data << endl;
	cout << "test delete_leftmost_sheet" << endl;
	delete_left_sheet(p);
	p->print();
	delete_left_sheet(p);
	p->print();
	delete_left_sheet(p);
	p->print();

	cout << endl << endl << "Check homework 2" << endl;
	p->print();
	scale(p->root);
	p->print();
	cout << "summ p = " << sum(p->root) << endl;
	cout << "count_neg p = " << count_neg(p->root) << endl;
	p->print();
	BNode* s6 = new BNode(6);
	BNode* s5 = new BNode(-5);
	BNode* s4 = new BNode(-4);
	BNode* s0 = new BNode(5);
	BNode* s3 = new BNode(3, s6, s0);
	BNode* s2 = new BNode(4, s4, s5);
	BNode* s1 = new BNode(1, s2, s3);
	BThree k(s1);
	k.print();
	cout << "count_neg k = " << count_neg(k.root) << endl;
	cout << "height k = " << height(k.root) << endl;
	p->print();
	cout << "height p = " << height(p->root) << endl;
	reflect(p->root);
	cout << "test reflect -  " << endl;
	p->print();
	cout << "test mult p " << mult(p->root) << endl;
	p->print();
	k.print();
	cout << "test mult k " << mult(k.root) << endl;
	cout << "print k ";
	k.print();
	cout << "test k.min = " << min(k.root) << endl;
	k.print();
	p->print();
	cout << "test p.min = " << min(p->root) << endl;
	p->print();
	cout << "test deleteLeaves" << endl;
	delLeaves(p->root);
	p->print();
	BThree* N = quest2();
	N->print();
	cout << "test del0" << endl;
	del0(N->root);
	N->print();
	f_del(N->root);
	N->print();
	enlarge(N->root, 123);
	N->print();

	enlarge(N->root, 123);
	N->print();

	enlarge(N->root, 123);
	N->print();
	p->print();
	enlarge(p->root, 123);
	p->print();
	t.print();
	BNode* r7 = new BNode(50);
	BNode* r3 = new BNode(10);
	BNode* r2 = new BNode(25, r3, r7);
	BNode* r5 = new BNode(130);
	BNode* r6 = new BNode(120);
	BNode* r4 = new BNode(125, r6, r5);
	BNode* r1 = new BNode(100, r2, r4);
	BThree t1(r1);
	t1.print();
	addCy(r1, 27);
	t1.print();
	addCy(r1, 999);
	t1.print();
	del(t1.root, 999);
	t1.print();
	return EXIT_SUCCESS;
}