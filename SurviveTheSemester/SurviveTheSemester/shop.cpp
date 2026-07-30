#include "shop.h"
#include "Validations.h"

void buyShop(Player* student, Item item)
{
	if (student->spendMoney(item.price))
	{
		student->inventory.addItem(item);
		cout << "Money Left : RM " << student->money << endl;
	}
}

void campusShop(Player* student)
{
	Item items[3] =
	{
		{"Coffee", 5, 5, 0, 15, -1},
		{"Sandwich", 6, 0, 0, 15, 0},
		{"Chocolate", 3, 0, 0, 3, 3}
	};

	int option = 0;
	while (option != 5) 
	{
		cout << endl << "===== APU Bila Bila =====" << endl;
		cout << "Money : RM " << student->money << endl;
		cout << "1. Coffee - RM 5" << endl;
		cout << "2. Sandwich - RM 6" << endl;
		cout << "3. Chocolate - Rm 3" << endl;
		cout << "4. View Inventory" << endl;
		cout << "5. Leave" << endl;
		cout << "What would you like to do? : ";
		cin >> option;
		if (!isInputValid())
		{
			continue;
		}
		if (option >= 1 && option <= 3)
		{
			buyShop(student, items[option - 1]);
		}
		else if (option == 4)
		{
			//student->inventory.displayInventory();
			student->openInventory();
		}
		else if (option != 5)
		{
			cout << "Invalid Input!" << endl;
		}
		
	}
}

void downtownShop(Player* student)
{
	Item items[3] =
	{
		{ "Energy Drink", 8, -3, 0, 25, 0 },
		{ "Study Notes", 12, 5, 3, 0, 0 },
		{ "Instant Noodles", 4, 0, 0, 10, 0 }
	};

	int option = 0;
	while (option != 5)
	{
		cout << endl << "===== KLCC Pavillion =====" << endl;
		cout << "Money : RM " << student->money << endl;
		cout << "1. Energy Drink - RM 8" << endl;
		cout << "2. Study Notes - RM 12" << endl;
		cout << "3. Instant Noodles - Rm 4" << endl;
		cout << "4. View Inventory" << endl;
		cout << "5. Leave" << endl;
		cout << "What would you like to do? : ";
		cin >> option;
		if (!isInputValid())
		{
			continue;
		}
		if (option >= 1 && option <= 3)
		{
			buyShop(student, items[option - 1]);
		}
		else if (option == 4)
		{
			student->inventory.displayInventory();
		}
		else if (option != 5)
		{
			cout << "Invalid Input!" << endl;
		}
	}
}