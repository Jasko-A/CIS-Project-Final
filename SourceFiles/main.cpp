/**
Main file
**/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/BinarySearchTree.h"
#include "../HeaderFiles/HashTable.h"

using namespace std;

void menu();

int main()
{
	cout << "Welcome to the USDA\n\n";
	fstream inFile;
	string line;
	inFile.open("USDA_data_small.txt");
	if (inFile)
	{
		while (inFile >> line)
		{
			//here we must parse the string into bits of data that we need for the nodes
		}
		
		
		
	}

	menu();
	return 0;
}

void menu()
{
	cout << "\tWelcome to the USDA Nutrition Fact Sorter\tby:\t" << " Jasmin Adzic\n" << setw(81) << "Austin Bohannon\n" << setw(82) << "Brandon Archbold\n" << setw(80) << "Mikhail Smelik\n" << setw(71) << "Ahmed\n";
}
