#pragma once
#include "Display.h"
#include <iostream>

using namespace std;


struct PlayerStats
{
	float focus;
	float knowledge;
	float energy;
	float motivation;
};

class Player
{
public:
	string name;
	float focus;
	float knowledge;
	float energy;
	float motivation;
	float luck;


	Player(string name, int luck)
	{
		this->name = name;
		this->focus = 100;
		this->knowledge = 20;
		this->energy = 80;
		this->motivation = 7;
		this->luck = luck;
	}
	void displayPlayerStats()
	{
		cout << endl;
		cout << "Player Name       : " << name << endl;
		cout << "Player Focus      : " << focus << endl;
 		cout << "Player Knowledge  : " << knowledge << endl;
		cout << "Player Energy     : " << energy << endl;
		cout << "Player Motivation : " << motivation << endl;
		cout << "Player Luck       : " << luck << endl;

	}
	void displayCombatStats()
	{
		cout << "Focus      : " << focus << endl;
		cout << "Knowledge  : " << knowledge << endl;
		cout << "Energy     : " << energy << endl;
		cout << "Motivation : " << motivation << endl;
	}
	PlayerStats tempStat()
	{
		return { focus, knowledge, energy, motivation };
	}
	void displayStatChanges(PlayerStats before)
	{
		printChange("Focus      ", before.focus, focus);
		printChange("Knowledge  ", before.knowledge, knowledge);
		printChange("Energy     ", before.energy, energy);
		printChange("Motivation ", before.motivation, motivation);
	}
	bool isDead()
	{
		if (focus <= 0)
		{
			cout << endl;
			slowPrint("You completely lost your Focus :(");
			slowPrint("You decided to drop out the Course");
			slowPrint("You failed the challenge...");
			cout << endl;
			return true;
		}
		return false;
	}
private:
	void printChange(string label, float oldValue, float newValue)
	{
		float diff = newValue - oldValue;
		cout << label << " : " << oldValue << " -> " << newValue << " (";
		if (diff > 0)
		{
			cout << "+" << diff;
			cout << ")" << endl;
		}
		else if (diff < 0)
		{
			cout << diff;
			cout << ")" << endl;

		}
		else
		{
			cout << "No Change";
			cout << ")" << endl;
		}
	}
};

string setName();
