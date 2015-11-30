// Search Manager Header File for Team Project
// Ahmed Shalan

#ifndef _SEARCH_MANAGER
#define _SEARCH_MANAGER


#include <iostream>
#include "BinarySearchTree.h"
#include "Food.h"
#include <string>
using namespace std;

void searchManager(BinarySearchTree * primaryTree, BinarySearchTree * secondaryTree);
void PrimaryKeySearchManager(BinarySearchTree * primaryTree);
void SecondaryKeySearchManager(BinarySearchTree * secondaryTree);
void displayFoodData(Food * searchedFoodItem);

#endif
