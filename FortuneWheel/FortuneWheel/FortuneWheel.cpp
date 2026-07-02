#include <iostream>
#include <ctime>

using namespace std;

template<class T>
class CircularNodeType
{
public:
	T info;
	CircularNodeType<T>* next;
};
template<class T>
class CircularLinkedList
{
public:
	CircularNodeType<T>* head;
	CircularNodeType<T>* tail;
	int size = 0;

	CircularLinkedList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}

	void insertAtEnd(T value)
	{
		CircularNodeType<T>* newNode = new CircularNodeType<T>;
		newNode->info = value;
		if (head == nullptr)
		{
			head = tail = newNode;
			tail->next = head;
		}
		else
		{
			newNode->next = head;
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}
	void DisplayNodes()
	{
		CircularNodeType<T>* current = tail->next;
		do
		{
			cout << current->info << " ";
			current = current->next;
		} while (current != tail->next);
	}
	void VisitNodes(int rNum)
	{

		CircularNodeType<T>* current = head;
		for (int i = 0; i < rNum; i++)
		{
			current = current->next;
		}
		cout << "Current Node: " << current->info << endl;
		head = current;
	}
};
int spin(int size)
{
	return (rand() % (size * 3)) + 1;

}

int main()
{
	srand(time(0));
	int size;
	CircularLinkedList<int>* wheel = new CircularLinkedList<int>();

	cout << "How many slot you want in the wheel : ";
	cin >> size;

	for (int i = 0; i < size; i++)
	{
		int value;
		cout << "Insert the Fortune for slot no " << i + 1 << " : ";
		cin >> value;
		wheel->insertAtEnd(value);
	}
	cout << "Fortunes in the wheel : ";
	wheel->DisplayNodes();
	cout << endl;
	int rNum = spin(size);
	cout << rNum << endl;
	wheel->VisitNodes(rNum);
	wheel->VisitNodes(3);
	
	return 0;
}