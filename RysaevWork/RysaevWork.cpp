// RysaevWork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "TypeClass.h"
#include "PipeClass.h"
#include "StationClass.h"
#include "Network.h"
#include "Filter.h"
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdio.h>
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
	cout << "14.NetWork" << endl;

}



int main()
{

	Graph InfNetWork;
	while (1) {
		printMenu();
		switch (GetCorrectNumber(1, 14))
		{
		case 1:
		{
			InfNetWork.AddPipe();

		}
		break;
		case 2:
		{
			InfNetWork.AddStation();
		}
		break;
		case 3:
		{
			system("cls");
			InfNetWork.ShowPipe();
			InfNetWork.ShowStation();
		}
		break;
		case 4:
		{
			InfNetWork.ChangePipe();
		}
		break;
		case 5:
		{
			InfNetWork.ChangeStation();
		}
		break;
		case 6:
		{
			InfNetWork.DeletePipe();
		}
		break;
		case 7:
		{
			InfNetWork.DeleteStation();
		}
		break;
		case 8:
		{
			system("cls");
			string filename;
			cout << "MaxSize of name: 20,Filename: " << endl;
			filter::GetCorrectString(filename,20);
				ofstream out;
				out.open(filename, ios::out);
				if (out.is_open())
				{
					InfNetWork.SavePipeFile(out);
					out << ' ' << std::endl;
					InfNetWork.SaveStationFile(out);
					out.close();
				}
			
		}
		break;
		case 9:
		{
			system("cls");
			ifstream fin;
			string filename;
			cout << "MaxSize of name: 20,Filename: " << endl;
			filter::GetCorrectString(filename,20);
			fin.open(filename, ios::in);
			if (fin.is_open()) {
				InfNetWork.LoadPipeFile(fin);
				fin.ignore(1000, '\n');
				InfNetWork.LoadStationFile(fin);
				fin.close();
			}
			else cout << "Not find file" << endl;
			InfNetWork.LoadFromFile();
		}
		break;
		case 10:
		{
			InfNetWork.FilterPaip();
		}
		break;
		case 11:
		{
			InfNetWork.FilterStation();
		}
		break;
		case 12: 
		{
			InfNetWork.PacketPipe();
		}
		break;
		case 13: 
		{
			InfNetWork.PacketStation();
		}
		break;
		case 14:
		{
			InfNetWork.Menu();
		}
		break;
		}
	}
}
