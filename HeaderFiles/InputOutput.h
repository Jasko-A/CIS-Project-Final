// Input Output Header File for file input and output
// Written by Mikhail Smelik


/*
The input output header file includes function declarations for when the
functions are defined in the input output source file. No class declarations
are made.
*/

#ifndef _INPUT_OUTPUT
#define _INPUT_OUTPUT

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "../HeaderFiles/Food.h"
#include "../HeaderFiles/BinarySearchTree.h"
#include "../HeaderFiles/HashTable.h"
using namespace std;

int fileSize(string fileName);																					//To count the lines for the HashTable
int hashSize(int fileSize);																						//To calculate hash size from number of lines
Food* fileInput(ifstream &inFile);																				//To get the data from the file
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable);		//To put the data in the ADTs
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable *hTable);			//To clear the data in the ADTs
void printToFile(ofstream &outFile, BinarySearchTree &BST);               //To print to a file
void reHash(HashTable *hTable, BinarySearchTree &BST);                    //To rehash the hash table with a new size

#endif
