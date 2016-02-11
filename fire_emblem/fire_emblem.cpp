#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct mapPlace
{
	string empty = "[ ]";
	string full = "[X]";
	string current;
	bool occupied = false;

	void show()
	{
		if(occupied)
		{
			current = full;
			cout << current;
		}
		else
		{
			current = empty;
			cout << current;
		}
	}
};

class Unit
{
public:
	Unit(const string& unitName, const int& unitHp, const int& unitAtk, const int& unitSkl,
		const int& unitSpd, const int& unitLck, const int& unitDef, const int& unitRes,
		const int& unitCon, const int& unitMov) : name(unitName), hp(unitHp), atk(unitAtk),
		skl(unitSkl), spd(unitSpd), lck(unitLck), def(unitDef), res(unitRes), con(unitCon),
		mov(unitMov){}
	Unit(){}

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

	void fight(Unit& enemyUnit)
	{
		if(enemyUnit.def < atk)
		{
			enemyUnit.hp = (enemyUnit.hp + enemyUnit.def) - atk;
		}

		if(enemyUnit.hp > 0)
		{
			if(def < enemyUnit.atk)
			{
				hp = (hp + def) - enemyUnit.atk;
			}

			if(spd >= (enemyUnit.spd + 4))
			{
				if(enemyUnit.def <= atk)
				{
					enemyUnit.hp = (enemyUnit.hp + enemyUnit.def) - atk;
				}
			}	
			else if(enemyUnit.spd > (spd + 4) && hp > 0)
			{
				if(def < enemyUnit.atk)
				{
					hp = (hp + def) - enemyUnit.atk;
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

		if(exp >= 100)
		{
			levelUp();
			exp = exp % 100;
		}
	}

	void move(vector<vector<mapPlace>>& map, const string& movement)
	{
		bool right;
		bool left;
		bool up;
		bool down;
		bool none;

		if(movement == "right")
		{
			right = true;
			left = false;
			up = false;
			down = false;
		}
		else if(movement == "left")
		{
			right = false;
			left = true;
			up = false;
			down = false;
		}
		else if(movement == "up")
		{
			right = false;
			left = false;
			up = true;
			down = false;
		}
		else if(movement == "down")
		{
			right = false;
			left = false;
			up = false;
			down = true;
		}
		else if(movement == "none")
		{
			right = false;
			left = false;
			up = false;
			down = false;
		}

		if(right == true && left == false && up == false && down == false)
		{
			if(x < map[y].size()-1)
			{
				map[y][x].occupied = false;
				x++;
				map[y][x].occupied = true;
			}
		}
		else if(right == false && left == true && up == false && down == false)
		{
			if(x < map[y].size()-1)
			{
				map[y][x].occupied = false;
				x--;
				map[y][x].occupied = true;
			}
		}
		else if(right == false && left == false && up == true && down == false)
		{
			if(y > 0)
			{
				map[y][x].occupied = false;
				y--;
				map[y][x].occupied = true;
			}
		}
		else if(right == false && left == false && up == false && down == true)
		{
			if(y < map.size()-1)
			{
				map[y][x].occupied = false;
				y++;
				map[y][x].occupied = true;
			}
		}
		else if(right == false && left == false && up == false && down == false)
		{
			if(x < map[y].size()-1)
			{
				map[y][x].occupied = true;
			}
		}
	}

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
	int x; //X Coordinate
	int y; //Y Coordinate

private:
	int exp = 99; //Experience
	int lvl = 1; //Level

	void gainExp(const Unit& enemyUnit)
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
};

void createUnitStats(vector<Unit>& unitList);
void createUnits(const string& name, const vector<int>& stats, vector<Unit>& unitList);
void displayUnit(const vector<Unit>& unitList, const string& unitName);
void command(const vector<Unit>& unitList);
void battle(vector<Unit>& unitList, const string& unitName1, const string& unitName2);
void displayMap(vector<vector<mapPlace>>& map, vector<Unit> unitList);
int selectUnit(const vector<Unit>& unitList, const string& unitName);
void playerPhase(vector<vector<mapPlace>>& map, vector<Unit> unitList);

int main()
{
	//Immediately creates units and generates map
	vector<Unit> unitList;
	createUnitStats(unitList);
	vector<vector<mapPlace>> map(16, vector<mapPlace>(16));

	//displayUnit(unitList, "all"); //Format for displayUnit()

	//command(unitList);

	int unitIndex = selectUnit(unitList, "LordEliwood"); //Format for selectUnit()

	//battle(unitList, "LordEliwood", "Soldier"); //Format for battle()
	//battle(unitList, "LordEliwood", "Soldier");

	unitList[unitIndex].x = 4; //Set coordinates of a unit
	unitList[unitIndex].y = 10;

	unitList[unitIndex].move(map, "none"); // Initialize unit on map
	displayMap(map, unitList);
	unitList[unitIndex].move(map, "right");
	displayMap(map, unitList);

	//playerPhase(map, unitList);



	return 0;
}

void createUnitStats(vector<Unit>& unitList) //Generates unit stats from a file
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

	while(ifs >> word) //Builds stat list
	{
		if(word[0] >= 'A' && word[0] <= 'Z') 
		{
			if(stats.size() == 9)
			{
				createUnits(unitName, stats, unitList);
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

	if(ifs.eof()) //Makes last unit in file
	{
		createUnits(unitName, stats, unitList);
		stats.clear();
		unitName = "";
	}

	ifs.close();
}

void createUnits(const string& name, const vector<int>& stats, vector<Unit>& unitList)
{
	Unit newUnit(name, stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6],
		stats[7], stats[8]);

	//newUnit.statDisplay();
	unitList.push_back(newUnit); //Puts unit into vector
}

void displayUnit(const vector<Unit>& unitList, const string& unitName) //Shows unit stats
{
	cout << endl;

	if(unitName == "all") //For all
	{
		for(Unit someUnit : unitList)
		{
			someUnit.statDisplay();
		}
	}
	else
	{
		for(Unit someUnit : unitList) //For a specified unit
		{
			if(unitName == someUnit.name)
			{
				someUnit.statDisplay();
				break;
			}
		}
	}
}

int selectUnit(const vector<Unit>& unitList, const string& unitName) //Gets index of unit
{
		for(int i = 0; i < unitList.size(); i++)
		{
			if(unitName == unitList[i].name)
			{
				return i;
			}
		}
}

void command(const vector<Unit>& unitList) //Executes commands
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

	displayUnit(unitList, unit1.name); //Before battle
	displayUnit(unitList, unit2.name);

	unit1.fight(unit2);

	for(Unit& someUnit : unitList)
	{
		if(unit1.name == someUnit.name)
		{
			someUnit = unit1;
		}
		if(unit2.name == someUnit.name)
		{
			someUnit = unit2;
		}
	}

	displayUnit(unitList, unit1.name); //After battle
	displayUnit(unitList, unit2.name);
}

void displayMap(vector<vector<mapPlace>>& map, vector<Unit> unitList)
{
	cout << endl;

	for(int i = 0; i < map.size(); i++)
	{
		for(int k = 0; k < map[i].size(); k++)
		{
			if(k < map[i].size()-1)
			{
				map[i][k].show();
			}
			else
			{
				map[i][k].show();
				cout << endl;
			}
		}
	}
}

void playerPhase(vector<vector<mapPlace>>& map, vector<Unit> unitList)
{
	srand(time(NULL));
	for(Unit& someUnit : unitList)
	{
		someUnit.x = rand() % 16;
		someUnit.y = rand() % 16;
		//displayMap(map, UnitList);

		//cout << "(" << someUnit.x << "," << someUnit.y << ")" << endl;
	}

}