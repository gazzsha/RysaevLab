// RysaevWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TypeClass.h"
#include "PipeClass.h"
#include "StationClass.h"
#include "Filter.h"
#include <fstream>
#include <vector>
#include <iomanip>
int Pipe::MaxIdPipe = 0;
int Station::MaxIdStation = 0;
using namespace std;


void printMenu() {
	cout << "1.Add pipe" << endl;
	cout << "2.Add station" << endl;
	cout << "3.Show information" << endl;
	cout << "4.Change pipe" << endl;
	cout << "5.Change station" << endl;
	cout << "6.Delete pipe" << endl;
	cout << "7.Delete station" << endl;
	cout << "8.Safe file" << endl;
	cout << "9.Load from file" << endl;
	cout << "10.Search pipe by filter" << endl;
	cout << "11.Search station by filter" << endl;
	cout << "12.Packet edit pipes" << endl;
	cout << "13.Packet edit stations" << endl;

}



int main()
{
	PipeClass PipeInf;
	StationClass StationInf;
	//vector<Pipe> Pipe(1);
	while (1) {
		printMenu();
		switch (GetCorrectNumber(1, 13))
		{
		case 1:
		{
			PipeInf.AddPipe();

		}
		break;
		case 2:
		{
			StationInf.AddStation();
		}
		break;
		case 3:
		{
			PipeInf.ShowPipe();
			StationInf.ShowStation();
		}
		break;
		case 4:
		{
			PipeInf.ChangePipe();
		}
		break;
		case 5:
		{
			StationInf.ChangeStation();
		}
		break;
		case 6:
		{
			PipeInf.DeletePipe();
		}
		break;
		case 7:
		{
			StationInf.DeleteStation();
		}
		break;
		case 8:
		{
			ofstream out;
			out.open("file.txt", ios::out);
			if (out.is_open())
			{
				PipeInf.SavePipeFile(out);
				out << ' ' << std::endl;
				StationInf.SaveStationFile(out);
				out.close();
			}
		}
		break;
		case 9:
		{
			ifstream fin;
			fin.open("file.txt", ios::in);
			if (fin.is_open()) {
				PipeInf.LoadPipeFile(fin);
				fin.ignore(1000, '\n');
				StationInf.LoadStationFile(fin);
			}
			fin.close();
		}
		break;
		case 10:
		{
			PipeInf.SearchByFilter();
		}
		break;
		case 11:
		{
			StationInf.FilterStation();
		}
		break;
		case 12: 
		{
			PipeInf.PacketPipe();
		}
		break;
		case 13: 
		{
			StationInf.PacketStation();
		}
		break;
		default:
			break;
		}
	}
}