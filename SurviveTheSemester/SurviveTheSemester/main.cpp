#include "Player.h"
#include "Challenge.h"
#include "Encounters.h"
#include "Display.h"
#include "Validations.h"
#include "exploration.h"
#include <iostream>
#include <random>
#include "Ascii.h"

using namespace std;

int randomLuck()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 20);

	return distrib(gen);
}

void copyPlayerData(Player* originalPlayer, Player* copiedPlayer)
{
	copiedPlayer->name = originalPlayer->name;
	copiedPlayer->focus = originalPlayer->focus;
	copiedPlayer->knowledge = originalPlayer->knowledge;
	copiedPlayer->energy = originalPlayer->energy;
	copiedPlayer->motivation = originalPlayer->motivation;
	copiedPlayer->luck = originalPlayer->luck;
	copiedPlayer->money = originalPlayer->money;
	copiedPlayer->studyNotesAvailable = originalPlayer->studyNotesAvailable;
	copiedPlayer->hasPartTimeJob = originalPlayer->hasPartTimeJob;
	copiedPlayer->inventory.clear();
	

	InventoryNode* current = originalPlayer->inventory.head;

	while (current != nullptr)
	{
		copiedPlayer->inventory.insertAtEnd(current->item, current->quantity);

		current = current->next;
	}
}

bool askRetryCurrentWeek()
{
	while (true)
	{
		char option;

		cout << endl;
		cout << "Do you want to retry this week? (y/n): ";
		cin >> option;

		if (!isInputValid())
		{
			continue;
		}

		if (option == 'y' || option == 'Y')
		{
			return true;
		}
		else if (option == 'n' || option == 'N')
		{
			return false;
		}
		else
		{
			cout << "Invalid Input!" << endl;
		}
	}
}

int playWeekSixToTwelve(Player* student)
{
	cout << endl;
	cout << "===== WEEK 6 =====" << endl;
	cout << endl;

	slowPrint("You arrived at APU expecting a normal class.");
	slowPrint("However, the lecturer surprised you with surprise quiz!");

	int quizResult = surpriseQuizChallenge(student);

	if (quizResult == 3)
	{
		return 3;
	}

	if (quizResult == 1)
	{
		cout << endl;
		slowPrint("You passed the Surprise Quiz!");
	}
	else if (quizResult == 2)
	{
		cout << endl;
		slowPrint("You failed the Surprise Quiz.");
		slowPrint("However, your semester continued.");
	}

	int explorationResult = weekSixExploration(student);

	if (explorationResult == 3)
	{
		return 3;
	}

	cout << endl;

	int groupResult = groupAssignmentChallenge(student);

	if (groupResult == 3)
	{
		return 3;
	}
	else if (groupResult == 2)
	{
		cout << endl;
		slowPrint("You failed to submit the Group Assignment properly.");
		slowPrint("However, you were still allowed to continue the semester.");
	}

	return 1;
}

int main()
{
	title();
	slowPrint("Welcome to APU!");
	slowPrint("You are challenged to finish the semester");

	cout << endl;

	int playerLuck = randomLuck();

	string playerName = setName();

	Player* student = new Player(playerName, playerLuck);

	student->displayPlayerStats();

// week 1

	Player* weekOneCheckpoint = new Player(playerName, playerLuck);

	copyPlayerData(student, weekOneCheckpoint);

	bool weekOneFinished = false;

	while (!weekOneFinished)
	{
		cout << endl;
		slowPrint("You are currently at WEEK 1 of your semester...");

		cout << endl;
		slowPrint("5:30 PM...");

		cout << endl;
		slowPrint("You just got back from school and tried to study...");

		int playerWin = phoneDistractionChallenge(student);

		switch (playerWin)
		{
		case 1:
			cout << endl;
			slowPrint("Your very first week of the semester finished like that...");

			weekOneFinished = true;
			break;

		case 2:
			cout << endl;
			slowPrint("You failed to overcome your Phone Distraction.");

			slowPrint("However, you still continued your semester.");

			weekOneFinished = true;
			break;

		case 3:
			cout << endl;
			slowPrint("You could not survive Week 1.");

			if (askRetryCurrentWeek())
			{
				copyPlayerData(weekOneCheckpoint, student);

				cout << endl;
				slowPrint("Restarting Week 1...");
			}
			else
			{
				delete weekOneCheckpoint;
				delete student;

				return 0;
			}

			break;

		default:
			cout << endl;
			cout << "Unknown encounter result!"<< endl;

			delete weekOneCheckpoint;
			delete student;

			return 0;
		}
	}

	delete weekOneCheckpoint;

// week 2

	Player* weekTwoCheckpoint = new Player(playerName, playerLuck);

	copyPlayerData(student, weekTwoCheckpoint);

	bool weekTwoFinished = false;

	while (!weekTwoFinished)
	{
		int explorationResult = weekTwoExploration(student);

		switch (explorationResult)
		{
		case 1:
			cout << endl;
			slowPrint("You finished your Week 2 exploration.");

			weekTwoFinished = true;
			break;

		case 3:
			cout << endl;
			slowPrint("You could not survive Week 2.");

			if (askRetryCurrentWeek())
			{
				copyPlayerData(weekTwoCheckpoint, student);

				cout << endl;
				slowPrint("Restarting Week 2...");
			}
			else
			{
				delete weekTwoCheckpoint;
				delete student;

				return 0;
			}

			break;

		default:
			cout << endl;
			cout << "Unknown exploration result!"<< endl;

			delete weekTwoCheckpoint;
			delete student;

			return 0;
		}
	}

	delete weekTwoCheckpoint;

// week 6 - 12

	cout << endl;
	slowPrint("The following weeks passed quickly...");

	slowPrint("You continued attending classes and completing your work.");

	slowPrint("Before you realised it, Week 6 had arrived.");

	student->energy += 25;
	student->focus += 10;
	student->checkStats();


	Player* weekSixToTwelveCheckpoint = new Player(playerName, playerLuck);

	copyPlayerData(student, weekSixToTwelveCheckpoint);

	bool weekSixToTwelveFinished = false;

	while (!weekSixToTwelveFinished)
	{
		int weekSixToTwelveResult = playWeekSixToTwelve(student);

		if (weekSixToTwelveResult == 1)
		{
			cout << endl;
			slowPrint("You survived the mid sem period!");

			weekSixToTwelveFinished = true;
		}
		else if (weekSixToTwelveResult == 3)
		{
			cout << endl;
			slowPrint("You could not survive mid sem weeks.");

			if (askRetryCurrentWeek())
			{
				copyPlayerData(weekSixToTwelveCheckpoint, student);

				cout << endl;
				slowPrint("Restarting from Week 6...");
			}
			else
			{
				delete weekSixToTwelveCheckpoint;
				delete student;

				return 0;
			}
		}
		else
		{
			cout << endl;
			cout << "Unknown mid sem weeks result!"<< endl;

			delete weekSixToTwelveCheckpoint;
			delete student;

			return 0;
		}
	}

	delete weekSixToTwelveCheckpoint;

// week 13 - 15

	Player* weekThirteenCheckpoint = new Player(playerName, playerLuck);

	copyPlayerData(student, weekThirteenCheckpoint);

	bool semesterFinished = false;

	while (!semesterFinished)
	{
	
	// week 13

		bool weekThirteenFinished = false;

		while (!weekThirteenFinished)
		{
			int weekThirteenResult = weekThirteenExploration(student);

			if (weekThirteenResult == 1)
			{
				cout << endl;
				slowPrint("Another week passed just like that...");

				weekThirteenFinished = true;
			}
			else if (weekThirteenResult == 3)
			{
				cout << endl;
				slowPrint("You could not survive Week 13.");

				if (askRetryCurrentWeek())
				{
					copyPlayerData(weekThirteenCheckpoint,student);

					cout << endl;
					slowPrint("Restarting from Week 13...");
				}
				else
				{
					delete weekThirteenCheckpoint;
					delete student;

					return 0;
				}
			}
			else
			{
				cout << endl;
				cout << "Unknown Week 13 result!"<< endl;

				delete weekThirteenCheckpoint;
				delete student;

				return 0;
			}
		}


	// week 14

		cout << endl;

		Player* weekFourteenCheckpoint = new Player(playerName, playerLuck);

		copyPlayerData(student,weekFourteenCheckpoint);

		bool weekFourteenFinished = false;

		while (!weekFourteenFinished)
		{
			int weekFourteenResult = procrastinationChallenge(student);

			if (weekFourteenResult == 1)
			{

				weekFourteenFinished = true;
			}
			else if (weekFourteenResult == 2)
			{

				weekFourteenFinished = true;
			}
			else if (weekFourteenResult == 3)
			{
				cout << endl;
				slowPrint("You could not survive Week 14.");

				if (askRetryCurrentWeek())
				{
					copyPlayerData(weekFourteenCheckpoint,student);

					cout << endl;
					slowPrint("Restarting from Week 14...");
				}
				else
				{
					delete weekFourteenCheckpoint;
					delete weekThirteenCheckpoint;
					delete student;

					return 0;
				}
			}
			else
			{
				cout << endl;
				cout << "Unknown Week 14 result!"<< endl;

				delete weekFourteenCheckpoint;
				delete weekThirteenCheckpoint;
				delete student;

				return 0;
			}
		}

		delete weekFourteenCheckpoint;


	// week 15 - final examination

		Player* finalExamCheckpoint = new Player(playerName, playerLuck);

		copyPlayerData(student, finalExamCheckpoint);

		bool finalExamFinished = false;

		while (!finalExamFinished)
		{
			int finalExamResult = finalExamChallenge(student);

			if (finalExamResult == 1)
			{
				cout << endl;

				cout << endl;
				cout << "================================" << endl;

				cout << "       SEMESTER COMPLETED" << endl;

				cout << "================================" << endl;

				finalExamFinished = true;
				semesterFinished = true;
			}
			else if (
				finalExamResult == 2 || finalExamResult == 3)
			{
				int option;
				bool finalChoiceMade = false;

				cout << endl;
				while (!finalChoiceMade)
				{
					cout << endl;
					cout << "1. Quit the Game" << endl;
					cout << "2. Retry the Final Exam" << endl;

					cout << "3. Replay from Week 13" << endl;

					cout << "What would you like to do? : ";

					cin >> option;

					if (!isInputValid())
					{
						continue;
					}

					switch (option)
					{
					case 1:
						cout << endl;
						slowPrint("You decided to end your semester journey.");

						delete finalExamCheckpoint;
						delete weekThirteenCheckpoint;
						delete student;

						return 0;

					case 2:
						copyPlayerData(finalExamCheckpoint, student);

						cout << endl;
						slowPrint("Restarting the Final Exam...");

						finalChoiceMade = true;
						break;

					case 3:
						copyPlayerData(weekThirteenCheckpoint, student);

						cout << endl;
						slowPrint("Returning to Week 13...");

						finalExamFinished = true;
						finalChoiceMade = true;
						break;

					default:
						cout << endl;
						cout << "Invalid Input! Try Putting (1 to 3)" << endl;

						continue;
					}
				}
			}
			else
			{
				cout << endl;
				cout << "Unknown Final Exam result!" << endl;

				delete finalExamCheckpoint;
				delete weekThirteenCheckpoint;
				delete student;

				return 0;
			}
		}

		delete finalExamCheckpoint;
	}

	delete weekThirteenCheckpoint;

	delete student;
	return 0;
}