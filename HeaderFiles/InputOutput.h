
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
#include "../HeaderFiles/SearchManager.h"
#include "../HeaderFiles/ListManager.h"
using namespace std;

int fileSize(string fileName);																					//To count the lines for the HashTable
int hashSize(int fileSize);																						//To calculate hash size from number of lines
Food* fileInput(ifstream &inFile);																				//To get the data from the file
void createADTs(ifstream &inFile, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable);		//To put the data in the ADTs
void emptyADTs(string fileName, BinarySearchTree &keyBST, BinarySearchTree &secBST, HashTable &hTable);			//To clear the data in the ADTs
void printToFile(ofstream &outFile, BinarySearchTree &BST);

#endif
