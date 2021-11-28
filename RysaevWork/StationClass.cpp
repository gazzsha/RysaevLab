#include "StationClass.h"
#include <iomanip>
#include <iostream>
#include "Filter.h"
#include <cstdlib>
#include <thread>
#include <chrono>

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
				filter::GetCorrectString(mapStation[ChangeId].name,30);
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

void StationClass::FilterNameStation()
{
	system("cls");
	StationFilterId.clear();
	std::string Param;
	std::cout << "Name of station:";
	filter::GetCorrectString(Param, 30);
	std::cout << std::endl;
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
void StationClass::FilterPercentageStation()
{
	system("cls");
	StationFilterId.clear();
	double k;
	std::cout << "Percentage: ";
	k=GetCorrectNumber(1.0,100.0);
	for (const auto& s : mapStation) {
		if (k * s.second.WorkShop <= (s.second.WorkShop - s.second.NumberWorkShop) * 100)
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
void StationClass::FilterStation()
{
	system("cls");
	int a;
	std::cout << "Choose\n1.Name of station\n2.Percentage of non-working stations\n3.Close" << std::endl;
	a = GetCorrectNumber(1, 2);
	switch (a) {
	case 1:
	{
		FilterNameStation();
	}
	break;
	case 2:
	{
		FilterPercentageStation();
	}
	break;
	case 3:
	{
		return void();
	}
	break;
	}
	}

void StationClass::PacketStation()
{
	system("cls");
	if (Station::MaxIdStation == 0) {
		std::cout << "Enter the station data" << std::endl;
		return void();
	}
	int a;
	std::cout << "Choose:\n1.Delete all stations\n2.Edit all stations\n3.Edit definite stations\n4.Close" << std::endl;
	a = GetCorrectNumber(1, 4);
	switch (a) {
	case 1:
	{
		system("cls");
		mapStation.clear();
		Station::MaxIdStation = 0;
		std::cout << "All stations are delete" << std::endl;
	}
	break;
	case 2:
	{
		system("cls");
		int a;
		std::cout << "Choose\n1-Name of station\n2-Percentage of idle stations" << std::endl;
		a = GetCorrectNumber(1, 2);
		switch (a) {
		case 1: {
			system("cls");
			ShowStation();
			for (auto& s : mapStation) {
				std::cout << "Station id: " << s.second.id << ' ' << "Name: " << s.second.name << std::endl;
				std::cout << "New name: ";
				s.second.name = filter::GetCorrectString(s.second.name,30);
				std::cout << std::endl;
			}
			std::cout << "All stations is edit" << std::endl;
		}
			  break;
		case 2: {
			system("cls");
			ShowStation();
			double eff, Numerator, Denominator;
			for (auto& s : mapStation) {
				Denominator = s.second.WorkShop;
				Numerator = s.second.NumberWorkShop;
				std::cout << "Station id: " << s.second.id << ' ' << "Percentage of non-working stations: " << (1 - Numerator / Denominator) * 100 << std::endl;
				std::cout << "New Percentage of non - working stations:";
				eff = GetCorrectNumber(1.0, 100.0);
				s.second.NumberWorkShop = (1 - eff / 100) * s.second.WorkShop;
				std::cout << std::endl;
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
			system("cls");
			ShowStation();
			std::this_thread::sleep_for(2000ms);
			FilterNameStation();
			if (size(StationFilterId) == 0) {
				break;
			}
			std::cout << "Edit found stations \n1.Edit all \n2.Edit the specified stations" << std::endl;
			a = GetCorrectNumber(1, 2);
			switch (a) {
			case 1: {
				for (const auto& p : StationFilterId) {
					std::cout << "Station id: " << mapStation[p].id << ' ' << "Name: " << mapStation[p].name << std::endl;
					std::cout << "New name(Max 30 symbol): ";
					filter::GetCorrectString(mapStation[p].name, 30);
					std::cout << std::endl;
				}
			}
				  break;
			case 2:
			{
				int a = 1;
				std::vector<int> res;
				res.clear();
				std::cout << "Available IDs: ";
				for (const auto& p : StationFilterId) {
					std::cout << p << ' ';
				}
				std::cout << std::endl;
				std::cout << "Write the pipe IDs which you want to change(0-Exit): " << std::endl;
				while (a != 0) {
					std::cout << "Id: "; a = GetCorrectNumber(0, Station::MaxIdStation);
					if (std::find(res.begin(), res.end(), a) != res.end()) {
						std::cout << "The element repeats" << std::endl; continue;
					}
					else res.push_back(a);
					if ((std::find(StationFilterId.begin(), StationFilterId.end(), a) == StationFilterId.end()) && (a != 0)) {
						std::cout << "This ID was not found" << std::endl; continue;
					}
				}
				res.pop_back();
				for (const auto& p : StationFilterId) {
					for (const auto& d : res) {
						if (p == d) {
							std::cout << "Pipe Id: " << mapStation[p].id << ' ' << "Name: " << mapStation[p].name << std::endl;
							std::cout << "New name(Max 30 symbol): ";
							filter::GetCorrectString(mapStation[p].name, 30);
							std::cout << std::endl;
						}
					}

				}

			}
			break;
			}
		}
		break;
		case 2:
		{
			double eff,Numerator,Denominator;
			system("cls");
			ShowStation();
			std::this_thread::sleep_for(2000ms);
			FilterPercentageStation();
			if (size(StationFilterId) == 0) {
				break;
			}
			std::cout << "Edit found stations \n1.Edit all \n2.Edit the specified stations" << std::endl;
			a = GetCorrectNumber(1, 2);
			switch (a) {
			case 1: 
			{
				for (const auto& p : StationFilterId) {
					Denominator = mapStation[p].WorkShop;
					Numerator = mapStation[p].NumberWorkShop;

					std::cout << "Station id: " << mapStation[p].id << ' ' << "Percentage of non-working stations: " <<(1-Numerator/Denominator)*100<< std::endl;
					std::cout << "New Percentage of non-working stations: ";
					eff = GetCorrectNumber(1.0, 100.0);
					mapStation[p].NumberWorkShop = (1 - eff / 100) * mapStation[p].WorkShop;
					std::cout << std::endl;
				}

			}
			break;
			case 2: 
			{
				int a = 1;

				std::vector<int> res;
				res.clear();
				std::cout << "Available IDs: ";
				for (const auto& p : StationFilterId) {
					std::cout << p << ' ';
				}
				std::cout << std::endl;
				std::cout << "Write the stations IDs which you want to change(0-Exit): " << std::endl;
				while (a != 0) {
					std::cout << "Id: "; a = GetCorrectNumber(0, Station::MaxIdStation);
					if (std::find(res.begin(), res.end(), a) != res.end()) {
						std::cout << "The element repeats" << std::endl; continue;
					}
					else res.push_back(a);
					if ((std::find(StationFilterId.begin(), StationFilterId.end(), a) == StationFilterId.end()) && (a != 0)) {
						std::cout << "This ID was not found" << std::endl; continue;
					}
				}
				res.pop_back();
				for (const auto& p : StationFilterId) {
					for (const auto& d : res) {
						if (p == d) {
							Denominator = mapStation[p].WorkShop;
							Numerator = mapStation[p].NumberWorkShop;
							std::cout << "Pipe Id: " << mapStation[p].id << ' ' << "Percentage of non - working stations :"  << (1 - Numerator / Denominator) * 100 << std::endl;
							std::cout << "New Percentage of non - working stations:";
							eff = GetCorrectNumber(1.0, 100.0);
							mapStation[p].NumberWorkShop = (1 - eff / 100) * mapStation[p].WorkShop;
							std::cout << std::endl;
						}
					}

				}


			}
			break;
			}
			
		}

		}}
	case 4 : 
		{
			return void();
		}
		break;
		}
	}
	
	

