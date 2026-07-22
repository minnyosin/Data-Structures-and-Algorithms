#include "Player.h"
#include "Challenge.h"
#include "Encounters.h"
#include "Display.h"
#include "Validations.h"
#include <random>



using namespace std;

int randomLuck()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 20);
	return distrib(gen);
}


int main()
{

	slowPrint("Welcome to APU!");
	slowPrint("You are challenged to finish the semester");
	cout << endl;

	int playerLuck = randomLuck();
	string playerName = setName();
restartPhoneDistraction:
	Player* student = new Player(playerName, playerLuck);
	student->displayPlayerStats();


	cout << endl;
	slowPrint("You are currently at week 1 of your semester..");
	cout << endl;
	slowPrint("5:30 PM...");
	cout << endl;
	slowPrint("You just got back from school and tried to study...");

	
	int playerWin = phoneDistractionChallenge(student);
	switch (playerWin)
	{
	case 1:
		slowPrint("Congs!", 100);
		break; // change later
	
	case 2:
		slowPrint("You blamed yourself.");
		break;
	
	case 3:
		do
		{
			char option;
			cout << "Do you want to try again?(y/n) : ";
			cin >> option;


			if (option == 'y')
			{
				delete student;
				goto restartPhoneDistraction;
			}
			else if (option == 'n')
			{
				slowPrint("What a LOOOOOOOOOOOSER!", 400);
				delete student;
				return 0;
			}
			else
			{
				cout << "Invalid Input!" << endl;
				continue;
			}
		} while (isInputValid());
	}
	delete student;
	return 0;
}



