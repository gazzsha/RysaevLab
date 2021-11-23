#include "StationClass.h"
#include <iomanip>
#include <iostream>
#include "Filter.h"
#include <cstdlib>

using namespace std;
void StationClass::AddStation()
{
	Station station;
	mapStation.emplace(station.id, station);
}

void StationClass::ShowStation()
{
	if (size(mapStation) != 0) {
		cout << "================================================================================" << endl;
		cout << "Station" << '\n' << "Id Station" << setw(28) << "Name" << setw(12) << "Workshop" << setw(19) << "Working station" << setw(11) << "Percent" << endl;
		cout << "================================================================================" << endl;
		for (const auto& s : mapStation) {
			std::cout << s.second.id << std::setw(37) << s.second.name << std::setw(12) << s.second.WorkShop << std::setw(19) << s.second.NumberWorkShop << std::setw(11) << s.second.eff << std::endl;
		}
	}
	else std::cout << "Not input station" << std::endl;
}

void StationClass::ChangeStation()
{
	unsigned ChangeId;
	int a;
	if (size(mapStation) != 0) {
		std::cout << "Id of station:" << std::endl;
		ChangeId = GetCorrectNumber(1, Station::MaxIdStation);
		if (mapStation.find(ChangeId) != mapStation.end()) {
			std::cout << "Pipe is find,you can change name or eff of it." << std::endl;
			std::cout << "1-Name,0-Eff" << std::endl;
			a = GetCorrectNumber(0, 1);
			switch (a) {
			case 0: 
			{
				std::cout << "Eff now:" << mapStation[ChangeId].eff << std::endl;
				std::cout << "New eff(1-100):" << std::endl;
				mapStation[ChangeId].eff = GetCorrectNumber(1, 100);

			}
			break;
			case 1: 
			{
				std::cout << "Name of station now:" << mapStation[ChangeId].name << std::endl;
				std::cout << "New name:" << std::endl;
				filter::GetCorrectString(mapStation[ChangeId].name);
			}
			break;
			}
		}
		else std::cout << "Station is not find" << std::endl;

	}
	else std::cout << "Station is not imput" << std::endl;
}

void StationClass::DeleteStation()
{
		unsigned DeleteId;
		if (size(mapStation) != 0) {
			std::cout << "Id of station:" << std::endl;
			DeleteId = GetCorrectNumber(1, Station::MaxIdStation);
			if (mapStation.find(DeleteId) != mapStation.end()) {
				std::cout << "Station is find" << std::endl;
				mapStation.erase(DeleteId);
				std::cout<< "Station is delete" << std::endl;
			}
			else std::cout << "Station is not find" << std::endl;
		}
		else std::cout << "Station is not imput" << std::endl;
	}

void StationClass::SaveStationFile(std::ofstream& out)
{
	if (!mapStation.empty())
	{
		out << Station::MaxIdStation << std::endl;
		for ( auto& S : mapStation) {
			S.second.SaveStation(out);
		}
	}
	else
		std::cout << "Station is not input" << std::endl;
}

void StationClass::LoadStationFile(std::ifstream& fin)
{

	if (fin.peek()!=-1 && fin.peek() != ' ') {
		fin >> Station::MaxIdStation;
		while (fin.peek() != ' ' && fin.peek()=='\n') {
			Station station(fin);
			mapStation.emplace(station.id, station);
		}
	}
}

void StationClass::FilterStation()
{
	StationFilterId.clear();
	std::string Param;
	int a;
	double k;
	std::cout << "Choose,1-Name of station,2-Percentage of idle stations" << std::endl;
	a = GetCorrectNumber(1, 2);
	switch (a) {
	case 1:
	{
		std::cout << "Name of statiom?" << std::endl;
		filter::GetCorrectString(Param);
		for (const auto& s : mapStation) {
			if (Param == s.second.name)
				StationFilterId.push_back(s.first);
		}
		if (size(StationFilterId) != 0) {
			cout << "================================================================================" << endl;
			cout << "Station" << '\n' << "Id Station" << setw(28) << "Name" << setw(12) << "Workshop" << setw(19) << "Working station" << setw(11) << "Percent" << endl;
			cout << "================================================================================" << endl;
			for (const auto& s : StationFilterId) {
				std::cout << mapStation[s].id << std::setw(37) << mapStation[s].name << std::setw(12) << mapStation[s].WorkShop << std::setw(19) << mapStation[s].NumberWorkShop << std::setw(11) << mapStation[s].eff << std::endl;
			}

		}
		else std::cout << "Not find with name:" << Param << ::endl;
	}
	break;
	case 2:
	{
		StationFilterId.clear();
		std::cout << "Percentage of idle stations" << std::endl;
		k = GetCorrectNumber(1, 100);
		for (const auto& s : mapStation) {
			if (k * s.second.WorkShop <= (s.second.WorkShop - s.second.NumberWorkShop)*100)
				StationFilterId.push_back(s.first);
		}
		if (size(StationFilterId) != 0) {
			cout << "================================================================================" << endl;
			cout << "Station" << '\n' << "Id Station" << setw(28) << "Name" << setw(12) << "Workshop" << setw(19) << "Working station" << setw(11) << "Percent" << endl;
			cout << "================================================================================" << endl;
			for (const auto& s : StationFilterId) {
				std::cout << mapStation[s].id << std::setw(37) << mapStation[s].name << std::setw(12) << mapStation[s].WorkShop << std::setw(19) << mapStation[s].NumberWorkShop << std::setw(11) << mapStation[s].eff << std::endl;
			}

		}
		else std::cout << "Not find with perametr:" << k << ::endl;
		
		}
	break;

	}

	}

void StationClass::PacketStation()
{
	int a;
	std::cout << "Choose" << std::endl;
	std::cout << "1-Delete all stations" << std::endl;
	std::cout << "2-Edit all stations" << std::endl;
	std::cout << "3-Edit definite stations" << std::endl;
	a = GetCorrectNumber(1, 3);
	switch (a) {
	case 1:
	{
		mapStation.clear();
		Station::MaxIdStation = 0;
		std::cout << "All stations are delete" << std::endl;
	}
	break;
	case 2:
	{
		int a;
		std::cout << "Edit of name or number of working station" << std::endl;
		std::cout << "1-Names of station" << std::endl;
		std::cout << "2-Numbers of working station" << std::endl;
		a = GetCorrectNumber(1, 2);
		switch (a) {
		case 1: {
			ShowStation();
			for (auto& s : mapStation) {
				std::cout << "Station with id: " << s.second.id << ' ' << "Have name: " << s.second.name << std::endl;
				std::cout << "New name: ";
				s.second.name = filter::GetCorrectString(s.second.name);
			}
			std::cout << "All stations is edit" << std::endl;
		}
			  break;
		case 2: {
			ShowStation();
			for (auto& s : mapStation) {
				std::cout << "Station with id: " << s.second.id << ' ' << "Have number of working station: " << s.second.NumberWorkShop << std::endl;
				std::cout << "New number: ";
				s.second.NumberWorkShop = GetCorrectNumber(1, s.second.WorkShop);
			}
			std::cout << "All stations is edit" << std::endl;
		}
			  break;
		}
	}
	break;
	case 3:
	{
		int a;
		std::cout << "Choose" << std::endl;
		std::cout << "1-Name" << std::endl;
		std::cout << "2-Percent of not working station" << std::endl;
		a = GetCorrectNumber(1, 2);
		switch (a) {
		case 1:
		{
			ShowStation();
			StationFilterId.clear();
			std::string Param;
			std::string newName;
			std::cout << "Name of statiom?" << std::endl;
			filter::GetCorrectString(Param);
			for (const auto& s : mapStation) {
				if (Param == s.second.name)
					StationFilterId.push_back(s.first);
			}
			if (size(StationFilterId) != 0) {
				std::cout << "Station is find with name: "<<Param << std::endl;
				std::cout << "New name: ";
				filter::GetCorrectString(newName);
				for (auto& s : StationFilterId) {
					mapStation[s].name = newName;
				}
				std::cout << "Selected stations are edit" << endl;
			}
			else std::cout << "Not find" << std::endl;
		}
		break;
		case 2:
		{
			ShowStation();
			int Param;
			StationFilterId.clear();
			std::cout << "Percent of not working stations?" << std::endl;
			Param = GetCorrectNumber(1, 100);
			for (const auto& s : mapStation) {
				if (Param * s.second.WorkShop <= (s.second.WorkShop - s.second.NumberWorkShop) * 100)
					StationFilterId.push_back(s.first);
			}
			if (size(StationFilterId) != 0) {
				for (auto& s : StationFilterId) {
					std::cout << "Station with this value of not working stations:" << Param << ' ' << "is find" << "Id of station: "<<mapStation[s].id<<' ' << "Number of workingShop: " << mapStation[s].NumberWorkShop << std::endl;
					mapStation[s].NumberWorkShop = GetCorrectNumber(1, mapStation[s].WorkShop);
				}
				std::cout << "Selected stations are edit" << endl;
			}
			else std::cout << "Not find" << std::endl;
		}
		break;
		}
	}
	}
	}