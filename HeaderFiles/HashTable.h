/*****
HashTable Class
Written by: Austin Bohannon

Made to work with pointers to objects so that no data has to be copied,
it's just organized.
*****/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Food.h"
#include "LinkedList.h"

class HashTable
{
    LinkedList * arr;
    int arraySize, filledSlots, collisions, count;
    int _hash(int id);
public:
    //Constructor - Destructor
    HashTable(int setSize);
    ~HashTable();
    //Mutators and accessors
    void addEntry(Food * newEntry);
    bool remove(Food * deletePtr);
    bool search(int id, Food *& returnedPtr);
    //Const accessors
    int getSize() const {return arraySize;}
    int getFilledSlots() const {return filledSlots;}
    int getCollisions() const {return collisions;}
    int getCount() const {return count;}
};

#endif
