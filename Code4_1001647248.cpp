//bryan Rodriguez : 1001647248
#include "House.h"
#include "TrickOrTreater.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
using namespace std;


void get_command_line_params(int argc, char *argv[], string& TOTnames, string& houses, string& candies)
{
	if (argc == 4)
	{
		TOTnames = argv[1];
		houses = argv[2];
		candies = argv[3];
	}
	else
	{
		throw invalid_argument("Missing command line parameters - - Usage : TrickOrTreaters filename Houses filename Candies filename");
	}
}



int main(int argc, char *argv[])
{
	string TOTnameStr;
	string houseStr;
	string candiesStr;

	stringstream headerNames;

	
	try
	{
		get_command_line_params(argc, argv, TOTnameStr, houseStr, candiesStr);
	}
	catch (invalid_argument& say)
	{
		cout << "Exception: " << say.what() << "\n\n";
		exit(0);
	}
	

	ifstream TOTnameFile{TOTnameStr};
	ifstream housesFile{houseStr};
	ifstream candiesFile{candiesStr};
	
	map<int, string> candyMap;
	vector<House*> Houses;
	vector<TrickOrTreater> TOTs;

	if (candiesFile.is_open() && (housesFile.is_open() && TOTnameFile.is_open())) // stocking variables from files
	{
		string bufferStr;
		char *token;
		char bufferChar[100];
		int key;
		string value;

		while (getline(candiesFile,bufferStr)) 
		{
			strcpy(bufferChar, bufferStr.c_str());
			token = strtok(bufferChar, "|");
			strcpy(bufferChar,token);
			value = bufferChar;
			token = strtok(NULL,"|");
			key = atoi(token);
			candyMap.insert(make_pair(key,value));
		}

		getline(housesFile,bufferStr);
		Houses.push_back(new House(bufferStr, candyMap));
		headerNames << "          " << bufferStr;
		string prevBuffer = bufferStr;

		while (getline(housesFile,bufferStr)) 
		{
			Houses.push_back(new House(bufferStr,candyMap));
			headerNames << setw((11 - prevBuffer.length()) + bufferStr.length()) << bufferStr;
			prevBuffer = bufferStr;
		}

		while (getline(TOTnameFile, bufferStr)) 
		{
			TOTs.push_back(TrickOrTreater {bufferStr, Houses});
			cout << bufferStr << endl;
		}
		
	}
	else
	{
		cout << "\n one of the files did not open properly \n";
		exit(0);
	}

	string newPage = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	for (auto &TOT : TOTs)
	{
		TOT.startThread();
	}
	
	while (TrickOrTreater::ImDone != TOTs.size())
	{
		cout << newPage;
		cout << headerNames.str() << "\n";
		for (auto &TOT : TOTs)
		{
			cout << TOT.getPath() << TOT.getName() << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(5));
	}
	

	for (auto &TOT : TOTs) 
	{
		cout << TOT << endl;
		TOT.joinThread();
		
	}


	for (auto &houses : Houses) 
	{
		delete houses;
	}
	Houses.clear();
	candiesFile.close();
	housesFile.close();
	TOTnameFile.close();




	return 0;
}