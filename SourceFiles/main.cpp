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
#include "../HeaderFiles/InputOutput.h"

using namespace std;

//int fileSize(string fileName);																					//To count the lines for the HashTable
//int hashSize(int fileSize);																						//To calculate hash size from number of lines
//Food* fileInput(ifstream &inFile);																				//To get the data from the file
//void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable);		//To put the data in the ADTs
//void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable);			//To clear the data in the ADTs
//void printToFile(ofstream &outFile, BinarySearchTree &BST);													//To print everything out
Food * addNew();
int enterInt();																									//Input validation for an int
double enterDouble();
string enterStr();																								//Input validation for a string
void menu();																									//Display menu

/**===================================*/
/*main creates all ADTs and manages the main menu through a while loop and switch.
main calls many other functions to handle various things.

main neither takes nor returns a value.
*/
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
    HashTable *hTable = new HashTable(hashSize(fileSize(fileName)));

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
                if(hTable->addEntry(newNode))
                {
                    keyBST.insert(newNode);
                    secBST.insert(newNode);
                }
                if(hTable->getFilledSlots() * 100 / hTable->getSize() >= 75)
                    reHash(hTable, keyBST);
                break;
            case 'D': //Delete data
            case 'd':
                cout << "\nNDB_No. (5 digit) ";
                if (hTable->search(enterInt(), newNode))
                {
                    deleteStack.push(newNode);
                    hTable->remove(newNode);
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
                listManager(&keyBST, &secBST, hTable);
                break;

            case 'U': //Undo delete
            case 'u':
                if(!deleteStack.isEmpty()){
                    deleteStack.pop(newNode);
                    keyBST.insert(newNode);
                    secBST.insert(newNode);
                    hTable->addEntry(newNode);
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
                << "\nSize of Array:          " << hTable->getSize()
                << "\nCount:                  " << hTable->getCount()
                << "\nFilled Slots:           " << hTable->getFilledSlots()
                << "\nCollisions:             " << hTable->getCollisions()
                << "\nNumber of Linked Lists: " << hTable->getNumberLL()
                << "\nLongest Linked List:    " << hTable->getLongestLL()
                << "\nAverage Linked List:    " << hTable->getAverageLL()
                << "\nLoad Factor:            " << setprecision(4) << (static_cast<double>(hTable->getFilledSlots())*100 / hTable->getSize()) << "%"
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
/* menu outputs the options to stdout

No input parameters
No output parameters */
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
/* addNew creates a new Food item from stdin and returns its pointer

No input parameters
Returns a Food pointer */
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

    for(unsigned int i = 0; i < fName.size(); i++)
        fName[i] = toupper(fName[i]);

    Food * newFood = new Food(uKey, fName, _water, _cal, _protein, _fat, _fiber, _sugar);
    return newFood;
}

/** =================================== */
/* enterInt gets an int from stdin and handles errors

No input parameters
Returns an int */
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
/* enterDouble gets a double from stdin and handles errors

No input parameters
Returns a double */
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
/* enterStr takes a string and clears the line

No input parameter
Returns a string */
string enterStr()
{
    string in;
    cout << "Enter a string: ";
    getline(cin, in);
    cin.ignore(256, '\n');
    return in;
}
