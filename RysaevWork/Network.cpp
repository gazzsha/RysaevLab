#include "Network.h"
#include "StationClass.h"
#include "PipeClass.h"
#include <iostream>
#include "Filter.h"
#include <algorithm>
#include <iomanip>
#include "TypeClass.h"

void Graph::Menu()
{
	int a;
	system("cls");
	std::cout << "Choose: \n1-Add a link \n2-Delete a link\n3-Sort Graph\n4-Show connection\n5-Close" << std::endl;
	a = GetCorrectNumber(1, 5);
	switch (a) {
	case 1: 
	{

		AddNetWork();
		Menu();
	}
	break;
	case 2: 
	{
		Delete();
	}
	break;
	case 3: 
	{
		Show();
	}
	break;
	case 4: 
	{
		system("cls");
		int a;
		showconnected();
		std::cout << "1-Back to main menu\n2-Bact to network menu" << std::endl;
		a = GetCorrectNumber(1, 2);
		switch (a) {
		case 1:
		{
			break;
		}
		break;
		case 2: 
		{
			Menu();
		}
		break;
		}
	}
	break;
	case 5:
	{
		break;
	}
	break;
	}
}



void Graph::LoadFromFile()
{
	used.clear();
	graphNetwork.clear();
	mapNetwork.clear();
	freeId.clear();
	busyId.clear();
	for (auto& s : mapPipe) {
		if (s.second.connected !=0) {
			busyId.push_back(s.second.id);
			used.emplace(s.second.inId,0);
			used.emplace(s.second.outId,0);
			Network network(s.second.inId,s.second.outId);
			mapNetwork.emplace(s.second.id, network);
			graphNetwork.emplace(s.second.inId, s.second.outId);
			mapNetwork.emplace(s.second.id, Network(s.second.inId, s.second.outId));
		}
	}
}

void Graph::AddNetWork()
{
	int Id, out;
	char g = true;
	if (size(mapPipe) == 0) {
		system("cls");
		std::cout << "Not data" << std::endl;
		return void();
	}
	freeId.clear();
	for (auto& p : mapPipe) {
		if (p.second.connected == false) {
			freeId.push_back(p.second.id);
		}
	}
	ShowPipe();
	ShowStation();
	while ((g==true)&&(!freeId.empty())) {
		std::cout << "Choose Id pipe to connected from Availables: ";
		for (auto& f : freeId) {
			std::cout << f << ' ';
		}	
		std::cout << std::endl;
		Id = GetCorrectNumber(1, Pipe::MaxIdPipe);
		if (find(freeId.begin(), freeId.end(), Id) != freeId.end()) {
				mapPipe[Id].connected = true;
				std::cout << "Choose input Station" << std::endl;
				mapPipe[Id].inId = GetCorrectNumber(1, Station::MaxIdStation);
				used.emplace(mapPipe[Id].inId, 0);
				std::cout << "Choose output Station" << std::endl;
				out = GetCorrectNumber(1, Station::MaxIdStation);
				{
					while (out == mapPipe[Id].inId) {
						std::cout << "Id of stations repeats" << std::endl;
						out = GetCorrectNumber(1, Station::MaxIdStation);
					}
				}
				mapPipe[Id].outId = out;
				Network network(mapPipe[Id].inId, mapPipe[Id].outId);
				mapNetwork.emplace(Id,network);
				used.emplace(out, 0);
				graphNetwork.emplace(mapPipe[Id].inId, mapPipe[Id].outId);
				mapNetwork.emplace(Id, Network(mapPipe[Id].inId, mapPipe[Id].outId));
				busyId.push_back(Id);
				freeId.erase(find(freeId.begin(), freeId.end(), Id));
		}
		else std::cout << "Not free Id" << std::endl;
			std::cout << "Do you want to continue?" << std::endl;
			g = filter::GetCorrectBool();
	}
}

void Graph::dfs(int a, std::vector<int>& ans,bool &cycle)
{
	used[a] = 1;
	if (graphNetwork.find(a) == graphNetwork.end()) {
		used[a] = 3;
	}
	for (auto& s : graphNetwork) {
		if (s.first == a) {
			int next = s.second;
			if (used[next]==0) {
				dfs(next, ans,cycle);
			}
			else if (used[next]==1)
				cycle = true;
		}
		} 
	
	ans.push_back(a);
}

void Graph::sort()
{
	
	for (auto& s : used) 
		s.second = 0;
		ans.clear();
		for (auto& s : used) {
			if (s.second==0) {
				dfs(s.first, ans,cycle);
			}
		}
std::reverse(ans.begin(), ans.end());	
}


void Graph::Show()
{
	std::cout << "The original graph: ";
	for (auto& s : used) {
		std::cout << s.first << ' ';
	}
	std::cout << std::endl;
	sort();
	std::cout << std::endl;
	if (cycle == true) {
		std::cout << "Graph is cycle" << std::endl;
	}
	else {

		std::cout << "Final graph: \n";
		for (auto& s : ans)
			std::cout << s << ' ';
		std::cout << std::endl; 
	}
	}

void Graph::Delete()
{
	if (busyId.empty()) {
		std::cout << "Not busy pipes" << std::endl; return void();
	}
	int Id;
	char h = true;
	showconnected();
		while ((h==true) && (!busyId.empty())) {
				std::cout << "Choose Id pipe to delete link from Availables:";
				for (auto& b : busyId) {
					std::cout << b << ' ';
				}
				std::cout << std::endl;
				Id = GetCorrectNumber(1, *std::max_element(busyId.begin(), busyId.end()));
				if (find(busyId.begin(), busyId.end(), Id) != busyId.end()) {
					mapPipe[Id].connected = false;
					mapPipe[Id].inId = -1;
					mapPipe[Id].outId = -1;
					used.erase(Id);
					graphNetwork.erase(mapPipe[Id].inId);
					busyId.erase(find(busyId.begin(), busyId.end(), Id));
					mapPipe[Id].inId = -1;
					mapPipe[Id].outId = -1;
					mapNetwork.erase(Id);


				}
				else std::cout << "Not find Id" << std::endl;
				std::cout << "Do you want to continue?" << std::endl;
				h = filter::GetCorrectBool();
		}
	
}

void Graph::showconnected()
{
	if (!used.empty()) {
		std::cout << "===============================================" << std::endl;
		std::cout << "Id pipe" << std::setw(20) << "Id input Station" << std::setw(20) << "Id output Station" << std::endl;
		std::cout << "===============================================" << std::endl;
		for (auto& s : mapNetwork) {
			std::cout << s.first << std::setw(12) << s.second.idinSt << std::setw(18) << s.second.idoutSt << std::endl;
		}
	}
	else std::cout << "Add network" << std::endl;
}
