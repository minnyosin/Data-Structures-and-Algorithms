#include "Encounters.h"
#include "Challenge.h"
#include "Display.h"
#include <random>
#include <iostream>
#include "Validations.h"
#include "Ascii.h"

int randomEnemyAttack()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(0, 3);
	return distrib(gen) + 1;
}
int randomLuckCheck()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distrib(1, 20);

	return distrib(gen);
}

int phoneDistractionChallenge(Player* student)
{
	cout << endl;
	phoneAscii();
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
		student->checkStats();
		if (student->isDead())
		{
			delete phoneDistraction;
			return 3;
		}
		if (phoneDistraction->isDead())
		{

			--phoneDistraction->challengeTime;
			slowPrint("You beat the Phone Distraction!");
			cout << endl;
			student->checkStats();
			cout << "==== Battle Result ====" << endl;
			student->displayPlayerStats();
			cout << endl;
			phoneDistraction->displayChallengeStats();
			delete phoneDistraction;
			return 1;
		}

		if (!isYourTurn)
		{
			slowPrint("But later...");
			cout << endl;
			slowPrint("Your phone starts distracting you!");
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

			slowPrint("You ran out of time, it is already bedtime!");
			slowPrint("You could not beat your phone's distraction :(");
			cout << endl;
			student->motivation -= 2;
			student->focus -= 10;
			student->checkStats();
			cout << "==== Battle Result ====" << endl;
			student->displayPlayerStats();
			cout << endl;
			phoneDistraction->displayChallengeStats();
			if (student->isDead())
			{
				delete phoneDistraction;
				return 3;
			}
			delete phoneDistraction;
			return 2;
		}

		student->checkStats();



		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);
		cout << endl;
		phoneDistraction->displayStatChanges(challengeBefore);
		cout << endl << "=========================" << endl;

		if (student->isDead())
		{
			delete phoneDistraction;
			return 3;
		}

	}
	delete phoneDistraction;
	return 2;
}

int attendingClassEncounter(Player* student)
{
	classroomAscii();
	cout << endl;
	slowPrint("You decided to attend your class!");
	cout << endl;

	Challenge* difficultLecture = new Challenge("Difficult Lecture", 60, 6, 7);

	difficultLecture->displayChallengeStats();

	float knowledgeBeforeClass = student->knowledge;

	while (
		difficultLecture->challengeLevel > 0 &&
		student->focus > 0 &&
		difficultLecture->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();
		ChallengeStats challengeBefore = difficultLecture->tempStat();

		if (isYourTurn)
		{
			cout << endl;
			cout << "1. Listen Carefully" << endl;
			cout << "2. Take Detailed Notes" << endl;
			cout << "3. Ask the Lecturer" << endl;
			cout << "4. Open Inventory" << endl;
			cout << "What would you do? : ";

			cin >> option1;

			if (!isInputValid())
			{
				continue;
			}

			switch (option1)
			{
			case 1:
				if (student->energy < difficultLecture->pressure)
				{
					cout << endl;
					slowPrint("You don't have enough energy to listen carefully!");
					slowPrint("Try recovering some energy first.");

					continue;
				}

				cout << endl;
				slowPrint("You focused on what the lecturer was explaining.");
				slowPrint("You understood some parts of the difficult topic.");
				slowPrint("You gained knowledge, but used some energy.");

				cout << endl;

				student->energy -= difficultLecture->pressure;

				student->knowledge += 2;

				difficultLecture->challengeLevel -= (((student->energy / 100.0) * (student->motivation * student->focus * 0.01))+(student->knowledge / 10.0));

				isYourTurn = false;
				break;

			case 2:
				if (student->focus < 5)
				{
					cout << endl;
					slowPrint("You don't have enough focus to take notes!");

					continue;
				}

				cout << endl;
				slowPrint("You started taking detailed notes.");
				slowPrint("Writing everything helped you understand the topic.");
				slowPrint("However, taking notes used some of your focus.");

				cout << endl;

				student->focus -= 5;
				student->knowledge += 2;

				difficultLecture->challengeLevel -= 12;

				isYourTurn = false;
				break;

			case 3:
				if (student->motivation < 1)
				{
					cout << endl;
					slowPrint("You don't have enough motivation to ask a question!");

					continue;
				}

				cout << endl;
				slowPrint("You raised your hand and asked the lecturer a question.");
				slowPrint("The lecturer explained the difficult topic again.");
				slowPrint("You gained a lot of knowledge from the explanation.");

				cout << endl;

				student->motivation -= 1;
				student->knowledge += 3;

				difficultLecture->challengeLevel -= 18;

				slowPrint("You were too busy speaking with the lecturer.");
				slowPrint("Nothing distracted you during this round!");

				break;

			case 4:
				student->openInventory();
				student->checkStats();

				if (student->isDead())
				{
					delete difficultLecture;
					return 3;
				}

				continue;

			default:
				cout << endl;
				cout << "Invalid Input! Try Putting (1 to 4)"<< endl;

				continue;
			}
		}
		student->checkStats();
		if (student->isDead())
		{
			delete difficultLecture;
			return 3;
		}
		if (difficultLecture->isDead())
		{
			--difficultLecture->challengeTime;

			cout << endl;
			slowPrint("You successfully finished attending the class!");
			slowPrint("You understood the difficult lecture.");
			slowPrint("You kept all the knowledge you gained during class!");

			cout << endl;

			student->checkStats();

			cout << "==== Class Result ====" << endl;
			student->displayPlayerStats();

			cout << endl;
			difficultLecture->displayChallengeStats();

			delete difficultLecture;
			return 1;
		}

		if (!isYourTurn)
		{
			slowPrint("But suddenly...");
			cout << endl;

			int randomAttack = randomEnemyAttack();

			if (randomAttack == 1)
			{
				slowPrint("The lecturer started explaining a very difficult part!");
				slowPrint("You became confused and lost some focus.");

				student->focus -= 6;
			}
			else if (randomAttack == 2)
			{
				slowPrint("A notification appeared on your phone!");
				slowPrint("You checked your phone and missed part of the explanation.");

				student->focus -= 5;
			}
			else if (randomAttack == 3)
			{
				slowPrint("Your friend started speaking to you during class.");
				slowPrint("You tried to listen to your friend and the lecturer together.");
				slowPrint("You lost some focus and energy.");

				student->focus -= 4;
				student->energy -= 3;
			}
			else
			{
				slowPrint("The lecturer started explaining the topic too quickly!");
				slowPrint("You struggled to follow the explanation.");

				student->energy -= 6;
				student->motivation -= 1;
			}

			isYourTurn = true;
		}

		cout << endl;
		--difficultLecture->challengeTime;

		if (difficultLecture->isTimeout())
		{
			slowPrint("The class has ended!");
			slowPrint("You could not understand the difficult lecture.");
			slowPrint("You lost all the knowledge gained during this class.");

			cout << endl;

			student->knowledge = knowledgeBeforeClass;

			student->motivation -= 2;
			student->focus -= 5;

			student->checkStats();

			cout << "==== Class Result ====" << endl;
			student->displayPlayerStats();

			cout << endl;
			difficultLecture->displayChallengeStats();

			if (student->isDead())
			{
				delete difficultLecture;
				return 3;
			}

			delete difficultLecture;
			return 2;
		}

		student->checkStats();

		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);

		cout << endl;
		difficultLecture->displayStatChanges(challengeBefore);

		cout << endl;
		cout << "=========================" << endl;

		if (student->isDead())
		{
			student->knowledge = knowledgeBeforeClass;

			delete difficultLecture;
			return 3;
		}
	}

	student->knowledge = knowledgeBeforeClass;

	delete difficultLecture;
	return 2;
}

int surpriseQuizChallenge(Player* student)
{
	testAscii();
	cout << endl;
	slowPrint("You encountered a Surprise Quiz!");
	cout << endl;

	Challenge* surpriseQuiz = new Challenge("Surprise Quiz", 70, 8, 6);

	surpriseQuiz->displayChallengeStats();

	while (
		surpriseQuiz->challengeLevel > 0 &&
		student->focus > 0 &&
		surpriseQuiz->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();

		ChallengeStats challengeBefore = surpriseQuiz->tempStat();

		cout << endl;
		cout << "1. Answer Using Your Knowledge" << endl;
		cout << "2. Think Carefully" << endl;
		cout << "3. Make a Lucky Guess" << endl;
		cout << "4. Open Inventory" << endl;
		cout << "What would you do? : ";

		cin >> option1;

		if (!isInputValid())
		{
			continue;
		}

		switch (option1)
		{
		case 1:
			if (student->energy < surpriseQuiz->pressure)
			{
				cout << endl;
				slowPrint("You don't have enough energy to answer the question!");
				slowPrint("Try recovering some energy first.");

				continue;
			}

			cout << endl;
			slowPrint("You used your knowledge to answer the question.");
			slowPrint("You remembered something from your previous classes.");

			cout << endl;

			student->energy -= surpriseQuiz->pressure;

			surpriseQuiz->challengeLevel -= (student->knowledge / 2.0);

			isYourTurn = false;
			break;

		case 2:
			if (student->focus < 6)
			{
				cout << endl;
				slowPrint("You don't have enough focus to think carefully!");

				continue;
			}

			cout << endl;
			slowPrint("You carefully examined every possible answer.");
			slowPrint("You found an answer that made the most sense.");

			cout << endl;

			student->focus -= 6;
			surpriseQuiz->challengeLevel -= 15;

			isYourTurn = false;
			break;

		case 3:
		{
			cout << endl;
			slowPrint("You could not remember the answer.");
			slowPrint("You decided to make a lucky guess!");

			cout << endl;

			int luckResult = randomLuckCheck();

			cout << "Your Luck : " << student->luck << endl;

			cout << "Luck Roll : " << luckResult << endl;

			if (luckResult <= student->luck)
			{
				cout << endl;
				slowPrint("Your lucky guess was correct!");

				surpriseQuiz->challengeLevel -= 25;
			}
			else
			{
				cout << endl;
				slowPrint("Your lucky guess was completely wrong!");
				slowPrint("You began doubting your other answers.");

				student->focus -= 8;
				student->motivation -= 1;
			}

			isYourTurn = false;
			break;
		}

		case 4:
			cout << endl;
			student->openInventory();
			student->checkStats();

			if (student->isDead())
			{
				delete surpriseQuiz;
				return 3;
			}

			continue;

		default:
			cout << endl;
			cout << "Invalid Input! Try Putting (1 to 4)"<< endl;

			continue;
		}
		student->checkStats();
		if (student->isDead())
		{
			delete surpriseQuiz;
			return 3;
		}
		if (surpriseQuiz->isDead())
		{
			--surpriseQuiz->challengeTime;

			cout << endl;
			slowPrint("You successfully completed the Surprise Quiz!");
			slowPrint("You felt more confident about your studies.");

			student->motivation += 2;
			student->receiveMoney(10);
			student->checkStats();

			cout << endl;
			cout << "==== Quiz Result ====" << endl;

			student->displayPlayerStats();

			cout << endl;
			surpriseQuiz->displayChallengeStats();

			delete surpriseQuiz;
			return 1;
		}

		if (!isYourTurn)
		{
			slowPrint("But suddenly...");
			cout << endl;

			int randomAttack = randomEnemyAttack();

			if (randomAttack == 1)
			{
				slowPrint("The question contained very confusing words.");
				slowPrint("You started doubting your answer.");

				student->focus -= 6;
			}
			else if (randomAttack == 2)
			{
				slowPrint("Another student kept disturbing you by asking for answers");
				slowPrint("The lecturer noticed that and warned both of you!");

				student->motivation -= 2;
				student->focus -= 2;
			}
			else if (randomAttack == 3)
			{
				slowPrint("You suddenly forgot an important formula.");
				slowPrint("You struggled to remember it.");

				student->focus -= 7;
			}
			else
			{
				slowPrint("Another student submitted the quiz early.");
				slowPrint("You started rushing through your answers.");

				student->energy -= 5;
			}

			isYourTurn = true;
		}

		cout << endl;
		--surpriseQuiz->challengeTime;

		student->checkStats();

		if (surpriseQuiz->isTimeout())
		{
			cout << endl;
			slowPrint("The quiz time has ended!");
			slowPrint("You could not complete all the questions.");

			student->motivation -= 2;
			student->focus -= 5;
			student->checkStats();

			cout << endl;
			cout << "==== Quiz Result ====" << endl;

			student->displayPlayerStats();

			cout << endl;
			surpriseQuiz->displayChallengeStats();

			if (student->isDead())
			{
				delete surpriseQuiz;
				return 3;
			}

			delete surpriseQuiz;
			return 2;
		}

		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);

		cout << endl;
		surpriseQuiz->displayStatChanges(challengeBefore);

		cout << endl;
		cout << "=========================" << endl;

		if (student->isDead())
		{
			delete surpriseQuiz;
			return 3;
		}
	}

	delete surpriseQuiz;
	return 2;
}

int groupAssignmentChallenge(Player* student)
{
	groupassignmentAscii();
	cout << endl;
	slowPrint("You encountered a Group Assignment Crisis!");
	Challenge* groupAssignment = new Challenge("Group Assignment Crisis", 110, 10, 6);
	
	int assignmentWeek = 7;

	cout << endl;
	cout << "===== WEEK 7 =====" << endl;
	cout << endl;

	slowPrint("Your lecturer announced the Group Assignment.");
	slowPrint("Your group has until Week 12 to complete it.");

	cout << endl;

	groupAssignment->displayChallengeStats();

	while (
		groupAssignment->challengeLevel > 0 &&
		student->focus > 0 &&
		groupAssignment->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();

		ChallengeStats challengeBefore = groupAssignment->tempStat();

		cout << endl;
		cout << "1. Work on Your Assigned Part" << endl;
		cout << "2. Communicate With Your Teammates" << endl;
		cout << "3. Cover a Missing Teammate's Work" << endl;
		cout << "4. Trust Your Teammate" << endl;
		cout << "5. Open Inventory" << endl;
		cout << "What would you do? : ";

		cin >> option1;

		if (!isInputValid())
		{
			continue;
		}

		switch (option1)
		{
		case 1:
			if (student->energy < groupAssignment->pressure)
			{
				cout << endl;
				slowPrint("You don't have enough energy to complete your part!");
				slowPrint("Try recovering some energy first.");

				continue;
			}

			cout << endl;
			slowPrint("You continued working on your assigned part.");
			slowPrint("You gained some knowledge from doing the work.");

			cout << endl;

			student->energy -= groupAssignment->pressure;

			student->knowledge += 1;

			groupAssignment->challengeLevel -= (((student->energy / 100.0) * (student->motivation * student->focus * 0.01)) + (student->knowledge / 10.0));

			isYourTurn = false;
			break;

		case 2:
			if (student->focus < 5)
			{
				cout << endl;
				slowPrint("You don't have enough focus to communicate properly!");

				continue;
			}

			cout << endl;
			slowPrint("You organised a meeting with your teammates.");
			slowPrint("Everyone now understands their responsibility.");
			slowPrint("Good communication prevented a problem this round!");

			cout << endl;

			student->focus -= 5;
			student->motivation += 1;

			groupAssignment->challengeLevel -= 18;

			break;

		case 3:
			if (student->energy < 20)
			{
				cout << endl;
				slowPrint("You need at least 20 Energy to do the extra work!");

				slowPrint("Try recovering some energy first.");

				continue;
			}

			cout << endl;
			slowPrint("One teammate did not complete their part.");
			slowPrint("You decided to complete their work yourself.");
			slowPrint("You made a lot of progress, but became exhausted.");

			cout << endl;

			student->energy -= 20;
			student->motivation -= 2;

			groupAssignment->challengeLevel -= 30;

			isYourTurn = false;
			break;

		case 4:
		{
			cout << endl;
			slowPrint("You trusted your teammate to complete an important section.");

			cout << endl;

			int luckResult = randomLuckCheck();

			cout << "Your Luck : " << student->luck << endl;

			cout << "Luck Roll : " << luckResult << endl;

			if (luckResult <= student->luck)
			{
				cout << endl;
				slowPrint("Your teammate completed their part perfectly!");
				slowPrint("The group made a lot of progress.");

				groupAssignment->challengeLevel -= 25;
			}
			else
			{
				cout << endl;
				slowPrint("Your teammate submitted incomplete work!");
				slowPrint("You now have even more work to complete.");

				student->focus -= 7;
				groupAssignment->challengeLevel += 5;
			}

			isYourTurn = false;
			break;
		}

		case 5:
			cout << endl;
			student->openInventory();
			student->checkStats();

			if (student->isDead())
			{
				delete groupAssignment;
				return 3;
			}

			continue;

		default:
			cout << endl;
			cout << "Invalid Input! Try Putting (1 to 5)"<< endl;

			continue;
		}
		student->checkStats();
		if (student->isDead())
		{
			delete groupAssignment;
			return 3;
		}
		if (groupAssignment->isDead())
		{
			--groupAssignment->challengeTime;

			cout << endl;
			slowPrint("You completed the Group Assignment!");
			cout << "You completed it during week " << assignmentWeek << "!" << endl;

			slowPrint("Your team successfully submitted the project.");
			slowPrint("You gained valuable knowledge from the experience.");

			cout << endl;

			student->knowledge += 5;
			student->motivation += 2;
			student->receiveMoney(20);

			student->checkStats();

			cout << endl;
			cout << "==== Assignment Result ===="<< endl;

			student->displayPlayerStats();

			cout << endl;
			groupAssignment->displayChallengeStats();

			delete groupAssignment;
			return 1;
		}

		bool movedToNextWeek = false;

		if (assignmentWeek < 12)
		{
			assignmentWeek++;
			movedToNextWeek = true;

			cout << endl;
			slowPrint("Another week passed...");

			cout << endl;
			cout << "===== WEEK " << assignmentWeek << " =====" << endl << endl;
			if (assignmentWeek == 12)
			{
				cout << endl;
				slowPrint("The final submission deadline is tonight.");
				slowPrint("This is your last chance to finish the assignment.");
			}
		}
		if (movedToNextWeek)
		{
			if (!isYourTurn)
			{
				if (assignmentWeek == 8)
				{
					slowPrint("One of your teammates stopped replying to the group messages.");
					slowPrint("They still had not started their assigned section.");
					slowPrint("You began losing motivation.");

					student->motivation -= 3;
				}
				else if (assignmentWeek == 9)
				{
					slowPrint("Two teammates disagreed about the direction of the project.");
					slowPrint("The group spent too much time arguing instead of working.");
					slowPrint("The disagreement made it difficult for you to focus.");

					student->focus -= 6;
				}
				else if (assignmentWeek == 10)
				{
					slowPrint("One teammate misunderstood the section assigned to them.");
					slowPrint("Their work did not match the assignment requirements.");
					slowPrint("You used some of your energy helping them correct it.");

					student->energy -= 7;
				}
				else if (assignmentWeek == 11)
				{
					slowPrint("Your group showed the unfinished project to the lecturer.");
					slowPrint("The lecturer said that several important details were missing.");
					slowPrint("The additional corrections affected your focus and motivation.");

					student->focus -= 4;
					student->motivation -= 1;
				}
				else if (assignmentWeek == 12)
				{
					slowPrint("One teammate suggested several last-minute changes.");
					slowPrint("The submission deadline was now extremely close.");
					slowPrint("The last-minute work affected your energy and focus.");

					student->energy -= 5;
					student->focus -= 4;
				}

				isYourTurn = true;
			}
			else
			{
				cout << endl;
				slowPrint("Because you communicated with your teammates early, the group solved this week's problem before it became serious.");
			}
		}

		cout << endl;
		--groupAssignment->challengeTime;

		student->checkStats();

		if (groupAssignment->isTimeout())
		{
			cout << endl;
			slowPrint("However...");
			cout << endl;
			slowPrint("The assignment deadline has arrived!");
			slowPrint("Your group failed to complete the assignment.");
			slowPrint("The unfinished assignment affected your motivation and focus.");

			cout << endl;

			student->motivation -= 4;
			student->focus -= 8;

			student->checkStats();

			cout << "==== Assignment Result ===="<< endl;
			
			student->displayPlayerStats();

			cout << endl;
			groupAssignment->displayChallengeStats();

			if (student->isDead())
			{
				delete groupAssignment;
				return 3;
			}

			delete groupAssignment;
			return 2;
		}

		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);

		cout << endl;
		groupAssignment->displayStatChanges(challengeBefore);

		cout << endl;
		cout << "=========================" << endl;
	
		if (student->isDead())
		{
			delete groupAssignment;
			return 3;
		}
	}

	delete groupAssignment;
	return 2;
}
int procrastinationChallenge(Player* student)
{
	cout << endl;
	cout << "===== WEEK 14 =====" << endl;
	cout << endl;

	slowPrint("Your Final Exam is getting closer.");
	slowPrint("You decided to stay home and spend the week studying.");
	cout << endl;

	slowPrint("You opened your lecture notes...");
	slowPrint("However, you could not convince yourself to start studying.");
	cout << endl;

	slowPrint("You encountered Procrastination!");
	cout << endl;

	Challenge* procrastination = new Challenge("Final Exam Procrastination", 60, 7, 6);
	procrastinationAscii();
	procrastination->displayChallengeStats();

	while (
		procrastination->challengeLevel > 0 &&
		student->focus > 0 &&
		procrastination->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();

		ChallengeStats challengeBefore = procrastination->tempStat();

		cout << endl;
		cout << "1. Revise an Important Topic" << endl;
		cout << "2. Follow a Study Timetable" << endl;
		cout << "3. Take a Short Break" << endl;
		cout << "4. Open Inventory" << endl;
		cout << "What would you do? : ";

		cin >> option1;

		if (!isInputValid())
		{
			continue;
		}

		switch (option1)
		{
		case 1:
			if (student->energy <
				procrastination->pressure)
			{
				cout << endl;
				slowPrint("You don't have enough energy to revise this topic!");
				slowPrint("Try taking a short break or using an item.");

				continue;
			}

			cout << endl;
			slowPrint("You decided to revise an important topic.");
			slowPrint("The topic was difficult, but you slowly understood it.");
			slowPrint("You gained some knowledge at the cost of your energy.");

			cout << endl;

			student->energy -= procrastination->pressure;

			student->knowledge += 2;

			procrastination->challengeLevel -= (((student->energy / 100.0) * (student->motivation * student->focus * 0.01)) + (student->knowledge / 10.0));

			isYourTurn = false;
			break;

		case 2:
			if (student->focus < 5)
			{
				cout << endl;
				slowPrint("You don't have enough focus to follow the timetable!");
				slowPrint("Try recovering some focus first.");

				continue;
			}

			cout << endl;
			slowPrint("You created a simple study timetable.");
			slowPrint("You divided your revision into smaller topics.");
			slowPrint("Following the timetable helped you avoid distractions.");

			cout << endl;

			student->focus -= 5;
			student->motivation += 1;

			procrastination->challengeLevel -= 16;

			break;

		case 3:
			cout << endl;
			slowPrint("You decided to take a short break.");
			slowPrint("You recovered some energy and focus.");
			slowPrint("However, you made no revision progress.");

			cout << endl;

			student->energy += 12;
			student->focus += 4;

			isYourTurn = false;
			break;

		case 4:
			cout << endl;
			student->openInventory();
			student->checkStats();

			if (student->isDead())
			{
				delete procrastination;
				return 3;
			}

			continue;

		default:
			cout << endl;
			cout << "Invalid Input! Try Putting (1 to 4)" << endl;

			continue;
		}
		student->checkStats();
		if (student->isDead())
		{
			delete procrastination;
			return 3;
		}
		if (procrastination->isDead())
		{
			cout << endl;
			slowPrint("You successfully overcame Procrastination!");
			slowPrint("You completed your revision plan for the Final Exam.");
			slowPrint("You kept all the knowledge you gained while studying.");

			cout << endl;

			student->knowledge += 5;
			student->motivation += 2;

			student->checkStats();

			cout << "==== Revision Result ====" << endl;

			student->displayPlayerStats();

			cout << endl;
			procrastination->displayChallengeStats();

			delete procrastination;
			return 1;
		}

		if (!isYourTurn)
		{
			slowPrint("But later...");
			cout << endl;

			slowPrint("Procrastination started affecting you again!");

			cout << endl;

			int randomAttack = randomEnemyAttack();

			if (randomAttack == 1)
			{
				slowPrint("You told yourself that the exam was still several days away.");
				slowPrint("You started losing your motivation to study.");

				student->motivation -= 3;
			}
			else if (randomAttack == 2)
			{
				slowPrint("You started organising your notes instead of reading them.");
				slowPrint("You spent a lot of energy without learning anything.");

				student->energy -= 5;
			}
			else if (randomAttack == 3)
			{
				slowPrint("You found a topic that was extremely difficult.");
				slowPrint("You began avoiding the topic and lost some focus.");

				student->focus -= 7;
			}
			else
			{
				slowPrint("Your friend invited you to play games online.");

				slowPrint("You became distracted and forgot about your revision.");

				student->focus -= 4;
				student->motivation -= 1;
			}

			isYourTurn = true;
		}

		cout << endl;
		--procrastination->challengeTime;

		student->checkStats();

		if (procrastination->isTimeout())
		{
			cout << endl;
			slowPrint("Week 14 has already come to an end!");
			slowPrint("You could not complete all of your revision.");
			slowPrint("The Final Exam is now getting dangerously close.");

			cout << endl;

			student->motivation -= 3;
			student->focus -= 5;

			student->checkStats();

			cout << "==== Revision Result ===="
				<< endl;

			student->displayPlayerStats();

			cout << endl;
			procrastination->displayChallengeStats();

			if (student->isDead())
			{
				delete procrastination;
				return 3;
			}

			delete procrastination;
			return 2;
		}

		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);

		cout << endl;
		procrastination->displayStatChanges(challengeBefore);

		cout << endl;
		cout << "=========================" << endl;

		if (student->isDead())
		{
			delete procrastination;
			return 3;
		}
	}

	delete procrastination;
	return 2;
}
int finalExamChallenge(Player* student)
{

	cout << endl;
	cout << "===== WEEK 15 =====" << endl;
	cout << endl;

	slowPrint("The morning of your Final Exam arrived.");
	slowPrint("You entered the examination hall and found your seat.");
	slowPrint("This exam will decide whether you complete the semester.");

	cout << endl;
	slowPrint("You encountered the Final Examination!");
	cout << endl;

	Challenge* finalExam = new Challenge("Final Examination", 40, 8, 6);

	bool usedLuck = false;

	finalExam->displayChallengeStats();

	cout << endl;
	cout << "Recommended Knowledge : 40" << endl;
	cout << "Your Knowledge        : " << student->knowledge << endl;

	if (student->knowledge >= 40)
	{
		cout << endl;
		slowPrint("You feel that you have gained enough knowledge to face the exam.");
	}
	else
	{
		cout << endl;
		slowPrint("You feel unprepared for some of the exam topics.");
		slowPrint("You may need to depend on your one Luck chance.");
	}

	while (
		finalExam->challengeLevel > 0 &&
		student->focus > 0 &&
		finalExam->challengeTime > 0)
	{
		int option1;
		bool isYourTurn = true;

		PlayerStats playerBefore = student->tempStat();

		ChallengeStats challengeBefore = finalExam->tempStat();

		cout << endl;
		cout << "1. Answer Using Your Knowledge" << endl;
		cout << "2. Think Carefully About the Question" << endl;
		cout << "3. Take a Moment to Calm Down" << endl;

		if (!usedLuck)
		{
			cout << "4. Depend on Your Luck (One Chance)" << endl;
		}
		else
		{
			cout << "4. Depend on Your Luck (Already Used)" << endl;
		}

		cout << "5. Open Inventory" << endl;
		cout << "What would you do? : ";

		cin >> option1;

		if (!isInputValid())
		{
			continue;
		}

		switch (option1)
		{
		case 1:
		{
			if (student->energy <
				finalExam->pressure)
			{
				cout << endl;
				slowPrint("You don't have enough energy to answer the question!");
				slowPrint("Try using an item or calming yourself down.");

				continue;
			}

			cout << endl;
			slowPrint("You answered the question using what you learned.");

			slowPrint("You remembered the topic from your previous revision.");

			cout << endl;

			student->energy -= finalExam->pressure;

			float examDamage = (((student->energy / 100.0) * (student->motivation * (student->focus) * 0.01)) + (student->knowledge / 10.0));

			finalExam->challengeLevel -= examDamage;

			isYourTurn = false;
			break;
		}

		case 2:
		{
			if (student->focus < 7)
			{
				cout << endl;
				slowPrint("You don't have enough focus to think carefully!");

				continue;
			}

			cout << endl;
			slowPrint("You read the question several times.");
			slowPrint("You slowly understood what the question was asking.");
			slowPrint("Thinking carefully prevented the exam from confusing you.");

			cout << endl;

			student->focus -= 7;

			float examDamage = (((student->energy / 100.0) * (student->motivation * (student->focus) * 0.01)) + (student->knowledge / 10.0));

			finalExam->challengeLevel -= examDamage;

			break;
		}

		case 3:
		{
			cout << endl;
			slowPrint("You stopped writing for a moment.");
			slowPrint("You took a deep breath and tried to calm yourself.");
			slowPrint("You recovered some energy and focus.");
			slowPrint("However, you made no progress during this turn.");

			cout << endl;

			student->energy += 12;
			student->focus += 5;

			isYourTurn = false;
			break;
		}

		case 4:
		{
			if (usedLuck)
			{
				cout << endl;
				slowPrint("You have already used your one Luck chance!");
				slowPrint("You must answer the remaining questions yourself.");

				continue;
			}

			usedLuck = true;

			cout << endl;
			slowPrint("You encountered a question that you could not remember.");
			slowPrint("You decided to depend on your Luck one final time!");

			cout << endl;

			int luckResult = randomLuckCheck();

			cout << "Your Luck : " << student->luck << endl;
			cout << "Luck Roll : " << luckResult << endl;

			if (luckResult <= student->luck)
			{
				cout << endl;
				slowPrint("The question was similar to something you had studied!");
				slowPrint("You successfully remembered the answer.");

				float examDamage = (((student->energy / 100.0) * (student->motivation * (student->focus) * 0.01)) + (student->knowledge / 10.0));

				finalExam->challengeLevel -= examDamage;

				finalExam->challengeTime += 1;
			}
			else
			{
				cout << endl;
				slowPrint("The question was completely unfamiliar to you!");
				slowPrint("Your lucky guess was wrong.");
				slowPrint("You cannot depend on Luck again during this exam.");

				student->focus -= 8;
				student->motivation -= 1;
			}

			isYourTurn = false;
			break;
		}

		case 5:
			cout << endl;
			student->openInventory();
			student->checkStats();

			if (student->isDead())
			{
				delete finalExam;
				return 3;
			}
			continue;

		default:
			cout << endl;
			cout << "Invalid Input! Try Putting (1 to 5)" << endl;

			continue;
		}
		cout << endl;
		--finalExam->challengeTime;

		student->checkStats();
		if (student->isDead())
		{
			delete finalExam;
			return 3;
		}

		if (finalExam->isDead())
		{
			cout << endl;
			slowPrint("You successfully completed the Final Examination!");

			cout << endl;

			if (finalExam->challengeTime > 0)
			{
				cout << "================================" << endl;

				cout << "       PASSED WITH HONOURS" << endl;

				cout << "================================" << endl;

				cout << endl;

				slowPrint("You completed the exam with time remaining.");
				slowPrint("Your preparation throughout the semester paid off.");

				student->motivation += 2;
			}
			else
			{
				cout << "================================" << endl;

				cout << "              PASSED" << endl;

				cout << "================================" << endl;

				cout << endl;

				slowPrint("You completed the final question just before time ended.");
				slowPrint("You successfully passed the semester.");

				student->motivation += 1;
			}

			student->checkStats();

			cout << endl;
			cout << "==== Final Exam Result ====" << endl;

			student->displayPlayerStats();

			cout << endl;
			finalExam->displayChallengeStats();

			delete finalExam;
			return 1;
		}

		if (!isYourTurn)
		{
			slowPrint("But suddenly...");
			cout << endl;

			int randomAttack =
				randomEnemyAttack();

			if (randomAttack == 1)
			{
				slowPrint("You encountered a question with confusing wording.");
				slowPrint("You started doubting what the question was asking.");

				student->focus -= 8;
			}
			else if (randomAttack == 2)
			{
				slowPrint("You encountered a long question worth many marks.");
				slowPrint("Writing the answer used a lot of your energy.");

				student->energy -= 7;
			}
			else if (randomAttack == 3)
			{
				slowPrint("You looked at the clock and noticed time was running out.");
				slowPrint("The time pressure affected your focus and motivation.");

				student->focus -= 3;
				student->motivation -= 2;
			}
			else
			{
				slowPrint("You suddenly forgot a formula that you had revised.");
				slowPrint("You struggled to remember it.");

				student->focus -= 6;
				student->energy -= 3;
			}

			isYourTurn = true;
		}

		student->checkStats();

		if (finalExam->isTimeout())
		{
			cout << endl;
			slowPrint("The lecturer announced that the exam time was over!");
			slowPrint("You were unable to complete enough questions.");
			slowPrint("You failed the Final Examination.");

			cout << endl;

			student->motivation -= 5;
			student->focus -= 8;

			student->checkStats();

			cout << "==== Final Exam Result ====" << endl;

			student->displayPlayerStats();

			cout << endl;
			finalExam->displayChallengeStats();

			if (student->isDead())
			{
				delete finalExam;
				return 3;
			}

			delete finalExam;
			return 2;
		}

		cout << "===== Round Result =====" << endl;

		cout << endl;
		student->displayStatChanges(playerBefore);

		cout << endl;
		finalExam->displayStatChanges(challengeBefore);

		cout << endl;
		cout << "=========================" << endl;

		if (student->isDead())
		{
			delete finalExam;
			return 3;
		}
	}

	delete finalExam;
	return 2;
}
