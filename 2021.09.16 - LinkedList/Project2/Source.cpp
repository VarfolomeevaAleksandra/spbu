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

struct DList
{
	DNode* head, * tail;
	DList()
	{
		head = tail = nullptr;
	}

	void last()
	{
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
	}
};