#pragma once
#include "Display.h"
#include "Inventory.h"
#include "Validations.h"
#include <iostream>
#include <string>

using namespace std;


struct PlayerStats
{
	float focus;
	float knowledge;
	float energy;
	float motivation;
	int money;
	
};

class Player
{
public:
	string name;
	float focus;
	float knowledge;
	float energy;
	float motivation;
	float luck;
	int money;
	InventoryLinkedList inventory;
	bool hasPartTimeJob;
	int studyNotesAvailable;

	Player(string name, int luck)
	{
		this->name = name;
		this->focus = 100;
		this->knowledge = 20;
		this->energy = 80;
		this->motivation = 7;
		this->luck = luck;
		this->money = 30;
		this->hasPartTimeJob = false;
		this->studyNotesAvailable = 3;
	}
	void checkStats()
	{
		if (focus > 100)
		{
			focus = 100;
		}
		if (energy > 100)
		{
			energy = 100;
		}
		if (motivation > 10)
		{
			motivation = 10;
		}
			
		if (focus < 0)
		{
			focus = 0;
		}
		if (knowledge < 0)
		{
			knowledge = 0;
		}
		if (energy < 0)
		{
			energy = 0;
		}
		if (motivation < 0)
		{
			motivation = 0;
		}
		if (money < 0)
		{
			money = 0;
		}
	}
	void displayPlayerStats()
	{
		cout << endl;
		cout << "Player Name       : " << name << endl;
		cout << "Player Focus      : " << focus << endl;
 		cout << "Player Knowledge  : " << knowledge << endl;
		cout << "Player Energy     : " << energy << endl;
		cout << "Player Motivation : " << motivation << endl;
		cout << "Player Luck       : " << luck << endl;
		cout << "Player Money      : RM " << money << endl;

	}
	void displayCombatStats()
	{
		cout << "Focus      : " << focus << endl;
		cout << "Knowledge  : " << knowledge << endl;
		cout << "Energy     : " << energy << endl;
		cout << "Motivation : " << motivation << endl;
	}
	PlayerStats tempStat()
	{
		return { focus, knowledge, energy, motivation, money };
	}
	void printChange(string label, float oldValue, float newValue)
	{
		float diff = newValue - oldValue;
		cout << label << " : " << oldValue << " -> " << newValue << " (";
		if (diff > 0)
		{
			cout << "+" << diff;
			cout << ")" << endl;
		}
		else if (diff < 0)
		{
			cout << diff;
			cout << ")" << endl;

		}
		else
		{
			cout << "No Change";
			cout << ")" << endl;
		}
	}
	void displayStatChanges(PlayerStats before)
	{
		printChange("Focus      ", before.focus, focus);
		printChange("Knowledge  ", before.knowledge, knowledge);
		printChange("Energy     ", before.energy, energy);
		printChange("Motivation ", before.motivation, motivation);
		printChange("Money      ", (float)before.money, (float)money);

	}
	bool spendMoney(int amount)
	{
		if (amount <= 0)
		{
			return false;
		}
		if (money < amount)
		{
			slowPrint("You don't have enough money!");
			return false;
		}
		money -= amount;
		return true;
	}
	void receiveMoney(int amount)
	{
		if (amount <= 0)
		{
			return;
		}
		money += amount;
		cout << "You received RM" << amount << "!" << endl;
	}
	bool useItem(int index)
	{
		InventoryNode* selected = inventory.getItemAt(index);
		if (selected == nullptr)
		{
			return false;
		}
		PlayerStats before = tempStat();
		Item usedItem = selected->item;
		cout << endl;
		slowPrint("You used " + usedItem.name + "!");

		focus += usedItem.focusRegen;
		knowledge += usedItem.knowledgeRegen;
		energy += usedItem.energyRegen;
		motivation += usedItem.motivationRegen;
		checkStats();

		selected->quantity--;
		cout << endl << "==== Item Result ====" << endl;
		displayStatChanges(before);
		cout << "========================" << endl;
		if (selected->quantity <= 0)
		{
			inventory.removeItemAt(index);
		}
		return true;
	}
	bool openInventory()
	{
		if (inventory.isEmpty())
		{
			cout << endl;
			slowPrint("Your inventory is empty");
			return false;
		}
		int option;
		inventory.displayInventory(); 
		cout << inventory.size + 1 << ". Go Back" << endl;
		cout << "Choose an Item to use: ";
		cin >> option;
		if (!isInputValid())
		{
			return false;
		}
		if (option == inventory.size + 1)
		{
			return false;
		}
		if (option < 1 || option > inventory.size)
		{
			cout << "Invalid Item!" << endl;
			return false;
		}
		return useItem(option - 1);
	}
	bool isDead()
	{
		if (focus <= 0)
		{
			cout << endl;
			slowPrint("You completely lost your Focus :(");
			slowPrint("You decided to drop out the Course");
			slowPrint("You failed the challenge...");
			cout << endl;
			return true;
		}
		return false;
	}

	
};

inline string setName()
{
	string name;
	bool isNameCorrect = false;
	while (!isNameCorrect)
	{
		name.clear();
		cout << "Enter your name:";
		getline(cin, name);
		
		isNameCorrect = name.find_first_not_of(" \t\r\n") != string::npos;
	}
	
	return name;
}
