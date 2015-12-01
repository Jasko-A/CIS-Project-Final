#ifndef InputOutput_h

#define InputOutput_h




#include <iostream>

#include <string>

#include <fstream>

#include <iomanip>

#include "../HeaderFiles/Food.h"

#include "../HeaderFiles/BinarySearchTree.h"

#include "../HeaderFiles/HashTable.h"

#include "HashTable.h"

#include "BinarySearchTree.h"




using namespace std;




class InputOutput

{

public:

    int fileSize(string fileName); //To count the lines for the HashTable

    int hashSize(int fileSize);

    Food* fileInput(ifstream &inFile); //To get the data from the file

    void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable); //To put the data in the ADTs

    void printToFile(ofstream &outFile, Stack<Food *> * printStack);




    void reHash(HashTable &hTable);




};




#endif /* InputOutput_h */
