#include "Player.h"
#include <string>

string setName()
{
	string name;
	cout << "Enter your name : ";
	getline(cin, name);
	return name;
}
