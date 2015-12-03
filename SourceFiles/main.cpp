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

int fileSize(string fileName);																					//To count the lines for the HashTable
int hashSize(int fileSize);																						//To calculate hash size from number of lines
Food* fileInput(ifstream &inFile);																				//To get the data from the file
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable);		//To put the data in the ADTs
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable);			//To clear the data in the ADTs
void printToFile(ofstream &outFile, BinarySearchTree &BST);													//To print everything out
Food * addNew();
void toArray(BinarySearchTree &BST, Food *arr);
int enterInt();																									//Input validation for an int
double enterDouble();
string enterStr();																								//Input validation for a string
void menu();																									//Display menu

int main()
{
    cout << "USDA Nutritional Facts Management System\n\nBY:\n" << "Jasmin Adzic\n" << "Brandon Archbold\n" << "Austin Bohannon\n" << "Ahmed Shalan\n" << "Mikhail Smelik\n";

    string fileName = "../ResourceFile/USDA_data_small.txt"; //Delete for production

	ofstream outFile;
    ifstream inFile;
    /*string fileName; // Uncomment for production
     do{
     cout << "Enter file name: ";
     cin >> fileName;*/

    inFile.open(fileName.c_str());
    if (!inFile)
        cout << "ERROR: File \"" << fileName << "\" Not Found\n";
    /*
     }while(!inFile);*/ //Uncomment for production

    BinarySearchTree keyBST(true); //true means sort by unique key
    BinarySearchTree secBST(false); //false means sort by non unique key
    HashTable hTable(hashSize(fileSize(fileName)));

    createADTs(inFile, keyBST, secBST, hTable);

    inFile.close();

    bool checker = true;  // this is for the while loop
    char choice;
    Stack<Food *> deleteStack;

    while(checker)
    {
        menu();
        cout << "\nEnter a Menu Option: ";
        cin.get(choice);
        cin.ignore(256,'\n');

        Food * newNode;

        switch (choice)
        {
            case 'A': //Add new data
            case 'a':
                newNode = addNew();
                if(hTable.addEntry(newNode))
                {
                    keyBST.insert(newNode);
                    secBST.insert(newNode);
                }
                break;
            case 'D': //Delete data
            case 'd':
                cout << "\nNDB_No. (5 digit) ";
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
                cout << "Enter file name: ";
                cin >> fileName;
                inFile.open(fileName.c_str());
                if (inFile)
                {
                    emptyADTs(fileName, keyBST, secBST, hTable);
                    createADTs(inFile, keyBST, secBST, hTable);
                }
                else
                    cout << "ERROR: File \"" << fileName << "\" Not Found\n";
                cin.ignore();
                inFile.close();
                break;
            case 'W': //Write to a file
            case 'w':
                //Empty stack
                while(!deleteStack.isEmpty())
                    deleteStack.pop(newNode);
                //Write to file
                cout << "Enter file name: ";
                cin >> fileName;
                cin.ignore();
                outFile.open(fileName.c_str());
				printToFile(outFile, keyBST);
				outFile.close();
                break;
            case 'T': //Statistics
            case 't':
                cout << "\nHASH TABLE STATISTICS:"
                << "\nSize of Array:          " << hTable.getSize()
                << "\nCount:                  " << hTable.getCount()
                << "\nFilled Slots:           " << hTable.getFilledSlots()
                << "\nCollisions:             " << hTable.getCollisions()
                << "\nNumber of Linked Lists: " << hTable.getNumberLL()
                << "\nLongest Linked List:    " << hTable.getLongestLL()
                << "\nAverage Linked List:    " << hTable.getAverageLL()
                << "\nLoad Factor:            " << setprecision(4) << (static_cast<double>(hTable.getFilledSlots())*100 / hTable.getSize()) << "%"
                << endl;
                break;
            case 'Q': //Quit
            case 'q':
                //End the loop
                checker = false;
                //Print the output
                outFile.open("output.txt");
				printToFile(outFile, keyBST);
				outFile.close();
                break;
            default:
                cout << "ERROR: Unrecognized Command\n";
        }
    }
    return 0;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
int fileSize(string fileName)
{
    ifstream inFile(fileName.c_str());
    int count = 0;
    string temp;
    while(getline(inFile, temp))
        count++;
    return count;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
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

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
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
            water = -1;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Calories
        start = 0;
        if ((buffer.substr(start, index)).length())
            calories = stoi(buffer.substr(start, index));
        else
            calories = -1;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Protein
        start = 0;
        if ((buffer.substr(start, index)).length())
            protein = stod(buffer.substr(start, index));
        else
            protein = -1;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot);//Fat
        start = 0;
        if ((buffer.substr(start, index)).length())
            fat = stod(buffer.substr(start, index));
        else
            fat = -1;

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
            fiber = -1;

        start = index + 1;
        buffer = buffer.substr(start, buffer.length());
        index = buffer.find(carrot); //Fiber
        start = 0;
        if ((buffer.substr(start, index)).length())
            sugar = stod(buffer.substr(start, index));
        else
            sugar = -1;

        Food * newFood = new Food(key, name, water, calories, protein, fat, fiber, sugar);
        return newFood;
    }
    else
        return NULL;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
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

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable) //Needs the BSTs
{
    hTable.rehash(hashSize(fileSize(fileName)));
    keyBST.clear();
    secBST.clear();
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void printToFile(ofstream &outFile, BinarySearchTree &BST)
{
	const int size = BST.size();
    Food *arr = new Food[size];
    toArray(BST, arr);
    for (int i = 0; i < BST.size(); i++)
    {
        outFile <<"~" << arr[i].getKey()
        << "~^~" << arr[i].getName()
        << "~^";
        if(arr[i].getW() >= 0)
            outFile << arr[i].getW();
        outFile << "^";
        if(arr[i].getC() >= 0)
            outFile << arr[i].getC();
        outFile << "^";
        if(arr[i].getP() >= 0)
            outFile << arr[i].getP();
        outFile << "^";
        if(arr[i].getF() >= 0)
            outFile << arr[i].getF();
        outFile << "^";
        if(arr[i].getFi() >= 0)
            outFile << arr[i].getFi();
        outFile << "^";
        if(arr[i].getS() >= 0)
            outFile << arr[i].getS();
        outFile << "^\n";
    }
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void toArray(BinarySearchTree &BST, Food *arr)
{
    BST.inOrderArr(arr);
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
void menu()
{
    cout << "\n            Main Menu             \n"
    << "----------------------------------\n"
    << "A - Add New Data\n"
    << "D - Delete Data by NDB_No.\n"
    << "S - Search Manager\n"
    << "L - List Manager\n"
    << "U - Undo Delete\n"
    << "O - Open a Data File\n"
    << "W - Write Data to File\n"
    << "T - Statsitics\n"
    << "Q - Quit Program\n";
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
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

    cout << "\nNDB_No.    (5 digit) ";
    uKey = enterInt();
    cout << "Shrt_Desc  (60 char) Enter string: ";
    getline(cin, fName);
    cout << "Water       (g/100g) ";
    _water = enterDouble();
    cout << "Calories (kcal/100g) ";
    _cal = enterInt();
    cout << "Protein     (g/100g) ";
    _protein = enterDouble();
    cout << "Fat         (g/100g) ";
    _fat = enterDouble();
    cout << "Fiber       (g/100g) ";
    _fiber = enterDouble();
    cout << "Sugar       (g/100g) ";
    _sugar = enterDouble();

    for(int i = 0; i < fName.size(); i++)
        fName[i] = toupper(fName[i]);

    Food * newFood = new Food(uKey, fName, _water, _cal, _protein, _fat, _fiber, _sugar);
    return newFood;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
int enterInt()
{
    int in;
    bool success;
    do {
        cout << "Enter a value: ";
        success = cin >> in;
        cin.clear();
        cin.ignore(256, '\n');
    } while (!success);
    return in;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
double enterDouble()
{
    double in;
    bool success;
    do {
        cout << "Enter a value: ";
        success = cin >> in;
        cin.clear();
        cin.ignore(256, '\n');
    } while (!success);
    return in;
}

/** =================================== */
/* <function purpose>
<explanation of all input parameters>
<explanation of all output actions and return value > */
string enterStr()
{
    string in;
    cout << "Enter a string: ";
    getline(cin, in);
    cin.ignore(256, '\n');
    return in;
}
