#pragma once
#include <iostream>
#include <string>
#include <string>
#include <vector>


namespace filter {
	bool GetCorrectBool();
	std::string GetCorrectString(std::string& k,int lenght);
}
template <typename T> 
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x<min || x>max) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Please,choose number again(" << min << "-" << max << "):";
	}
	return x;
}
