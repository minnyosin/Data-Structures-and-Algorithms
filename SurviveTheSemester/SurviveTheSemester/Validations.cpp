#include "Player.h"

void checkStats(Player *student)
{
	if (student->focus >= 100)
	{
		student->focus = 100;
	}
	if (student->energy >= 100)
	{
		student->energy = 100;
	}
	if (student->motivation >= 10)
	{
		student->motivation = 10;
	}
	if (student->energy <= 0)
	{
		student->energy = 0;
	}
	if (student->focus <= 0)
	{
		student->focus = 0;
	}
	if (student->motivation <= 0)
	{
		student->motivation = 0;
	}
}
bool isInputValid()
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << endl << "Invalid Input!" << endl;
		return false;
	}
	return true;
}