#pragma once
#include<unordered_map>
#include "TypeClass.h"
#include <fstream>
#include <vector>
class PipeClass
{
private: 
	std::unordered_map<int, Pipe> mapPipe;
	std::vector<int> PipeFilterId;

public:
	void AddPipe();
	void ShowPipe();
	void ChangePipe();
	void DeletePipe();
	void SavePipeFile(std::ofstream& out);
	void LoadPipeFile(std::ifstream& fin);
	void FilterPaip();
	void PacketPipe();

};

