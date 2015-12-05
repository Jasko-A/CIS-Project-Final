/*****
HashTable Class
Written by: Austin Bohannon

Made to work with pointers to Food objects so that no data has to be copied,
it's just organized. The HashTable is to be used for O(1) lookup of different
foods by Database Nutrient Number. It is also able to access all of its Food
objects to be able to print out the food in an unordered manner. The HashTable
uses linked list resolution, and as such is merely an array of LinkedLists that
manages many of its own aspects.
*****/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Food.h"
#include "LinkedList.h"

class HashTable
{
    LinkedList * arr;
    int arraySize, filledSlots, collisions, count;
    int _hash(int id) const;
public:
    //Constructor - Destructor
    HashTable(int setSize);
    ~HashTable();
    //Mutators and accessors
    bool addEntry(Food * newEntry);
    bool remove(Food * deletePtr);
    bool search(int id, Food *& returnedPtr);
    void rehash(int setSize);
    int getNumberLL();
    int getLongestLL();
    double getAverageLL();
    void visitAll(void visit(Food *));
    //Const accessors
    int getSize() const {return arraySize;}
    int getFilledSlots() const {return filledSlots;}
    int getCollisions() const {return collisions;}
    int getCount() const {return count;}
};

#endif
