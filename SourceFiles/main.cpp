#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/BinarySearchTree.h"
#include "../HeaderFiles/HashTable.h"

using namespace std;

int fileSize(string fileName); //To count the lines for the HashTable
int hashSize(int fileSize);
Food* fileInput(ifstream &inFile); //To get the data from the file
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable); //To put the data in the ADTs
void printToFile(ofstream &outFile, Stack<Food> * printStack);
Food * addNew();
void reHash(HashTable &hTable);
int enterInt();

void menu(); //Display menu

int main()
{
    cout << "USDA Nutritional Facts Management System\n\nBY:\n" << "Jasmin Adzic\n" << "Brandon Archbold\n" << "Austin Bohannon\n" << "Ahmed Shalan\n" << "Mikhail Smelik\n";
    
    string fileName = "../ResourceFile/USDA_data_big.txt";
    
    
    BinarySearchTree keyBST, secBST; //Cannot declare because remove and search are still virtual, also, we'll need separate BST classes
    HashTable hTable(hashSize(fileSize(fileName)));
    
    ifstream inFile;
	inFile.open(fileName.c_str());
		if (!inFile)
			cout << "FILE DOESN'T EXIST\n";
    createADTs(inFile, keyBST, secBST, hTable); //Commented out until BSTs work
    
    bool checker = true;  // this is for the while loop
    char choice;
    Stack<Food> * outputStack;
    
    while(checker)
    {
        cout << endl;
        menu();
        cout << "\nChoice: ";
        cin >> choice; //Change this to a better implementation
        
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
				keyBST.remove()
				enterInt();
                break;
            case 'S': //Search
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
            case 'H': //Search with hash
            case 'h':
				if (hTable.search(enterInt(), newNode))
					cout << newNode->getName() << endl;
				else
					cout << "Key not found\n";
                break;
            case 'P':
			case 'p': 
				keyBST.printIndentedTree();
                break;
            case 'W': //Write to a file
            case 'w':
              /*  ofstream outFile;
                outFile.open("output.txt");
                outputStack = keyBST.inOrderStack;
                printToFile(outFile, outputStack);*/
                break;
            case 'T': //Statistics
            case 't':
				cout << "Count: " << hTable.getCount() << "\nSize: " << hTable.getSize() << "\nFilled Slots: " << hTable.getFilledSlots() << "\nCollisions: " << hTable.getCollisions() << "\nLoad Factor: " << (static_cast<double>(hTable.getFilledSlots()) / hTable.getSize()) << endl;
                break;
            case 'Q': //Quit
            case 'q':
                checker = false;
                break;
                
                
        }
    }
    
    menu();
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
    bool isPrime;
    
    do
    {
        isPrime = true;
        for (int i = 2; i < hashSize; i++)
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
        
        int key = stoi(buffer.substr(1, 6));//This will always be the same distance, no need to look for it
        //cout << "KEY: " << key << endl; //This should be deleted before production
        
        buffer = buffer.substr(9, buffer.length()); // Similar here, although only the starting place
        index = buffer.find(carrot);
        string name = buffer.substr(0, index-1);
        //cout << "NAME: " << name << endl;
        
        start = index + 2;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
		if ((buffer.substr(start, index)).length())
			water = stod(buffer.substr(start, index));
		else
			water = 0;
        //cout << "WATER: " << showpoint << fixed << setprecision(2) << water << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
		if ((buffer.substr(start, index)).length())
			calories = stoi(buffer.substr(start, index));
		else
			calories = 0;
        //cout << "CALORIES: " << calories << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
		if ((buffer.substr(start, index)).length())
			protein = stod(buffer.substr(start, index));
		else
			protein = 0;
        //cout << "PROTEIN: " << showpoint << fixed << setprecision(2) << protein << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
		if ((buffer.substr(start, index)).length())
			fat = stod(buffer.substr(start, index));
		else
			fat = 0;
        //cout << "FAT: " << showpoint << fixed << setprecision(2) << fat << endl;
        
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
        //cout << "FIBER: " << showpoint << fixed << setprecision(2) << fiber << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
		if ((buffer.substr(start, index)).length())
			sugar = stod(buffer.substr(start, index));
		else
			sugar = 0;
        //cout << "SUGAR: " << showpoint << fixed << setprecision(2) << sugar << endl;
        
        //cout << endl;
        
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
        //doesnt work because the bst.insert has & and not a *. if that would be switched it should work
        keyBST.insert(temp); //Currently throws an error because BST does not want pointers
        secBST.insert(temp); //Currently throws an error because BST does not want pointers
        hTable.addEntry(temp);
    }
    return;
}

void printToFile(ofstream &outFile, Stack<Food>* printStack)
{
    Food * temp;
    outFile << "Sorted Data using the unique key" << endl << endl;
    while (printStack->getCount() != 0)
    {
        printStack->pop(temp);
        outFile << temp->getKey() << " " << temp->getName() << " " << temp->getW() << " " << temp->getC() << " " << temp->getP();
        outFile << " " << temp->getF() << " " << temp->getFi() << " " << temp->getS() << endl;
    }
}

void reHash(HashTable &hTable)
{
    int hashActualSize = hTable.getCount();
    int newSize = hashSize(hashActualSize);
    HashTable newHashTable(newSize);
}


void menu()
{
    cout << "\n\nList of Menu options\n\n";
    cout << "A - Add New Data\n"
    << "D - Delete Data by key number\n"
    << "S - Search by unique key or item name through the BST\n"
    << "H - Search with hash Table\n"
    << "P - Special Print\n"
    << "W - Write Data to File\n"//not sure what this is for but it is in the requirements list
    << "T - Statsitics\n" // not sure what this is for
    << "Q - Quit Program\n";
}

Food * addNew()				//needs inpu validation
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

	Food * newFood = new Food(uKey, fName, _water, _cal, _protein, _fat, _fiber, _sugar);
	return newFood;
}

//int enterInt()
//{
//	int sKey;
//	bool success;
//	do {
//		cout << "Enter a value: ";
//		success = cin >> sKey;
//		cin.clear();
//		cin.ignore(256, '\n');
//	} while (success);
//	return sKey;
//}
