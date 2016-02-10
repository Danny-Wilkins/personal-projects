#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Unit
{
public:
	Unit(const string& unitName, const int& unitHp, const int& unitAtk, const int& unitSkl,
		const int& unitSpd, const int& unitLck, const int& unitDef, const int& unitRes,
		const int& unitCon, const int& unitMov) : name(unitName), hp(unitHp), atk(unitAtk),
		skl(unitSkl), spd(unitSpd), lck(unitLck), def(unitDef), res(unitRes), con(unitCon),
		mov(unitMov)
	{

	}
	Unit()
	{

	}

	void statDisplay() const
	{
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Atk: " << atk << endl;
		cout << "Skill: " << skl << endl;
		cout << "Speed: " << spd << endl;
		cout << "Luck: " << lck << endl;
		cout << "Defense: " << def << endl;
		cout << "Resistance: " << res << endl;
		cout << "Constitution: " << con << endl;
		cout << "Movement: " << mov << endl << endl;
	}

	/*void genStats(string& name, vector<int>& stats)
	{
		Unit newUnit(name, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6],
			stats[7], stats[8]);

		newUnit.statDisplay();
	}*/

	void fight(Unit& enemyUnit)
	{
			if(enemyUnit.def < atk)
			{
				enemyUnit.hp = (enemyUnit.hp + enemyUnit.def) - atk;
			}
			else //No damage
			{
				enemyUnit.hp = enemyUnit.hp - 0;
			}
		

		if(enemyUnit.hp > 0)
		{
			if(def < enemyUnit.atk)
			{
				hp = (hp + def) - enemyUnit.atk;
			}
			else //No damage
			{
				hp = hp - 0;
			}

			if(spd >= (enemyUnit.spd + 4))
			{
				if(enemyUnit.def <= atk)
				{
					enemyUnit.hp = (enemyUnit.hp + enemyUnit.def) - atk;
				}
				else //No damage
				{
					enemyUnit.hp = enemyUnit.hp - 0;
				}
			}	
			else if(enemyUnit.spd > (spd + 4) && hp > 0)
			{
				if(def < enemyUnit.atk)
				{
					hp = (hp + def) - enemyUnit.atk;
				}
				else //No damage
				{
					hp = hp - 0;
				}
			}
		}

		if(enemyUnit.hp <= 0)
		{
			enemyUnit.hp = 0;
			gainExp(enemyUnit);
		}
		if(hp <= 0)
		{
			hp = 0;
		}

		if(exp >=100)
		{
			levelUp();
			exp = 0;
		}
	}

	void gainExp(Unit& enemyUnit)
	{
		exp += (enemyUnit.lvl*3 + 20);
	}

	void levelUp()
	{
		int statUp;
		srand(time(NULL));

		lvl += 1;

		statUp = rand() % 2;
		if(statUp == 1)
		{
			hp += 1;
			cout << "Hp, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			atk += 1;
			cout << "Atk, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			skl += 1;
			cout << "Skl, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			spd += 1;
			cout << "Spd, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			lck += 1;
			cout << "Lck, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			def += 1;
			cout << "Def, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			res += 1;
			cout << "Res, ";
		}
		statUp = rand() % 2;
		if(statUp == 1)
		{
			con += 1;
			cout << "Con, ";
		}

		cout << "up!" << endl;
	}

//private:
	string name; //Name
	int hp;	//HP
	int atk; //Strength/Magic
	int skl; //Skill
	int spd; //Speed
	int lck; //Luck
	int def; //Defense
	int res; //Resistance
	int con; //Constitution
	int mov; //Movement
	int exp = 99; //Experience
	int lvl = 1; //Level
};

void genUnits(vector<Unit>& unitList);
void genStats(const string& name, const vector<int>& stats, vector<Unit>& unitList);
void displayUnit(const vector<Unit>& unitList, const string& unitName);
void command(const vector<Unit>& unitList);
void battle(vector<Unit>& unitList, const string& unitName1, const string& unitName2);

int main()
{
	vector<Unit> unitList;
	genUnits(unitList);
	//displayUnit(unitList, "all");
	//command(unitList);
	battle(unitList, "LordEliwood", "Soldier");
	battle(unitList, "LordEliwood", "Soldier");

	return 0;
}

void genUnits(vector<Unit>& unitList) //Generates units from a file
{
	string word;
	string unitName;
	int unitStat;
	vector<int> stats;

	ifstream ifs("fe7_base_stats_parsed.txt");

	if(!ifs)
	{
		cerr << "File not found!" << endl;
		exit(1);
	}

	while(ifs >> word)
	{
		if(word[0] >= 'A' && word[0] <= 'Z')
		{
			if(stats.size() == 9)
			{
				genStats(unitName, stats, unitList);
				stats.clear();
				unitName = "";
			}

			unitName = word;
		}
		else
		{
			unitStat = stoi(word);
			stats.push_back(unitStat);
		}
	}

	if(ifs.eof())
	{
		genStats(unitName, stats, unitList);
		stats.clear();
		unitName = "";
	}

	ifs.close();
}

void genStats(const string& name, const vector<int>& stats, vector<Unit>& unitList)
{
	Unit newUnit(name, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6],
		stats[7], stats[8]);

	//newUnit.statDisplay();
	unitList.push_back(newUnit);
}

void displayUnit(const vector<Unit>& unitList, const string& unitName)
{
	cout << endl;

	if(unitName == "all")
	{
		for(Unit someUnit : unitList)
		{
			someUnit.statDisplay();
		}
	}
	else
	{
		for(Unit someUnit : unitList)
		{
			if(unitName == someUnit.name)
			{
				someUnit.statDisplay();
				break;
			}
		}
	}
}

void command(const vector<Unit>& unitList)
{
	string inputCommand;
	cout << "Enter a command: ";
	cin >> inputCommand;
	cout << endl;

	if(inputCommand == "displayUnit")
	{
		string unitName;
		cout << "Which unit would you like to display: ";
		cin >> unitName;
		displayUnit(unitList, unitName);
	}

	if(inputCommand != "quit")
	{
		command(unitList);
	}
}

void battle(vector<Unit>& unitList, const string& unitName1, const string& unitName2)
{
	Unit unit1;
	Unit unit2;

	for(Unit someUnit : unitList)
	{
		if(unitName1 == someUnit.name)
		{
			unit1 = someUnit;
		}
		if(unitName2 == someUnit.name)
		{
			unit2 = someUnit;
		}
	}

	displayUnit(unitList, unit1.name);
	displayUnit(unitList, unit2.name);

	unit1.fight(unit2);

	/*for(Unit someUnit : unitList) //Strangely not working
	{
		if(unit1.name == someUnit.name)
		{
			someUnit = unit1;
		}
		if(unit2.name == someUnit.name)
		{
			someUnit = unit2;
		}
	}*/

	for(int i = 0; i < unitList.size(); i++)
	{
		if(unitList[i].name == unit1.name)
		{
			unitList[i] = unit1;
		}
		if(unitList[i].name == unit2.name)
		{
			unitList[i] = unit2;
		}
	}

	displayUnit(unitList, unit1.name);
	displayUnit(unitList, unit2.name);
}