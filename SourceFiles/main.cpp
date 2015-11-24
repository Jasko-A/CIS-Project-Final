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
	bool checker = true;  // this is for the do while loop
	cout << "\tWelcome to the USDA Nutrition Fact Sorter\tby:\t" << " Jasmin Adzic\n" << setw(81) << "Austin Bohannon\n" << setw(82) << "Brandon Archbold\n" << setw(80) << "Mikhail Smelik\n" << setw(71) << "Ahmed\n";

	fstream inFile;
	inFile.open("USDA_data_small.txt");

	string buffer;
	int key;
	int stringLength = 0;
	int index = 0;
	int start = 0;
	char carrot = '^';



	if (inFile)
	{
		while (getline(inFile, buffer))
		{

			buffer = buffer.substr(1, buffer.length());
			index = buffer.find(carrot);
			start = 0;
			string temp1 = buffer.substr(start, index);
			key = stoi(temp1);
			//cout << key << endl;
			start = index + 1;
			buffer = buffer.substr(start, buffer.length());
			index = buffer.find(carrot);
			start = 0;
			string name = buffer.substr(start, index);
			//cout << name << endl;

			start = index + 1;
			buffer = buffer.substr(start, buffer.length());
			index = buffer.find(carrot);
			start = 0;
			string temp2 = buffer.substr(start, index);
			double water = stod(temp2);
			cout << showpoint << fixed << setprecision(2) << water << endl;

			start = index + 1;
			buffer = buffer.substr(start, buffer.length());
			index = buffer.find(carrot);
			start = 0;
			temp2 = buffer.substr(start, index);
			int calories = stoi(temp2);
			cout << calories << endl;

			start = index + 1;
			buffer = buffer.substr(start, buffer.length());
			index = buffer.find(carrot);
			start = 0;
			temp2 = buffer.substr(start, index);
			double protein = stod(temp2);
			cout << showpoint << fixed << setprecision(2) << protein << endl;

			//here we must parse the string into bits of data that we need for the nodes
		}



	}
	char choice;

	do
	{
		cout << endl;
		menu();
		cout << "\nChoice: ";
		cin >> choice;


		switch (choice)
		{
		case 'A':
		case 'a':
			break;
		case 'D':
		case 'd':
			break;
		case 'S':
		case 's':
			char answer;
			cout << "Would you like to seach by unique key (Y/N): ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
				int x = 0;		//temporary
			//do the function
			else if (answer == 'N' || answer == 'n')
				// do the next one
				break;
		case 'H':
		case 'h':
			break;
		case 'P':
		case 'p':
			break;
		case 'W':
		case 'w':
			break;
		case 'T':
		case 't':
			break;
		case 'Q':
		case 'q':
			checker = false;
			break;


		}
	} while (checker);

	menu();
	return 0;
}

void menu()
{
	cout << "\n\nList of Menu options\n\n";
	cout << "A - Add New Data\n"
		<< "D - Delete Data by key number\n"
		<< "S - Search by unique key or item name through the BST\n"
		<< "H - search with hash Table\n"
		<< "P - Special Print\n"
		<< "W - Write Data to File\n"//not sure what this is for but it is in the requirements list
		<< "T - Statsitics\n" // not sure what this is for
		<< "Q - Quit Program\n";
}

