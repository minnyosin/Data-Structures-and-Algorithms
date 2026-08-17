#pragma once
#include <iostream>

using namespace std;

struct ChallengeStats
{
	float challengeLevel;
	int challengeTime;
};
class Challenge
{
public:
	string name;
	float challengeLevel;
	float pressure;
	int challengeTime;

	Challenge(string name, float challengeLevel, float pressure, int challengeTime)
	{
		this->name = name;
		this->challengeLevel = challengeLevel;
		this->pressure = pressure;
		this->challengeTime = challengeTime;
	}
	void displayChallengeStats()
	{
		cout << "Challenge Name     : " << name << endl;
		cout << "Challenge Level    : " << challengeLevel << endl;
		cout << "Challenge Pressure : " << pressure << endl;
		cout << "Challenge Time     : " << challengeTime << endl;
	}
	void displayCombatStats()
	{
		cout << "Level : " << challengeLevel << endl;
		cout << "Time : " << challengeTime << endl;
	}
	ChallengeStats tempStat()
	{
		return { challengeLevel, challengeTime };
	}

	void displayStatChanges(ChallengeStats before)
	{
		printChange("Level", before.challengeLevel, challengeLevel);
		printChange("Time ", (float)before.challengeTime, (float)challengeTime);
	}
	bool isDead()
	{
		if (challengeLevel <= 0)
		{
			challengeLevel = 0;
			return true;
		}
		return false;
	}
	bool isTimeout()
	{
		if (challengeTime <= 0)
		{
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