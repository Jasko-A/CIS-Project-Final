// Search Manager Header File for Team Project
// Ahmed Shalan

#ifndef _LIST_MANAGER
#define _LIST_MANAGER


#include <iostream>
#include <string>
using namespace std;

template<class ItemType>
class ListManager
{
private:
    
public:
    ListManager(){;}
    void ListUnsortedData(); //Not complete
    void ListByPrimaryKey(BinarySearchTree<ItemType> * primaryTree);
    void ListBySecondaryKey(BinarySearchTree<ItemType> * secondaryTree);
    void undoDelete();       //Not complete
};

template<class ItemType>
void display(ItemType & item)
{
    item.displayFoodData();
}

///////////////////////// public function definitions ///////////////////////////
template<class ItemType>
void ListManager<ItemType>::ListByPrimaryKey(BinarySearchTree<ItemType> * primaryTree)
{
    cout << "Listing by the USDA identification number: \n";
    
    primaryTree->inOrder(display);
}

template<class ItemType>
void ListManager<ItemType>::ListBySecondaryKey(BinarySearchTree<ItemType> * secondaryTree)
{
    cout << "Listing alphabeticaly by food name: \n";
    
    secondaryTree->inOrder(display);
}

#endif