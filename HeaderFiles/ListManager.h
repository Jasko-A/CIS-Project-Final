// List Manager Header File for screen output
// Written by Ahmed Shalan


/*
The list manager header file includes function declerations for when the
the functions are defined in the list manager source file. No class
declarations are made.
*/


#ifndef _LIST_MANAGER
#define _LIST_MANAGER


#include <iostream>
#include "BinarySearchTree.h"          //For inOrder functions
#include "SearchManager.h"             //For the displayFoodData function
#include "HashTable.h"                 //For the visitAll function
#include "Food.h"
#include <string>
using namespace std;

void listManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree, HashTable * hashTable);
void unsortedList(HashTable * hashTable);
void treeList(BinarySearchTree * tree);
void indentedPrint(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree);

#endif
