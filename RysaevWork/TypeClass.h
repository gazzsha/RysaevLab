#pragma once
#include <fstream>
class Pipe
{
public: 
	static int MaxIdPipe;
	size_t id;
	double length, diameter;
	bool work;
	Pipe();
	void SavePipe(std::ofstream&out);
	Pipe(std::ifstream& fin);
};

class Station {
public: 
	static int MaxIdStation;
	size_t id;
	std::string name;
	int WorkShop, NumberWorkShop;
	double eff;
	Station();
	void SaveStation(std::ofstream& out);
	Station(std::ifstream& fin);

};

