#include <iostream>

using namespace std;

template <class T>
class DoublyNodeType
{
public:
	T info;
	DoublyNodeType<T>* next;
	DoublyNodeType<T>* prev;
};
template <class T>
class DoublyLinkedList
{
public:
	DoublyNodeType<T>* head;
	DoublyNodeType<T>* tail;
	int size = 0;

	void insertAtEnd(T value)
	{
		DoublyNodeType<T>* newNode = new DoublyNodeType<T>;
		newNode->info = value;
		newNode->next = nullptr;
		newNode->prev = tail;
		tail = newNode;

		if (head == nullptr)
		{
			head = newNode;
		}
		else
		{
			newNode->prev->next = newNode;
		}
		size++;
	}
	void insertAtBeginning(T value)
	{
		DoublyNodeType<T>* newNode = new DoublyNodeType<T>;
		newNode->info = value;
		newNode->next = head;
		newNode->prev = nullptr;
		head = newNode;

		if (tail == nullptr)
		{
			tail = newNode;
		}
		else
		{
			newNode->next->prev = newNode;
		}
		size++;
	}
	void insertExactlyAt(T value, int index)
	{
		if (index <= size)
		{
			if (index == 0)
			{
				insertAtBeginning(value);
			}
			else if (index == size)
			{
				insertAtEnd(value);
			}
			else
			{
				DoublyNodeType<T>* newNode = new DoublyNodeType<T>;
				newNode->info = value;
				DoublyNodeType<T>* beforeThis = head;
				for (int i = 0; i < index; i++)
				{
					beforeThis = beforeThis->next;
				}
				newNode->next = beforeThis;
				newNode->prev = beforeThis->prev;
				beforeThis->prev = newNode;
				newNode->prev->next = newNode;
				size++;
			}
		}
	}
	void print()
	{
		DoublyNodeType<T>* current = head;
		while (current != nullptr)
		{
			cout << current->info << " ";
			current = current->next;
		}

	}
};

int main()
{
	DoublyLinkedList<int>* li = new DoublyLinkedList<int>;
	li->insertAtBeginning(3);
	li->insertAtBeginning(7);
	li->insertAtEnd(5);
	li->insertExactlyAt(9, 2);
	li->print();

	return 0;
}