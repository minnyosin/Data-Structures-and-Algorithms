#include "Validations.h"
#include <iostream>

using namespace std;

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