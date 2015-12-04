// List Manager Header File for Team Project
// Ahmed Shalan

#ifndef _LIST_MANAGER
#define _LIST_MANAGER

#include <iostream>
#include "BinarySearchTree.h"
#include "SearchManager.h"
#include "HashTable.h"
#include "Food.h"
#include "Stack.h"
#include <string>
using namespace std;

void listManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree, HashTable * hashTable);
void unsortedList(HashTable * hashTable);
void treeList(BinarySearchTree * tree);
void displayItem(Food * foodItem);

#endif
