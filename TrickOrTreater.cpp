//bryan rodriguez : 1001647248
#include "TrickOrTreater.h"

//member functions
int TrickOrTreater::ImDone = 0;

TrickOrTreater::TrickOrTreater(std::string Name, std::vector<House*> houses) : name{ Name }, ListOfHouses{ houses }
{
}

std::string TrickOrTreater::getName() 
{
	return name;
}

void TrickOrTreater::startThread() 
{
	TOTThreadPtr = new std::thread(&TrickOrTreater::GoTrickOrTreating, this);
}

void TrickOrTreater::joinThread() 
{
	this->TOTThreadPtr->join();
}

void TrickOrTreater::GoTrickOrTreating() 
{
	for (auto house : ListOfHouses) 
	{
		int speed = (rand() % 500) + 1;
		Walk(speed);
		std::string candyName = house->ringDoorbell(path);
		Bucket[candyName]++;
		
	}
	TrickOrTreater::ImDone++;
}

void TrickOrTreater::Walk(int speed) 
{
	int i = 0;
	for (i = 0; i < 10; i++) 
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		path << ".";
	}
}

std::string TrickOrTreater::getPath() 
{
	return path.str();
}

// non member functions

std::ostream& operator<<(std::ostream& output, TrickOrTreater& TOT)
{
	output << TOT.name << "'s - ";
	for (auto candy : TOT.Bucket) 
	{
		output << candy.second << " " << candy.first << "," ;
	}
	return output;

}