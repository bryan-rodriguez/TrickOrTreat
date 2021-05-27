//bryan rodriguez : 1001647248
#include "House.h"
#include <chrono>

House::House(std::string name, std::map<int, std::string> candyMap) : houseName{ name }, CandyRankingMap{ candyMap }
{
}

std::string House::ringDoorbell(std::ostringstream &os) 
{
	door.lock();
	os << "*";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	int randNum = rand() % CandyRankingMap.size() + 1;
	door.unlock();
	return CandyRankingMap.at(randNum);
}