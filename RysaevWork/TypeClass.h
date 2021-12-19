#pragma once
#include <fstream>
class Pipe
{
public: 
	static int MaxIdPipe;
	size_t id;
	double length, diameter;
	bool work;
	bool connected;
	size_t inId;
	size_t outId;
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

class Network {
public: 
	size_t idinSt;
	size_t idoutSt;
	Network(int a,int b);
};

