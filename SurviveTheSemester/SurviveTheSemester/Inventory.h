#pragma once
#include "Item.h"
#include <iostream>

using namespace std;

class InventoryNode
{
public:
	Item item;
	int quantity;
	InventoryNode* next;
};

class InventoryLinkedList
{
public:
	InventoryNode* head;
	InventoryNode* tail;
	int size;

	InventoryLinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}
	~InventoryLinkedList()
	{
		clear();
	}
	bool isEmpty()
	{
		return size == 0;
	}
	void insertAtEnd(Item item, int quantity)
	{
		InventoryNode* newNode = new InventoryNode;
		newNode->item = item;
		newNode->quantity = quantity;
		newNode->next = nullptr;

		if (head == nullptr)
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
	void addItem(Item item, int quantity = 1)
	{
		if (quantity <= 0)
		{
			return;
		}
		InventoryNode* current = head;
		while (current != nullptr)
		{
			if (current->item.name == item.name)
			{
				current->quantity += quantity;
				cout << item.name << " was added to your inventory!" << endl;
				cout << "Current Quantity : " << current->quantity << endl;
				return;
			}
			current = current->next;
		}
		insertAtEnd(item, quantity);
		cout << item.name << " was added to your inventory!" << endl;
	}
	InventoryNode* getItemAt(int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "Index out of bounds!" << endl;
			return nullptr;
		}
		InventoryNode* current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current;
	}
	void removeItemAt(int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "Index out of bounds!" << endl;
			return;
		}
		InventoryNode* toDelete;
		if (index == 0)
		{
			toDelete = head;
			head = head->next;
			if (head == nullptr)
			{
				tail = nullptr;
			}
		}
		else
		{
			InventoryNode* previous = head;
			for (int i = 0; i < index - 1; i++)
			{
				previous = previous->next;
			}
			toDelete = previous->next;
			previous->next = toDelete->next;
			if (toDelete == tail)
			{
				tail = previous;
			}

		}
		delete toDelete;
		size--;
	}
	void displayInventory()
	{
		cout << endl << " ==== Inventory ==== " << endl;
		if (isEmpty())
		{
			cout << "Your inventory is empty." << endl;
			cout << "=======================" << endl;
			return;
		}
		InventoryNode* current = head;
		int index = 1;
		while (current != nullptr)
		{
			cout << index << ". " << current->item.name << " x" << current->quantity << endl;
			current = current->next;
			index++;
		}
		cout << "=================" << endl;
	}
	void clear()
	{
		while (head != nullptr)
		{
			InventoryNode* current = head;
			head = head->next;
			delete current;
		}
		tail = nullptr;
		size = 0;
	}
};