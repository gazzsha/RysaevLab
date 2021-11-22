#include "Filter.h"
#include <conio.h>
#include <string>

bool filter::GetCorrectBool()
{
	char repair;
	while (true)
	{
		repair = _getch();
		if (repair == '0')
			return false;
		else if (repair == '1')
			return true;
		else
			std::cout << "Error! Input correct value!!!" << std::endl;
	}
}

std::string filter::GetCorrectString(std::string& k)
{
		std::string a;
		std::cin.seekg(std::cin.eof());
		std::getline(std::cin, a);
		k = a;
		a.erase(remove(a.begin(), a.end(), ' '), a.end());
		while (a.empty()) {
			std::cout << "Try again.\n";
			std::getline(std::cin, a);
			k = a;
			a.erase(remove(a.begin(), a.end(), ' '), a.end());
		}
		return k.substr(k.find_first_not_of(" \t"));
	}





