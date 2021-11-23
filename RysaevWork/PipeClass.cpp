#include "PipeClass.h"
#include <iomanip>
#include "Filter.h"
#include "TypeClass.h"


void PipeClass::AddPipe()
{
	Pipe pipe;
	mapPipe.emplace(pipe.id, pipe);
}

void PipeClass::ShowPipe()
{
	if (size(mapPipe) != 0) {
		std::cout << "==================================================" << std::endl;
		std::cout << "Pipe" << '\n' << "Id Pipe" << std::setw(12) << "Length" << std::setw(19) << "Diameter" << std::setw(11) << "Work" << std::endl;
		std::cout << "==================================================" << std::endl;
		for (const auto& p : mapPipe) {
			std::cout << p.second.id << std::setw(18) << p.second.length << std::setw(18) << p.second.diameter << std::setw(12) << p.second.work << std::endl;
		}
	}
	else std::cout << "Not input pipe" << std::endl;
}

void PipeClass::ChangePipe()
{
	unsigned ChangeId;
	if (size(mapPipe) != 0) {
		std::cout << "Id of pipe:" << std::endl;
		ChangeId = GetCorrectNumber(1, Pipe::MaxIdPipe);
		if (mapPipe.find(ChangeId) != mapPipe.end()) {
			std::cout << "Pipe is find,you can change work status of it." << std::endl;
			std::cout << "Status now:" << mapPipe[ChangeId].work << std::endl;
			std::cout << "1-It is working,0-It isnt working" << std::endl;
			mapPipe[ChangeId].work = filter::GetCorrectBool();
		}
		else std::cout << "Pipe is not find" << std::endl;

	}
	else std::cout << "Pipe is not imput" << std::endl;

}

void PipeClass::DeletePipe()
{
	unsigned DeleteId;
	if (size(mapPipe) != 0) {
		std::cout << "Id of pipe:" << std::endl;
		DeleteId = GetCorrectNumber(1, Pipe::MaxIdPipe);
		if (mapPipe.find(DeleteId) != mapPipe.end()) {
			std::cout << "Pipe is find" << std::endl;
			mapPipe.erase(DeleteId);
			
			std:: cout<< "Pipe is delete" << std::endl;
		}
		else std::cout << "Pipe is not find" << std::endl;
	}
	else std::cout << "Pipe is not input" << std::endl;
}

void PipeClass::SavePipeFile(std::ofstream& out)
{
	if (!mapPipe.empty())
	{
		out << Pipe::MaxIdPipe << std::endl;
		for (auto& P : mapPipe) {
			P.second.SavePipe(out);
		}
	}
	else 
		std::cout << "Pipe is not input" << std::endl; 
}

void PipeClass::LoadPipeFile(std::ifstream& fin){
	if (fin.peek() != -1) {
		fin >> Pipe::MaxIdPipe;
		while (fin.peek() !=' ' && fin.peek()!=-1) {
			Pipe pipe(fin);
			mapPipe.emplace(pipe.id, pipe);
			fin.ignore(1000, '\n');
		}
	}
}

void PipeClass::FilterPaip()
{
	bool Param;
	PipeFilterId.clear();
	std::cout << "Work status of Pipe?" << std::endl;
	Param = filter::GetCorrectBool();
	for (const auto& P : mapPipe) {
		if (P.second.work == Param)
			PipeFilterId.push_back(P.first);
	}
}

void PipeClass::SearchByFilter()
{
	FilterPaip();
	if (size(PipeFilterId) != 0) {
		std::cout << "==================================================" << std::endl;
		std::cout << "Pipe" << '\n' << "Id Pipe" << std::setw(12) << "Length" << std::setw(19) << "Diameter" << std::setw(11) << "Work" << std::endl;
		std::cout << "==================================================" << std::endl;
		for (const auto& s : PipeFilterId) {
			std::cout << mapPipe[s].id << std::setw(18) << mapPipe[s].length << std::setw(18) << mapPipe[s].diameter << std::setw(12) << mapPipe[s].work << std::endl;
		}
	}
	else std::cout << "Not pipe with work status" << std::endl;
}

void PipeClass::PacketPipe()
{
	int a;
	std::cout << "Choose" << std::endl;
	std::cout << "1-Delete all pipes" << std::endl;
	std::cout << "2-Edit all pipes" << std::endl;
	std::cout << "3-Edit definite pipes" << std::endl;
	a = GetCorrectNumber(1, 3);
	switch (a) {
	case 1: 
	{
		mapPipe.clear();
		Pipe::MaxIdPipe = 0;
		std::cout << "All pipes are delete" << std::endl;
		}
	break;
	case 2: 
	{
		for (auto& P : mapPipe) {
			P.second.work = !P.second.work;
		}
		std::cout << "All pipes are edit" << std::endl;
	}
	break;
	case 3: 
	{
		FilterPaip();
		for (auto& p : PipeFilterId) {
			mapPipe[p].work = !mapPipe[p].work;
		}
		std::cout << "Selected pipes are edit" << std::endl;
	}
	break;
	}

	}






