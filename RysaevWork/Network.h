#pragma once
#include "PipeClass.h"
#include "StationClass.h"
#include <map>
class Graph :public PipeClass, public StationClass{
public:
	std::multimap <int, int> graphNetwork;
	std::vector<int> ans;
	std::unordered_map<int, bool> used;
	std::unordered_map<size_t, Network> mapNetwork;
	void AddNetWork();
	void Menu();
	void dfs(int a,std::vector<int> &ans);
	void sort();
	void Show();
	void Delete();
	void showconnected();
	std::vector<int> freeId;
	std::vector<int> busyId;
};

