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

void reHash(HashTable &hTable);

void menu(); //Display menu

int main()
{
    cout << "USDA Nutritional Facts Management System\n\nBY:\n" << "Jasmin Adzic\n" << "Brandon Archbold\n" << "Austin Bohannon\n" << "Ahmed Shalan\n" << "Mikhail Smelik\n";
    
    string fileName = "../ResourceFile/USDA_data_small.txt";
    
    
    //BinarySearchTree keyBST, secBST; //Cannot declare because remove and search are still virtual, also, we'll need separate BST classes
    HashTable hTable(hashSize(fileSize(fileName)));
    
    ifstream inFile;
    inFile.open(fileName.c_str());
    //createADTs(inFile, keyBST, secBST, hTable); //Commented out until BSTs work
    
    bool checker = true;  // this is for the while loop
    char choice;
    Stack<Food> * outputStack;
    
    while(checker)
    {
        cout << endl;
        menu();
        cout << "\nChoice: ";
        cin >> choice; //Change this to a better implementation
        
        
        switch (choice)
        {
            case 'A': //Add new data
            case 'a':
                break;
            case 'D': //Delete data
            case 'd':
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
                break;
            case 'P':
            case 'p':
                break;
            case 'W': //Write to a file
            case 'w':
                ofstream outFile;
                outFile.open("output.txt");
                outputStack = keyBST->inOrderStack;
                printToFile(outFile, outputStack);
                break;
            case 'T': //Statistics
            case 't':
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
        
        int key = stoi(buffer.substr(1, 6));//This will always be the same distance, no need to look for it
        cout << "KEY: " << key << endl; //This should be deleted before production
        
        buffer = buffer.substr(7, buffer.length()); // Similar here, although only the starting place
        index = buffer.find(carrot);
        string name = buffer.substr(0, index);
        cout << "NAME: " << name << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
        double water = stod(buffer.substr(start, index));
        cout << "WATER: " << showpoint << fixed << setprecision(2) << water << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
        int calories = stoi(buffer.substr(start, index));
        cout << "CALORIES: " << calories << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
        double protein = stod(buffer.substr(start, index));
        cout << "PROTEIN: " << showpoint << fixed << setprecision(2) << protein << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);
        start = 0;
        double fat = stod(buffer.substr(start, index));
        cout << "FAT: " << showpoint << fixed << setprecision(2) << fat << endl;
        
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
        double fiber = stod(buffer.substr(start, index));
        cout << "FIBER: " << showpoint << fixed << setprecision(2) << fiber << endl;
        
        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
        double sugar = stod(buffer.substr(start, index));
        cout << "SUGAR: " << showpoint << fixed << setprecision(2) << sugar << endl;
        
        cout << endl;
        
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
        //keyBST.insert(temp); //Currently throws an error because BST does not want pointers
        //secBST.insert(temp); //Currently throws an error because BST does not want pointers
        hTable.addEntry(temp);
    }
    return;
}

void printToFile(ofstream &outFile, Stack * printStack)
{
    Food * temp;
    outFile >> "Sorted Data using the unique key" >> endl >> endl;
    while (printStack->getCount() != 0)
    {
        printStack->pop(temp);
        outFile >> temp->getKey() >> " " >> temp->getName() >> " " >> temp->getW() >> " " >> temp->getC() >> " " >> temp->getP();
        outFile >> " " >> temp->getF() >> " " >> temp->getFi() >> " " >> temp->getS() >> endl;
    }
}

void reHash(HashTable &hTable)
{
    int hashActualSize = hTable->getCount();
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
