#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/BinarySearchTree.h"
#include "../HeaderFiles/HashTable.h"
#include "../HeaderFiles/InputOutput.h"

using namespace std;

int InputOutput::fileSize(string fileName)
{
    ifstream inFile(fileName.c_str());
    int count = 0;
    string temp;
    while(getline(inFile, temp))
        count++;
    return count;
}

int InputOutput::hashSize(int fileSize)
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

Food InputOutput::*fileInput(ifstream &inFile)//For an example of this function in action, run while(fileInput(inFile)); OR while(temp = fileInput(inFile));
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

void InputOutput::createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable)
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

void InputOutput::printToFile(ofstream &outFile, Stack * printStack)
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

void InputOutput::reHash(HashTable &hTable)
{
    int hashActualSize = hTable->getCount();
    int newSize = hashSize(hashActualSize);
    HashTable newHashTable(newSize);
}
