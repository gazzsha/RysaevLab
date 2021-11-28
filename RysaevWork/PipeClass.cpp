#include "PipeClass.h"
#include <iomanip>
#include "Filter.h"
#include "TypeClass.h"
#include <algorithm>

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
	system("cls");
	bool Param;
	PipeFilterId.clear();
	std::cout << "Write down what status of pipes to look for: \n0-Not work \n1-Work" << std::endl;
	Param = filter::GetCorrectBool();
	for (const auto& P : mapPipe) {
		if (P.second.work == Param)
			PipeFilterId.push_back(P.first);
	}
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
	system("cls");
	if (Pipe::MaxIdPipe == 0) {
		std::cout << "Enter the pipe data" << std::endl;
		return void();
	}
	int a;
	std::cout << "Choose\n1-Delete all pipes\n2-Edit all pipes\n3-Edit definite pipes\n4.Close" << std::endl;
	a = GetCorrectNumber(1, 4);
	switch (a) {
	case 1: 
	{
		system("cls");
		mapPipe.clear();
		Pipe::MaxIdPipe = 0;
		std::cout << "All pipes are delete" << std::endl;
		}
	break;
	case 2: 
	{
		system("cls");
		ShowPipe();
		for ( auto& p : mapPipe) {
			std::cout << "Pipe id: " << p.second.id<< ' ' << "Pipe status: " << p.second.work << std::endl;
			std::cout << "New status of pipe(0-Not wotking,1-Working) ";
			p.second.work = filter::GetCorrectBool();
			std::cout << std::endl;
		}
		std::cout << "All pipes are edit" << std::endl;
	}
	break;
	case 3: 
	{
		int a;
		system("cls");
		FilterPaip();
		if (size(PipeFilterId) == 0) {
			break;
		}
		std::cout << "Edit found pipes \n1.Edit all \n2.Edit the specified pipes\n3.Delete all\n4.Delete the specified pipes\n5.Close" << std::endl;
		a = GetCorrectNumber(1, 5);
		switch (a) {
		case 1:
		{
			for (const auto& p : PipeFilterId) {
				std::cout << "Pipe id: " << mapPipe[p].id << ' ' << "Pipe status: " << mapPipe[p].work << std::endl;
				std::cout << "New status of pipe(0-Not wotking,1-Working) ";
				mapPipe[p].work = filter::GetCorrectBool();
				std::cout << std::endl;
			}
		}
		break;
		case 2:
		{
			int a = 1;
			std::vector <int> res;
			res.clear();
			std::cout << "Available IDs: ";
			for (const auto& p : PipeFilterId) {
				std::cout << p << ' ';
			}
			std::cout << std::endl;
			std::cout << "Write the pipe IDs which you want to change(0-Exit): " << std::endl;
			while (a != 0) {
				std::cout << "Id: "; a = GetCorrectNumber(0, Pipe::MaxIdPipe);
				if (std::find(res.begin(), res.end(), a) != res.end()) {
					std::cout << "The element repeats" << std::endl; continue;
				}
				else res.push_back(a);
				if ((std::find(PipeFilterId.begin(), PipeFilterId.end(), a) == PipeFilterId.end()) && (a != 0)) {
					std::cout << "This ID was not found" << std::endl; continue;
				}
			}
			res.pop_back();
			for (const auto& p : PipeFilterId) {
				for (const auto& d : res) {
					if (p == d) {
						std::cout << "Pipe Id: " << mapPipe[p].id << ' ' << "Work status: " << mapPipe[p].work << std::endl;
						std::cout << "New status of pipe(0-Not wotking,1-Working) ";
						mapPipe[p].work = filter::GetCorrectBool();
						std::cout << std::endl;
					}
				}

			}


		}
		break;
		case 3:
		{
			for (auto& s : PipeFilterId) {
				mapPipe.erase(s);
			}
			system("cls");
			std::cout << "Pipes are deleted" << std::endl;
		}
		break;
		case 4:
		{
			int a = 1;
			std::vector <int> res;
			res.clear();
			std::cout << "Available IDs: ";
			for (const auto& p : PipeFilterId) {
				std::cout << p << ' ';
			}
			std::cout << std::endl;
			std::cout << "Write the pipe IDs which you want to change(0-Exit): " << std::endl;
			while (a != 0) {
				std::cout << "Id: "; a = GetCorrectNumber(0, Pipe::MaxIdPipe);
				if (std::find(res.begin(), res.end(), a) != res.end()) {
					std::cout << "The element repeats" << std::endl; continue;
				}
				else res.push_back(a);
				if ((std::find(PipeFilterId.begin(), PipeFilterId.end(), a) == PipeFilterId.end()) && (a != 0)) {
					std::cout << "This ID was not found" << std::endl; continue;
				}
			}
			res.pop_back();
			for (const auto& p : PipeFilterId) {
				for (const auto& d : res) {
					if (p == d) {
						mapPipe.erase(p);
					}
				}

			}
			system("cls");
			std::cout << "Pipes are deleted" << std::endl;

		}
		break;
		case 5: {
			system("cls");
			break;
		}
			  break;
		}
	}
	break;
	case 4: 
		{
		system("cls");
			break;
		}

		}
	

	}






