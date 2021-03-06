#include "TypeClass.h"
#include <string>
#include <iomanip>
#include "Filter.h"


Pipe::Pipe()
{

	MaxIdPipe++;
	this->id = MaxIdPipe;
	std::cout << "Lenght:" << std::endl;
	this->length = GetCorrectNumber(1, 100);
	std::cout << "Diameter:" << std::endl;
	this->diameter = GetCorrectNumber(1, 100);
	std::cout << "Work status:" << std::endl;
	this->work = filter::GetCorrectBool();
	this->connected = false;
}

void Pipe::SavePipe(std::ofstream& out)
{
	out << id << std::endl
		<< length << std::endl
		<< diameter << std::endl
		<< work << std::endl
		<< connected << std::endl
		<< inId << std::endl
		<< outId << std::endl;
}

Pipe::Pipe(std::ifstream& fin)
{
	fin >> this->id
		>> this->length
		>> this->diameter
		>> this->work
		>> this->connected
		>> this->inId
		>> this->outId;

}


Station::Station()
{
	MaxIdStation++;
	this->id = MaxIdStation;
	std::cout << "MaxSize of name: 30, Name: " << std::endl;
	filter::GetCorrectString(this->name,30);
	std::cout << "WorkShop:" << std::endl;
	this->WorkShop = GetCorrectNumber(1, 20);
	std::cout << "Number on working shop:" << std::endl;
	this->NumberWorkShop = GetCorrectNumber(1, this->WorkShop);
	std::cout << "Eff of station:" << std::endl;
	this->eff = GetCorrectNumber(1, 100);
}

void Station::SaveStation(std::ofstream& out)
{
	out << id << std::endl
		<< name << std::endl
		<< WorkShop << std::endl
		<< NumberWorkShop << std::endl
		<< eff << std::endl;
}

Station::Station(std::ifstream& fin)
{
	fin >> this->id;
	fin.ignore(1000,'\n');
	getline(fin, this->name);
	fin >> this-> WorkShop
		>> this->NumberWorkShop
		>> this->eff;
}

Network::Network(int a, int b)
{
	this->idinSt = a;
	this->idoutSt = b;
}
