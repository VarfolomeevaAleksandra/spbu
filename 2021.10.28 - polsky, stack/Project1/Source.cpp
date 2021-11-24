#include<iostream>
#include<string>
#include<stack>
using namespace std;

int f2()
{
	stack<int> s;
	int p;
	int a = 0;
	int b = 0;
	char x;
	int result;
	while (cin >> x && x != 'z')
	{
		if (isdigit(x))
		{
			cin.putback(x);
			cin >> p;
			s.push(p);
		}
		else if (x != 'z')
		{
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			switch (x)
			{
			case '+': s.push(a + b); break; 
			case '-': s.push(b - a); break;
			case '*': s.push(a * b); break;
			case '/': s.push(b / a); break;
			}
		}
	}
	return s.top();
}
string f1()
{
	stack<char> sign;
	char x;
	string result;
	int number;
	while (cin >> x && x != 'z')
	{
		if (isdigit(x))
		{
			cin.putback(x);
			cin >> number;
			result += to_string(number);
		}
		else
		{
			
			if ((x == '-' || x == '+'))
			{
				while (true)
				{
					if (sign.empty() || sign.top() == '(') break;
					result += sign.top();
					sign.pop();
				}
				sign.push(x);
			}
			else if (x == '*' || x == '/')
			{
				while (true)
				{
					if (sign.empty() || sign.top() == '(' || sign.top() == '+' || sign.top() == '-') break;
					result += sign.top();
					sign.pop();
				}
				sign.push(x);
			}
			else if (x == '(')
			{
				sign.push(x);
			}
			else if (x == ')')
			{
				while (sign.empty() == false && sign.top() != '(')
				{
					result += sign.top();
					sign.pop();
				}
				sign.pop();
			}
		}
	}
	while (sign.empty() == false)
	{
		result += sign.top();
		sign.pop();
	}
	return result;
}
int main()
{
	cout << "¬ведите выражение в обратной польской записи" << endl;
	cout << "result = " << f2() << endl;
	cout << "¬ведите выражение в обычной записи" << endl;
	cout << "result = " << f1() << endl;
}