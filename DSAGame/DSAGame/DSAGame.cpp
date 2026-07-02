# include <iostream>

using namespace std;

class Enemy
{
	string name;
	int health;
	int damage;
	int killExp;
	int killGold;

public:
	Enemy(string name, int health, int damage, int killExp, int killGold)
	{
		this->name = name;
		this->health = health;
		this->damage = damage;
		this->killExp = killExp;
		this->killGold = killGold;
	}
	int attack()
	{
		return damage;
	}
	void takeDamage(int damage)
	{
		if (damage < 0)
		{
			damage = 0;
		}
		health -= damage;

		if (health < 0)
		{
			health = 0;
		}
	}
	bool is_dead()
	{
		if (health <= 0)
		{
			return true;
		}
		return false;
	}
	int getExp()
	{
		return killExp;
	}
	int getGold()
	{
		return killGold;
	}
};
int main()
{
	Enemy* dragon = new Enemy("Dragon",450, 25, 100, 25);
	dragon->attack();

	return 0;
}