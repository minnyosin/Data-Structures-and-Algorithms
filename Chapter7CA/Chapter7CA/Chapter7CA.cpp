#include <iostream>

using namespace std;


class NodeType
{
public:
	int info;
	NodeType* next;
};
class LinkedListStack
{
public:
	NodeType* head;
	NodeType* tail;
	int size;

	LinkedListStack()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}
	~LinkedListStack()
	{
		NodeType* current = head;
		while (head != nullptr)
		{
			current = current->next;
			delete head;
			head = current;
		}
	}

	void push(int value)
	{
		NodeType* newNode = new NodeType();
		newNode->info = value;
		newNode->next = head;
		head = newNode;
		size++;
		if (tail = nullptr)
		{
			tail = newNode;
		}
	}
	void pop()
	{
		if (size > 0)
		{
			NodeType* toBeDeleted = new NodeType();
			head = head->next;
			delete toBeDeleted;
			size--;
			if (head == nullptr)
			{
				tail = nullptr;
			}
		}
	}
	void top()
	{
		cout << head->info << endl;
	}
	int getSize()
	{
		return size;
	}
	bool isEmpty()
	{
		return size == 0;
	}
	void Display()
	{
		if (!isEmpty())
		{
			for (int i = size-1; i >= 0; i--)
			{
				NodeType* current = head;
				for (int j = 0; j < i; j++)
				{
					current = current->next;
				}
				cout << current->info << endl;
			}
		}
		else
		{
			cout << "Empty Stack!";
		}
	}

};
class ArrayStack
{
	char* list;
	int stackTop;
	int maxStackSize;

public:
	ArrayStack(int max)
	{
		maxStackSize = max;
		list = new char[max];
		stackTop = -1;
	}
	~ArrayStack()
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

void CA2()
{
	LinkedListStack* coins = new LinkedListStack();

	coins->push(50);
	coins->push(20);
	coins->push(10);
	coins->push(10);
	coins->push(20);
	coins->push(50);
	coins->push(50);
	coins->push(20);
	coins->push(10);
	coins->push(20);
	coins->push(20);

	coins->pop();
	coins->pop();
	coins->pop();

	coins->push(50);
	coins->push(10);
	coins->push(10);

	coins->Display();

	delete coins;
}
int main()
{
	ArrayStack* stack1 = new ArrayStack(10);
	//stack1->push('a');
	//stack1->push('b');
	//stack1->push('c');
	//stack1->pop();
	//stack1->top();
	//stack1->display();

	//delete stack1;

	//cout << endl;
	//LinkedListStack* l1 = new LinkedListStack();

	//l1->push(10);
	//l1->push(12);
	//l1->push(14);
	//l1->pop();
	//l1->top();
	//l1->Display();

	//delete l1;

	CA2();
	return 0;
}

// do CA2 for the stack!!!!! use linked list (may be easier?)