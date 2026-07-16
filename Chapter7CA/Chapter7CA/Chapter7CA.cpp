#include <iostream>

using namespace std;

class Stack
{
	char* list;
	int stackTop;
	int maxStackSize;

public:
	Stack(int max)
	{
		maxStackSize = max;
		list = new char[max];
		stackTop = -1;
	}
	~Stack()
	{
		delete[] list;
		maxStackSize = 0;
		stackTop = -1;
	}
	void push(char n)
	{
		if (stackTop < maxStackSize - 1)
		{
			list[++stackTop] = n;
		}
		else
		{
			cout << "Stack Overflow" << endl;
		}
	}
	char pop()
	{
		if (stackTop > -1)
		{
			return list[stackTop--];
		}
	}
	void top()
	{
		if (stackTop > -1)
		{
			cout << list[stackTop] << endl;
		}
	}
	bool isEmpty()
	{
		return stackTop == -1;
	}
	void display()
	{
		if (stackTop > -1)
		{
			for (int i = 0; i <= stackTop; i++)
			{
				cout << list[i] << endl;
			}
		}
	}
};
int main()
{
	Stack* stack1 = new Stack(10);
	stack1->push('a');
	stack1->push('b');
	stack1->push('c');
	stack1->pop();
	stack1->top();
	stack1->display();

	return 0;
}

// do CA2 for the stack!!!!! use linked list (may be easier?)