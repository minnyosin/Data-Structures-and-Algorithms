#include "exploration.h"
#include "Encounters.h"
#include "shop.h"
#include "Display.h"
#include "Validations.h"
#include <iostream>
#include <random>
#include "Ascii.h"

using namespace std;

int randomExplorationEvent()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 3);
	
	return distrib(gen) + 1;
}
int weekTwoExploration(Player* student)
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
	slowPrint("===== WEEK 2 =====");
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
			apuAscii();
			slowPrint("You decided to go to APU and tried to attend class regularly.");
			slowPrint("You arrived before your class started.");
			cout << endl;

			currentLocation = 1;
			firstLocationChosen = true;
			break;

		case 2:
			cout << endl;
			klccAscii();
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
		
	}

		while (!explorationFinished)
		{
			if (currentLocation == 1)
			{
				if (student->energy <= 0)
				{
					cout << endl;
					slowPrint("You have completely run out of energy!");
					slowPrint("You cannot attend class or explore.");
					slowPrint("You must use an item or return home.");
					cout << endl;
				}

				cout << endl;
				cout << "===== APU Campus =====" << endl;
				cout << endl;

				cout << "1. Attend Class" << endl;
				cout << "2. Explore the Campus" << endl;
				cout << "3. Visit the APU Bila Bila" << endl;
				cout << "4. Open Inventory" << endl;
				cout << "5. Go to Downtown" << endl;
				cout << "6. Go Home" << endl;
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
					if (student->energy <= 0)
					{
						cout << endl;
						slowPrint("You don't have enough energy to attend class!");
						slowPrint("Buy and use an item, or return home.");
						break;
					}

					int classResult = attendingClassEncounter(student);

					attendedClass = true;

					if (classResult == 1)
					{
						cout << endl;
						slowPrint("After class, you still had time to explore the campus.");
					}
					else if (classResult == 2)
					{
						cout << endl;
						slowPrint("The class ended, but you could still explore the campus.");
					}
					else if (classResult == 3)
					{
						return 3;
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
					if (student->energy <= 0)
					{
						cout << endl;
						slowPrint("You are too tired to explore the campus!");
						slowPrint("Buy and use an item, or return home.");
						break;
					}
					cout << endl;
					slowPrint("You decided to explore around the campus.");
					cout << endl;

					int randomEvent = randomExplorationEvent();
					if (randomEvent == 1)
					{
						seniorAscii();
						slowPrint("You met a helpful senior student.");
						slowPrint("The senior helped you understand your assignment.");
						student->knowledge += 2;
						student->motivation += 2;

					}
					else if (randomEvent == 2)
					{
						moneyAscii();
						slowPrint("You found RM 5 while you are walking around!");
						student->receiveMoney(5);
					}
					else if (randomEvent == 3)
					{
						activityAscii();
						slowPrint("You were attracted by the activites in level 3, central point.");
						slowPrint("You joined some activities and had some fun.");
						student->motivation += 3;
						student->energy -= 5;
					}
					else
					{
						elevatorAscii();
						slowPrint("You entered the elevator during peak hour.");
						slowPrint("It stopped at almost every floor before reaching your destination.");
						slowPrint("You lost some energy and patience.");

						student->energy -= 3;
						student->focus -= 2;
					}
					cout << endl;
					student->checkStats();
					student->displayStatChanges(playerBefore);

					if (student->focus <= 0)
					{
						student->isDead();
						return 3;
					}
					exploredCampus = true;
					break;
				}

				case 3:
				{
					cout << endl;
					shopAscii();
					slowPrint("You decided to visit the Bila Bila");
					cout << endl;

					campusShop(student);
					break;
				}
				case 4:
				{
					cout << endl;
					student->openInventory();
					student->checkStats();
					break;
				}
				case 5:
				{
					cout << endl;
					if (!attendedClass && missedClass)
					{
						klccAscii();
						slowPrint("You took the Train to KLCC.");
					}
					else if (!attendedClass)
					{
						klccAscii();
						slowPrint("You left APU before attending your class.");
						slowPrint("You will not be able to attend it later.");
						slowPrint("You took the Train to KLCC.");
						missedClass = true;
					}
					else
					{
						klccAscii();
						slowPrint("You took the Train to KLCC.");
					}
					
					currentLocation = 2;
					break;
				}	
				

				case 6:
				{
					cout << endl;
					if (!attendedClass)
					{
						homeAscii();
						slowPrint("You decided to go home without attending class.");

						missedClass = true;
					}
					else
					{
						homeAscii();
						slowPrint("You decided to return home after class.");
					}
					slowPrint("You rested after returning home.");
					student->energy += 30;
					student->focus += 5;
					student->checkStats();
					explorationFinished = true;
					break;
				}

				default:
					cout << endl;
					cout << "Invalid Input! Try putting (1 to 6)" << endl;
					continue;

				}
			}
			else if (currentLocation == 2)
			{
				if (student->energy <= 0)
				{
					cout << endl;
					slowPrint("You have completely run out of energy!");
					slowPrint("You cannot work or explore Downtown.");
					slowPrint("You must use an item or return home.");
					cout << endl;
				}

				cout << endl;
				cout << "===== KLCC =====" << endl;
				cout << endl;

				cout << "1. Visit the Downtown Store" << endl;
				cout << "2. Search for a part-time job" << endl;
				cout << "3. Explore Downtown" << endl;
				cout << "4. Open Inventory" << endl;
				cout << "5. Go to APU" << endl;
				cout << "6. Go Home" << endl;
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
					storeAscii();
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
					if (student->energy < 15)
					{
						cout << endl;
						slowPrint("You don't have enough energy to work!");
						slowPrint("Working requires at least 15 Energy.");
						slowPrint("Buy and use an item, or return home.");
						break;
					}

					cout << endl;
					cafeAscii();
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
					student->hasPartTimeJob = true;
					student->receiveMoney(15);
					student->energy -= 15;
					student->motivation -= 1;
					student->checkStats();
					cout << endl;
					student->displayStatChanges(playerBefore);
					

					searchedPartTime = true;
					break;
				}
				case 3:
				{
					PlayerStats playerBefore = student->tempStat();
					cout << endl;
					
					if (exploredDowntown)
					{
						cout << endl;
						slowPrint(
							"You have already explored Downtown today."
						);

						break;
					}
					if (student->energy <= 0)
					{
						cout << endl;
						slowPrint("You are too tired to explore Downtown!");
						slowPrint("Buy and use an item, or return home.");
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
						streetAscii();
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
						bagAscii();
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
						lostAscii();
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
						classmateAscii();
						slowPrint(
							"You met one of your classmates."
						);

						slowPrint(
							"Your classmate shared today's lecture notes."
						);

						student->knowledge += 2;
						student->motivation += 1;
					}
					cout << endl;
					student->checkStats();
					student->displayStatChanges(playerBefore);
					if (student->focus <= 0)
					{
						student->isDead();
						return 3;
					}
					exploredDowntown = true;
					break;
				}
				case 4:
				{
					cout << endl;
					student->openInventory();
					student->checkStats();
					break;
				}
				case 5:
				{
					cout << endl;
					apuAscii();
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
				}
				case 6:
					cout << endl;
					homeAscii();
					slowPrint(
						
						"You decided to return home from Downtown."
					);
					slowPrint("You rested after returning home.");
					student->energy += 30;
					student->focus += 5;
					student->checkStats();
					explorationFinished = true;
					break;
				
				default:
				{
					cout << endl;
					cout << "Invalid Input! Try Putting (1 to 6)"<< endl;

					continue;
				}
				}
			}

			student->checkStats();
			if (student->focus <= 0)
			{
				student->isDead();
				return 3;
			}
		}
		if (!attendedClass)
		{
			cout << endl;
			slowPrint("You missed today's class.");
			slowPrint("You lost some knowledge and motivation.");

			student->knowledge -= 2;
			student->motivation -= 1;
		}
		student->checkStats();
		cout << endl;
		cout << "===== Week 2 Result =====" << endl;
		student->displayStatChanges(playerBefore);
		cout << "========================" << endl;
		
	
	return 1;
}
int weekSixExploration(Player* student)
{
	int option;
	int currentLocation = 1;

	bool explorationFinished = false;
	bool studiedLibrary = false;
	bool talkedToClassmates = false;
	bool workedPartTime = false;
	bool visitedGamingCafe = false;

	PlayerStats playerBefore = student->tempStat();

	cout << endl;
	slowPrint("===== Week 6 Exploration =====");
	cout << endl;
	slowPrint("The Surprise Quiz was finally over.");
	slowPrint("You still had some time before returning home.");

	while (!explorationFinished)
	{
		if (currentLocation == 1)
		{
			if (student->energy <= 0)
			{
				cout << endl;
				slowPrint("You have completely run out of energy!");

				slowPrint("You must use an item or return home.");

				cout << endl;
			}

			cout << endl;
			cout << "===== APU =====" << endl;
			cout << endl;

			cout << "1. Study at the Library" << endl;
			cout << "2. Talk to Your Classmates" << endl;
			cout << "3. Visit the APU Bila Bila" << endl;
			cout << "4. Open Inventory" << endl;
			cout << "5. Go to KLCC" << endl;
			cout << "6. Go Home" << endl;
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
				PlayerStats activityBefore =
					student->tempStat();

				if (studiedLibrary)
				{
					cout << endl;
					slowPrint("You have already studied at the library today.");

					break;
				}

				if (student->energy < 7)
				{
					cout << endl;
					slowPrint("You don't have enough energy to study at the library!");

					slowPrint("You need at least 7 Energy.");

					break;
				}

				cout << endl;
				libraryAscii();
				slowPrint("You decided to study at the library.");

				slowPrint("Even though the lecturer has not officially announced the assignment,");

				slowPrint("you started preparing for it.");

				slowPrint("You gained Knowledge, but used some Energy.");

				cout << endl;

				student->knowledge += 4;
				student->energy -= 7;

				student->checkStats();
				student->displayStatChanges(activityBefore);

				studiedLibrary = true;
				break;
			}

			case 2:
			{
				PlayerStats activityBefore = student->tempStat();

				if (talkedToClassmates)
				{
					cout << endl;
					slowPrint("You have already spoken to your classmates today.");

					break;
				}

				if (student->energy <= 0)
				{
					cout << endl;
					slowPrint("You are too tired to speak with your classmates.");

					break;
				}

				cout << endl;
				classmatesAscii();
				slowPrint("You spoke with your classmates about the upcoming assignment.");

				slowPrint("They gave you their information from seniors.");

				student->knowledge += 1;
				student->motivation += 2;
				student->energy -= 2;

				student->checkStats();

				cout << endl;
				student->displayStatChanges(activityBefore);

				talkedToClassmates = true;
				break;
			}

			case 3:
				cout << endl;
				shopAscii();
				slowPrint("You decided to visit the APU Bila Bila.");

				cout << endl;
				campusShop(student);
				break;

			case 4:
				cout << endl;
				student->openInventory();
				student->checkStats();
				break;

			case 5:
				cout << endl;
				klccAscii();
				slowPrint("You decided to travel to KLCC.");

				currentLocation = 2;
				break;

			case 6:
				cout << endl;
				homeAscii();
				slowPrint("You decided to return home.");

				slowPrint("You rested well after a long hard week.");

				student->energy += 25;
				student->focus += 5;
				student->checkStats();

				explorationFinished = true;
				break;

			default:
				cout << endl;
				cout << "Invalid Input! Try Putting (1 to 6)"<< endl;

				continue;
			}
		}
		else if (currentLocation == 2)
		{
			if (student->energy <= 0)
			{
				cout << endl;
				slowPrint("You have completely run out of energy!");

				slowPrint("You must use an item or return home.");

				cout << endl;
			}

			cout << endl;
			cout << "===== KLCC =====" << endl;
			cout << endl;

			cout << "1. Work at Your Part-Time Job" << endl;
			cout << "2. Visit the Downtown Store" << endl;
			cout << "3. Visit the Gaming Cafe" << endl;
			cout << "4. Open Inventory" << endl;
			cout << "5. Go to APU" << endl;
			cout << "6. Go Home" << endl;
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
				PlayerStats activityBefore = student->tempStat();
				if (!student->hasPartTimeJob)
				{
					cout << endl;
					slowPrint("You do not have a part-time job!");
					break;
				}
				if (workedPartTime)
				{
					cout << endl;
					slowPrint("You have already worked today.");

					break;
				}

				if (student->energy < 15)
				{
					cout << endl;
					slowPrint("You don't have enough energy to work!");

					slowPrint("Working requires at least 15 Energy.");

					break;
				}

				cout << endl;
				slowPrint("You worked at your part-time job.");

				slowPrint("You received RM15, but the work made you tired.");

				cout << endl;

				student->receiveMoney(15);
				student->energy -= 15;
				student->motivation -= 1;

				student->checkStats();

				cout << endl;
				student->displayStatChanges(activityBefore);

				workedPartTime = true;
				break;
			}

			case 2:
				cout << endl;
				storeAscii();
				slowPrint("You decided to visit the Downtown Store.");

				cout << endl;
				downtownShop(student);
				break;

			case 3:
			{
				PlayerStats activityBefore = student->tempStat();

				if (visitedGamingCafe)
				{
					cout << endl;
					slowPrint("You have already visited the Gaming Cafe today.");

					break;
				}

				if (student->energy <= 0)
				{
					cout << endl;
					slowPrint("You are too tired to visit the Gaming Cafe.");

					break;
				}

				cout << endl;
				gamingAscii();
				slowPrint("You decided to visit the Gaming Cafe.");

				slowPrint("Playing games costs RM8.");

				if (student->spendMoney(8))
				{
					cout << endl;
					slowPrint("You played games and forgot about your stress.");

					student->motivation += 3;
					student->focus -= 4;
					student->energy -= 3;

					student->checkStats();

					cout << endl;
					student->displayStatChanges(activityBefore);

					visitedGamingCafe = true;
				}

				break;
			}

			case 4:
				cout << endl;
				student->openInventory();
				student->checkStats();
				break;

			case 5:
				cout << endl;
				apuAscii();
				slowPrint("You decided to return to APU.");

				currentLocation = 1;
				break;

			case 6:
				cout << endl;
				homeAscii();
				slowPrint("You decided to return home from KLCC.");

				slowPrint("You rested well after a long hard week.");

				student->energy += 25;
				student->focus += 5;
				student->checkStats();

				explorationFinished = true;
				break;

			default:
				cout << endl;
				cout << "Invalid Input! Try Putting (1 to 6)"<< endl;

				continue;
			}
		}

		student->checkStats();

		if (student->focus <= 0)
		{
			student->isDead();
			return 3;
		}
	}

	cout << endl;
	cout << "===== Week 6 Result ====="<< endl;

	student->displayStatChanges(playerBefore);

	cout << "========================="<< endl;

	return 1; 
}
int weekThirteenExploration(Player* student)
{
	int option;
	int currentLocation = 1;

	bool explorationFinished = false;
	bool studiedLibrary = false;
	bool studiedWithClassmates = false; 
	bool workedPartTime = false;
	bool gotoMovie = false;

	PlayerStats playerBefore = student->tempStat();

	slowPrint("===== WEEK 13 =====");
	cout << endl;

	slowPrint("You just finished the last class of the semester.");
	slowPrint("You are now free of any classes, you are allowed to study on your own before the final exam.");


	while (!explorationFinished)
	{
		if (currentLocation == 1)
		{
			if (student->energy <= 0)
			{
				cout << endl;
				slowPrint("You have completely run out of energy!");

				slowPrint("You must use an item or return home.");

				cout << endl;
			}

			cout << endl;
			cout << "===== APU =====" << endl;
			cout << endl;

			cout << "1. Study at the Library" << endl;
			cout << "2. Study with Your Classmates" << endl;
			cout << "3. Visit the APU Bila Bila" << endl;
			cout << "4. Open Inventory" << endl;
			cout << "5. Go to KLCC" << endl;
			cout << "6. Go Home" << endl;
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
				PlayerStats activityBefore =
					student->tempStat();

				if (studiedLibrary)
				{
					cout << endl;
					slowPrint("You have already studied at the library today.");

					break;
				}

				if (student->energy < 7)
				{
					cout << endl;
					slowPrint("You don't have enough energy to study at the library!");

					slowPrint("You need at least 7 Energy.");

					break;
				}

				cout << endl;
				libraryAscii();
				slowPrint("You decided to study at the library.");

				slowPrint("You started preparing for the final exam.");

				slowPrint("You gained Knowledge, but used some Energy.");

				cout << endl;

				student->knowledge += 4;
				student->energy -= 7;

				student->checkStats();
				student->displayStatChanges(activityBefore);

				studiedLibrary = true;
				break;
			}

			case 2:
			{
				PlayerStats activityBefore = student->tempStat();

				if (studiedWithClassmates)
				{
					cout << endl;
					slowPrint("You have already studied with your classmates.");

					break;
				}

				if (student->energy < 7)
				{
					cout << endl;
					slowPrint("You are too tired to study with your classmates.");

					break;
				}

				cout << endl;
				classmatesAscii();
				slowPrint("You studied together with your classmates for the final exam.");

				slowPrint("They explained you the topics that you don't understand.");

				student->knowledge += 4;
				student->motivation += 2;
				student->energy -= 7;

				student->checkStats();

				cout << endl;
				student->displayStatChanges(activityBefore);

				studiedWithClassmates = true;
				break;
			}

			case 3:
				cout << endl;
				shopAscii();
				
				slowPrint("You decided to visit the APU Bila Bila.");

				cout << endl;
				campusShop(student);
				break;

			case 4:
				cout << endl;
				student->openInventory();
				student->checkStats();
				break;

			case 5:
				cout << endl;
				klccAscii();
				slowPrint("You decided to travel to KLCC.");

				currentLocation = 2;
				break;

			case 6:
				cout << endl;
				homeAscii();
				slowPrint("You decided to return home.");

				slowPrint("You rested well for this week");

				student->energy += 15;
				student->focus += 5;
				student->checkStats();

				explorationFinished = true;
				break;

			default:
				cout << endl;
				cout << "Invalid Input! Try Putting (1 to 6)" << endl;

				continue;
			}
		}
		else if (currentLocation == 2)
		{
			if (student->energy <= 0)
			{
				cout << endl;
				slowPrint("You have completely run out of energy!");

				slowPrint("You must use an item or return home.");

				cout << endl;
			}

			cout << endl;
			cout << "===== KLCC =====" << endl;
			cout << endl;

			cout << "1. Work at Your Part-Time Job" << endl;
			cout << "2. Visit the Downtown Store" << endl;
			cout << "3. Visit TGV and watch a movie" << endl;
			cout << "4. Open Inventory" << endl;
			cout << "5. Go to APU" << endl;
			cout << "6. Go Home" << endl;
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
				PlayerStats activityBefore = student->tempStat();

				if (!student->hasPartTimeJob)
				{
					cout << endl;
					slowPrint("You do not have a part-time job!");
					break;
				}
				if (workedPartTime)
				{
					cout << endl;
					slowPrint("You have already worked today.");

					break;
				}

				if (student->energy < 15)
				{
					cout << endl;
					slowPrint("You don't have enough energy to work!");

					slowPrint("Working requires at least 15 Energy.");

					break;
				}

				cout << endl;
				cafeAscii();
				slowPrint("You worked at your part-time job.");

				slowPrint("You received RM15, but the work made you tired.");

				cout << endl;

				student->receiveMoney(15);
				student->energy -= 15;
				student->motivation -= 1;

				student->checkStats();

				cout << endl;
				student->displayStatChanges(activityBefore);

				workedPartTime = true;
				break;
			}

			case 2:
				cout << endl;
				storeAscii();
				slowPrint("You decided to visit the Downtown Store.");

				cout << endl;
				downtownShop(student);
				break;

			case 3:
			{
				PlayerStats activityBefore = student->tempStat();

				if (gotoMovie)
				{
					cout << endl;
					slowPrint("You have already watched a movie today.");

					break;
				}

				if (student->energy <= 0)
				{
					cout << endl;
					slowPrint("You are too tired even to watch a movie");
					slowPrint("You might fall asleep!");

					break;
				}

				cout << endl;
				cinemaAscii();
				slowPrint("You decided to watch a movie.");

				slowPrint("Watching movie costs RM10.");

				if (student->spendMoney(10))
				{
					cout << endl;
					slowPrint("You watched the movie and forgot about your stress.");
					slowPrint("The movie was not amazing, but you enjoyed taking a break.");

					student->motivation += 3;
					student->focus -= 4;
					student->energy -= 3;

					student->checkStats();

					cout << endl;
					student->displayStatChanges(activityBefore);

					gotoMovie = true;
				}

				break;
			}

			case 4:
				cout << endl;
				student->openInventory();
				student->checkStats();
				break;

			case 5:
				cout << endl;
				apuAscii();
				slowPrint("You decided to return to APU.");

				currentLocation = 1;
				break;

			case 6:
				cout << endl;
				homeAscii();
				slowPrint("You decided to return home from KLCC.");

				slowPrint("You rested well for this week.");

				student->energy += 15;
				student->focus += 5;
				student->checkStats();

				explorationFinished = true;
				break;

			default:
				cout << endl;
				cout << "Invalid Input! Try Putting (1 to 6)" << endl;

				continue;
			}
		}

		student->checkStats();

		if (student->focus <= 0)
		{
			student->isDead();
			return 3;
		}
	}

	cout << endl;
	cout << "===== Week 13 Result =====" << endl;

	student->displayStatChanges(playerBefore);

	cout << "=========================" << endl;

	return 1;
}