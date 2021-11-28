#pragma once
#include <unordered_map>
#include "TypeClass.h"
#include <vector>
class StationClass
{
private:
	std::unordered_map<int, Station> mapStation;
	std::vector<int>StationFilterId;
public: 
	void AddStation();
	void ShowStation();
	void ChangeStation();
	void DeleteStation();
	void SaveStationFile(std::ofstream& out);
	void LoadStationFile(std::ifstream& fin);
	void FilterStation();
	void PacketStation();
	void FilterNameStation();
	void FilterPercentageStation();
};

