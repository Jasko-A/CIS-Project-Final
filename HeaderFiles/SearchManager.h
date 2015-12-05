// Search Manager Header File for screen output
// Written by Ahmed Shalan


/*
The search manager header file includes function declerations for when the
the functions are defined in the search manager source file. No class
declarations are made.
*/

#ifndef _SEARCH_MANAGER
#define _SEARCH_MANAGER


#include <iostream>
#include "BinarySearchTree.h"            //For the BST search
#include "Food.h"
#include <string>
using namespace std;

void searchManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree);
void PrimaryKeySearchManager(BinarySearchTree * primaryTree);
void SecondaryKeySearchManager(BinarySearchTree * secondaryTree);
void displayFoodData(Food * searchedFoodItem);

#endif
