#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
using namespace std;

class unit;
struct mapPlace;

struct mapPlace
{
	string empty = "[  ]";
	//string full = "[X]";
	string full;
	string current;
	string name;
	bool occupied = false;
	bool enemy = false;

	void show()
	{
		if(occupied)
		{
			full = "[" + name + "]";
			current = full;

			if(enemy == false)
			{
				cout << "\033[1;34m" << current << "\033[0m";
			}
			else
			{
				cout << "\033[1;31m" << current << "\033[0m";
			}
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
				if(enemy == true)
				{
					map[y][x].enemy = true;
				}
				map[y][x].occupied = false;
				x++;
				map[y][x].occupied = true;
				map[y][x].name = name.substr(0,2);
			}
		}
		else if(right == false && left == true && up == false && down == false)
		{
			if(x > 0)
			{
				if(enemy == true)
				{
					map[y][x].enemy = true;
				}
				map[y][x].occupied = false;
				x--;
				map[y][x].occupied = true;
				map[y][x].name = name.substr(0,2);
			}
		}
		else if(right == false && left == false && up == true && down == false)
		{
			if(y > 0)
			{
				if(enemy == true)
				{
					map[y][x].enemy = true;
				}
				map[y][x].occupied = false;
				y--;
				map[y][x].occupied = true;
				map[y][x].name = name.substr(0,2);
			}
		}
		else if(right == false && left == false && up == false && down == true)
		{
			if(y < map.size()-1)
			{
				if(enemy == true)
				{
					map[y][x].enemy = true;
				}
				map[y][x].occupied = false;
				y++;
				map[y][x].occupied = true;
				map[y][x].name = name.substr(0,2);
			}
		}
		else if(right == false && left == false && up == false && down == false)
		{
				if(enemy == true)
				{
					map[y][x].enemy = true;
				}
			if(x < map[y].size()-1)
			{
				map[y][x].occupied = true;
				map[y][x].name = name.substr(0,2);
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
	bool enemy = false;

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
void displayMap(vector<vector<mapPlace>>& map, vector<Unit>& unitList);
int selectUnit(const vector<Unit>& unitList, string& unitName);
void playerPhase(vector<vector<mapPlace>>& map, vector<Unit>& unitList,
				 vector<string>& activeUnitList);
void moveUnit(vector<vector<mapPlace>>& map, vector<Unit>& unitList, const int unitIndex);
void gameSetup(vector<vector<mapPlace>>& map, vector<Unit>& unitList, 
			   vector<string>& activeUnitList);
void activeUnits(const vector<string>& activeUnitList);

int main()
{
	//Immediately creates units and generates map
	vector<Unit> unitList;
	vector<string> activeUnitList;
	createUnitStats(unitList);
	vector<vector<mapPlace>> map(24, vector<mapPlace>(24));

	//displayUnit(unitList, "all"); //Format for displayUnit()

	//command(unitList);

	//int unitIndex = selectUnit(unitList, "LordEliwood"); //Format for selectUnit()
	//int selected;
	//string nameInput;

	//battle(unitList, "LordEliwood", "Soldier"); //Format for battle()
	//battle(unitList, "LordEliwood", "Soldier");

	//unitList[unitIndex].x = 0; //Set coordinates of a unit
	//unitList[unitIndex].y = 0;

	//moveUnit(map, unitList, unitIndex);

	gameSetup(map, unitList, activeUnitList);
	playerPhase(map, unitList, activeUnitList);

	/*cout << "Select a unit: " << endl;
	cin >> nameInput;

	selected = selectUnit(unitList, nameInput);

	moveUnit(map, unitList, selected);*/

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

int selectUnit(const vector<Unit>& unitList, string& unitName) //Gets index of unit
{
	for(int i = 0; i < unitList.size(); i++)
	{
		if(unitName == unitList[i].name)
		{
			return i;
		}
	}

	cout << "Select another unit: " << endl;
	cin >> unitName;
	selectUnit(unitList, unitName);
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

void displayMap(vector<vector<mapPlace>>& map, vector<Unit>& unitList)
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

void playerPhase(vector<vector<mapPlace>>& map, vector<Unit>& unitList,
				 vector<string>& activeUnitList)
{
	int movedUnits = 0;
	vector<string> movedUnitsNames;
	bool found = false;
	int selected;
	string nameInput;

	while(movedUnits < 5)
	{
		activeUnits(activeUnitList);
		cout << "Select a unit: " << endl;
		cin >> nameInput;

		selected = selectUnit(unitList, nameInput);

		for(int i = 0; i < movedUnitsNames.size(); i++)
		{
			if(unitList[selected].name == movedUnitsNames[i])
			{
				found = true;
				cout << "You already moved that unit." << endl;
			}
		}

		if(!found && unitList[selected].enemy == false)
		{
			moveUnit(map, unitList, selected);
			movedUnitsNames.push_back(unitList[selected].name);
			movedUnits++;
		}

		found = false;
	}
}

void moveUnit(vector<vector<mapPlace>>& map, vector<Unit>& unitList, const int unitIndex)
{	
	unitList[unitIndex].move(map, "none");
	displayMap(map, unitList);
	char input;
	int moves = unitList[unitIndex].mov;
	
	for(int i = 0; i < moves; i++)
	{
		system("clear");
		displayMap(map, unitList);
		cout << "You have " << (moves - i) << " moves left." << endl; 

		int x = unitList[unitIndex].x;
		int y = unitList[unitIndex].y;

		cin >> input;

		switch(input) 
		{
			case 'w':
				if(y > 0)
				{
					if(map[y-1][x].occupied == false)
					{
						unitList[unitIndex].move(map, "up");
					}
				}
				break;
			case 's':
				if(y < map.size()-1)
				{
					if(map[y+1][x].occupied == false)
					{
						unitList[unitIndex].move(map, "down");
					}
				}
				break;
			case 'a':
				if(map[y][x-1].occupied == false)
				{
					unitList[unitIndex].move(map, "left");
				}
				break;
			case 'd':
				if(map[y][x+1].occupied == false)
				{
					unitList[unitIndex].move(map, "right");
				}
				break;
			default:
				unitList[unitIndex].move(map, "none");
				break;
		}

		if(unitList[unitIndex].x == x && unitList[unitIndex].y == y)
		{
			i--;
			cout << "You cannot move there." << endl;
		}
	}

	system("clear");
	displayMap(map, unitList);
}

void gameSetup(vector<vector<mapPlace>>& map, vector<Unit>& unitList, 
			   vector<string>& activeUnitList)
{
	srand(time(NULL)); //Units CAN be on the same tile but it's unlikely
	usleep(2000000);   //So I might try to prevent that later

	int unit1 = rand() % unitList.size();
	int unit2 = rand() % unitList.size();
	int unit3 = rand() % unitList.size();
	int unit4 = rand() % unitList.size();
	int unit5 = rand() % unitList.size();

	int enemy1 = rand() % unitList.size();
	int enemy2 = rand() % unitList.size();
	int enemy3 = rand() % unitList.size();
	int enemy4 = rand() % unitList.size();
	int enemy5 = rand() % unitList.size();

	while(unit1 == enemy1 || unit1 == enemy2 || unit1 == enemy3 || unit1 == enemy4
		|| unit1 == enemy5 || unit1 == unit2 || unit1 == unit3 || unit1 == unit4 
		|| unit1 == unit5)
	{
		unit1 = rand() % unitList.size();
	}
	while(unit2 == enemy1 || unit2 == enemy2 || unit2 == enemy3 || unit2 == enemy4
		|| unit2 == enemy5 || unit2 == unit1 || unit2 == unit3 || unit2 == unit4 
		|| unit2 == unit5)
	{
		unit2 = rand() % unitList.size();
	}
	while(unit3 == enemy1 || unit3 == enemy2 || unit3 == enemy3 || unit3 == enemy4
		|| unit3 == enemy5 || unit3 == unit1 || unit3 == unit2 ||unit3 == unit4 
		|| unit3 == unit5)
	{
		unit3 = rand() % unitList.size();
	}
	while(unit4 == enemy1 || unit4 == enemy2 || unit4 == enemy3 || unit4 == enemy4
		|| unit4 == enemy5 ||unit4 == unit1 || unit4 == unit2 || unit4 == unit3 
		|| unit4 == unit5)
	{
		unit4 = rand() % unitList.size();
	}
	while(unit5 == enemy1 || unit5 == enemy2 || unit5 == enemy3 || unit5 == enemy4
		|| unit5 == enemy5 || unit5 == unit1 || unit5 == unit2 || unit5 == unit3 
		|| unit5 == unit4)
	{
		unit5 = rand() % unitList.size();
	}
	while(enemy1 == enemy2 || enemy1 == enemy3 || enemy1 == enemy4
		|| enemy1 == enemy5 || enemy1 == unit1 || enemy1 == unit2 || enemy1 == unit3 
		|| enemy1 == unit4)
	{
		enemy1 = rand() % unitList.size();
	}
	while(enemy2 == enemy1 || enemy2 == enemy3 || enemy2 == enemy4
		|| enemy2 == enemy5 || enemy2 == unit1 || enemy2 == unit2 || enemy2 == unit3 
		|| enemy2 == unit4)
	{
		enemy2 = rand() % unitList.size();
	}
	while(enemy3 == enemy1 || enemy3 == enemy2 || enemy3 == enemy4
		|| enemy3 == enemy5 || enemy3 == unit1 || enemy3 == unit2 || enemy3 == unit3 
		|| enemy3 == unit4)
	{
		enemy3 = rand() % unitList.size();
	}
	while(enemy4 == enemy1 || enemy4 == enemy2 || enemy4 == enemy3 || enemy4 == enemy5 
		|| enemy4 == unit1 || enemy4 == unit2 || enemy4 == unit3 
		|| enemy4 == unit4)
	{
		enemy4 = rand() % unitList.size();
	}
	while(enemy5 == enemy1 || enemy5 == enemy2 || enemy5 == enemy3 || enemy5 == enemy4
		|| enemy5 == unit1 || enemy5 == unit2 || enemy5 == unit3 
		|| enemy5 == unit4)
	{
		enemy5 = rand() % unitList.size();
	}

	unitList[unit1].x = rand() % (map[0].size() / 3);
	unitList[unit1].y = rand() % (map[0].size() / 3);
	unitList[unit2].x = rand() % (map[0].size() / 3);
	unitList[unit2].y = rand() % (map[0].size() / 3);
	unitList[unit3].x = rand() % (map[0].size() / 3);
	unitList[unit3].y = rand() % (map[0].size() / 3);
	unitList[unit4].x = rand() % (map[0].size() / 3);
	unitList[unit4].y = rand() % (map[0].size() / 3);
	unitList[unit5].x = rand() % (map[0].size() / 3);
	unitList[unit5].y = rand() % (map[0].size() / 3);

	unitList[enemy1].x = rand() % (map[0].size());
	unitList[enemy1].y = rand() % (map[0].size());
	unitList[enemy2].x = rand() % (map[0].size());
	unitList[enemy2].y = rand() % (map[0].size());
	unitList[enemy3].x = rand() % (map[0].size());
	unitList[enemy3].y = rand() % (map[0].size());
	unitList[enemy4].x = rand() % (map[0].size());
	unitList[enemy4].y = rand() % (map[0].size());
	unitList[enemy5].x = rand() % (map[0].size());
	unitList[enemy5].y = rand() % (map[0].size());

	while((unitList[unit1].x == unitList[unit2].x && unitList[unit1].y == unitList[unit2].y)
		|| (unitList[unit1].x == unitList[unit3].x && unitList[unit3].y == unitList[unit3].y)
		|| (unitList[unit1].x == unitList[unit4].x && unitList[unit1].y == unitList[unit4].y)
		|| (unitList[unit1].x == unitList[unit5].x && unitList[unit1].y == unitList[unit5].y))
	{
		unitList[unit1].x = rand() % (map[0].size() / 3);
		unitList[unit1].y = rand() % (map[0].size() / 3);
	}
	while((unitList[unit2].x == unitList[unit3].x && unitList[unit2].y == unitList[unit3].y)
		|| (unitList[unit2].x == unitList[unit4].x && unitList[unit2].y == unitList[unit4].y)
		|| (unitList[unit2].x == unitList[unit5].x && unitList[unit2].y == unitList[unit5].y))
	{
		unitList[unit2].x = rand() % (map[0].size() / 3);
		unitList[unit2].y = rand() % (map[0].size() / 3);
	}
	while((unitList[unit3].x == unitList[unit4].x && unitList[unit3].y == unitList[unit4].y)
		|| (unitList[unit3].x == unitList[unit5].x && unitList[unit3].y == unitList[unit5].y))
	{
		unitList[unit3].x = rand() % (map[0].size() / 3);
		unitList[unit3].y = rand() % (map[0].size() / 3);
	}
	while((unitList[unit4].x == unitList[unit5].x && unitList[unit4].y == unitList[unit5].y))
	{
		unitList[unit4].x = rand() % (map[0].size() / 3);
		unitList[unit4].y = rand() % (map[0].size() / 3);
	}

	unitList[unit1].move(map, "none");
	unitList[unit2].move(map, "none");
	unitList[unit3].move(map, "none");
	unitList[unit4].move(map, "none");
	unitList[unit5].move(map, "none");

	unitList[enemy1].enemy = true;
	unitList[enemy1].move(map, "none");
	unitList[enemy2].enemy = true;
	unitList[enemy2].move(map, "none");
	unitList[enemy3].enemy = true;
	unitList[enemy3].move(map, "none");
	unitList[enemy4].enemy = true;
	unitList[enemy4].move(map, "none");
	unitList[enemy5].enemy = true;
	unitList[enemy5].move(map, "none");

	system("clear");

	activeUnitList.push_back("Your Active units: ");

	activeUnitList.push_back(unitList[unit1].name);
	activeUnitList.push_back(unitList[unit2].name);
	activeUnitList.push_back(unitList[unit3].name);
	activeUnitList.push_back(unitList[unit4].name);
	activeUnitList.push_back(unitList[unit5].name);

	activeUnitList.push_back("\nEnemies: ");

	activeUnitList.push_back(unitList[enemy1].name);
	activeUnitList.push_back(unitList[enemy2].name);
	activeUnitList.push_back(unitList[enemy3].name);
	activeUnitList.push_back(unitList[enemy4].name);
	activeUnitList.push_back(unitList[enemy5].name);

	displayMap(map, unitList);
}

void activeUnits(const vector<string>& activeUnitList)
{
	for(int i = 0; i < activeUnitList.size(); i++)
	{
		cout << activeUnitList[i] << endl;
	}

	cout << endl;
}