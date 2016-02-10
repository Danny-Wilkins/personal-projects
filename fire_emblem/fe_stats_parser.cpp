/*
Author: Danny Wilkins
Program: fe_stats_parser - Removes html and other unwanted data from a particular html file
Date: 2/10/16
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream ifs("fe7_base_stats.html");
	ofstream ofs("fe7_base_stats_parsed.txt");

	char c;
	string word = "";
	char junk;
	vector<string> notJunk;

	if(!ifs)
	{
		cerr << "File not found" << endl;
		exit(1);
	}

	while(ifs >> c)
	{
		if(c == '<') //Checks for opening html tag
		{
			if((word.size() > 3 || (word[0] >= '0' && word[0] <= '9')) && (word != "Class"
				&& word != "Weapons")) //Sorts out unwanted snippets of leftover junk 
			{
				notJunk.push_back(word);
			}

			word = "";

			ifs >> junk; //Pushes first junk character

			while(junk != '>') //Continues pushing junk until closing tag
			{
				ifs >> junk;
			}
		}
		else if((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z'))
		{
			word += c;
		}
	}

	ifs.close();

	for(string item : notJunk) //Writes all info to new file
	{
		ofs << item << endl;
	}

	ofs.close();

	return 0;
}