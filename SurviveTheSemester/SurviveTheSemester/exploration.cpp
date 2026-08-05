#include "Exploration.h"
#include "Encounters.h"
#include "shop.h"
#include "Display.h"
#include "Validations.h"
#include <iostream>
#include <random>

using namespace std;

int randomExplorationEvent()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 2);
	
	return distrib(gen) + 1;
}
void weekTwoExploration(Player* student)
{
	int option;
	int currentLocation = 0;
	bool firstLocationChosen = false;
	bool explorationFinished = false;
	bool attendedClass = false;
	bool missedClass = false;
	bool exploredCampus = false;
	bool exploredDowntown = false;
	bool searchedPartTime = false;

	PlayerStats playerBefore = student->tempStat();

	cout << endl;
	slowPrint("===== Week 2 =====");
	cout << endl;

	slowPrint("7:30 AM...");
	slowPrint("Your alarm starts ringing.");

	cout << endl;;
	slowPrint("As soons as you wake up, you noticed that you have a class at 9:00 AM.");
	slowPrint("However, you also think that going to school is boring and instead, you want to go to the KLCC.");

	cout << endl;

	while (!firstLocationChosen)
	{
		cout << "1. Go to APU!" << endl;
		cout << "2. Go to KLCC" << endl;
		cout << "Where would you like to go? : ";
		cin >> option;

		if (!isInputValid())
		{
			continue;
		}
		switch (option)
		{
		case 1:
			cout << endl;
			slowPrint("You decided to go to APU and attend class regularly.");
			slowPrint("You arrived before your class started.");
			cout << endl;

			currentLocation = 1;
			firstLocationChosen = true;
			break;

		case 2:
			cout << endl;
			slowPrint("You decided to go to KLCC.");
			slowPrint("You will not be able to attend today's class");
			cout << endl;

			currentLocation = 2;
			firstLocationChosen = true;
			missedClass = true;
			break;
		
		default:
			cout << endl;
			cout << "Invalid Input! Try putting (1 or 2)" << endl;
			continue;
		}
		
	

		while (!explorationFinished)
		{
			if (currentLocation == 1)
			{
				cout << endl;
				cout << "===== APU Campus =====" << endl;
				cout << endl;

				cout << "1. Attend Class" << endl;
				cout << "2. Explore the Campus" << endl;
				cout << "3. Visit the APU Bila Bila" << endl;
				cout << "4. Go to Downtown" << endl;
				cout << "5. Go Home" << endl;
				cout << "What would you like to do? : ";
				cin >> option;

				if (!isInputValid())
				{
					continue;
				}
				switch (option)
				{
				case 1:
				{
					if (attendedClass)
					{
						cout << endl;
						slowPrint("You have already attended today's class!");
						break;
					}
					if (missedClass)
					{
						cout << endl;
						slowPrint("You arrived too late to attend the class.");
						slowPrint("The class has already finished.");
						break;
					}

					int classResult = attendingClassEncounter(student);

					attendedClass = true;

					if (classResult == 1)
					{
						cout << endl;
						slowPrint("You successfully completed the class!");
						slowPrint("You can continue exploration the campus.");
					}
					else if (classResult == 2)
					{
						cout << endl;
						slowPrint("You failed to understand the lecture.");
						slowPrint("You can still explore the campus.");
					}
					else // this is 3 and the player died!
					{
						explorationFinished = true;
					}
					break;
				}

				case 2:
				{
					PlayerStats playerBefore = student->tempStat();
					cout << endl;
					if (exploredCampus)
					{
						cout << endl;
						slowPrint("You have already explored the campus today.");
						break;
					}
					cout << endl;
					slowPrint("You decided to explore around the campus.");
					cout << endl;

					int randomEvent = randomExplorationEvent();
					if (randomEvent == 1)
					{
						slowPrint("You met a helpful senior student.");
						slowPrint("The senior helped you understand your assignment.");
						student->knowledge += 2;
						student->motivation += 2;

					}
					else if (randomEvent == 2)
					{
						slowPrint("You found RM 5 while you are walking around!");
						student->receiveMoney(5);
					}
					else
					{
						slowPrint("You were attracted by the activites in level 3, central point.");
						slowPrint("You joined some activities and had some fun.");
						student->motivation += 3;
						student->energy -= 5;
					}
					cout << endl;
					student->displayStatChanges(playerBefore);
					exploredCampus = true;
					break;
				}

				case 3:
				{
					cout << endl;
					slowPrint("You decided to visit the Bila Bila");
					cout << endl;

					campusShop(student);
					break;
				}

				case 4:
				{
					cout << endl;
					if (!attendedClass && missedClass)
					{
						slowPrint("You took the Train to KLCC.");
					}
					else if (!attendedClass)
					{
						slowPrint("You left APU before attending your class.");
						slowPrint("You will not be able to attend it later.");
						slowPrint("You took the Train to KLCC.");
						missedClass = true;
					}
					else
					{
						slowPrint("You took the Train to KLCC.");
					}
					
					currentLocation = 2;
					break;
				}	
				

				case 5:
				{
					cout << endl;
					if (!attendedClass)
					{
						slowPrint("You decided to go home without atted class.");
						student->knowledge -= 2;
						student->motivation -= 1;

						missedClass = true;
					}
					else
					{
						slowPrint("You decided to return home after class.");
					}
					explorationFinished = true;
					break;
				}

				default:
					cout << endl;
					cout << "Invalid Input! Try putting (1 to 5)" << endl;
					continue;

				}
			}
			else if (currentLocation == 2)
			{
				cout << endl;
				cout << "===== KLCC =====" << endl;
				cout << endl;

				cout << "1. Visit the Downtown Store" << endl;
				cout << "2. Search for a part-time job" << endl;
				cout << "3. Explore Downtown" << endl;
				cout << "4. Go to APU" << endl;
				cout << "5. Go Home" << endl;
				cout << "What would you like to do? : ";

				cin >> option;

				if (!isInputValid())
				{
					continue;
				}

				switch (option)
				{
				case 1:
				{
					cout << endl;
					slowPrint(
						"You decided to visit the Downtown Store."
					);

					cout << endl;

					downtownShop(student);
					break;
				}
				case 2:
				{
					PlayerStats playerBefore = student->tempStat();
					if (searchedPartTime)
					{
						cout << endl;
						slowPrint(
							"You already got a job"
						);

						break;
					}

					cout << endl;
					slowPrint(
						"You found a cafe looking for part-time workers."
					);

					slowPrint(
						"You decided to apply for the job"
					);
					slowPrint(
						"You received RM 15 for working for the first time!"
					);
					slowPrint(
						"You will also receive RM 15 everytime you come to KLCC and decide to work, with the cost of your energy"
					);


					cout << endl;
					student->receiveMoney(15);
					student->energy -= 15;
					student->motivation -= 1;
					student->displayStatChanges(playerBefore);

					searchedPartTime = true;
					break;
				}
				case 3:
				{
					PlayerStats playerBefore = student->tempStat();
					if (exploredDowntown)
					{
						cout << endl;
						slowPrint(
							"You have already explored Downtown today."
						);

						break;
					}

					cout << endl;
					slowPrint(
						"You decided to explore around Downtown."
					);

					cout << endl;

					int randomEvent =
						randomExplorationEvent();

					if (randomEvent == 1)
					{
						slowPrint(
							"You found a street performer."
						);

						slowPrint(
							"The performance improved your mood."
						);

						student->motivation += 3;
					}
					else if (randomEvent == 2)
					{
						slowPrint(
							"You helped someone carry their shopping bags."
						);

						slowPrint(
							"They gave you RM5 as thanks."
						);

						student->receiveMoney(5);
						student->energy -= 3;
					}
					else if (randomEvent == 3)
					{
						slowPrint(
							"You became lost while exploring Downtown."
						);

						slowPrint(
							"You walked for an hour before finding your way."
						);

						student->energy -= 10;
						student->focus -= 2;
					}
					else
					{
						slowPrint(
							"You met one of your classmates."
						);

						slowPrint(
							"Your classmate shared today's lecture notes."
						);

						student->knowledge += 2;
						student->motivation += 1;
					}
					student->displayStatChanges(playerBefore);
					exploredDowntown = true;
					break;
				}

				case 4:
				{
					cout << endl;
					slowPrint(
						"You decided to travel to APU."
					);

					if (missedClass)
					{
						slowPrint(
							"Today's class has already finished."
						);

						slowPrint(
							"You can still explore the campus and visit the store."
						);
					}

					currentLocation = 1;
					break;

				case 5:
					cout << endl;
					slowPrint(
						"You decided to return home from Downtown."
					);

					explorationFinished = true;
					break;
				}
				default:
				{
					cout << endl;
					cout << "Invalid Input! Try Putting (1 to 5)"
						<< endl;

					continue;
				}
				}
			}

			student->checkStats();

			if (!explorationFinished && student->isDead())
			{
				explorationFinished = true;
			}
		}
		student->checkStats();
		cout << endl;
		student->displayStatChanges(playerBefore);
		cout << "========================" << endl;
	}

}