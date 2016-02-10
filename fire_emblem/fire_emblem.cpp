#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Unit
{
public:
	Unit(const string& unitName, const int& unitHp, const int& unitSm, const int& unitSkl,
		const int& unitSpd, const int& unitLck, const int& unitDef, const int& unitRes,
		const int& unitCon, const int& unitMov) : name(unitName), hp(unitHp), sm(unitSm),
		skl(unitSkl), spd(unitSpd), lck(unitLck), def(unitDef), res(unitRes), con(unitCon),
		mov(unitMov)
	{

	}

	void statDisplay() const
	{
		cout << "Name: " << name << endl;
		cout << "HP: " << hp << endl;
		cout << "Strength/Magic: " << sm << endl;
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

//private:
	string name; //Name
	int hp;	//HP
	int sm;	//Strength/Magic
	int skl; //Skill
	int spd; //Speed
	int lck; //Luck
	int def; //Defense
	int res; //Resistance
	int con; //Constitution
	int mov; //Movement
};

void genUnits(vector<Unit>& unitList);
void genStats(const string& name, const vector<int>& stats, vector<Unit>& unitList);
void displayUnit(const vector<Unit>& unitList, const string& displayName);
void command(const vector<Unit>& unitList);

int main()
{
	vector<Unit> unitList;
	genUnits(unitList);
	displayUnit(unitList, "all");
	//command(unitList);

	return 0;
}

void genUnits(vector<Unit>& unitList) //Generates units from a file
{
	string word;
	string unitClass;
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
				genStats(unitClass, stats, unitList);
				stats.clear();
				unitClass = "";
			}

			unitClass = word;
		}
		else
		{
			unitStat = stoi(word);
			stats.push_back(unitStat);
		}
	}

	if(ifs.eof())
	{
		genStats(unitClass, stats, unitList);
		stats.clear();
		unitClass = "";
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

void displayUnit(const vector<Unit>& unitList, const string& displayName)
{
	cout << endl;

	if(displayName == "all")
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
			if(displayName == someUnit.name)
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
		string displayName;
		cout << "Which unit would you like to display: ";
		cin >> displayName;
		displayUnit(unitList, displayName);
	}

	if(inputCommand != "quit")
	{
		command(unitList);
	}
}