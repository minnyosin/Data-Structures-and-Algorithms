#include <iostream>

using namespace std;

class Player {
public:
	string name;
	string id;
	int duration;
	int level;
	string rank;

};

class PlayerNode
{
public:
	Player player;
	PlayerNode* link;
};



class NodeType
{
public:
	int info;
	NodeType* next;
};

class LinkedList
{
public:
	NodeType* head;
	NodeType* tail;
	int size;

	LinkedList()
	{
		this->size = 0;
		this->head = nullptr;
		this->tail = nullptr;
	}
	~LinkedList()
	{
		cout << "Going to delete all " << size << " elements of the list";
		NodeType* current = head;
		while (head != nullptr)
		{
			current = current->next;
			delete head;
			head = current;
		}
	}

	void insertAtBeginning(int value)
	{
		NodeType* newNode = new NodeType();
		newNode->info = value;
		newNode->next = head;
		head = newNode;
		size++;
		if (tail == nullptr)
		{
			tail = newNode;
		}
	}
	void insertAtEnd(int value)
	{
		NodeType* newNode = new NodeType;
		newNode->info = value;
		newNode->next = NULL;

		if (head == NULL)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
		size++;
	}
	void insertItemAt(int value, int index)
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
				NodeType* newNode = new NodeType;
				newNode->info = value;
				NodeType* prev = head;
				for (int i = 0; i < index - 1; i++)
				{
					prev = prev->next;
				}
				newNode->next = prev->next;
				prev->next = newNode;
				size++;
			}
		}
	}
	void deleteFirst()
	{
		if (size > 0)
		{
			NodeType* toBeDeleted = head;
			head = head->next;
			delete toBeDeleted;
			size--;

			if (head == nullptr)
			{
				tail = nullptr;
			}
		}
	}
	void deleteLast()
	{
		if (size > 0)
		{
			if (size == 1)
			{
				delete head;
				head = tail = nullptr;
			}
			else
			{
				NodeType* beforeLast = head;
				while (beforeLast->next->next != NULL)
				{
					beforeLast = beforeLast->next;
				}
				delete beforeLast->next;
				beforeLast->next = NULL;
				tail = beforeLast;
			}
			size--;
		}
		
		
	}
	void deleteItemAt(int index)
	{
		if (index < size)
		{
			if (index == 0)
			{
				deleteFirst();
			}
			else
			{
				NodeType* prev = nullptr;
				NodeType* toDelete = head;

				for (int i = 0; i < index; i++)
				{
					prev = toDelete;
					toDelete = toDelete->next;
				}
				prev->next = toDelete->next;
				delete toDelete;
				size--;
			}
		}
	}
	int getItemAt(int index)
	{
		if (index < 0 || index > size)
		{
			cout << "Index is out of bounds" << endl;
			abort();
		}
		NodeType* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->info;
	}
	int setItemAt(int index, int value)
	{
		if (index < 0 || index > size)
		{
			cout << "Index is out of bounds" << endl;
			abort();
		}
		NodeType* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->info = value;
	}
	void clear()
	{
		cout << "Going to delete all " << size << " elements of the list.";
		NodeType* current = head;
		while (head != nullptr)
		{
			current = current->next;
			delete head;
			head = current;
		}
		size = 0;
	}
};

void CA4()
{
	int searchIndex;
	int updateValue;
	LinkedList* l1 = new LinkedList();
	NodeType* current;

	l1->insertAtBeginning(5);
	l1->insertAtBeginning(9);
	l1->insertAtBeginning(3);
	l1->insertAtEnd(10);
	l1->insertItemAt(7, 2);

	cout << "size : " << l1->size;

	current = l1->head;
	cout << endl;
	cout << "Elements : ";
	while (current != nullptr)
	{
		cout << current->info << " ";
		current = current->next;
	}
	
	l1->deleteFirst();
	l1->deleteLast();
	cout << endl;
	current = l1->head;
	while (current != nullptr)
	{
		cout << current->info << " ";
		current = current->next;
	}
	cout << endl;
	cout << "Which item do you want to see?:";
	cin >> searchIndex;
	cout << "Item at index " << searchIndex  << " : " << l1->getItemAt(searchIndex);
	cout << endl;
	cout << "What is the value that you want to update? : ";
	cin >> updateValue;
	cout << "Value of Item at index " << searchIndex << ", which was " << l1->getItemAt(searchIndex) << ", is updated to " << l1->setItemAt(searchIndex, updateValue);

	cout << endl;
	l1->clear();
	
}
int main()
{
	//PlayerNode* newNode = new PlayerNode;
	//Player player1 = Player();
	//player1.name = "John";
	//player1.id = "10051";
	//player1.duration = 12;
	//player1.level = 5;
	//player1.rank = "Junior";

	//newNode->player = player1;
	//newNode->link = nullptr;

	//cout << "Info at the new node: " << endl;
	//cout << "Name : " << newNode->player.name << endl;
	//cout << "Id : " << newNode->player.id << endl;
	//cout << "Duration : " << newNode->player.duration << endl;
	//cout << "Level : " << newNode->player.level << endl;
	//cout << "Rank : " << newNode->player.rank << endl;
	//cout << endl;
	//cout << "next node : " << newNode->link << endl;

	CA4();

	return 0;
}

