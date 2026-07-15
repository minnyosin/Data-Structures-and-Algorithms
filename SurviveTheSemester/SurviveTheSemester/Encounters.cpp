#include "Encounters.h"
#include "Challenge.h"
#include "Display.h"
#include <random>
#include <iostream>
#include "Validations.h"

int randomEnemyAttack()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 3);
	return distrib(gen) + 1;
}

int phoneDistractionChallenge(Player* student)
{
	slowPrint("You encountered a Phone Distraction!");
	cout << endl;

	Challenge* phoneDistraction = new Challenge("Phone Distraction", 40, 5, 6);
	phoneDistraction->displayChallengeStats();


	while (
		phoneDistraction->challengeLevel > 0 &&
		student->focus > 0 &&
		phoneDistraction->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();
		ChallengeStats challengeBefore = phoneDistraction->tempStat();

		if (isYourTurn)
		{
			cout << endl;
			cout << "1. Focused Study" << endl;
			cout << "2. Turn Off Phone" << endl;
			cout << "3. Take a Break" << endl;
			cout << "What would you do? : ";

			cin >> option1;
			
			if (!isInputValid()) continue;


			switch (option1)
			{
			case 1:
				if (student->energy < phoneDistraction->pressure)
				{
					cout << endl;
					slowPrint("You don't have enough energy to study, try resting a bit!");
					continue;
				}
				cout << endl;
				slowPrint("You chose to continue studying!");
				slowPrint("You gained some knowledge with the cost of your energy.");
				slowPrint("You also forgot to use your phone while studying.");
				cout << endl;
				student->energy -= (phoneDistraction->pressure);
				student->knowledge += 1;
				phoneDistraction->challengeLevel -= (((student->energy / 100.0) * (student->motivation * (student->focus) * 0.01)) + (student->knowledge / 10.0));
				isYourTurn = false;
				break;

			case 2:
				cout << endl;
				slowPrint("You chose to turn off phone!");
				cout << endl;
				phoneDistraction->challengeLevel -= 15;
				student->motivation -= 1;
				slowPrint("Phone failed to distract! (phone will not make a move)");
				break;

			case 3:
				cout << endl;
				slowPrint("You chose to take a break!");
				slowPrint("You gained some energy and focus!");
				slowPrint("You also forgot to use your phone while taking a rest.");
				cout << endl;
				student->energy += 10;
				student->focus += 5;
				isYourTurn = false;
				break;

			default:
				cout << endl << "Invalid Input! Try Putting (1 or 2 or 3) " << endl;
				continue;
			}

		}
		if (phoneDistraction->isDead())
		{

			--phoneDistraction->challengeTime;
			slowPrint("You beat the Phone Distraction!");
			cout << endl;
			checkStats(student);
			cout << "==== Battle Result ====" << endl;
			student->displayPlayerStats();
			cout << endl;
			phoneDistraction->displayChallengeStats();
			return 1;
			break;
		}

		if (!isYourTurn)
		{
			slowPrint("But later...");
			cout << endl;
			slowPrint("Phone start distracting you!");
			cout << endl;
			int randomAttack = randomEnemyAttack();

			if (randomAttack == 1)
			{
				slowPrint("A new social media notification appears!");
				slowPrint("You instantly checked and you lost some of your focus!");
				student->focus -= 5;
			}
			else if (randomAttack == 2)
			{
				slowPrint("You start scrolling through short videos.");
				slowPrint("You really did not notice that you were doomscrolling and lost your focus!");
				student->focus -= 7;
			}
			else
			{
				slowPrint("You lose track of time checking messages.");
				slowPrint("Chatting with your friends made your energy drain!");
				student->energy -= 5;
			}
			isYourTurn = true;
		}
		cout << endl;
		--phoneDistraction->challengeTime;



		if (phoneDistraction->isTimeout())
		{

			slowPrint("You ran out of time, it is already bed time!");
			slowPrint("You could not beat your phone's distraction :(");
			cout << endl;
			student->motivation -= 2;
			student->focus -= 10;
			checkStats(student);
			cout << "==== Battle Result ====" << endl;
			student->displayPlayerStats();
			cout << endl;
			phoneDistraction->displayChallengeStats();
			if (student->isDead())
			{
				return 3;
				break;
			}
			return 2;
			break;
		}

		checkStats(student);



		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);
		cout << endl;
		phoneDistraction->displayStatChanges(challengeBefore);
		cout << endl << "=========================" << endl;

		if (student->isDead())
		{
			return 3;
			break;
		}

	}
	delete phoneDistraction;
}