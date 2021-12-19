#pragma once
#include<unordered_map>
#include "TypeClass.h"
#include <fstream>
#include <vector>
class PipeClass
{
protected:
	std::vector<int> PipeFilterId;
	std::unordered_map<int, Pipe> mapPipe;

public:
	void AddPipe();
	void ShowPipe();
	void ChangePipe();
	void DeletePipe();
	void SavePipeFile(std::ofstream& out);
	void LoadPipeFile(std::ifstream& fin);
	void FilterPaip();
	void PacketPipe();
	friend class Graph;
};

