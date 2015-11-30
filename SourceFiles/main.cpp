/**===================================*/
/*CIS 22C Team Project
Team 8: USDA Nutritional Facts Sorter and Filer
by: Austin Bohannon, Brandon Archbold, Ahmed Shalan, Mikhail Smelik, Jasmin Adzic

The purpose of this function is to sort data from a file, put that data into objects
in which they will be stored into a hash table, binary search tree ,and a stack.
The program, upon choice, will later print the indented tree, print the sorted data,
delete a certain object, add an object, update the tree/hash table, and show the
statisics of the hash table.

*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/BinarySearchTree.h"
#include "../HeaderFiles/HashTable.h"
#include "../HeaderFiles/SearchManager.h"
#include "../HeaderFiles/ListManager.h"

using namespace std;

int fileSize(string fileName); //To count the lines for the HashTable
int hashSize(int fileSize); //To calculate hash size from number of lines
Food* fileInput(ifstream &inFile); //To get the data from the file
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable); //To put the data in the ADTs
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable); //To clear the data in the ADTs
void printToFile(ofstream &outFile, Stack<Food> * printStack); //To print everything out
Food * addNew(); //To add a new Food object to all of the ADTs from stdin
//void reHash(HashTable &hTable); //Unnecessary
int enterInt(); //Input validation for an int
string enterStr(); //Input validation for a string
void menu(); //Display menu

int main()
{
    cout << "USDA Nutritional Facts Management System\n\nBY:\n" << "Jasmin Adzic\n" << "Brandon Archbold\n" << "Austin Bohannon\n" << "Ahmed Shalan\n" << "Mikhail Smelik\n";

    string fileName = "../ResourceFile/USDA_data_small.txt"; //Delete for production

    ifstream inFile;
    /*string fileName; // Uncomment for production
    do{
        cout << "Enter file name: ";
        cin >> fileName;*/

        inFile.open(fileName.c_str());
            if (!inFile)
                cout << "FILE DOESN'T EXIST\n";
/*
    }while(!inFile);*/ //Uncomment for production

	BinarySearchTree keyBST(true); //true means sort by unique key
	BinarySearchTree secBST(false); //false means sort by non unique key
    HashTable hTable(hashSize(fileSize(fileName)));

    createADTs(inFile, keyBST, secBST, hTable);

    inFile.close();

    bool checker = true;  // this is for the while loop
    char choice;
    Stack<Food> * outputStack;
    Stack<Food *> deleteStack;

    while(checker)
    {
        menu();
        cout << "\nChoice: ";
        cin.get(choice);
        cin.ignore(256,'\n');

		Food * newNode;

        switch (choice)
        {
            case 'A': //Add new data
            case 'a':
		newNode = addNew();
		keyBST.insert(newNode);
		secBST.insert(newNode);
		hTable.addEntry(newNode);
                break;
            case 'D': //Delete data
            case 'd':

                if (hTable.search(enterInt(), newNode))
		{
                    deleteStack.push(newNode);
                    hTable.remove(newNode);
                    keyBST.remove(newNode->getKey());
                    secBST.remove(newNode->getName());
                }
                else
                    cout << "Key not found\n";

                break;
            case 'S': //Search Manager
            case 's':
                searchManager(&keyBST, &secBST);

                /*
                char answer;
                cout << "Would you like to seach by unique key (Y/N): ";
                cin >> answer;
                if (answer == 'Y' || answer == 'y')
                {
                    if (hTable.search(enterInt(), newNode))
                        cout << newNode->getName() << endl;
                    else
                        cout << "Key not found\n";
                }
                else if (answer == 'N' || answer == 'n')
                {
                    if(newNode = secBST.search(enterStr())) //Doesn't seem to work?
                        cout << newNode->getKey() << " " << newNode->getName() << endl;
                    else
                        cout << "Key not found\n";
                }*/
                break;
            case 'L': //List Manager
            case 'l':
                listManager(&keyBST, &secBST, &hTable);
                break;

            case 'U': //Undo delete
            case 'u':
                if(!deleteStack.isEmpty()){
                    deleteStack.pop(newNode);
                    keyBST.insert(newNode);
                    secBST.insert(newNode);
                    hTable.addEntry(newNode);
                }
                else
                    cout << "No Previous Deletions\n";

                break;
	    case 'O': //Open a file
	    case 'o': //Currently only works for HashTable
		do{
        	    cout << "Enter file name: ";
       		    cin >> fileName;
        	    inFile.open(fileName.c_str());
            		if (!inFile)
               	    cout << "FILE DOESN'T EXIST\n";
    		}while(!inFile);
		emptyADTs(fileName, keyBST, secBST, hTable);
		createADTs(inFile, keyBST, secBST, hTable);
		inFile.close();
		cin.ignore();
            case 'W': //Write to a file
            case 'w':
                while(!deleteStack.isEmpty())
                    deleteStack.pop(newNode);
              /*  ofstream outFile;
                outFile.open("output.txt");
                outputStack = keyBST.inOrderStack;
                printToFile(outFile, outputStack);*/
                break;
            case 'T': //Statistics
            case 't':
				cout << "\nSize of Array: " << hTable.getSize()
				<< "\nCount: " << hTable.getCount()
				<< "\nFilled Slots: " << hTable.getFilledSlots()
				<< "\nCollisions: " << hTable.getCollisions()
				<< "\nNumber of Linked Lists: " << hTable.getNumberLL()
				<< "\nLongest Linked List: " << hTable.getLongestLL()
				<< "\nAverage Linked List: " << hTable.getAverageLL()
				<< "\nLoad Factor: " << (static_cast<double>(hTable.getFilledSlots())*100 / hTable.getSize()) << "%"
				<< endl;
                break;
            case 'Q': //Quit
            case 'q':
                checker = false;
                break;
	    default:
		cout << "Unrecognized command\n";
        }
    }
    return 0;
}

int fileSize(string fileName)
{
    ifstream inFile(fileName.c_str());
    int count = 0;
    string temp;
    while(getline(inFile, temp))
        count++;
    return count;
}

int hashSize(int fileSize)
{
    int number = 0;
    int hashSize = fileSize * 2;
    int sqrtHashSize;
    bool isPrime;

    do
    {
	sqrtHashSize = sqrt(hashSize);
        isPrime = true;
        for (int i = 2; i < sqrtHashSize; i++)
        {
            if (hashSize % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        hashSize++;
    } while (isPrime == false);
    number = hashSize - 1;

    return number;
}

Food* fileInput(ifstream &inFile)//For an example of this function in action, run while(fileInput(inFile)); OR while(temp = fileInput(inFile));
{
    string buffer;
    getline(inFile, buffer);

    if (buffer.length()) //Ensures we don't go out of range
    {
        int index;
        int start;
        static const char carrot = '^'; //Not even really necessary

		double water;
		int calories;
		double protein;
		double fat;
		double fiber;
		double sugar;

        int key = stoi(buffer.substr(1, 6));//Key

        buffer = buffer.substr(9, buffer.length());
        index = buffer.find(carrot);
        string name = buffer.substr(0, index-1);//Name

        start = index + 2;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Water
        start = 0;
		if ((buffer.substr(start, index)).length())
			water = stod(buffer.substr(start, index));
		else
			water = 0;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Calories
        start = 0;
		if ((buffer.substr(start, index)).length())
			calories = stoi(buffer.substr(start, index));
		else
			calories = 0;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Protein
        start = 0;
		if ((buffer.substr(start, index)).length())
			protein = stod(buffer.substr(start, index));
		else
			protein = 0;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Fat
        start = 0;
		if ((buffer.substr(start, index)).length())
			fat = stod(buffer.substr(start, index));
		else
			fat = 0;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Ash

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Carbohydrates

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
		if ((buffer.substr(start, index)).length())
			fiber = stod(buffer.substr(start, index));
		else
			fiber = 0;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
		if ((buffer.substr(start, index)).length())
			sugar = stod(buffer.substr(start, index));
		else
			sugar = 0;

        Food * newFood = new Food(key, name, water, calories, protein, fat, fiber, sugar);
        return newFood;
    }
    else
        return NULL;
}

void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable)
{
    Food * temp;
    while(temp = fileInput(inFile))
    {
        keyBST.insert(temp);
        secBST.insert(temp);
        hTable.addEntry(temp);
    }
    return;
}

void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable) //Needs the BSTs
{
    hTable.rehash(hashSize(fileSize(fileName)));
}

void printToFile(ofstream &outFile, Stack<Food*>* printStack)
{
    Food * temp;
    outFile << "Sorted Data using the unique key" << endl << endl;
    while (printStack->getCount() != 0)
    {
        printStack->pop(temp);
        outFile <<"~" << temp->getKey() << "~^~" << temp->getName() << "~^" << temp->getW() << "^" << temp->getC() << "^" << temp->getP();
        outFile << "^" << temp->getF() << "^" << temp->getFi() << "^" << temp->getS() << "^"<< endl;
    }
}

/*void reHash(HashTable &hTable) //Unnecessary
{
    int hashActualSize = hTable.getCount();
    int newSize = hashSize(hashActualSize);
    HashTable newHashTable(newSize);
}*/


void menu()
{
    cout << "\nList of Menu options\n\n";
    cout << "A - Add New Data\n"
    << "D - Delete Data by key number\n"
    << "S - Search Manager\n"
    << "L - List Manager\n"
    << "U - Undo Delete\n"
    << "O - Open a Data File\n"
    << "W - Write Data to File\n"
    << "T - Statsitics\n"
    << "Q - Quit Program\n";
}

Food * addNew()				//needs input validation
{
	int uKey;
	string fName;
	double _water;
	int _cal;
	double _protein;
	double _fat;
	double _fiber;
	double _sugar;

	cout << "\nEnter a key: ";
	cin >> uKey;
	cout << "\nEnter a food name: ";
	cin >> fName;
	cout << "\nEnter water content: ";
	cin >> _water;
	cout << "\nEnter calorie content: ";
	cin >> _cal;
	cout << "\nEnter protein content: ";
	cin >> _protein;
	cout << "\nEnter fat content: ";
	cin >> _fat;
	cout << "\nEnter fiber content: ";
	cin >> _fiber;
	cout << "\nEnter sugar content: ";
	cin >> _sugar;
	cin.ignore(256, '\n');

	Food * newFood = new Food(uKey, fName, _water, _cal, _protein, _fat, _fiber, _sugar);
	return newFood;
}

int enterInt()
{
	int sKey;
	bool success;
	do {
		cout << "Enter a value: ";
		//success = cin >> sKey;
		cin.clear();
		cin.ignore(256, '\n');
	} while (!success);
	return sKey;
}

string enterStr()
{
    string str;
    cout << "Enter a string: ";
    cin >> str;
    cin.ignore(256, '\n');
    return str;
}
